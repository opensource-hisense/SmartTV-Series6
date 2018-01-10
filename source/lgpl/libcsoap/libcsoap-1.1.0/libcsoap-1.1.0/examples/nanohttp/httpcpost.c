/******************************************************************
*  $Id: httpcpost.c 254826 2013-01-10 12:29:18Z akosteltsev $
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

#ifdef WIN32
#include <stdafx.h>
#include <malloc.h>
#else
#include <stdio.h>
#endif

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char *argv[])
#endif
{
	httpc_conn_t *conn;
	hresponse_t *res;
	hpair_t *pair;
	char postdata[1054];
	int status;

	if (argc < 2) {
		fprintf(stderr, "usage %s <url> \n", argv[0]);
		exit(1);
	}

	log_set_level(HLOG_VERBOSE);

	conn = httpc_new();

	log_debug1("Opening connection");
	status = httpc_post_open(conn, argv[1]);
	if (status) {
		log_error2("Can not open connection (%d)", status);
		return 1;
	}

	while (1) {
		printf("Enter chunk (max 1024): ");
		gets(postdata);
		if (!strcmp(postdata, ".")) break;
		log_debug1("sending chunk ...");
		httpc_post_send(conn, postdata, strlen(postdata));
	}

	log_debug1("please wait ...");
	res = httpc_post_finish(conn);

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
	} else 	{
		log_error1("response object is null");
	}

	httpc_free(conn);
	return 0;

}
