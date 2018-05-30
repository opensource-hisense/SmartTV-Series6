/*
 * xhci-mstar.c - xHCI host controller driver platform Bus Glue.
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>

#include "xhci.h"
#include "xhci-mstar.h"
#include "../core/bc-mstar.h"
#include "../core/mstar-lib.h"


static void xhci_plat_quirks(struct device *dev, struct xhci_hcd *xhci)
{
	/*
	 * As of now platform drivers don't provide MSI support so we ensure
	 * here that the generic code does not try to make a pci_dev from our
	 * dev struct in order to setup MSI
	 */
	xhci->quirks |= XHCI_PLAT;
	xhci->quirks |= XHCI_RESET_ON_RESUME;
	xhci->quirks |= XHCI_SPURIOUS_SUCCESS;
	// xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	xhci->hci_version = 0x96;  //modified for real version. 
}

/* called during probe() after chip reset completes */
static int xhci_plat_setup(struct usb_hcd *hcd)
{
	return xhci_gen_setup(hcd, xhci_plat_quirks);
}

static const struct hc_driver mstar_plat_xhci_driver = {
	.description =		"mstar-xhci-hcd",
	.product_desc =		"Mstar xHCI Host Controller",
	.hcd_priv_size =	sizeof(struct xhci_hcd *),

	/*
	 * generic hardware linkage
	 */
	.irq =			xhci_irq,
	.flags =		HCD_MEMORY | HCD_USB3 | HCD_SHARED,

	/*
	 * basic lifecycle operations
	 */
	.reset =		xhci_plat_setup,
	.start =		xhci_run,
	.stop =			xhci_stop,
	.shutdown =		xhci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		xhci_urb_enqueue,
	.urb_dequeue =		xhci_urb_dequeue,
	.alloc_dev =		xhci_alloc_dev,
	.free_dev =		xhci_free_dev,
	.alloc_streams =	xhci_alloc_streams,
	.free_streams =		xhci_free_streams,
	.add_endpoint =		xhci_add_endpoint,
	.drop_endpoint =	xhci_drop_endpoint,
	.endpoint_reset =	xhci_endpoint_reset,
	.check_bandwidth =	xhci_check_bandwidth,
	.reset_bandwidth =	xhci_reset_bandwidth,
	.address_device =	xhci_address_device,
	.update_hub_device =	xhci_update_hub_device,
	.reset_device =		xhci_discover_or_reset_device,

	/*
	 * scheduling support
	 */
	.get_frame_number =	xhci_get_frame,

	/* Root hub support */
	.hub_control =		xhci_hub_control,
	.hub_status_data =	xhci_hub_status_data,
	.bus_suspend =		xhci_bus_suspend,
	.bus_resume =		xhci_bus_resume,
};

void DEQ_init(uintptr_t U3PHY_D_base, uintptr_t U3PHY_A_base)
{
	writeb(0x00,   (void*)(U3PHY_A_base+0xAE*2));   
	writew(0x080C, (void*)(U3PHY_D_base+0x82*2));   
	writeb(0x10,   (void*)(U3PHY_D_base+0xA4*2)); //0x10  0x30  
	writew(0x4100, (void*)(U3PHY_D_base+0xA0*2));   
	
	writew(0x06,   (void*)(U3PHY_A_base+0x06*2));   
}

void  XHCI_enable_testbus(uintptr_t CHIPTOP_base, uintptr_t U3TOP_base, uintptr_t XHCI_base)
{
	writeb(0x00,   (void*)(CHIPTOP_base+0xEC*2));   
	writeb(0x20,   (void*)(CHIPTOP_base+0x24*2));   
	writeb(0x42,   (void*)(CHIPTOP_base+0xEE*2));   // select usb30_test_out
	// writeb(0x00,   (void*)(CHIPTOP_base+0xEA*2));   
	writeb(0x40,   (void*)(CHIPTOP_base+0xEB*2-1));   
	//writew(0xFFFF, (void*)(CHIPTOP_base+0x12*2));   
	//writew(0xFFFF, (void*)(CHIPTOP_base+0x14*2));   
	//writeb(0xFF,   (void*)(CHIPTOP_base+0x16*2));   
	//writeb(0x01,   (void*)(CHIPTOP_base+0x21*2-1));   
	//writeb(0x02,   (void*)(CHIPTOP_base+0x3A*2));   
	
	//writeb(0x0d,   (void*)(U3PHY_D_base+0xD5*2-1));   
	//writeb(0x23,   (void*)(U3PHY_D_base+0x2E*2));   
	//writeb(0x40,   (void*)(U3PHY_D_base+0x2F*2-1));   

	//writeb(0x09,   (void*)(U3TOP_base+0x0C*2)); 	// [5] = reg_debug_mask to 1'b0
	                                                // [4:0] = 0x06= rrdy & wrdy
	writeb(0x00,   (void*)(U3TOP_base+0x0C*2));

	writeb(0x11,    (void*) (XHCI_base+0x608c));   
	writeb(0x30,    (void*) (XHCI_base+0x608f));
	writeb(0x39,    (void*) (XHCI_base+0x6805));  
	writeb(0x3a,    (void*) (XHCI_base+0x6806));  
	writeb(0x21,    (void*) (XHCI_base+0x6807));  
}

