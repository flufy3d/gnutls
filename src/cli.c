/*
 *      Copyright (C) 2000,2001 Nikos Mavroyanopoulos
 *
 * This file is part of GNUTLS.
 *
 * GNUTLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUTLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "../lib/gnutls.h"
#include <sys/time.h>

#ifndef SHUT_WR
# define SHUT_WR 1
#endif

#ifndef SHUT_RDWR
# define SHUT_RDWR 2
#endif

#define SA struct sockaddr
#define ERR(err,s) if (err==-1) {perror(s);return(1);}
#define MAX_BUF 4096

#define RESUME

#define MAX(X,Y) (X >= Y ? X : Y);
#define CAFILE "x509/ca.pem"
#define CRLFILE NULL
#define CLIKEYFILE "x509/clikey.pem"
#define CLICERTFILE "x509/clicert.pem"

#define PRINTX(x,y) if (y[0]!=0) printf(" -   %s %s\n", x, y)
#define PRINT_DN(X) PRINTX( "CN:", X->common_name); \
	PRINTX( "OU:", X->organizational_unit_name); \
	PRINTX( "O:", X->organization); \
	PRINTX( "L:", X->locality_name); \
	PRINTX( "S:", X->state_or_province_name); \
	PRINTX( "C:", X->country); \
	PRINTX( "E:", X->email); \
	PRINTX( "SAN:", gnutls_x509pki_client_get_subject_dns_name(x509_info))

static int print_info( GNUTLS_STATE state) {
const char *tmp;
ANON_CLIENT_AUTH_INFO dh_info;
X509PKI_CLIENT_AUTH_INFO x509_info;
const gnutls_DN* dn;

	tmp = gnutls_kx_get_name(gnutls_get_current_kx( state));
	printf("- Key Exchange: %s\n", tmp);
	if (gnutls_get_auth_info_type(state) == GNUTLS_ANON) {
		dh_info = gnutls_get_auth_info(state);
		if (dh_info != NULL)
			printf("- Anonymous DH using prime of %d bits\n",
			       gnutls_anon_client_get_dh_bits(dh_info));
	}

	if (gnutls_get_auth_info_type(state) == GNUTLS_X509PKI) {
		x509_info = gnutls_get_auth_info(state);
		if (x509_info != NULL) {
			switch( gnutls_x509pki_client_get_peer_certificate_status(x509_info)) {
			case GNUTLS_CERT_NOT_TRUSTED:
				printf("- Peer's X509 Certificate was NOT verified\n");
				break;
			case GNUTLS_CERT_EXPIRED:
				printf("- Peer's X509 Certificate was verified but is expired\n");
				break;
			case GNUTLS_CERT_TRUSTED:
				printf("- Peer's X509 Certificate was verified\n");
				break;
			case GNUTLS_CERT_NONE:
				printf("- Peer did not send any X509 Certificate.\n");
				break;
			case GNUTLS_CERT_INVALID:
			default:
				printf("- Peer's X509 Certificate was invalid\n");
				break;

			}

			printf(" - Certificate info:\n");
			printf(" - Certificate version: #%d\n", gnutls_x509pki_client_get_peer_certificate_version(x509_info));

			dn = gnutls_x509pki_client_get_peer_dn( x509_info);
			PRINT_DN( dn);

			dn = gnutls_x509pki_client_get_issuer_dn( x509_info);
			printf(" - Certificate Issuer's info:\n");
			PRINT_DN( dn);
		}
	}

	tmp = gnutls_version_get_name(gnutls_get_current_version(state));
	printf("- Version: %s\n", tmp);

	tmp = gnutls_compression_get_name(gnutls_get_current_compression_method( state));
	printf("- Compression: %s\n", tmp);

	tmp = gnutls_cipher_get_name(gnutls_get_current_cipher( state));
	printf("- Cipher: %s\n", tmp);

	tmp = gnutls_mac_get_name(gnutls_get_current_mac_algorithm( state));
	printf("- MAC: %s\n", tmp);

	return 0;
}

int cert_callback( gnutls_DN *client_cert, gnutls_DN *issuer_cert, int ncerts, gnutls_DN* req_ca_cert, int nreqs) {

	if (client_cert==NULL) {
		return 0; /* means the we will only be called again
		           * if the library cannot determine which
		           * certificate to send
		           */
	}

