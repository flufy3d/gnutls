/* This example code is placed in the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <gnutls/gnutls.h>

#if GNUTLS_VERSION_NUMBER >= 0x030300
# define DEFAULT_PRIORITY "SYSTEM"
#else
# define DEFAULT_PRIORITY "NORMAL"
#endif

/* This is a sample TLS 1.0 echo server, for anonymous authentication only.
 */


#define SOCKET_ERR(err,s) if(err==-1) {perror(s);return(1);}
#define MAX_BUF 1024
#define PORT 5556               /* listen to 5556 port */

/* These are global */
static gnutls_dh_params_t dh_params;

static int generate_dh_params(void)
{
        unsigned int bits = gnutls_sec_param_to_pk_bits(GNUTLS_PK_DH,
                                                        GNUTLS_SEC_PARAM_LEGACY);
        /* Generate Diffie-Hellman parameters - for use with DHE
         * kx algorithms. These should be discarded and regenerated
         * once a day, once a week or once a month. Depending on the
         * security requirements.
         */
        gnutls_dh_params_init(&dh_params);
        gnutls_dh_params_generate2(dh_params, bits);

        return 0;
}

int main(void)
{
        int err, listen_sd;
        int sd, ret;
        struct sockaddr_in sa_serv;
        struct sockaddr_in sa_cli;
        socklen_t client_len;
        char topbuf[512];
        gnutls_session_t session;
        gnutls_anon_server_credentials_t anoncred;
        char buffer[MAX_BUF + 1];
        int optval = 1;

        if (gnutls_check_version("3.1.4") == NULL) {
                fprintf(stderr, "GnuTLS 3.1.4 is required for this example\n");
                exit(1);
        }

        gnutls_global_init();

        gnutls_anon_allocate_server_credentials(&anoncred);

        generate_dh_params();

        gnutls_anon_set_server_dh_params(anoncred, dh_params);

        /* Socket operations
         */
        listen_sd = socket(AF_INET, SOCK_STREAM, 0);
        SOCKET_ERR(listen_sd, "socket");

        memset(&sa_serv, '\0', sizeof(sa_serv));
        sa_serv.sin_family = AF_INET;
        sa_serv.sin_addr.s_addr = INADDR_ANY;
        sa_serv.sin_port = htons(PORT); /* Server Port number */

        setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (void *) &optval,
                   sizeof(int));

        err =
            bind(listen_sd, (struct sockaddr *) &sa_serv, sizeof(sa_serv));
        SOCKET_ERR(err, "bind");
        err = listen(listen_sd, 1024);
        SOCKET_ERR(err, "listen");

        printf("Server ready. Listening to port '%d'.\n\n", PORT);

        client_len = sizeof(sa_cli);
        for (;;) {
                gnutls_init(&session, GNUTLS_SERVER);
                gnutls_priority_set_direct(session,
                                           DEFAULT_PRIORITY
                                           ":+ANON-ECDH:+ANON-DH",
                                           NULL);
                gnutls_credentials_set(session, GNUTLS_CRD_ANON, anoncred);

                sd = accept(listen_sd, (struct sockaddr *) &sa_cli,
                            &client_len);

                printf("- connection from %s, port %d\n",
                       inet_ntop(AF_INET, &sa_cli.sin_addr, topbuf,
                                 sizeof(topbuf)), ntohs(sa_cli.sin_port));

                gnutls_transport_set_int(session, sd);

                do {
                        ret = gnutls_handshake(session);
                }
                while (ret < 0 && gnutls_error_is_fatal(ret) == 0);

                if (ret < 0) {
                        close(sd);
                        gnutls_deinit(session);
                        fprintf(stderr,
                                "*** Handshake has failed (%s)\n\n",
                                gnutls_strerror(ret));
                        continue;
                }
                printf("- Handshake was completed\n");

                /* see the Getting peer's information example */
                /* print_info(session); */

                for (;;) {
                        ret = gnutls_record_recv(session, buffer, MAX_BUF);

                        if (ret == 0) {
                                printf
                                    ("\n- Peer has closed the GnuTLS connection\n");
                                break;
                        } else if (ret < 0
                                   && gnutls_error_is_fatal(ret) == 0) {
                                fprintf(stderr, "*** Warning: %s\n",
                                        gnutls_strerror(ret));
                        } else if (ret < 0) {
                                fprintf(stderr, "\n*** Received corrupted "
                                        "data(%d). Closing the connection.\n\n",
                                        ret);
                                break;
                        } else if (ret > 0) {
                                /* echo data back to the client
                                 */
                                gnutls_record_send(session, buffer, ret);
                        }
                }
                printf("\n");
                /* do not wait for the peer to close the connection.
                 */
                gnutls_bye(session, GNUTLS_SHUT_WR);

                close(sd);
                gnutls_deinit(session);

        }
        close(listen_sd);

        gnutls_anon_free_server_credentials(anoncred);

        gnutls_global_deinit();

        return 0;

}