static void XHCI_enable_PPC(uintptr_t U3TOP_base)
{
	u16 addr_w, bit_num;
	uintptr_t addr;
	u8  value, low_active;
	u8  i, portnum=1;

#ifndef CONFIG_MSTAR_XUSB_PCIE_PLATFORM
	#ifdef XHCI_2PORTS
	portnum=2;
	#endif
#endif

	for (i=0; i<portnum; i++) {

		switch (i) {
		case 0:
			addr_w = readw((void*)(U3TOP_base+0xFC*2));
			addr = (uintptr_t)addr_w << 8;
			addr_w = readw((void*)(U3TOP_base+0xFE*2));
			addr |= addr_w & 0xFF;
			bit_num = (addr_w >> 8) & 0x7;
			low_active = (u8)((addr_w >> 8) & 0x8);
			break;
		case 1:
			addr_w = readw((void*)(U3TOP_base+0xE6*2));
			addr = (uintptr_t)addr_w << 8;
			addr_w = readw((void*)(U3TOP_base+0xE8*2));
			addr |= addr_w & 0xFF;
			bit_num = (addr_w >> 8) & 0x7;
			low_active = (u8)((addr_w >> 8) & 0x8);
			break;
		default:	/* "can't happen" */
			return;
		}
	
		if (addr)
		{
			printk("XHCI_enable_PPC: Turn on USB3.0 port %d power \n", i);
			printk("Addr: 0x%lx bit_num: %d low_active:%d\n", addr, bit_num, low_active);

			value = (u8)(1 << bit_num);

			if (low_active)
			{
				if (addr & 0x1)
					writeb(readb((void*)(_MSTAR_PM_BASE+addr*2-1)) & (u8)(~value), (void*)(_MSTAR_PM_BASE+addr*2-1)); 
				else
					writeb(readb((void*)(_MSTAR_PM_BASE+addr*2)) & (u8)(~value), (void*)(_MSTAR_PM_BASE+addr*2)); 
			}
			else
			{
				if (addr & 0x1)
					writeb(readb((void*)(_MSTAR_PM_BASE+addr*2-1)) | value, (void*)(_MSTAR_PM_BASE+addr*2-1)); 
				else
					writeb(readb((void*)(_MSTAR_PM_BASE+addr*2)) | value, (void*)(_MSTAR_PM_BASE+addr*2)); 
			}
		}
	}
}


void Mstar_U2utmi_init(uintptr_t UTMI_base, uintptr_t U3TOP_base, unsigned int flag)
{
	if ((UTMI_base==0) || (U3TOP_base==0))
		return;
	
	if (0 == readw((void*)(UTMI_base+0x20*2)))
	{
		printk("utmi clk enable\n");
		writew(0x8051, (void*) (UTMI_base+0x20*2)); 
		writew(0x2088, (void*) (UTMI_base+0x22*2)); 
		writew(0x0004, (void*) (UTMI_base+0x2*2)); 
		writew(0x6BC3, (void*) (UTMI_base)); 
		mdelay(1);
		writew(0x69C3, (void*) (UTMI_base)); 
		mdelay(1);
		writew(0x0001, (void*) (UTMI_base)); 
		mdelay(1);
	}

	writeb(0x07, (void*) (UTMI_base+0x8*2));   //default value 0x7; don't change it. 

	if (flag & EHCFLAG_TESTPKG)
	{
		writew(0x2084, (void*) (UTMI_base+0x2*2));
		writew(0x8051, (void*) (UTMI_base+0x20*2));
	}

#if _USB_HS_CUR_DRIVE_DM_ALLWAYS_HIGH_PATCH
	/*
	 * patch for DM always keep high issue
	 * init overwrite register
	 */
	writeb(readb((void*)(UTMI_base+0x0*2)) & (u8)(~BIT3), (void*) (UTMI_base+0x0*2)); //DP_PUEN = 0
	writeb(readb((void*)(UTMI_base+0x0*2)) & (u8)(~BIT4), (void*) (UTMI_base+0x0*2)); //DM_PUEN = 0

	writeb(readb((void*)(UTMI_base+0x0*2)) & (u8)(~BIT5), (void*) (UTMI_base+0x0*2)); //R_PUMODE = 0

	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT6, (void*) (UTMI_base+0x0*2)); //R_DP_PDEN = 1
	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT7, (void*) (UTMI_base+0x0*2)); //R_DM_PDEN = 1

	writeb(readb((void*)(UTMI_base+0x10*2)) | BIT6, (void*) (UTMI_base+0x10*2)); //hs_txser_en_cb = 1
	writeb(readb((void*)(UTMI_base+0x10*2)) & (u8)(~BIT7), (void*) (UTMI_base+0x10*2)); //hs_se0_cb = 0

	/* turn on overwrite mode */
	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT1, (void*) (UTMI_base+0x0*2)); //tern_ov = 1
#endif	

	writeb(readb((void*)(UTMI_base+0x3C*2)) | 0x01, (void*) (UTMI_base+0x3C*2)); // set CA_START as 1
	mdelay(1);

	writeb(readb((void*)(UTMI_base+0x3C*2)) & (u8)(~0x01), (void*) (UTMI_base+0x3C*2)); // release CA_START

	while ((readb((void*)(UTMI_base+0x3C*2)) & 0x02) == 0); // polling bit <1> (CA_END)

	if ((0xFFF0 == (readw((void*)(UTMI_base+0x3C*2)) & 0xFFF0 )) ||
		(0x0000 == (readw((void*)(UTMI_base+0x3C*2)) & 0xFFF0 ))  )
	{
		printk("WARNING: CA Fail !! \n");
	}
	
	if (flag & EHCFLAG_DPDM_SWAP)
		writeb(readb((void*)(UTMI_base+0x0b*2-1)) |0x20, (void*) (UTMI_base+0x0b*2-1)); // dp dm swap

	writeb((u8)((readb((void*)(UTMI_base+0x06*2)) & 0x9F) | 0x40), (void*) (UTMI_base+0x06*2)); //reg_tx_force_hs_current_enable

	writeb(readb((void*)(UTMI_base+0x03*2-1)) | 0x28, (void*) (UTMI_base+0x03*2-1)); //Disconnect window select
	writeb(readb((void*)(UTMI_base+0x03*2-1)) & 0xef, (void*) (UTMI_base+0x03*2-1)); //Disconnect window select

	writeb(readb((void*)(UTMI_base+0x07*2-1)) & 0xfd, (void*) (UTMI_base+0x07*2-1)); //Disable improved CDR
	writeb(readb((void*)(UTMI_base+0x09*2-1)) |0x81, (void*) (UTMI_base+0x09*2-1)); // UTMI RX anti-dead-loc, ISI effect improvement
	writeb(readb((void*)(UTMI_base+0x0b*2-1)) |0x80, (void*) (UTMI_base+0x0b*2-1)); // TX timing select latch path
	writeb(readb((void*)(UTMI_base+0x15*2-1)) |0x20, (void*) (UTMI_base+0x15*2-1)); // Chirp signal source select

	//Enable XHCI preamble function with keep-alive
	writeb(readb((void*)(UTMI_base+0x3F*2-1)) |0x80, (void*) (UTMI_base+0x3F*2-1)); // Enable XHCI preamble function

