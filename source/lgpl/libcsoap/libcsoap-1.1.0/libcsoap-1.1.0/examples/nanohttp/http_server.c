/******************************************************************
*  $Id: http_server.c 254826 2013-01-10 12:29:18Z akosteltsev $
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
* Email: hero@persua.de
******************************************************************/
#include <stdio.h>
#include <string.h>

#include <nanohttp/nanohttp-logging.h>
#include <nanohttp/nanohttp-server.h>

static int simple_authenticator(hrequest_t *req, const char *user, const char *password)
{

	log_info3("logging in user=\"%s\" password=\"%s\"", user, password);

	if (strcmp(user, "bob")) {

		log_warn2("user \"%s\" unkown", user);
		return 0;
	}

	if (strcmp(password, "builder")) {

		log_warn1("wrong password");
		return 0;
	}

	return 1;
}

static void secure_service(httpd_conn_t *conn, hrequest_t *req)
{

	httpd_send_header(conn, 200, "OK");
	hsocket_send(conn->sock,
		"<html>"
			"<head>"
				"<title>Secure ressource!</title>"
			"</head>"
			"<body>"
				"<h1>Authenticated access!!!</h1>"
			"</body>"
		"</html>");

	return;
}

static void default_service(httpd_conn_t *conn, hrequest_t *req)
{

	httpd_send_header(conn, 404, "Not found");
	hsocket_send(conn->sock,
		"<html>"
			"<head>"
				"<title>Default error page</title>"
			"</head>"
			"<body>"
				"<h1>Default error page</h1>"
				"<div>");

	hsocket_send(conn->sock, req->path);

	hsocket_send(conn->sock, " can not be found"
		       		"</div>"
			"</body>"
		"</html>");

	return;
}	

static void headers_service(httpd_conn_t *conn, hrequest_t *req)
{
	hpair_t *walker;

	httpd_send_header(conn, 200, "OK");
	hsocket_send(conn->sock,
		"<html>"
			"<head>"
				"<title>Request headers</title>"
			"</head>"
			"<body>"
				"<h1>Request headers</h1>"
				"<ul>");

	for (walker=req->header; walker; walker=walker->next)
	{
		hsocket_send(conn->sock, "<li>");
		hsocket_send(conn->sock, walker->key);
		hsocket_send(conn->sock, " = ");
		hsocket_send(conn->sock, walker->value);
		hsocket_send(conn->sock, "</li>");
	}

	hsocket_send(conn->sock,
				"</ul>"
			"</body>"
		"</html>");

	return;
}

static void root_service(httpd_conn_t *conn, hrequest_t *req)
{
	httpd_send_header(conn, 200, "OK");
	hsocket_send(conn->sock,
		"<html>"
			"<head>"
				"<title>nanoHTTP server examples</title>"
			"</head>"
			"<body>"
				"<h1>nanoHTTP server examples</h1>"
				"<ul>"
					"<li><a href=\"/\">Simple service</a></li>"
					"<li><a href=\"/secure\">Secure service</a> (try: bob/builder)</li>"
					"<li><a href=\"/headers\">Request headers</a></li>"
					"<li><a href=\"/not_existent\">The default service</a></li>"
				"</ul>"
			"</body>"
		"</html>");

	return;
}

int main(int argc, char *argv[])
{
	hlog_set_level(HLOG_INFO);

	if (httpd_init(argc, argv)) {

		fprintf(stderr, "Can not init httpd");
		return 1;
	}

	if (!httpd_register("/", root_service)) {

		fprintf(stderr, "Can not register service");
		return 1;
	}

	if (!httpd_register_secure("/secure", secure_service, simple_authenticator)) {

		fprintf(stderr, "Can not register secure service");
		return 1;
	}

	if (!httpd_register("/headers", headers_service)) {

		fprintf(stderr, "Can not register headers service");
		return 1;
	}

	if (!httpd_register_default("/error", default_service)) {

		fprintf(stderr, "Can not register default service");
		return 1;
	}

	if (httpd_run()) {

		fprintf(stderr, "can not run httpd");
		return 1;
	}

	httpd_destroy();

	return 0;
}