#if 0
	/* here we should prompt the user and ask him
	 * which certificate to choose. Too bored to 
	 * implement that. --nmav
	 */
	for (i=0;i<ncerts;i++){
		fprintf(stderr, "%s.", client_cert->common_name);
		fprintf(stderr, "%s\n", issuer_cert->common_name);
	}
	for (i=0;i<nreqs;i++){
		fprintf(stderr, "%s.", req_ca_cert->common_name);
	}
	fprintf(stderr, "\n");
	return 0;
#endif

	return -1; /* send no certificate to the peer */
}

int main(int argc, char** argv)
{
	int err, ret;
	int sd, ii;
	struct sockaddr_in sa;
	GNUTLS_STATE state;
	char buffer[MAX_BUF+1];
	char *session;
	char* session_id;
	int session_size;
	int session_id_size;
	char* tmp_session_id;
	int tmp_session_id_size;
	fd_set rset;
	int maxfd;
	struct timeval tv;
	int user_term = 0;
	SRP_CLIENT_CREDENTIALS cred;
	X509PKI_CLIENT_CREDENTIALS xcred;

	if (argc!=3) {
		fprintf(stderr, "Usage: cli [IP] [PORT]\n");
		exit(1);
	}
	
	if (gnutls_global_init() < 0) {
		fprintf(stderr, "global state initialization error\n");
		exit(1);
	}



	/* X509 stuff */
	if (gnutls_allocate_x509_client_sc( &xcred, 1) < 0) {  /* space for 1 certificate */
		fprintf(stderr, "memory error\n");
		exit(1);
	}
	gnutls_set_x509_client_trust( xcred, CAFILE, CRLFILE);
	gnutls_set_x509_client_key( xcred, CLICERTFILE, CLIKEYFILE);
	gnutls_set_x509_cert_callback( xcred, cert_callback);

	/* SRP stuff */
	if (gnutls_allocate_srp_client_sc( &cred)<0) {
		fprintf(stderr, "memory error\n");
		exit(1);
	}
	gnutls_set_srp_client_cred( cred, "test", "test");
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERR(sd, "socket");

	memset(&sa, '\0', sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(atoi(argv[2]));
	inet_pton( AF_INET, argv[1], &sa.sin_addr); 

	err = connect(sd, (SA *) & sa, sizeof(sa));
	ERR(err, "connect");

#ifdef RESUME
	gnutls_init(&state, GNUTLS_CLIENT);
	
	gnutls_set_protocol_priority( state, GNUTLS_TLS1, GNUTLS_SSL3, 0);
	gnutls_set_cipher_priority( state, GNUTLS_3DES_CBC, GNUTLS_RIJNDAEL_CBC, 0);
	gnutls_set_compression_priority( state, GNUTLS_ZLIB, GNUTLS_NULL_COMPRESSION, 0);
	gnutls_set_kx_priority( state, GNUTLS_KX_RSA, GNUTLS_KX_SRP, GNUTLS_KX_DH_ANON, 0);
	gnutls_set_mac_priority( state, GNUTLS_MAC_SHA, GNUTLS_MAC_MD5, 0);

	gnutls_set_cred( state, GNUTLS_ANON, NULL);
	gnutls_set_cred( state, GNUTLS_SRP, cred);
	gnutls_set_cred( state, GNUTLS_X509PKI, xcred);

/* This TLS extension may break old implementations.
 *
 *	gnutls_ext_set_dnsname( state, "localhost"); 
 */

	ret = gnutls_handshake(sd, state);

	if (ret < 0) {
		fprintf(stderr, "*** Handshake has failed\n");
		gnutls_perror(ret);
		gnutls_deinit(state);
		return 1;
	} else {
		printf("- Handshake was completed\n");
	}
	gnutls_get_current_session( state, NULL, &session_size);
	session = malloc(session_size);
	gnutls_get_current_session( state, session, &session_size);

	gnutls_get_current_session_id( state, NULL, &session_id_size);
	session_id = malloc(session_id_size);
	gnutls_get_current_session_id( state, session_id, &session_id_size);

/* print some information */
	print_info( state);

	printf("- Disconnecting\n");
	gnutls_bye(sd, state, GNUTLS_SHUT_RDWR);
	shutdown( sd, SHUT_WR);
	close(sd);
	gnutls_deinit( state);	
	

	printf("\n\n- Connecting again- trying to resume previous session\n");
	sd = socket(AF_INET, SOCK_STREAM, 0);
	ERR(sd, "socket");

	err = connect(sd, (SA *) & sa, sizeof(sa));
	ERR(err, "connect");

#endif

	/* Begin handshake again */
	gnutls_init(&state, GNUTLS_CLIENT);
	
	gnutls_set_protocol_priority( state, GNUTLS_TLS1, GNUTLS_SSL3, 0);
	gnutls_set_cipher_priority( state, GNUTLS_3DES_CBC, GNUTLS_TWOFISH_CBC, GNUTLS_RIJNDAEL_CBC, 0);
	gnutls_set_compression_priority( state, GNUTLS_NULL_COMPRESSION, 0);
	gnutls_set_kx_priority( state, GNUTLS_KX_RSA, GNUTLS_KX_SRP, GNUTLS_KX_DH_ANON, 0);

	gnutls_set_cred( state, GNUTLS_ANON, NULL);
	gnutls_set_cred( state, GNUTLS_SRP, cred);
	gnutls_set_cred( state, GNUTLS_X509PKI, xcred);

	gnutls_ext_set_dnsname( state, "hello.server.org");

	gnutls_set_mac_priority( state, GNUTLS_MAC_SHA, GNUTLS_MAC_MD5, 0);

#ifdef RESUME
	gnutls_set_current_session( state, session, session_size);
	free(session);
#endif

	ret = gnutls_handshake(sd, state);

	if (ret < 0) {
		fprintf(stderr, "*** Handshake failed\n");
		gnutls_perror(ret);
		gnutls_deinit(state);
		return 1;
	} else {
		printf("- Handshake was completed\n");
	}

	/* check if we actually resumed the previous session */
	gnutls_get_current_session_id( state, NULL, &tmp_session_id_size);
	tmp_session_id = malloc(tmp_session_id_size);
	gnutls_get_current_session_id( state, tmp_session_id, &tmp_session_id_size);

	if (memcmp( tmp_session_id, session_id, session_id_size)==0) {
		printf("- Previous session was resumed\n");
	} else {
		fprintf(stderr, "*** Previous session was NOT resumed\n");	
	}
	free(tmp_session_id);
	free(session_id);

/* print some information */
	print_info( state);
	
	printf("\n- Simple Client Mode:\n\n");

	FD_ZERO(&rset);
	for(;;) {
		FD_SET(fileno(stdin), &rset);
		FD_SET(sd, &rset);
		
		maxfd = MAX(fileno(stdin), sd);
		tv.tv_sec = 3;
		tv.tv_usec = 0;
		select(maxfd+1, &rset, NULL, NULL, &tv);

		if (FD_ISSET(sd, &rset)) {
			bzero(buffer, MAX_BUF+1);
			ret = gnutls_read(sd, state, buffer, MAX_BUF);

			/* remove new line */

			if (gnutls_is_fatal_error(ret) == 1 || ret==0) {
				if (ret == 0) {
					printf("- Peer has closed the GNUTLS connection\n");
					break;
				} else {
					fprintf(stderr, "*** Received corrupted data(%d) - server has terminated the connection abnormally\n",
						ret);
					break;
				}
			} else {
				if (ret==GNUTLS_E_WARNING_ALERT_RECEIVED || ret==GNUTLS_E_FATAL_ALERT_RECEIVED)
					printf("* Received alert [%d]\n", gnutls_get_last_alert(state));
				if (ret==GNUTLS_E_REHANDSHAKE)
					printf("* Rehandshake was performed\n");

				if (ret > 0) {
					printf("- Received[%d]: ", ret);
					for (ii=0;ii<ret;ii++) {
						fputc(buffer[ii], stdout);
					}
					fputs("\n", stdout);
				}
			}
			if (user_term!=0) break;
		}
		if (FD_ISSET(fileno(stdin), &rset)) {
	
			if( fgets(buffer, MAX_BUF, stdin) == NULL) {
				gnutls_bye(sd, state, GNUTLS_SHUT_WR);
				user_term = 1;
				continue;
			}
			gnutls_write( sd, state, buffer, strlen(buffer));
			printf("- Sent: %d bytes\n", strlen(buffer));

		}
	}
	if (user_term!=0) gnutls_bye(sd, state, GNUTLS_SHUT_RDWR);
	
	shutdown( sd, SHUT_RDWR); /* no more receptions */
	close(sd);
	
	gnutls_free_srp_client_sc( cred);
	gnutls_free_x509_client_sc( xcred);
	gnutls_deinit( state);

	gnutls_global_deinit();
	
	return 0;
}
