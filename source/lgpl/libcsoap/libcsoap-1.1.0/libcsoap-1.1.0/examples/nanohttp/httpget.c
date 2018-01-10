/******************************************************************
*  $Id: httpget.c 254826 2013-01-10 12:29:18Z akosteltsev $
*
* CSOAP Project:  A http client/server library in C (example)
* Copyright (C) 2003  Ferhat Ayaz
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA  02111-1307, USA.
* 
* Email: ayaz@jprogrammer.net
******************************************************************/
#include <nanohttp/nanohttp-client.h>

#include <stdio.h>


int main(int argc, char *argv[])
{
	httpc_conn_t *conn;
	hresponse_t *res;
	hpair_t *pair;

	if (argc < 2) {
		fprintf(stderr, "usage %s <url>\n", argv[0]);
		exit(1);
	}

	log_set_level(HLOG_VERBOSE);
	if (httpc_init(argc, argv))
	{
	 log_error1("Can not init httpc");
	 return 1;
	}

	conn = httpc_new();
	res = httpc_get(conn, argv[1]);

	if (res != NULL) {
		log_info2("Spec  : '%s'", res->spec);
		log_info2("Status: %d", res->errcode);
		log_info2("Desc  : '%s'", res->desc);

		if (res->body) {
			pair = res->header;
			while (pair != NULL) {
				log_debug3("%s: %s", pair->key, pair->value);
				pair = pair->next;
			}

			puts(res->body);
		}
		else
			log_error1("body is null");

		hresponse_free(res);
	} else {
		log_error1("response object is null");
	}

	httpc_free(conn);
	return 0;
}
