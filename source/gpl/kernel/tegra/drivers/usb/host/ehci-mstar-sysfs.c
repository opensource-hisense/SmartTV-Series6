///////////////////////////////////////////////////////////////////////////////////////////////////
//
// * Copyright (c) 2006 - 2008 MStar Semiconductor, Inc.
// This program is free software.
// You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// Not verified functions, just test

#if (MP_USB_MSTAR==1) && defined(CONFIG_USB_EHCI_SUSPEND_PORT)
static ssize_t show_port_suspend(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct ehci_hcd		*ehci;
	u32 __iomem	*reg;
	u32		status;
	unsigned isSuspend;

	ehci = hcd_to_ehci(bus_to_hcd(dev_get_drvdata(dev)));
	reg = &ehci->regs->port_status[0];
	status = ehci_readl(ehci, reg);
	if (status & 0x80)
		isSuspend = 1;
	else
		isSuspend = 0;

	return sprintf(buf, "%d\n", isSuspend);;
}

static ssize_t set_port_suspend(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct ehci_hcd	*ehci;
	ssize_t			ret;
	int				config;
	u32 __iomem		*reg;
	u32				status;

	if ( sscanf(buf, "%d", &config) != 1 )
		return -EINVAL;

	ehci = hcd_to_ehci(bus_to_hcd(dev_get_drvdata(dev)));
	reg = &ehci->regs->port_status[0];
	status = ehci_readl(ehci, reg);

	if (config == 1)
	{
		if ( !(status & PORT_SUSPEND) && (status & PORT_CONNECT) )
		{
			//printk("ehci suspend\n");
			ehci_writel(ehci, status | PORT_SUSPEND, reg);
		}
	}
	else
	{
		if ( status & PORT_SUSPEND )
		{
			//printk("ehci port reset\n");
			ehci_writel(ehci, status | (PORT_RESET |PORT_RESUME), reg);
			msleep(70);
			ehci_writel(ehci, status & ~(PORT_RESET|PORT_RESUME), reg);
		}
	}

	ret = count;
	return ret;
}
static DEVICE_ATTR(port_suspend, 0644, show_port_suspend, set_port_suspend);
#endif
