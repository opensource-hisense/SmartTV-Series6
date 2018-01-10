/******************************************************************
 * $Id: simpleclient.c 254826 2013-01-10 12:29:18Z akosteltsev $
 *
 * CSOAP Project:  CSOAP examples project 
 * Copyright (C) 2003-2004  Ferhat Ayaz
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA02111-1307USA
 *
 * Email: ferhatayaz@yahoo.com
 ******************************************************************/

#include <nanohttp/nanohttp-logging.h>

#include <libcsoap/soap-client.h>


static const char *url = "http://localhost:10000/csoapserver";
static const char *urn = "urn:examples";
static const char *method = "sayHello";


int
main(int argc, char *argv[])
{
  SoapCtx *ctx, *ctx2;
  herror_t err;

  /* log_set_level(HLOG_VERBOSE); */
  err = soap_client_init_args(argc, argv);
  if (err != H_OK)
  {
    log_error4("%s():%s [%d]", herror_func(err), herror_message(err),
               herror_code(err));
    herror_release(err);
    return 1;
  }

  err = soap_ctx_new_with_method(urn, method, &ctx);
  if (err != H_OK)
  {
    log_error4("%s():%s [%d]", herror_func(err), herror_message(err),
               herror_code(err));
    herror_release(err);
    return 1;
  }

  soap_env_add_item(ctx->env, "xsd:string", "name", "Jonny B. Good");

  if (argc > 1)
    err = soap_client_invoke(ctx, &ctx2, argv[1], "");
  else
    err = soap_client_invoke(ctx, &ctx2, url, "");

  if (err != H_OK)
  {
    log_error4("[%d] %s(): %s ", herror_code(err), herror_func(err),
               herror_message(err));
    herror_release(err);
    soap_ctx_free(ctx);
    return 1;
  }

  soap_xml_doc_print(ctx2->env->root->doc);
  soap_ctx_free(ctx2);
  soap_ctx_free(ctx);

  soap_client_destroy();
  return 0;
}