#if defined(XHCI_ENABLE_240MHZ)  //exclude Agate
	/* before Madison, bit4 [for 240 setting], bit5 [no use]
	 * after Madison, bit4 [no use], bit5 [for 240 setting]
	 * setting both bits for all chips.
	 */
	writeb(readb((void*)(UTMI_base+0x08*2)) | 0x38, (void*) (UTMI_base+0x08*2)); // for 240's phase as 120's clock
	#if defined(XHCI_USE_120_PHASE)
	//Fix it for Eiffel Only. 
	writeb(readb((void*)(UTMI_base+0x08*2)) & 0xF7, (void*) (UTMI_base+0x08*2)); // Clear setting of "240's phase as 120's clock"
	#endif	
#endif

	// change to 55 timing; for all chips.
	writeb(readb((void*)(UTMI_base+0x15*2-1)) |0x40, (void*) (UTMI_base+0x15*2-1)); // change to 55 timing

	// for CLK 120 override enable; for xHCI on all chips
	writeb(readb((void*)(UTMI_base+0x09*2-1)) |0x04, (void*) (UTMI_base+0x09*2-1)); // for CLK 120 override enable

	/* Init UTMI disconnect level setting */
	writeb(UTMI_DISCON_LEVEL_2A, (void*)(UTMI_base+0x2a*2));

	writeb(UTMI_EYE_SETTING_2C, (void*) (UTMI_base+0x2c*2));
	writeb(UTMI_EYE_SETTING_2D, (void*) (UTMI_base+0x2d*2-1));
	writeb(UTMI_EYE_SETTING_2E, (void*) (UTMI_base+0x2e*2));
	writeb(UTMI_EYE_SETTING_2F, (void*) (UTMI_base+0x2f*2-1));

#if defined(ENABLE_LS_CROSS_POINT_ECO)
	writeb(readb((void*)(UTMI_base+0x04*2)) | 0x40, (void*) (UTMI_base+0x04*2));  //enable deglitch SE0би(low-speed cross point)
#endif

#if defined(ENABLE_TX_RX_RESET_CLK_GATING_ECO)
	writeb(readb((void*)(UTMI_base+0x04*2)) | 0x20, (void*) (UTMI_base+0x04*2)); //enable hw auto deassert sw reset(tx/rx reset)
#endif

#if defined(ENABLE_KEEPALIVE_ECO)
	writeb(readb((void*)(UTMI_base+0x04*2)) | 0x80, (void*) (UTMI_base+0x04*2));	//enable LS keep alive & preamble
#endif

#if defined(ENABLE_HS_DM_KEEP_HIGH_ECO)
	/* Change override to hs_txser_en.	Dm always keep high issue */ 
	writeb(readb((void*)(UTMI_base+0x10*2)) | BIT6, (void*) (UTMI_base+0x10*2));
#endif

#if _USB_HS_CUR_DRIVE_DM_ALLWAYS_HIGH_PATCH
	/*
	 * patch for DM always keep high issue
	 * init overwrite register
	 */
	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT6, (void*) (UTMI_base+0x0*2)); //R_DP_PDEN = 1
	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT7, (void*) (UTMI_base+0x0*2)); //R_DM_PDEN = 1

	/* turn on overwrite mode */
	writeb(readb((void*)(UTMI_base+0x0*2)) | BIT1, (void*) (UTMI_base+0x0*2)); //tern_ov = 1
#endif

#if _USB_ANALOG_RX_SQUELCH_PATCH
	/* squelch level adjust by calibration value */
	{
		unsigned int ca_da_ov, ca_db_ov, ca_tmp;
		ca_tmp = readw((void*)(UTMI_base+0x3c*2));
		ca_da_ov = (((ca_tmp >> 4) & 0x3f) - 5) + 0x40;
		ca_db_ov = (((ca_tmp >> 10) & 0x3f) - 5) + 0x40;
		printk("[%x]-5 ->(ca_da_ov, ca_db_ov) = (%x,%x)\n", ca_tmp, ca_da_ov, ca_db_ov);
		writeb(ca_da_ov ,(void*)(UTMI_base+0x3B*2-1));
		writeb(ca_db_ov ,(void*)(UTMI_base+0x24*2));
	}
#endif
	
#if (XHCI_CHIRP_PATCH)
	writeb(UTMI_DISCON_LEVEL_2A, (void*) (UTMI_base+0x3E*2)); //override value 
	writeb((u8)((readb((void*)(U3TOP_base+0x24*2)) & 0xF0) | 0x0A), (void*)(U3TOP_base+0x24*2)); // set T1=50, T2=20
	writeb(readb((void*)(UTMI_base+0x3F*2-1)) | 0x1, (void*) (UTMI_base+0x3F*2-1)); //enable the patch 
#endif 

	if (flag & EHCFLAG_TESTPKG)
	{
		writew(0x0600, (void*) (UTMI_base+0x14*2)); 
		writew(0x0078, (void*) (UTMI_base+0x10*2)); 
		writew(0x0BFE, (void*) (UTMI_base+0x32*2)); 
	}
}


