/*
 * Copyright (C) 2010-2012 Free Software Foundation, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of GnuTLS.
 *
 * The GnuTLS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#ifndef __GNUTLS_TPM_H
#define __GNUTLS_TPM_H

#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct tpm_key_list_st;
typedef struct tpm_key_list_st *gnutls_tpm_key_list_t;

#define GNUTLS_TPM_KEY_SIGNING (1<<2)
#define GNUTLS_TPM_REGISTER_KEY (1<<3)

int
gnutls_tpm_privkey_generate (gnutls_pk_algorithm_t pk, unsigned int bits, 
                             const char* srk_password,
                             const char* key_password,
                             gnutls_x509_crt_fmt_t format,
                             gnutls_datum_t* privkey, 
                             gnutls_datum_t* pubkey,
                             unsigned int flags);

void gnutls_tpm_key_list_deinit (gnutls_tpm_key_list_t list);
int gnutls_tpm_key_list_get_url (gnutls_tpm_key_list_t list, unsigned int idx, char** url, unsigned int flags);
int gnutls_tpm_get_registered (gnutls_tpm_key_list_t *list);
int gnutls_tpm_privkey_delete (const char* url, const char* srk_password);


#ifdef __cplusplus
}
#endif

#endif
