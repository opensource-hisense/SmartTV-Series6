/******************************************************************
 *  $Id: tr.h 254826 2013-01-10 12:29:18Z akosteltsev $
 *
 * CSOAP Project:  A SOAP client/server library in C
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
#ifndef XSD2C_TR_H
#define XSD2C_TR_H

/*void trInitModule(const char* ns);*/
void trInitModule();
void trFreeModule();

char* trC2XSD(const char* cType);
char* trXSD2C(const char* xsdType);

char* trC2XSDList(const char* cType);
char* trXSD2CList(const char* xsdType);

void trRegisterType(const char* xsdType, const char* cType, int builtin);
void trRegisterTypeNS(const char* ns, const char* xsdType, const char* cType, int builtin);

void trRegisterListType(const char* xsdType, const char* cType);
void trRegisterListTypeNS(const char* ns, const char* xsdType, const char* cType);

int trGetBuildInFlag(const char* xsdType);

char* trXSDParseNs(char* xsdType);

#endif