#if (!defined(XHCI_PHY_MT28)) && (!defined(XHCI_PHY_MS28))
static void Mstar_U3phy_init(uintptr_t U3PHY_D_base, uintptr_t U3PHY_A_base)
{

	//U3phy initial sequence 
	writew(0x0,    (void*) (U3PHY_A_base)); 		 // power on rx atop 
	writew(0x0,    (void*) (U3PHY_A_base+0x2*2));	 // power on tx atop
	writew(0x0910, (void*) (U3PHY_D_base+0x4*2));  
	writew(0x0,    (void*) (U3PHY_A_base+0x3A*2)); 
	writew(0x0160, (void*) (U3PHY_D_base+0x18*2)); 
	writew(0x0,    (void*) (U3PHY_D_base+0x20*2));	 // power on u3_phy clockgen 
	writew(0x0,    (void*) (U3PHY_D_base+0x22*2));	 // power on u3_phy clockgen 

	writew(0x013F, (void*) (U3PHY_D_base+0x4A*2)); 
	writew(0x1010, (void*) (U3PHY_D_base+0x4C*2)); 

	writew(0x0,    (void*) (U3PHY_A_base+0x3A*2));	 // override PD control
	writeb(0x1C,   (void*) (U3PHY_A_base+0xCD*2-1)); // reg_test_usb3aeq_acc;  long EQ converge 
	writeb(0x40,   (void*) (U3PHY_A_base+0xC9*2-1)); // reg_gcr_usb3aeq_threshold_abs
	writeb(0x10,   (void*) (U3PHY_A_base+0xE5*2-1)); // [4]: AEQ select PD no-delay and 2elay path, 0: delay, 1: no-
	writeb(0x11,   (void*) (U3PHY_A_base+0xC6*2));	 // analog symbol lock and EQ converage step 
	writeb(0x02,   (void*) (U3PHY_D_base+0xA0*2));	 // [1] aeq mode

	writeb(0x07,   (void*) (U3PHY_A_base+0xB0*2));	 // reg_gcr_usb3rx_eq_str_ov_value

#if (ENABLE_XHCI_SSC)  
	writew(0x04D8,	(void*) (U3PHY_D_base+0xC6*2));  //reg_tx_synth_span
	writew(0x0003,	(void*) (U3PHY_D_base+0xC4*2));  //reg_tx_synth_step
	writew(0x9375,	(void*) (U3PHY_D_base+0xC0*2));  //reg_tx_synth_set
	writeb(0x18,	(void*) (U3PHY_D_base+0xC2*2));  //reg_tx_synth_set
#endif	

	////Set Tolerance  //only for Agate_U01
	/// writew(0x0103, (void*) (U3PHY_D_base+0x44*2)); 

	// Comma
	// writeb(0x84,   (void*) (U3PHY_A_base+0xCD*2-1)); // reg_test_aeq_acc, 8bit

	// RX phase control
	writew(0x0100, (void*)(U3PHY_A_base+0x90*2));	
	writew(0x0302, (void*)(U3PHY_A_base+0x92*2));	
	writew(0x0504, (void*)(U3PHY_A_base+0x94*2));	
	writew(0x0706, (void*)(U3PHY_A_base+0x96*2));	
	writew(0x1708, (void*)(U3PHY_A_base+0x98*2));	
	writew(0x1516, (void*)(U3PHY_A_base+0x9A*2));	
	writew(0x1314, (void*)(U3PHY_A_base+0x9C*2));	
	writew(0x1112, (void*)(U3PHY_A_base+0x9E*2));	
	writew(0x3000, (void*)(U3PHY_D_base+0xA8*2)); 
	writew(0x7380, (void*)(U3PHY_A_base+0x40*2));	

#if (XHCI_ENABLE_DEQ)	
	DEQ_init(U3PHY_D_base, U3PHY_A_base);
#endif

#if (XHCI_TX_SWING_PATCH)
	writeb(0x3F, (void*)(U3PHY_A_base+0x60*2)); 
	writeb(0x39, (void*)(U3PHY_A_base+0x62*2)); 
#endif 
}
#endif

#if defined(XHCI_PHY_EFUSE) && defined(XHCI_PHY_MS28) 
void Mstar_U3phy_MS28_eFuse_2p(uintptr_t U3PHY_P0_A_base, uintptr_t U3PHY_P1_A_base)
{
	u32 value=0;	
	u8  setting=0;
	struct mstar_efuse efuse;

	efuse.efuse_base_addr = MSTAR_EFUSE_BASE;
	efuse.reg_set_addr = EFUSE_REG_ADDR;
	efuse.reg_read = EFUSE_REG_READ;
	efuse.reg_data = EFUSE_REG_DATA;
	efuse.bank_addr = RTERM_XHC_BANK;
	efuse.issue_read = EFUSE_READ_TRIG;
	
	value = mstar_efuse_read(&efuse);
	if ((value & 0x80008000) == 0x80008000) {
		printk("\n [ XHC: get efuse value: 0x%x ] \n", value);
		setting = (u8)((value>>USB30RX0_EFUSE_BITOFFSET) & 0x1F);
		writeb((readb((void*)(U3PHY_P0_A_base+GCR_USB3RX0_RCTRL))&(~0x1F)) | setting,  (void*)(U3PHY_P0_A_base+GCR_USB3RX0_RCTRL));
		setting = (u8)((value>>USB30TX0_EFUSE_BITOFFSET) & 0x1F);
		writeb((readb((void*)(U3PHY_P0_A_base+GCR_USB3TX0_RT))&(~0x1F)) | setting,  (void*)(U3PHY_P0_A_base+GCR_USB3TX0_RT));

		setting = (u8)((value>>USB30RX1_EFUSE_BITOFFSET) & 0x1F);
		writeb((readb((void*)(U3PHY_P1_A_base+GCR_USB3RX1_RCTRL))&(~0x1F)) | setting,  (void*)(U3PHY_P1_A_base+GCR_USB3RX1_RCTRL));
		setting = (u8)((value>>USB30TX1_EFUSE_BITOFFSET) & 0x1F);
		writeb((readb((void*)(U3PHY_P1_A_base+GCR_USB3TX1_RT))&(~0x1F)) | setting,  (void*)(U3PHY_P1_A_base+GCR_USB3TX1_RT));
	}
}
#endif

