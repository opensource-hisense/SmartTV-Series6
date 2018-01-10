#ifndef __TEEDER_INCLUDE_H__
#define __TEEDER_INCLUDE_H__

/*******************************************************
 * Minimal DER functionality for composing Secure Stop *
 *******************************************************/

#define DER_INTEGER  0x02
#define DER_SEQUENCE 0x30
#define DER_OCTETS 0x04

int DER_GetHeaderLen(int len);

unsigned char * DER_WriteHeader(unsigned char * p, int type, int len);

#endif
