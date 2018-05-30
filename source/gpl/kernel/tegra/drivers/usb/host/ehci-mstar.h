/*
 * eHCI host controller driver
 *
 * Copyright (C) 2012 MStar Inc.
 *
 *
 * Date: Aug 2012
 */

#ifndef _EHCI_MSTAR_H
#define _EHCI_MSTAR_H

#define EHCI_MSTAR_VERSION "20170301"

#include <ehci-mstar-31040.h>

#ifdef CONFIG_MSTAR_BDMA
void m_BDMA_write(unsigned int, unsigned int);
void set_64bit_OBF_cipher(void);
int get_64bit_OBF_cipher(void);
#endif
#endif	/* _EHCI_MSTAR_H */