#if defined(XHCI_PHY_MS28)
static void Mstar_U3phy_MS28_init(uintptr_t U3PHY_D_base, uintptr_t U3PHY_A_base)
{
#ifdef XHCI_SINGLE_PORT_ENABLE_MAC
	writeb(readb((void*)(U3PHY_D_base+0x84*2))| 0x40, (void*)(U3PHY_D_base+0x84*2)); // open XHCI MAC clock
#endif
	//-- 28 hpm mstar only---
	writew(0x0104, (void*) (U3PHY_A_base+0x6*2));  // for Enable 1G clock pass to UTMI //[2] reg_pd_usb3_purt [7:6] reg_gcr_hpd_vsel 

	//U3phy initial sequence 
	writew(0x0,    (void*) (U3PHY_A_base)); 		 // power on rx atop 
	writew(0x0,    (void*) (U3PHY_A_base+0x2*2));	 // power on tx atop
	//writew(0x0910, (void*) (U3PHY_D_base+0x4*2));        // the same as default
	writew(0x0,    (void*) (U3PHY_A_base+0x3A*2));  // overwrite power on rx/tx atop
	writew(0x0160, (void*) (U3PHY_D_base+0x18*2)); 
	writew(0x0,    (void*) (U3PHY_D_base+0x20*2));	 // power on u3_phy clockgen 
	writew(0x0,    (void*) (U3PHY_D_base+0x22*2));	 // power on u3_phy clockgen 

	//writew(0x013F, (void*) (U3PHY_D_base+0x4A*2));      // the same as default
	//writew(0x1010, (void*) (U3PHY_D_base+0x4C*2));      // the same as default

	writew(0x0,    (void*) (U3PHY_A_base+0x3A*2));	 // override PD control
#ifdef XHCI_ENABLE_PD_OVERRIDE 
        writew(0x308,    (void*) (U3PHY_A_base+0x3A*2)); // [9,8,3] PD_TXCLK_USB3TXPLL, PD_USB3_IBIAS, PD_USB3TXPLL override enable
        writeb(readb((void*)(U3PHY_A_base+0x3*2-1)) & 0xbb,     (void*)(U3PHY_A_base+0x3*2-1)); // override value 0
#endif

#if 0  // not for MS28
	writeb(0x1C,   (void*) (U3PHY_A_base+0xCD*2-1)); // reg_test_usb3aeq_acc;  long EQ converge 
	writeb(0x40,   (void*) (U3PHY_A_base+0xC9*2-1)); // reg_gcr_usb3aeq_threshold_abs
	writeb(0x10,   (void*) (U3PHY_A_base+0xE5*2-1)); // [4]: AEQ select PD no-delay and 2elay path, 0: delay, 1: no-
	writeb(0x11,   (void*) (U3PHY_A_base+0xC6*2));	 // analog symbol lock and EQ converage step 
	writeb(0x02,   (void*) (U3PHY_D_base+0xA0*2));	 // [1] aeq mode

	writeb(0x07,   (void*) (U3PHY_A_base+0xB0*2));	 // reg_gcr_usb3rx_eq_str_ov_value
#endif

#if (ENABLE_XHCI_SSC)  
#ifdef XHCI_SSC_TX_SYNTH_SET_C0
	writew(XHCI_SSC_TX_SYNTH_SET_C0, (void*) (U3PHY_D_base+0xC0*2));  //reg_tx_synth_set
	writeb(XHCI_SSC_TX_SYNTH_SET_C2, (void*) (U3PHY_D_base+0xC2*2));  //reg_tx_synth_set
	writew(XHCI_SSC_TX_SYNTH_STEP_C4, (void*) (U3PHY_D_base+0xC4*2));  //reg_tx_synth_step
	writew(XHCI_SSC_TX_SYNTH_SPAN_C6, (void*) (U3PHY_D_base+0xC6*2));  //reg_tx_synth_span
#else
	writew(0x04D0,	(void*) (U3PHY_D_base+0xC6*2));  //reg_tx_synth_span
	writew(0x0003,	(void*) (U3PHY_D_base+0xC4*2));  //reg_tx_synth_step
	writew(0x9375,	(void*) (U3PHY_D_base+0xC0*2));  //reg_tx_synth_set
	writeb(0x18,	(void*) (U3PHY_D_base+0xC2*2));  //reg_tx_synth_set
#endif	
#endif

	// -- TX current ---
	//writeb(0x01, 	(void*) (U3PHY_A_base+0x35*2-1));
	writew(0x3932,  (void*) (U3PHY_A_base+0x60*2));
	writew(0x3939,  (void*) (U3PHY_A_base+0x62*2));
	writew(0x3932,  (void*) (U3PHY_A_base+0x64*2));
	writew(0x3939,  (void*) (U3PHY_A_base+0x66*2));
	writew(0x0400,  (void*) (U3PHY_A_base+0x12*2));
	// ---------------

	//-------- New for MS28 ---------
	writeb(0x0,    (void*) (U3PHY_A_base+0xA1*2-1));  //bit[15] EQ override
	writeb(0xF4,   (void*) (U3PHY_D_base+0x12*2));	  //TX lock threshold
	
	writeb(readb((void*)(U3PHY_A_base+0xF*2-1))&(u8)(~0x4),	(void*)(U3PHY_A_base+0xF*2-1));  // 0xF[10]  Fix AEQ RX-reset issue 

#ifdef XHCI_PHY_ENABLE_RX_LOCK
	writeb(readb((void*)(U3PHY_A_base+0x21*2-1)) | 0x80,	(void*)(U3PHY_A_base+0x21*2-1));  // enable rx_lock behavior.
#endif

#ifdef XHCI_PWS_P2
	writeb(readb((void*)(U3PHY_D_base+0x1E*2))| 0x1,	(void*)(U3PHY_D_base+0x1E*2));	//P2 power saving
#endif

#ifdef CONFIG_MSTAR_XUSB_PCIE_PLATFORM
	#ifdef XHCI_2PORTS
	if (U3PHY_D_base == _MSTAR_U3PHY_P0_DTOP_BASE)
		writeb(0xD,	(void*)(U3PHY_D_base+0x1E*2));	// P0 and P1 separated
	#endif
#endif

}
#endif


#if defined(XHCI_PHY_EFUSE) && defined(XHCI_PHY_MT28) 
void Mstar_U3phy_MT28_eFuse(uintptr_t U3PHY_D_M1_base)
{
	u16 i, value=0;	
	unsigned long	flags;
	spinlock_t	efuse_lock=__SPIN_LOCK_UNLOCKED(efuse_lock);

#if (XHC_EFUSE_FSM == 1)
	spin_lock_irqsave (&efuse_lock, flags);
	writew(XHC_EFUSE_OFFSET,  (void*)(_MSTAR_EFUSE_BASE+0x4E*2));  //bit[8]=0
	writeb(readb((void*)(_MSTAR_EFUSE_BASE+0x4C*2)) | 0x1,  (void*)(_MSTAR_EFUSE_BASE+0x4C*2));  //bit[0]=1
	for (i=0;  i<100; i++) {
		if ((readb((void*)(_MSTAR_EFUSE_BASE+0x4C*2)) & 0x1) == 0)
			break;
		mdelay(1);
	}
	if (100==i) {
		printk(" !!! WARNING: read eFuse timeout !!!\n");
		return;
	}
	value = readw((void*)(_MSTAR_EFUSE_BASE+0x80*2));
	spin_unlock_irqrestore (&efuse_lock, flags);
#else
	printk(" !!! ERROR: XHC_EFUSE_FSM0 not implement !!!\n");
	while(1);
#endif

	if (value & 0x8000) {
		printk("\n [ XHC: get efuse value: 0x%x ] \n", value);
		writew(0x3FF,  (void*)(U3PHY_D_M1_base+0x80*2));
		writew(value&0x3FF,  (void*)(U3PHY_D_M1_base+0x82*2));
	}
}
#endif

#if defined(XHCI_PHY_MT28)
static void Mstar_U3phy_MT28_init(uintptr_t U3PHY_D_M0_base, uintptr_t U3PHY_D_M1_base, 
	                       uintptr_t U3PHY_A_M0_base, uintptr_t U3PHY_A_M1_base)
{
	u16 value;

	//DA_SSUSB_TX_BIASI_B
	value = (u16)((readw((void*)(U3PHY_D_M1_base+0xA*2)) & (u16)(~0x0E00)) | 0x2000);
	writew(value,  (void*)(U3PHY_D_M1_base+0xA*2));
	//DA_SSUSB_idem_6db_b_olt
	value = (readw((void*)(U3PHY_D_M1_base+0x8*2)) & (u16)(~0x003F));
	value |= (0x100|0x24);	   //(0x100|0x18);
	writew(value,  (void*)(U3PHY_D_M1_base+0x8*2));
	//DA_SSUSB_IDRV_6DB_B_olt
	value = (readw((void*)(U3PHY_D_M1_base+0x6*2)) & (u16)(~0x3F00));
	value |= (0x4000|0x3600);  //(0x4000|0x2400);
	writew(value,  (void*)(U3PHY_D_M1_base+0x6*2));	
	//DA_SSUSB_IDEM_3P5db_B_olt	
	value = (readw((void*)(U3PHY_D_M1_base+0x6*2)) & (u16)(~0x003F));
	value |= (0x40|0x18);      //(0x40|0x10);
	writew(value,  (void*)(U3PHY_D_M1_base+0x6*2));
	//DA_SSUSB_IDRV_3P5db_b_olt
	value = (readw((void*)(U3PHY_D_M1_base+0x4*2)) & (u16)(~0x3F00));
	value |= (0x4000|0x3C00);  //(0x4000|0x2800);
	writew(value,  (void*)(U3PHY_D_M1_base+0x4*2));
	//DA_SSUSB_IDRV_0DB_b_olt
	value = (readw((void*)(U3PHY_D_M1_base+0x4*2)) & (u16)(~0x003F));
	value |= (0x40|0x3F);      //(0x40|0x30);
	writew(value,  (void*)(U3PHY_D_M1_base+0x4*2));

	//reg_ssusb_sigdet
	value = (readw((void*)(U3PHY_D_M0_base+0x8E*2)) & (u16)(~0x7F00));
	value |= (0x500);
	writew(value,  (void*)(U3PHY_D_M0_base+0x8E*2));

#if defined(XHCI_PHY_EFUSE)
	Mstar_U3phy_MT28_eFuse(U3PHY_D_M1_base);	
#endif
}
#endif

#if defined(ENABLE_USB_NEW_MIU_SLE)
void MIU_select_setting_xhc(uintptr_t U3TOP_base)
{
	printk("[USB] config miu select [%x] [%x] [%x] ][%x]\n", USB_MIU_SEL0, USB_MIU_SEL1, USB_MIU_SEL2, USB_MIU_SEL3);
	writeb(USB_MIU_SEL0, (void*)(U3TOP_base+0x3A*2));	//Setting MIU0 segment
	writeb(USB_MIU_SEL1, (void*)(U3TOP_base+0x36*2));	//Setting MIU1 segment
	writeb(USB_MIU_SEL2, (void*)(U3TOP_base+0x37*2-1));	//Setting MIU2 segment
	writeb(USB_MIU_SEL3, (void*)(U3TOP_base+0x38*2));	//Setting MIU3 segment
	writeb(readb((void*)(U3TOP_base+0x39*2-1)) | BIT6, (void*)(U3TOP_base+0x39*2-1));	//Enable miu partition mechanism
#if !defined(DISABLE_MIU_LOW_BOUND_ADDR_SUBTRACT_ECO)
	printk("[USB] enable miu lower bound address subtraction\n");
	writeb(readb((void*)(U3TOP_base+0x39*2-1)) | BIT7, (void*)(U3TOP_base+0x39*2-1));
#endif

}
#endif

static void Mstar_xhc_init(uintptr_t UTMI_base, uintptr_t XHCI_base, 
	uintptr_t U3TOP_base, uintptr_t U3BC_base, unsigned int flag)
{
	printk("Mstar_xhc_init version:%s\n", XHCI_MSTAR_VERSION);

	// Init USB2 UTMI
	Mstar_U2utmi_init(UTMI_base, U3TOP_base, flag);

	// Init USB3 PHY 
#if defined(XHCI_PHY_MT28)
	#if defined(XHCI_2PORTS)
	Mstar_U3phy_MT28_init(_MSTAR_U3PHY_P0_DTOP_M0_BASE, _MSTAR_U3PHY_P0_DTOP_M1_BASE,
				_MSTAR_U3PHY_P0_ATOP_M0_BASE, _MSTAR_U3PHY_P0_ATOP_M1_BASE);
	Mstar_U3phy_MT28_init(_MSTAR_U3PHY_P1_DTOP_M0_BASE, _MSTAR_U3PHY_P1_DTOP_M1_BASE,
				_MSTAR_U3PHY_P1_ATOP_M0_BASE, _MSTAR_U3PHY_P1_ATOP_M1_BASE);
	#else
	Mstar_U3phy_MT28_init(_MSTAR_U3PHY_DTOP_M0_BASE, _MSTAR_U3PHY_DTOP_M1_BASE,
				_MSTAR_U3PHY_ATOP_M0_BASE, _MSTAR_U3PHY_ATOP_M1_BASE);
	#endif
#elif defined(XHCI_PHY_MS28)
	#if defined(XHCI_2PORTS)
	Mstar_U3phy_MS28_init(_MSTAR_U3PHY_P0_DTOP_BASE, _MSTAR_U3PHY_P0_ATOP_BASE);
	#ifndef CONFIG_MSTAR_XUSB_PCIE_PLATFORM
	Mstar_U3phy_MS28_init(_MSTAR_U3PHY_P1_DTOP_BASE, _MSTAR_U3PHY_P1_ATOP_BASE);
	#endif
		#if defined(XHCI_PHY_EFUSE)
	Mstar_U3phy_MS28_eFuse_2p(_MSTAR_U3PHY_P0_ATOP_BASE, _MSTAR_U3PHY_P1_ATOP_BASE);	
		#endif
	#else
	Mstar_U3phy_MS28_init(_MSTAR_U3PHY_DTOP_BASE, _MSTAR_U3PHY_ATOP_BASE);
	#endif
#else	
	Mstar_U3phy_init(_MSTAR_U3PHY_DTOP_BASE, _MSTAR_U3PHY_ATOP_BASE);
#endif  

#if defined(ENABLE_USB_NEW_MIU_SLE)
	MIU_select_setting_xhc(U3TOP_base);
#endif

	//First token idle
	writeb(readb((void*)(XHCI_base+0x4308)) | 0x0C, (void*)(XHCI_base+0x4308));  //First token idle (bit2~3 = "11")
	//Inter packet delay
	writeb(readb((void*)(XHCI_base+0x430F)) | 0xC0, (void*)(XHCI_base+0x430F));  //Inter packet delay (bit6~7 = "11")
	//LFPS patch
	writeb(readb((void*)(XHCI_base+0x681A)) | 0x10, (void*)(XHCI_base+0x681A));  //LFPS patch  (bit4 = 1)

	//Ignore checking of max packet size=0 in endpoint context (configure endpoint).
	writeb(readb((void*)(XHCI_base+0x4209)) | 0x08, (void*)(XHCI_base+0x4209)); //for SS_BI_0
	writeb(readb((void*)(XHCI_base+0x4249)) | 0x08, (void*)(XHCI_base+0x4249)); //for SS_BI_1

	//force one queue option for IN direction
	writeb(readb((void*)(XHCI_base+0x4210)) | 0x01, (void*)(XHCI_base+0x4210));

#if defined(XHCI_DISABLE_COMPLIANCE)
	writeb(readb((void*)(XHCI_base+0x6817)) | 0x80, (void*)(XHCI_base+0x6817));
#endif
	
	//Bus Reset setting => default 50ms; T1=30; T2=20
#if defined(XHCI_BUSRESET_REG_OFFSET_CHG)
	writeb((readb((void*)(U3TOP_base+XHCI_NEW_BUSRESET_REG_OFFSET)) & 0xF0) | 0x8, (void*)(U3TOP_base+XHCI_NEW_BUSRESET_REG_OFFSET)); 	
#else
	writeb((u8)((readb((void*)(U3TOP_base+0x24*2)) & 0xF0) | 0x8), (void*)(U3TOP_base+0x24*2));    // [5] = reg_debug_mask to 1'b0
#endif

#if defined(XHCI_ENABLE_LASTDOWNZ)
	writeb(readb((void*)(U3TOP_base+0x12*2)) | 0x8, (void*)(U3TOP_base+0x12*2));  //check both last_down_z & data count enable
#endif

#if defined(XHCI_MIU1_SEL_BIT30)
   	writeb(readb((void*)(U3TOP_base+0x11*2-1)) | 0x2, (void*)(U3TOP_base+0x11*2-1));  //set reg_miu1_sel to check address bit 30
#endif

#if defined(XHCI_MIU_PROTECT_ENABLE)
        writeb(readb((void*)(U3TOP_base+0x21*2-1)) | 0x8, (void*)(U3TOP_base+0x21*2-1)); // enable miu protect ECO
#endif

#if defined (XHCI_ENABLE_LOOPBACK_ECO)
	writeb(readb((void*)(U3TOP_base+LOOPBACK_ECO_OFFSET))|LOOPBACK_ECO_BIT , (void*)(U3TOP_base+LOOPBACK_ECO_OFFSET));
#endif

#if defined(XHCI_ENABLE_HOTRESET_ECO)
	//Re-enable again to prevent from overwitting by sboot PPC function. Only for Edison.  
	writeb(readb((void*)(U3TOP_base+0xFF*2-1))|0x80, (void*)(U3TOP_base+0xFF*2-1));
#endif
	
#if defined(XHCI_ALLOW_LOOPBACK_MODE) //only for Nike, allow HW enter loopback mode
	writeb(readb((void*)(U3TOP_base+0xf8*2)) | 0x1, (void*)(U3TOP_base+0xf8*2));
#endif

#if (XHCI_ENABLE_TESTBUS)
	XHCI_enable_testbus((_MSTAR_USB_BASEADR+(0x1E00*2)), U3TOP_base, XHCI_base);
#endif
	
#ifdef XHCI_ENABLE_PPC
	XHCI_enable_PPC(U3TOP_base);
#endif

	// SW note U3Phy init done. 
	writeb(readb((void*)(U3TOP_base+0xEA*2)) | BIT0, (void*)(U3TOP_base+0xEA*2));

	// Don't wait trbp response when link not in U0
	writeb(readb((void*)(XHCI_base+0x4205)) | 0x80, (void*)(XHCI_base+0x4205));

}

#if defined(CONFIG_OF)
extern unsigned int irq_of_parse_and_map(struct device_node *node, int index);
#endif

static int xhci_mstar_plat_probe(struct platform_device *pdev)
{
	const struct hc_driver	*driver;
	struct xhci_hcd		*xhci;
	struct usb_hcd		*hcd;
	int			ret;
	int			irq;	
	unsigned int flag=0;

	if (usb_disabled())
		return -ENODEV;

	printk("xHCI_%x%04x \n", readb((void*)(_MSTAR_PM_BASE+0x1ECC*2)), readw((void*)(_MSTAR_PM_BASE+0x1ECE*2)));
	printk("Mstar-xhci H.W init\n");
#if defined(XHCI_ENABLE_DPDM_SWAP)
	flag |= EHCFLAG_DPDM_SWAP;
#endif
	Mstar_xhc_init(_MSTAR_U3UTMI_BASE, _MSTAR_XHCI_BASE,
			_MSTAR_U3TOP_BASE, _MSTAR_U3BC_BASE, flag);

	driver = &mstar_plat_xhci_driver;

#if defined(CONFIG_OF)
	if (!pdev->dev.platform_data)
	{
		printk(KERN_WARNING "[USB][XHC] worring.... no platform_data\n");
	}
	
	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
	
	/* TODO: dirty. mstar only can use 64bit mask */
	// if (!dev->dev.coherent_dma_mask)
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(64);
	
	/* try to get irq from device tree */
	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
#else
	irq = platform_get_irq(pdev, 0);
#endif

#if defined(ENABLE_IRQ_REMAP) && defined(MSTAR_XHCI_IRQ)
	irq = MSTAR_XHCI_IRQ;
#else
	if (irq < 0)
		return -ENODEV;
#endif

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = _MSTAR_XHCI_BASE;
	hcd->rsrc_len = 0x4000<<1;

	hcd->regs = (void *)(uintptr_t)(hcd->rsrc_start);	        	
	if (!hcd->regs) {
		dev_dbg(&pdev->dev, "error mapping memory\n");
		ret = -EFAULT;
		goto put_hcd;
	}

	hcd->xhci_base = _MSTAR_XHCI_BASE;
	hcd->u3top_base = _MSTAR_U3TOP_BASE;
	hcd->utmi_base = _MSTAR_U3UTMI_BASE;
	hcd->bc_base = _MSTAR_U3BC_BASE;
#ifdef XHCI_PHY_MS28
	#ifdef XHCI_2PORTS
	hcd->u3dphy_base[0] = _MSTAR_U3PHY_P0_DTOP_BASE;
	hcd->u3dphy_base[1] = _MSTAR_U3PHY_P1_DTOP_BASE;
	#else
	hcd->u3dphy_base[0] = _MSTAR_U3PHY_DTOP_BASE;
	#endif
#endif

#ifdef ENABLE_BATTERY_CHARGE
	usb_bc_enable(hcd, true);
#else
	#if defined(USB_NO_BC_FUNCTION)  //list for ICs before Edison 
	//do nothing.
	#else
	//Disable default setting.
	usb_bc_enable(hcd, false);
	#endif
#endif

#if _UTMI_PWR_SAV_MODE_ENABLE
	usb_power_saving_enable(hcd, true);
#endif

	hcd->lock_usbreset=__SPIN_LOCK_UNLOCKED(hcd->lock_usbreset);

	ret = usb_add_hcd(hcd, (unsigned int)irq, IRQF_DISABLED /* | IRQF_SHARED */);
	if (ret)
		goto put_hcd;

	/* USB 2.0 roothub is stored in the platform_device now. */
	hcd = dev_get_drvdata(&pdev->dev);
	xhci = hcd_to_xhci(hcd);
	xhci->shared_hcd = usb_create_shared_hcd(driver, &pdev->dev,
			dev_name(&pdev->dev), hcd);
	if (!xhci->shared_hcd) {
		ret = -ENOMEM;
		goto dealloc_usb2_hcd;
	}

	/*
	 * Set the xHCI pointer before xhci_plat_setup() (aka hcd_driver.reset)
	 * is called by usb_add_hcd().
	 */
	*((struct xhci_hcd **) xhci->shared_hcd->hcd_priv) = xhci;

	xhci->shared_hcd->xhci_base = _MSTAR_XHCI_BASE;
	xhci->shared_hcd->u3top_base = _MSTAR_U3TOP_BASE;
	xhci->shared_hcd->utmi_base = _MSTAR_U3UTMI_BASE;	
	xhci->shared_hcd->bc_base = _MSTAR_U3BC_BASE;	
	xhci->shared_hcd->lock_usbreset=__SPIN_LOCK_UNLOCKED(xhci->shared_hcd->lock_usbreset);
#ifdef XHCI_PHY_MS28
	#ifdef XHCI_2PORTS
		xhci->shared_hcd->u3dphy_base[0] = _MSTAR_U3PHY_P0_DTOP_BASE;
		xhci->shared_hcd->u3dphy_base[1] = _MSTAR_U3PHY_P1_DTOP_BASE;
	#else
		xhci->shared_hcd->u3dphy_base[0] = _MSTAR_U3PHY_DTOP_BASE;
	#endif
#endif

	ret = usb_add_hcd(xhci->shared_hcd, (unsigned int)irq, IRQF_DISABLED /* | IRQF_SHARED */);
	if (ret)
		goto put_usb3_hcd;

	return 0;

put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);

dealloc_usb2_hcd:
	usb_remove_hcd(hcd);

put_hcd:
	usb_put_hcd(hcd);

	return ret;
}

static int xhci_mstar_plat_remove(struct platform_device *dev)
{
	struct usb_hcd	*hcd = platform_get_drvdata(dev);
	struct xhci_hcd	*xhci = hcd_to_xhci(hcd);

	usb_remove_hcd(xhci->shared_hcd);
	usb_put_hcd(xhci->shared_hcd);

	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);
	kfree(xhci);

	return 0;
}

#ifdef	CONFIG_PM
static int xhci_hcd_mstar_drv_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct usb_hcd *hcd;
	struct xhci_hcd *xhci;

	printk("xhci_hcd_mstar_drv_suspend \n");

	hcd = platform_get_drvdata(pdev);
	xhci = hcd_to_xhci(hcd);
	
	return xhci_suspend(xhci);
}

static int xhci_hcd_mstar_drv_resume(struct platform_device *pdev)
{
	unsigned int flag=0;
	struct xhci_hcd *xhci;
	int	   retval = 0;
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	printk("xhci_hcd_mstar_drv_resume \n");
	
#if defined(XHCI_ENABLE_DPDM_SWAP)
	flag |= EHCFLAG_DPDM_SWAP;
#endif
	Mstar_xhc_init(_MSTAR_U3UTMI_BASE, _MSTAR_XHCI_BASE,
			_MSTAR_U3TOP_BASE, _MSTAR_U3BC_BASE, flag);    

#ifdef ENABLE_BATTERY_CHARGE
	usb_bc_enable(hcd, true);
#else
	#if defined(USB_NO_BC_FUNCTION)  //list for ICs before Edison 
	//do nothing.
	#else
	//Disable default setting.
	usb_bc_enable(hcd, false);
	#endif
#endif

	xhci = hcd_to_xhci(hcd);
	retval = xhci_resume(xhci, false);
	if (retval) {
		printk(" xhci_resume FAIL : -0x%x !!", -retval); 
		return retval; 
	}        
	return 0;
}
#endif

#if defined(CONFIG_OF)
static struct of_device_id mstar_xhci_of_device_ids[] = {
	{.compatible = "Mstar-xhci-1"},
	{},
};
#endif

static struct platform_driver xhci_mstar_driver = {

	.probe =	xhci_mstar_plat_probe,
	.remove =	xhci_mstar_plat_remove,

#ifdef	CONFIG_PM
	.suspend	= xhci_hcd_mstar_drv_suspend,
	.resume		= xhci_hcd_mstar_drv_resume,    
#endif

	.driver = {
		.name   = "Mstar-xhci-1",
#if defined(CONFIG_OF)
		.of_match_table = mstar_xhci_of_device_ids,
#endif
	},
};
MODULE_ALIAS("platform:mstar-xhci-hcd");

int xhci_register_plat(void)
{
	return platform_driver_register(&xhci_mstar_driver);
}

void xhci_unregister_plat(void)
{
	platform_driver_unregister(&xhci_mstar_driver);
}
