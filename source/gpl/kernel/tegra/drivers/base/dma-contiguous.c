/*
 * Contiguous Memory Allocator for DMA mapping framework
 * Copyright (c) 2010-2011 by Samsung Electronics.
 * Written by:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *	Michal Nazarewicz <mina86@mina86.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License or (at your optional) any later version of the license.
 */

/* for using pr_info */
#define pr_fmt(fmt) "\033[31mFunction = %s, Line = %d, cma: \033[m" fmt , __PRETTY_FUNCTION__, __LINE__

#ifdef CONFIG_CMA_DEBUG
#ifndef DEBUG
#  define DEBUG
#endif
#endif

#include <asm/page.h>
#include <asm/dma-contiguous.h>

#include <linux/buffer_head.h>
#include <linux/memblock.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/mutex.h>
#include <linux/page-isolation.h>
#include <linux/sizes.h>
#include <linux/slab.h>
#include <linux/swap.h>
#include <linux/mm_types.h>
#include <linux/dma-contiguous.h>
#include "mdrv_types.h"
#include "mdrv_system.h"
#include <linux/dma-mapping.h>

#include <asm/tlbflush.h>
#include <asm/cacheflush.h>
#include <asm/outercache.h>
#include <linux/vmstat.h>

#ifdef CONFIG_MP_ION_PATCH_MSTAR
	//move to dma-contiguous.h
#else
struct cma {
	unsigned long	base_pfn;
	unsigned long	count;
	unsigned long	*bitmap;
	struct mutex    lock;

#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
    struct cma_measurement *cma_measurement_ptr;
#endif
};
#endif

struct cma *dma_contiguous_default_area;

#ifdef CONFIG_CMA_SIZE_MBYTES
#define CMA_SIZE_MBYTES CONFIG_CMA_SIZE_MBYTES
#else
#define CMA_SIZE_MBYTES 0
#endif

/*
 * Default global CMA area size can be defined in kernel's .config.
 * This is usefull mainly for distro maintainers to create a kernel
 * that works correctly for most supported systems.
 * The size can be set in bytes or as a percentage of the total memory
 * in the system.
 *
 * Users, who want to set the size of global CMA area for their system
 * should use cma= kernel parameter.
 */
static const phys_addr_t size_bytes = CMA_SIZE_MBYTES * SZ_1M;
static phys_addr_t size_cmdline = -1;

#ifdef CONFIG_MP_CMA_PATCH_CMA_MSTAR_DRIVER_BUFFER
/* To store every mstar driver cma_buffer size, including default cma_buffer with index is 0 */
struct CMA_BootArgs_Config cma_config[MAX_CMA_AREAS];
struct device mstar_cma_device[MAX_CMA_AREAS];
int mstar_driver_boot_cma_buffer_num = 0;


EXPORT_SYMBOL(cma_config);
EXPORT_SYMBOL(mstar_cma_device);
EXPORT_SYMBOL(mstar_driver_boot_cma_buffer_num);

/*
  * if  start address has been specified, only convert it to cpu bus address;
  * else, find start address
  */
static bool GetReservedPhysicalAddr(unsigned char miu, unsigned long *start, 
    unsigned long *size)

{
    unsigned long alignstart = 0, alignfactor = pageblock_nr_pages*PAGE_SIZE;

    if(miu < 0 || miu > 3 || *size == 0)
        goto GetReservedPhysicalAddr_Fail;
    
    if(*start != CMA_HEAP_MIUOFFSET_NOCARE)
    {
        if(!IS_ALIGNED(*start, alignfactor))
            goto GetReservedPhysicalAddr_Fail;
    }

    if(!IS_ALIGNED(*size, alignfactor))
        goto GetReservedPhysicalAddr_Fail;
    
    if(*start == CMA_HEAP_MIUOFFSET_NOCARE)
        return true;
    
    switch (miu)
    {
        case 0:
        {            
            alignstart = *start + ARM_MIU0_BUS_BASE;          
            break;
        }
        case 1:
        {            
            alignstart = *start + ARM_MIU1_BUS_BASE;           
            break;
        }
        case 2:
        {            
            alignstart = *start + ARM_MIU2_BUS_BASE;         
            break;
        }
        case 3:
        {            
            alignstart = *start + ARM_MIU3_BUS_BASE;           
            break;
        }
        default:
            goto GetReservedPhysicalAddr_Fail;
    }    

    *start = alignstart;
    return true;

GetReservedPhysicalAddr_Fail:
    printk(CMA_ERR "error: invalid parameters\n");
    *start = 0;
    *size = 0;
    return false;
}

extern phys_addr_t arm_lowmem_limit;
static unsigned long _find_in_range(phys_addr_t start, phys_addr_t end, phys_addr_t size, phys_addr_t alignfactor)
{
    phys_addr_t ret = 0;

    if((arm_lowmem_limit > start) && (arm_lowmem_limit < end))
    {
		/* find from lowmem first*/
        ret = memblock_find_in_range(start, arm_lowmem_limit, size, alignfactor);
        if(ret > 0)
		{
			//printk("\033[35mFunction = %s, Line = %d, find cma_buffer range from 0x%X to 0x%X\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, arm_lowmem_limit);
            return ret;
		}

		/* find from highmem */
        ret = memblock_find_in_range(arm_lowmem_limit, end, size, alignfactor);
        if(ret > 0)
		{
			//printk("\033[35mFunction = %s, Line = %d, find cma_buffer range from 0x%X to 0x%X\033[m\n", __PRETTY_FUNCTION__, __LINE__, arm_lowmem_limit, end);
            return ret;      
		}
    }
    else if(end > start)
    {
        ret = memblock_find_in_range(start, end, size, alignfactor);
        if(ret > 0)
		{
			//printk("\033[35mFunction = %s, Line = %d, find cma_buffer range from 0x%X to 0x%X\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, end);
            return ret;
		}
    }

	printk(CMA_ERR "\033[35mFunction = %s, Line = %d, ERROR!!\033[m\n", __PRETTY_FUNCTION__, __LINE__);
    return ret;
}

static unsigned long find_start_addr(unsigned char miu, unsigned long size)
{
    unsigned long ret = 0;
    unsigned long alignfactor = pageblock_nr_pages*PAGE_SIZE;

    if(miu < 0 || miu > 3)
        return 0;
	
    switch (miu)
    {
        case 0:
        {
            ret = _find_in_range(ARM_MIU0_BUS_BASE, ARM_MIU1_BUS_BASE, size, alignfactor);		 
            break;
        }
        case 1:
        {
            ret = _find_in_range(ARM_MIU1_BUS_BASE, ARM_MIU2_BUS_BASE, size, alignfactor);        
            break;
        }
        case 2:
        {
            ret = _find_in_range(ARM_MIU2_BUS_BASE, ARM_MIU3_BUS_BASE, size, alignfactor);       
            break;
        }
        case 3:
        {
            ret = _find_in_range(ARM_MIU3_BUS_BASE, CMA_HEAP_MIUOFFSET_NOCARE, size, alignfactor);        
            break;
        }
        default:
            return 0;
    }  

    return ret;
}

static bool parse_heap_config(char *cmdline, struct CMA_BootArgs_Config * heapconfig)
{
    char *option;
    int leng = 0;
    bool has_start = false;

    if(cmdline == NULL)
        goto INVALID_HEAP_CONFIG;

    option = strstr(cmdline, ",");
    leng = (int)(option - cmdline);
    if(leng > (CMA_HEAP_NAME_LENG-1))
        leng = CMA_HEAP_NAME_LENG -1;

    strncpy(heapconfig->name, cmdline, leng);
    heapconfig->name[leng] = '\0';

    option = strstr(cmdline, "st=");
    if(option != NULL)
        has_start = true;

    option = strstr(cmdline, "sz=");
    if(option == NULL)
        goto INVALID_HEAP_CONFIG;

    option = strstr(cmdline, "hid=");
    if(option == NULL)
        goto INVALID_HEAP_CONFIG;


    option = strstr(cmdline, "miu=");
    if(option == NULL)
        goto INVALID_HEAP_CONFIG;

    if(has_start)
    {
        sscanf(option, "miu=%d,hid=%d,sz=%lx,st=%lx", &heapconfig->miu, 
        &heapconfig->pool_id, &heapconfig->size, &heapconfig->start);    
    }
    else
    {
        sscanf(option, "miu=%d,hid=%d,sz=%lx", &heapconfig->miu, 
        &heapconfig->pool_id, &heapconfig->size);

        heapconfig->start = CMA_HEAP_MIUOFFSET_NOCARE;  
    }

    if(!GetReservedPhysicalAddr(heapconfig->miu, &heapconfig->start, &heapconfig->size))
        goto INVALID_HEAP_CONFIG;

    return true;

INVALID_HEAP_CONFIG:
	heapconfig->size = 0;
	return false;
}

int __init setup_cma0_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma0 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma1_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma1 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma2_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma2 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma3_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma3 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma4_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma4 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma5_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma5 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma6_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma6 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma7_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma7 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma8_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma8 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_cma9_info(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: cma9 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

early_param("CMA0", setup_cma0_info);
early_param("CMA1", setup_cma1_info);
early_param("CMA2", setup_cma2_info);
early_param("CMA3", setup_cma3_info);
early_param("CMA4", setup_cma4_info);
early_param("CMA5", setup_cma5_info);
early_param("CMA6", setup_cma6_info);
early_param("CMA7", setup_cma7_info);
early_param("CMA8", setup_cma8_info);
early_param("CMA9", setup_cma9_info);

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
#define MSTAR_MAX_MIU_CNT 3
struct device *zram_cma_device[MSTAR_MAX_MIU_CNT];	/* to get to cma_buffer by dev->cma */
int zram_cma_page_cnt[MSTAR_MAX_MIU_CNT] = {0};
unsigned long zram_cma_start[MSTAR_MAX_MIU_CNT] = {0}; /* to save zram_cma searching bitmap start index, this can save timecost by passing busy page */
int zram_device_cnt = 0;

int __init setup_zram_miu0_buffer(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: zram_miu0 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_zram_miu1_buffer(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: zram_miu1 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

int __init setup_zram_miu2_buffer(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))        
        printk(CMA_ERR "error: zram_miu2 args invalid\n");    
    else
        mstar_driver_boot_cma_buffer_num++;

    return 0;
}

early_param("ZRAM_MIU0", setup_zram_miu0_buffer);
early_param("ZRAM_MIU1", setup_zram_miu1_buffer);
early_param("ZRAM_MIU2", setup_zram_miu2_buffer);
#endif

#ifdef CONFIG_MP_CMA_PATCH_PCI_ALLOC_FREE_WITH_CMA
struct device *pci_cma_device;	/* to get to cma_buffer by dev->cma, and let pci-e device to use the cma (pci-e->cma = dev->cma) */

int __init setup_pci_cma_buffer(char *cmdline)
{
    if(!parse_heap_config(cmdline, &cma_config[mstar_driver_boot_cma_buffer_num]))
        printk(CMA_ERR "error: pci_cma args invalid\n");
    else
	{
		if(cma_config[mstar_driver_boot_cma_buffer_num].miu != 0)	/* pci device can only access miu0 */
		{
			printk(CMA_ERR "error: pci_cma is set to miu %d(cmdline is %s)\n", cma_config[mstar_driver_boot_cma_buffer_num].miu, cmdline);
			BUG();
		}

		printk(CMA_ERR "the pci_cma is set @0x%lX to 0x%lX", cma_config[mstar_driver_boot_cma_buffer_num].start, (cma_config[mstar_driver_boot_cma_buffer_num].start + cma_config[mstar_driver_boot_cma_buffer_num].size));
		mstar_driver_boot_cma_buffer_num++;
	}

	return 0;
}

early_param("PCIE_CMA_MIU0", setup_pci_cma_buffer);
EXPORT_SYMBOL(pci_cma_device);
#endif
#endif

#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
extern signed long long Show_Diff_Time(char *caller, ktime_t start_time, bool print);
#endif

struct cma *pfn_to_cma(unsigned long start)
{
	struct device *search_mstar_cma_device = &mstar_cma_device[0];
	struct cma *device_cma;

	int dma_declare_index = 0;

	while(dma_declare_index < mstar_driver_boot_cma_buffer_num)
	{
		device_cma = dev_get_cma_area(search_mstar_cma_device);
		//printk("\033[35mFunction = %s, Line = %d, device_cma start from 0x%lX to 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, device_cma->base_pfn, (device_cma->base_pfn + device_cma->count));

		if( (device_cma->base_pfn <= start)	&& (start < (device_cma->base_pfn + device_cma->count)) )
		{
			//printk("\033[35mFunction = %s, Line = %d, get cma!!\033[m\n", __PRETTY_FUNCTION__, __LINE__);
			return device_cma;
		}
		
		dma_declare_index++;
        search_mstar_cma_device++;
	}

	//printk("\033[35mFunction = %s, Line = %d, can not get cma\033[m\n", __PRETTY_FUNCTION__, __LINE__);
	return NULL;
}

static int __init early_cma(char *p)
{
    pr_debug("%s(%s)\n", __func__, p);
    size_cmdline = memparse(p, &p);
    return 0;
}
early_param("cma", early_cma);

#ifdef CONFIG_CMA_SIZE_PERCENTAGE

static phys_addr_t __init __maybe_unused cma_early_percent_memory(void)
{
	struct memblock_region *reg;
	unsigned long total_pages = 0;

	/*
	 * We cannot use memblock_phys_mem_size() here, because
	 * memblock_analyze() has not been called yet.
	 */
	for_each_memblock(memory, reg)
		total_pages += memblock_region_memory_end_pfn(reg) -
			       memblock_region_memory_base_pfn(reg);

	return (total_pages * CONFIG_CMA_SIZE_PERCENTAGE / 100) << PAGE_SHIFT;
}

#else

static inline __maybe_unused phys_addr_t cma_early_percent_memory(void)
{
	return 0;
}

#endif

static int count_cma_area_free_page_num(struct cma *counted_cma)
{
	int count_cma_free_page_count       = 0;
	int count_cma_free_start			= 0;
	int count_cma_bitmap_start_zero    	= 0;
	int count_cma_bitmap_end_zero    	= 0;

	int debug = 0;

	printk(CMA_DEBUG "\033[32mcma_area having \033[m");
	for(;;)
	{
		count_cma_bitmap_start_zero = find_next_zero_bit(counted_cma->bitmap, counted_cma->count, count_cma_free_start);

		if(count_cma_bitmap_start_zero >= counted_cma->count)
			break;
		if(debug)
			printk(CMA_DEBUG "######### count_cma_bitmap_start_zero=%x \n",count_cma_bitmap_start_zero);
		count_cma_free_start = count_cma_bitmap_start_zero + 1;
		
		count_cma_bitmap_end_zero = find_next_bit(counted_cma->bitmap, counted_cma->count, count_cma_free_start);

		if(debug)
			printk(CMA_DEBUG "######### count_cma_bitmap_end_zero=%x \n",count_cma_bitmap_end_zero);

		if(count_cma_bitmap_end_zero >= counted_cma->count)
		{
			count_cma_free_page_count += (counted_cma->count - count_cma_bitmap_start_zero);
			break;
		}

		count_cma_free_page_count += (count_cma_bitmap_end_zero - count_cma_bitmap_start_zero);

		count_cma_free_start = count_cma_bitmap_end_zero + 1;
		
		if(count_cma_free_start >= counted_cma->count)
			break;
	}
	printk(CMA_DEBUG "\033[32m%d free pages\033[m\n", count_cma_free_page_count);

	return count_cma_free_page_count;
}

static struct cma_reserved {
	phys_addr_t start;
	unsigned long size;
	struct device *dev;
} cma_reserved[MAX_CMA_AREAS] __initdata;
static unsigned cma_reserved_count __initdata;
#ifdef CONFIG_MP_CMA_PATCH_CMA_DYNAMIC_STRATEGY
unsigned int VDEC_CMA_size;
#endif
/**
 * dma_contiguous_reserve() - reserve area for contiguous memory handling
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory.
 */
void __init dma_contiguous_reserve(phys_addr_t limit)
{
	phys_addr_t selected_size = 0;
    int ret = 0;

#ifdef CONFIG_MP_CMA_PATCH_CMA_MSTAR_DRIVER_BUFFER
	int dma_declare_index = 0;

    /*
     *  mstar_cma_device store the device with successfully parsed cma buffer info
     */
	struct device *declare_mstar_cma_device = &mstar_cma_device[0];
#endif

	pr_info("%s(limit 0x%08lX)\n", __func__, (unsigned long)limit);

	if(size_cmdline != -1)
	{
		selected_size = size_cmdline;
	}
	else
	{
#ifdef CONFIG_CMA_SIZE_SEL_MBYTES
		selected_size = size_bytes;	// set in .config
#elif defined(CONFIG_CMA_SIZE_SEL_PERCENTAGE)
		selected_size = cma_early_percent_memory();	// set in .config
#elif defined(CONFIG_CMA_SIZE_SEL_MIN)
		selected_size = min(size_bytes, cma_early_percent_memory());	// both CONFIG_CMA_SIZE_MBYTES and CONFIG_CMA_SIZE_PERCENTAGE can be set in .config
#elif defined(CONFIG_CMA_SIZE_SEL_MAX)
		selected_size = max(size_bytes, cma_early_percent_memory());
#endif
	}

	if(selected_size)
	{
		pr_info("\033[35mreserving %ld MiB for global area\033[m\n", (unsigned long)selected_size / SZ_1M);
		ret = dma_declare_contiguous(NULL, selected_size, 0, limit);
       
#ifdef CONFIG_MP_CMA_PATCH_CMA_MSTAR_DRIVER_BUFFER
        if(ret)
        {
            printk(CMA_ERR "error: declare default cma config fail\n");
            BUG_ON(ret);
        }
#endif
    }

#ifdef CONFIG_MP_CMA_PATCH_CMA_MSTAR_DRIVER_BUFFER
	/*
	 * add cma buffer from bootargs, and assigne it to the specific device
	 * cma buffer is not limited in low memory, also can locate in high memory 
	 */
    
	while(dma_declare_index < mstar_driver_boot_cma_buffer_num)
	{
		pr_info("\033[35mreserving %ld MiB for mstar_driver(%s, pool_id is %d)\033[m\n", cma_config[dma_declare_index].size / SZ_1M, cma_config[dma_declare_index].name, cma_config[dma_declare_index].pool_id);
#ifdef CONFIG_MP_CMA_PATCH_CMA_DYNAMIC_STRATEGY 
		if(strstr(cma_config[dma_declare_index].name, "VDEC_XC1") != NULL){
			VDEC_CMA_size = cma_config[dma_declare_index].size / SZ_1M;
			pr_info("\033[32m VDEC_CMA_size = %d \033[m\n", VDEC_CMA_size);
		}
#endif            
        BUG_ON(cma_config[dma_declare_index].size == 0);
        if(CMA_HEAP_MIUOFFSET_NOCARE == cma_config[dma_declare_index].start)
        {
			pr_info("find cma_buffer start addr(@miu%d) for %s\033[m\n", cma_config[dma_declare_index].miu, cma_config[dma_declare_index].name);
			cma_config[dma_declare_index].start = find_start_addr(cma_config[dma_declare_index].miu, cma_config[dma_declare_index].size);

			BUG_ON(cma_config[dma_declare_index].start == 0);
        }
         
        //check if the reserved memory allocated across 2 memory zones: a part of it in normal zone, the other in high memory
        if(cma_config[dma_declare_index].start > 0)
        {
            if((cma_config[dma_declare_index].start < arm_lowmem_limit)
                && (cma_config[dma_declare_index].start + cma_config[dma_declare_index].size > arm_lowmem_limit))
            {
                printk(CMA_ERR "Warning: reserved memory allocated across 2 memory zones!!!=========\n");
				BUG_ON(1);
            }
        }

        ret = dma_declare_contiguous(declare_mstar_cma_device, cma_config[dma_declare_index].size, cma_config[dma_declare_index].start, limit);
		declare_mstar_cma_device->coherent_dma_mask = ~0;	// not sure, this mask will be used in __dma_alloc while doing cma_alloc, 0xFFFFFFFF is for NULL device

        if(ret)
        {
            printk(CMA_ERR "error: reserve memory fail, start %lu size %lu\n", 
            cma_config[dma_declare_index].start, cma_config[dma_declare_index].size);
            BUG_ON(ret);
        }

		declare_mstar_cma_device->init_name = cma_config[dma_declare_index].name;

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
		if(strstr(cma_config[dma_declare_index].name, "ZRAM_BUFFER") != NULL)
		{
			printk(CMA_DEBUG "\033[31mFunction = %s, Line = %d, assign zram_miu_%d device\033[m\n", __PRETTY_FUNCTION__, __LINE__, cma_config[dma_declare_index].miu);
			
			zram_cma_device[cma_config[dma_declare_index].miu] = declare_mstar_cma_device;
			zram_cma_page_cnt[cma_config[dma_declare_index].miu] = cma_config[dma_declare_index].size >> PAGE_SHIFT;
			
			printk(CMA_DEBUG "\033[31mFunction = %s, Line = %d, its name is %s\033[m\n", __PRETTY_FUNCTION__, __LINE__, zram_cma_device[cma_config[dma_declare_index].miu]->init_name);
			printk(CMA_DEBUG "\033[31mFunction = %s, Line = %d, zram_cma_page_cnt[%d] is %d pages\033[m\n", __PRETTY_FUNCTION__, __LINE__, zram_device_cnt, zram_cma_page_cnt[zram_device_cnt]);
			zram_device_cnt++;
		}
#endif

#ifdef CONFIG_MP_CMA_PATCH_PCI_ALLOC_FREE_WITH_CMA
		if(strstr(cma_config[dma_declare_index].name, "PCIE_CMA_MIU") != NULL)
		{
			printk(CMA_ERR "\033[31mFunction = %s, Line = %d, assign pci_miu_%d device\033[m\n", __PRETTY_FUNCTION__, __LINE__, cma_config[dma_declare_index].miu);
			pci_cma_device = declare_mstar_cma_device;
			printk(CMA_ERR "\033[31mFunction = %s, Line = %d, its name is %s\033[m\n", __PRETTY_FUNCTION__, __LINE__, pci_cma_device->init_name);
		}
#endif
		dma_declare_index++;
        declare_mstar_cma_device++;
	}
#endif
};

static DEFINE_MUTEX(cma_mutex);

static __init int cma_activate_area(unsigned long base_pfn, unsigned long count)
{
	unsigned long pfn = base_pfn;
	unsigned i = count >> pageblock_order;
	struct zone *zone;

	WARN_ON_ONCE(!pfn_valid(pfn));
	zone = page_zone(pfn_to_page(pfn));
	printk(CMA_DEBUG "\033[35mFunction = %s, cma_start pfn: 0x%X length: 0x%X is in zone %s\033[m\n", __PRETTY_FUNCTION__, (unsigned int)pfn, (unsigned int)count, zone->name);

	do {
		unsigned j;
		base_pfn = pfn;

		/* check if all pages in this pageblock are vaild and in the same zone i
		 * pageblock_nr_pages is 1024 pages
		 */
		for (j = pageblock_nr_pages; j; --j, pfn++) {
			WARN_ON_ONCE(!pfn_valid(pfn));
			if (page_zone(pfn_to_page(pfn)) != zone)
				return -EINVAL;
		}
		//printk("\033[35mFunction = %s, Line = %d, pfn is 0x%X\033[m\n", __PRETTY_FUNCTION__, __LINE__, (unsigned int)pfn);
		//printk("\033[35mFunction = %s, Line = %d, base_pfn is 0x%X\033[m\n", __PRETTY_FUNCTION__, __LINE__, (unsigned int)base_pfn);
		init_cma_reserved_pageblock(pfn_to_page(base_pfn));
	} while (--i);

#ifdef CONFIG_MP_CMA_PATCH_CMA_AGGRESSIVE_ALLOC
	adjust_managed_cma_page_count(zone, count); 
#endif
	
	return 0;
}

static void clear_cma_bitmap(struct cma *cma, unsigned long pfn, int count)
{
       mutex_lock(&cma->lock);
       bitmap_clear(cma->bitmap, pfn - cma->base_pfn, count);
       mutex_unlock(&cma->lock);
}

static __init struct cma *cma_create_area(unsigned long base_pfn,
				     unsigned long count)
{
	int bitmap_size = BITS_TO_LONGS(count) * sizeof(long);	// count is page_num, BITS_TO_LONGS(count) coverts count to ~ long size. bitmap_size is ~ byte the bitmap needs
	struct cma *cma;
	int ret = -ENOMEM;

	pr_debug("%s(base %08lx, count %lx, bitmap_size %d(bytes))\n", __func__, base_pfn, count, bitmap_size);

	cma = kmalloc(sizeof *cma, GFP_KERNEL);
	if (!cma)
		return ERR_PTR(-ENOMEM);

	cma->base_pfn = base_pfn;
	cma->count = count;
	cma->bitmap = kzalloc(bitmap_size, GFP_KERNEL);

	if (!cma->bitmap)
		goto no_mem;

	ret = cma_activate_area(base_pfn, count);
	if (ret)
		goto error;

	mutex_init(&cma->lock);
	pr_debug("%s: returned %p\n", __func__, (void *)cma);
	return cma;

error:
	kfree(cma->bitmap);
no_mem:
	kfree(cma);
	return ERR_PTR(ret);
}

// cma_reserved_count may not be 0, this means some cma buffer is pre-reserved, cma_init_reserved_areas will clear these pre-reserved areas, and mark as reserved cma_buffer

static int __init cma_init_reserved_areas(void)
{
	struct cma_reserved *r = cma_reserved;
	unsigned i = cma_reserved_count;

	pr_debug("%s()\n", __func__);

	for (; i; --i, ++r) {
		struct cma *cma;
		pr_info("init No-%d cma_buffer\n", (cma_reserved_count - i + 1));
		cma = cma_create_area(PFN_DOWN(r->start),
				      r->size >> PAGE_SHIFT);
		if (!IS_ERR(cma))
			dev_set_cma_area(r->dev, cma);
		else
		{
		    pr_info("cma_create_area No-%d cma struct fail\n", (cma_reserved_count - i + 1));
		    BUG_ON(1);
		}
	}
	return 0;
}
core_initcall(cma_init_reserved_areas);

/**
 * dma_declare_contiguous() - reserve area for contiguous memory handling
 *			      for particular device
 * @dev:   Pointer to device structure.
 * @size:  Size of the reserved memory.
 * @base:  Start address of the reserved memory (optional, 0 for any).
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory for specified device. It should be
 * called by board specific code when early allocator (memblock or bootmem)
 * is still activate.
 */
int __init dma_declare_contiguous(struct device *dev, phys_addr_t size,
				  phys_addr_t base, phys_addr_t limit)
{
	struct cma_reserved *r = &cma_reserved[cma_reserved_count];
	phys_addr_t alignment;
	phys_addr_t addr;

	pr_debug("%s(size %lx, base %08lx, limit %08lx)\n", __func__,
		 (unsigned long)size, (unsigned long)base,
		 (unsigned long)limit);

	pr_info("cma_reserved_count is %d\033[m\n", cma_reserved_count);
	pr_info("base is 0x%lX\n", (unsigned long)base);
	pr_info("size is 0x%lX\n", (unsigned long)size);

	/* Sanity checks */
	if (cma_reserved_count == ARRAY_SIZE(cma_reserved)) {
		pr_err("Not enough slots for CMA reserved regions!\n");
		return -ENOSPC;
	}

	if (!size)
		return -EINVAL;

	/* Sanitise input arguments */
	alignment = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);	// 4MB alignment
	base = ALIGN(base, alignment);	// to next 4MB address, ex: 0x20200000 -> 0x20400000
	size = ALIGN(size, alignment);	// 							  0x200000 ->   0x400000
	limit &= ~(alignment - 1);

	/* Reserve memory */
	if(base)
	{
		/* here means you are really want to reserve a memory region 
		 * from "base" to "base + size", so we will not search a memory region here.
		 * Instead, we directly reserve the memory from "base" to "base + size"
		 */

		/* first check if already in reserved region, 
		 * then add it to reserved region. if the memory region
		 * from "base" to "base + size" is already in a reserved region
		 * then declare will be failed
		 */
		if (memblock_is_region_reserved(base, size) || memblock_reserve(base, size) < 0)
		{
			printk(KERN_ERR "\033[35mFunction = %s, declare cma_buffer with base, but it can not be reserved\033[m\n", __PRETTY_FUNCTION__);
			base = -EBUSY;
			goto err;
		}
	}
	else
	{
		/*
		 * Use __memblock_alloc_base() since
		 * memblock_alloc_base() panic()s.
		 */

		/* Walks over free (memory && !reserved) areas of memblock in reverse to find memory and reserve it*/
		addr = __memblock_alloc_base(size, alignment, limit);
		if (!addr) {
			base = -ENOMEM;
			goto err;
		} else {
			base = addr;
		}
	}

	/*
	 * Each reserved area must be initialised later, when more kernel
	 * subsystems (like slab allocator) are available.
	 */
	r->start = base;
	r->size = size;
	r->dev = dev;
	cma_reserved_count++;
	pr_info("successfully reserved %ld MiB at 0x%08lX\n", (unsigned long)size / SZ_1M,
		(unsigned long)base);

	/* Architecture specific contiguous memory fixup. */
	dma_contiguous_early_fixup(base, size);
	return 0;
err:
	pr_err("CMA: failed to reserve %ld MiB\n", (unsigned long)size / SZ_1M);
	return base;
}

static int __dma_update_pte(pte_t *pte, pgtable_t token, unsigned long addr,
			    void *data)
{
	struct page *page = virt_to_page(addr);
	pgprot_t prot = *(pgprot_t *)data;

#ifdef CONFIG_ARM64
	set_pte(pte, mk_pte(page, prot));
#else
	set_pte_ext(pte, mk_pte(page, prot), 0);
#endif
	return 0;
}

static void __dma_remap(struct page *page, size_t size, pgprot_t prot)
{
	unsigned long start = (unsigned long) page_address(page);
	unsigned end = start + size;
	int err;

	err = apply_to_page_range(&init_mm, start,
		size, __dma_update_pte, &prot);
	if (err)
		pr_err("***%s: error=%d, pfn=%lx\n", __func__,
			err, page_to_pfn(page));
	dsb();
	flush_tlb_kernel_range(start, end);
}

void __dma_flush_buffer(struct page *page, size_t size)
{
	void *ptr;
    if (!page)
        return;
	ptr = page_address(page);
	if (ptr) {
		dmac_flush_range(ptr, ptr + size);
		outer_flush_range(__pa(ptr), __pa(ptr) + size);
	}
}

void __dma_clear_buffer2(struct page *page, size_t size)
{
	void *ptr;
    if (!page)
        return;
	ptr = page_address(page);
	if (ptr) {
		memset(ptr, 0, size);
		dmac_flush_range(ptr, ptr + size);
		outer_flush_range(__pa(ptr), __pa(ptr) + size);
	}
}

struct page *dma_alloc_at_from_contiguous(struct device *dev, int count,
				       unsigned int align, phys_addr_t at_addr)
{
	unsigned long mask, pfn, pageno, start = 0;
	struct cma *cma = dev_get_cma_area(dev);
	struct page *page = NULL;
	int ret;
	unsigned long start_pfn = __phys_to_pfn(at_addr);
#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
	struct cma_measurement *cma_measurement_data = NULL;
#endif

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
	int get_start = 0;
	int should_refind = 1;
	int remain_free_page_cnt = 0;
#endif

	if (!cma || !cma->count)
		return NULL;

	if (align > CONFIG_CMA_ALIGNMENT)
	{
		// if size > 2^8 pages ==> align will be > 8
		align = CONFIG_CMA_ALIGNMENT;
	}

	pr_debug("%s(cma %p, alloc %d pages, align %d)\n", __func__, (void *)cma, count, align);

	if (!count)
		return NULL;

	mask = (1 << align) - 1;

	if (start_pfn && start_pfn < cma->base_pfn)
		return NULL;
	start = start_pfn ? start_pfn - cma->base_pfn : start;		// if having start_pfn, start = start_pfn - cma->base_pfn

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
	/* for zram's frequent allocation, we dont always want to find free_cma_area from the cma_start page(the begin page of cma)
	 * we now change the cma_start page, however, the start_pfn is still 0, so all check condition will be same
	 */
	for(get_start = 0; get_start < zram_device_cnt; get_start++)
	{
		if(dev && (dev == zram_cma_device[get_start]))
		{
			start = zram_cma_start[get_start];
			break;
		}
	}
#endif

	if(count >= 10)
	{
		printk(CMA_DEBUG "\033[31m%s(alloc %d pages, at_addr 0x%X, start pfn 0x%X)\033[m\n", __func__, count, (unsigned int)at_addr, (unsigned int)start_pfn);
		printk(CMA_DEBUG "\033[35mFunction = %s, Line = %d, find bit_map from 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, start);
		printk(CMA_DEBUG "\033[32m[%s] Before %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

	for (;;) {
		unsigned long timeout;
#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
		unsigned long start_print = 0;
		unsigned long bitmap_size = BITS_TO_LONGS(cma->count) * sizeof(long);
#endif
		mutex_lock(&cma->lock);
		timeout = jiffies + msecs_to_jiffies(8000);

#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
		ktime_t start_time;
		s64 cma_alloc_time_cost_ms = 0;
#endif

refind:
		// bitmap_find_next_zero_area will return an index which points a zero-bit in bitmap, whose following "count" bits are all zero-bit(from pageno to pageno+count are all free pages)
		pageno = bitmap_find_next_zero_area(cma->bitmap, cma->count,
						    start, count, mask);
#ifdef CONFIG_MP_CMA_PATCH_FORCE_ALLOC_START_ADDR
		if (pageno >= cma->count || (start_pfn && start != pageno)){	// no such continuous area
#else
		if (pageno >= cma->count || (start && start != pageno)){	// no such continuous area
#endif

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
			/* this means we are using zram_cma_alloc */
			if(get_start < zram_device_cnt)
			{
				remain_free_page_cnt = count_cma_area_free_page_num(cma);
				if(should_refind && remain_free_page_cnt > 0)
				{
					printk(KERN_ERR "\033[31mFunction = %s, Line = %d, we need to goto the start of buffer to refind, should_refind is %d, remain_free_page_cnt is %d\033[m\n", 
						__PRETTY_FUNCTION__, __LINE__, should_refind, remain_free_page_cnt);
					printk(KERN_ERR "\033[35mFunction = %s, Line = %d, start is 0x%lX, count is %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, count);
					should_refind = 0;
					start = 0;
					zram_cma_start[get_start] = 0;

					goto refind;
				}
				
				printk(KERN_ERR "\033[35mFunction = %s, Line = %d, start is %lu, count is %d, pageno is %lu, cma->count is %lu\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, count, pageno, cma->count);
				printk(KERN_ERR "\033[35mFunction = %s, Line = %d, bitmap from 0x%lX to 0x%lX, bitmap_size is 0x%lX\033[m\n",
					__PRETTY_FUNCTION__, __LINE__, cma->bitmap, cma->bitmap + bitmap_size/4, bitmap_size);
			
				printk(KERN_ERR "\033[35mFunction = %s, Line = %d, zram_cma_start is %lu\033[m\n", __PRETTY_FUNCTION__, __LINE__, zram_cma_start[get_start]);

				for(start_print = cma->bitmap; start_print < cma->bitmap + bitmap_size/4; start_print += BITS_PER_LONG/8)
					printk(KERN_ERR "\033[35mLine = %d, [0x%lX] bitmap = 0x%lX\033[m\n", __LINE__, start_print, *(unsigned long *)start_print);
			}
#endif

			mutex_unlock(&cma->lock);
			break;
		}

		bitmap_set(cma->bitmap, pageno, count);
		/*
 		 * It's safe to drop the lock here. We've marked this region for
 		 * our exclusive use. If the migration fails we will take the
 		 * lock again and unmark it.
 		 */

		mutex_unlock(&cma->lock);

		pfn = cma->base_pfn + pageno;
retry:
		mutex_lock(&cma_mutex);
#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
		start_time = ktime_get_real();
#endif
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA);
#ifdef CONFIG_MP_CMA_PATCH_COUNT_TIMECOST
		if(cma != dma_contiguous_default_area)
		{
			cma_measurement_data = cma->cma_measurement_ptr;
			cma_alloc_time_cost_ms = Show_Diff_Time("alloc_contig_range", start_time, 0);

			mutex_lock(&cma_measurement_data->cma_measurement_lock);
			cma_measurement_data->total_migration_time_cost_ms += cma_alloc_time_cost_ms;
			mutex_unlock(&cma_measurement_data->cma_measurement_lock);
		}
#endif
		mutex_unlock(&cma_mutex);
		if (ret == 0) {
			page = pfn_to_page(pfn);
#ifdef CONFIG_MP_CMA_PATCH_CMA_AGGRESSIVE_ALLOC			
			adjust_managed_cma_page_count(page_zone(page), -count); 
#endif

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
			if(get_start < zram_device_cnt)
				zram_cma_start[get_start] = pageno + count;
#endif
			break;
#ifdef CONFIG_MP_CMA_PATCH_FORCE_ALLOC_START_ADDR
		} else if (start_pfn && time_before(jiffies, timeout)) {
#else
		} else if (start && time_before(jiffies, timeout)) {
#endif
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, cannot get cma_memory, retry\033[m\n", __PRETTY_FUNCTION__, __LINE__);
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, cannot get cma_memory, retry\033[m\n", __PRETTY_FUNCTION__, __LINE__);
			cond_resched();
			invalidate_bh_lrus();
			goto retry;
#ifdef CONFIG_MP_CMA_PATCH_FORCE_ALLOC_START_ADDR
		} else if (ret != -EBUSY || start_pfn) {
#else
		} else if (ret != -EBUSY || start) {
#endif
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, cannot get cma_memory, ret is %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, ret);
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, cannot get cma_memory, ret is %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, ret);
			clear_cma_bitmap(cma, pfn, count);
			break;
		}
		clear_cma_bitmap(cma, pfn, count);

		printk(CMA_DEBUG "\033[35mFunction = %s, Line = %d, start is 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, start);
		printk(CMA_DEBUG "\033[35mFunction = %s, Line = %d, pageno is 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, pageno);
		printk(CMA_DEBUG "\033[35mFunction = %s, Line = %d, pfn is 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, pfn);

		pr_info("%s(): memory range at 0x%lX is busy, retrying\n",
			 __func__, pfn << PAGE_SHIFT);
		/* try again with a bit different memory target */

#ifdef CONFIG_MP_CMA_PATCH_FORCE_ALLOC_START_ADDR
		if(start_pfn)
		{
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, do not change start from 0x%lX to 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, (pageno + mask + 1));
		}
		else
		{
			printk(CMA_ERR "\033[35mFunction = %s, Line = %d, change start from 0x%lX to 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, start, (pageno + mask + 1));
			start = pageno + mask + 1;
		}
#else
		start = pageno + mask + 1;
#endif
	}

	pr_debug("%s(): returned %p\n", __func__, page);

#ifdef CONFIG_ARM64
	if (page)
	{
		/* Remap to non-cache, or usb will not be detected
		 * 3.10.86 kernel do not need this, because its default dma_ops is "noncoherent_swiotlb_dma_ops".
		 * The noncoherent_swiotlb_dma_ops will do remap after this alloc is returned.
		 * Since 3.10.40 kernel default using arm_dma_ops, we need to do remap @ this alloc!!
		 */

		/* for macan 32bit, this will let __dma_clear_buffer() very slow */
		/* actually, we do not to do this for cma_pool, and 32bit kernel will do remap @__alloc_from_contiguous() */
		__dma_remap(page, count << PAGE_SHIFT, pgprot_dmacoherent(PAGE_KERNEL));
	}
#endif
	if(count >= 10)
	{
		if(page)
			printk(CMA_DEBUG "\033[32mAlloc Bus_Addr at 0x%X\033[m\n", (unsigned int)(pfn << PAGE_SHIFT));

		printk(CMA_DEBUG "\033[32m[%s] After %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

	return page;
}

/*
 * bitmap_find_first_zero_area - find the first contiguous aligned zero area
 * @map: The address to base the search on
 * @size: The bitmap size in bits
 * @start: The bitnumber to start searching at
 * @nr:The max length we want, if nr < 0, the max length is not limited
 * @len: The length of the first zero area 
 * @align_mask: Alignment mask for zero area
 */
static unsigned long bitmap_find_first_zero_area(unsigned long *map,
					 unsigned long size,
					 unsigned long start,
					 unsigned long nr,
					 unsigned long *len,
					 unsigned long align_mask)
{
	unsigned long index, end;

	index = find_next_zero_bit(map, size, start);

	/* Align allocation */
	index = __ALIGN_MASK(index, align_mask);

	if(nr < 0)
		end = size;
	else{
		end = index + nr;
		if(end > size)
			end = size;
	}
	end = find_next_bit(map, end, index);

	*len = end - index;
	
	return index;
}

struct page *dma_alloc_from_contiguous_direct(struct device *dev, int count,
				       unsigned int align, long *retlen)
{
	unsigned long mask, pfn, pageno, start = 0, len = 0;
	struct cma *cma = dev_get_cma_area(dev);
	struct page *page = NULL;
	int ret;

	if (!cma || !cma->count)
		return NULL;

	if (align > CONFIG_CMA_ALIGNMENT){
		// if size > 2^8 pages ==> align will be > 8
		align = CONFIG_CMA_ALIGNMENT;
	}

	//printk("\033[31m%s(alloc %d pages, align %d)\033[m\n", __func__, count, align);

	if (!count)
		return NULL;

	mask = (1 << align) - 1;

	if(count >= 30)
	{
		printk(CMA_DEBUG "\033[32m[%s] Before %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

	for (;;) {		 
		mutex_lock(&cma->lock);
		// bitmap_find_next_zero_area will return an index which points a zero-bit in bitmap, whose following "count" bits are all zero-bit(from pageno to pageno+count are all free pages)
		pageno = bitmap_find_first_zero_area(cma->bitmap, cma->count,
						    start, count, &len, mask);
		if (pageno >= cma->count){
			mutex_unlock(&cma->lock);
			break;
		}
		bitmap_set(cma->bitmap, pageno, len);
		mutex_unlock(&cma->lock);
		/*
		* It's safe to drop the lock here. We've marked this region for
		* our exclusive use. If the migration fails we will take the
		* lock again and unmark it.
		*/

		pfn = cma->base_pfn + pageno;
		mutex_lock(&cma_mutex);
		ret = alloc_contig_range(pfn, pfn + len, MIGRATE_CMA);
		mutex_unlock(&cma_mutex);
		if (ret == 0) {
			page = pfn_to_page(pfn);
#ifdef CONFIG_MP_CMA_PATCH_CMA_AGGRESSIVE_ALLOC			
			adjust_managed_cma_page_count(page_zone(page), -len); 
#endif
			break;
		} else if (ret != -EBUSY) {
			printk(CMA_ERR "[xiaohui] %s: alloc_contig_range fail\n", __func__);
			clear_cma_bitmap(cma, pfn, len);
			break;
		}
		clear_cma_bitmap(cma, pfn, len);
		pr_info("%s(): memory range at %p is busy, retrying,%d, %d, %s\n",
			 __func__, pfn_to_page(pfn),current->pid, current->tgid, current->comm);
		/* try again with a bit different memory target */
		start = pageno + mask + 1;
	}
	
	if(count >= 30)
	{
		printk(CMA_DEBUG "\033[32m[%s] After %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}
	
	*retlen = len;
	return page;
}

/**
 * dma_alloc_from_contiguous() - allocate pages from contiguous area
 * @dev:   Pointer to device for which the allocation is performed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 *
 * This function allocates memory buffer for specified device. It uses
 * device specific contiguous memory area if available or the default
 * global one. Requires architecture specific get_dev_cma_area() helper
 * function.
 */
struct page *dma_alloc_from_contiguous(struct device *dev, int count,
				       unsigned int align)
{
	return dma_alloc_at_from_contiguous(dev, count, align, 0);
}

/**
 * dma_release_from_contiguous() - release allocated pages
 * @dev:   Pointer to device for which the pages were allocated.
 * @pages: Allocated pages.	// start pfn
 * @count: Number of allocated pages.
 *
 * This function releases memory allocated by dma_alloc_from_contiguous().
 * It returns false when provided pages do not belong to contiguous area and
 * true otherwise.
 */
bool dma_release_from_contiguous(struct device *dev, struct page *pages,
				 int count)
{
	struct cma *cma = dev_get_cma_area(dev);
	unsigned long pfn;

	if (!cma || !pages)
		return false;

        if(!count)
            return true;

	pr_debug("%s(page %p)\n", __func__, (void *)pages);

	pfn = page_to_pfn(pages);

	if (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count)
		return false;

	VM_BUG_ON(pfn + count > cma->base_pfn + cma->count);

	if(count >= 10)
	{
		printk(CMA_DEBUG "\033[32m[%s] Before %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

#ifdef CONFIG_ARM64
	/* for macan 32bit, this will let __dma_clear_buffer() very slow */
	/* actually, we do not to do this for cma_pool, and 32bit kernel will do remap @__free_from_contiguous() */
	__dma_remap(pages, count << PAGE_SHIFT, PAGE_KERNEL_EXEC);
#endif

	free_contig_range(pfn, count);
	clear_cma_bitmap(cma, pfn, count);

#ifdef CONFIG_MP_CMA_PATCH_CMA_AGGRESSIVE_ALLOC
	adjust_managed_cma_page_count(page_zone(pages), count); 
#endif

	if(count >= 10)
	{
		printk(CMA_DEBUG "\033[32m[%s] After %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

	return true;
}

int dma_get_contiguous_stats(struct device *dev,
			struct dma_contiguous_stats *stats)
{
	struct cma *cma = NULL;

	if ((!dev) || !stats)
		return -EINVAL;

	if (dev->cma_area)
		cma = dev->cma_area;

	if (!cma)
		return -EINVAL;

	stats->size = (cma->count) << PAGE_SHIFT;
	stats->base = (cma->base_pfn) << PAGE_SHIFT;

	return 0;
}

#ifdef CONFIG_MP_ION_PATCH_MSTAR
/**
 * dma_alloc_from_contiguous_addr() - allocate pages from contiguous area from specified start address
 * @dev:   Pointer to device for which the allocation is performed.
 * @start: Start bus address to allocate.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).	// request 2^align pages
 *
 * This function allocates memory buffer for specified device. It uses
 * device specific contiguous memory area if available or the default
 * global one. Requires architecture specific get_dev_cma_area() helper
 * function.
 */
void *dma_alloc_from_contiguous_addr(struct device *dev, unsigned long start,
																int count, unsigned int align)
{
	unsigned long mask;
	struct cma *cma = dev_get_cma_area(dev);
	struct page *page = NULL;
	unsigned long start_pfn = start >> PAGE_SHIFT;
	int ret,next_bit;

	if (!cma || !cma->count)
		return NULL;
	
	if (!count)
		return NULL;

	//count = count >> PAGE_SHIFT;
	if(start_pfn < cma->base_pfn || start_pfn >= cma->base_pfn + cma->count || start_pfn + count > cma->base_pfn + cma->count){
		printk(CMA_ERR "invalide start address, start_pfn = 0x%X, count = 0x%X, cma[0x%X, 0x%X] \n", (unsigned int)start_pfn, (unsigned int)count, (unsigned int)cma->base_pfn, (unsigned int)cma->count);
		return NULL;
	}

	if (align > CONFIG_CMA_ALIGNMENT)
	{
		// if size > 2^8 pages ==> align will be > 8
		align = CONFIG_CMA_ALIGNMENT;
	}

	mask = (1 << align) - 1;
	start_pfn = (start_pfn + mask - 1) & ~mask;

	if(count >= 10)
	{
		printk(CMA_DEBUG "\033[31m%s(alloc %d pages, start 0x%X, start pfn 0x%X)\033[m\n", __func__, count, (unsigned int)start, (unsigned int)start_pfn);
		printk(CMA_DEBUG "\033[32m[%s] Before %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}

	mutex_lock(&cma->lock);
	next_bit = find_next_bit(cma->bitmap, cma->count, start_pfn - cma->base_pfn);	//	next is the offset, for the page_no pointing to next 1 bit(non-free page), corresponding to start_pfn
	if((next_bit - start_pfn) < count)	//can not allocate [start_pfn, start_pfn + count)
	{
		mutex_unlock(&cma->lock);
		printk(CMA_ERR "Cannot allocte [0x%X, 0x%X] due to offset 0x%X is occupied! \n",
			(unsigned int)start_pfn, (unsigned int)(start_pfn + count), (unsigned int)next_bit);
		goto RET;
	}
	bitmap_set(cma->bitmap, start_pfn - cma->base_pfn, count);
	mutex_unlock(&cma->lock);

	mutex_lock(&cma_mutex);
	ret = alloc_contig_range(start_pfn, start_pfn + count, MIGRATE_CMA);
	mutex_unlock(&cma_mutex);
	if (ret == 0) {
		page = pfn_to_page(start_pfn);
#ifdef CONFIG_MP_CMA_PATCH_CMA_AGGRESSIVE_ALLOC			
		adjust_managed_cma_page_count(page_zone(page), -count); 
#endif		
	} else if (ret != -EBUSY) {
		clear_cma_bitmap(cma, start_pfn, count);
		printk(CMA_ERR "allocte [%lx, %lx] failed \n", start_pfn , start_pfn + count);
		goto RET;
	}
	else{
		printk(CMA_ERR "######################## ret = %d \n",ret);	
		clear_cma_bitmap(cma, start_pfn, count);
		WARN_ON(1);
	}

	if(page && (count >= 10))
	{
		printk(CMA_DEBUG "\033[32mAlloc Bus_Addr at 0x%X\033[m\n", (unsigned int)(start_pfn << PAGE_SHIFT));
	}

	if(count >= 10)
	{
		printk(CMA_DEBUG "\033[32m[%s] After %s \033[m", current->comm, __PRETTY_FUNCTION__);
		count_cma_area_free_page_num(cma);
	}
	
RET:
	return page;
}
#endif

#if CONFIG_MP_CMA_PATCH_MSTAR_KMALLOC
#define MSTAR_KMALLOC_CNT 1024 * 6	// 4MB * 6
struct mstar_kmalloc_mapping {
	unsigned long bus_addr;
	int alloc_page_cnt;
	int used;
};
static struct mstar_kmalloc_mapping mstar_kmalloc_mapping[MSTAR_KMALLOC_CNT];
static DEFINE_MUTEX(mstar_kmalloc_lock);
void *mstar_kmalloc(size_t size, gfp_t flags);

void *mstar_kzalloc(size_t size, gfp_t flags){
	return mstar_kmalloc(size,flags | __GFP_ZERO);
}

void *mstar_kmalloc(size_t size, gfp_t flags)
{
	struct page *page = NULL;
	int insert_index;
	int alloc_page_cnt;
	void *addr;

	if(flags & GFP_ATOMIC || flags & GFP_NOWAIT || in_interrupt()){
		addr = kmalloc(size, flags);
		printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] WARNING %s %d kmalloc 0x%lx \033[m\n", __func__, __LINE__, addr);
		return addr;
	}

	if(size & (PAGE_SIZE - 1))
		alloc_page_cnt = (size >> PAGE_SHIFT) + 1;
	else
		alloc_page_cnt = (size >> PAGE_SHIFT);

	if(get_order(size) > 0){
		mutex_lock(&mstar_kmalloc_lock);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
		{
			if(mstar_kmalloc_mapping[insert_index].used)
				continue;
			else{
				page = dma_alloc_from_contiguous(NULL, alloc_page_cnt, get_order(size));
				if(page){
					__dma_remap(page, alloc_page_cnt << PAGE_SHIFT, PAGE_KERNEL_EXEC);
					mstar_kmalloc_mapping[insert_index].used = 1;
					mstar_kmalloc_mapping[insert_index].bus_addr = __page_to_pfn(page) << PAGE_SHIFT;
					mstar_kmalloc_mapping[insert_index].alloc_page_cnt = alloc_page_cnt;
					if(flags & __GFP_ZERO)
						memset(page_address(page),0,size);
					printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] %s %d Success 0x%lx\033[m\n",__func__,__LINE__,page_address(page));
					mutex_unlock(&mstar_kmalloc_lock);
					return page_address(page);
				}
				break;
			}
		}
		mutex_unlock(&mstar_kmalloc_lock);
		addr = kmalloc(size,flags);
		printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] WARNING %s %d List Full kmalloc 0x%lx\033[m\n",__func__,__LINE__,addr);
		return addr;
	}
	else{
		addr = kmalloc(size,flags);
		printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] WARNING %s %d kmalloc 0x%lx\033[m\n",__func__,__LINE__,addr);
		return addr;
	}
}

void mstar_kfree(const void *addr)
{
	struct page *page = NULL;
	int insert_index;
	page = virt_to_head_page(addr);
	if(page && is_default_cma_buffer(__page_to_pfn(page) << PAGE_SHIFT)){
		mutex_lock(&mstar_kmalloc_lock);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++){
			if(mstar_kmalloc_mapping[insert_index].used &&
				mstar_kmalloc_mapping[insert_index].bus_addr == (__page_to_pfn(page) << PAGE_SHIFT)){
				dma_release_from_contiguous(NULL, page, mstar_kmalloc_mapping[insert_index].alloc_page_cnt);
				mstar_kmalloc_mapping[insert_index].alloc_page_cnt = 0;
				mstar_kmalloc_mapping[insert_index].used = 0;
				mstar_kmalloc_mapping[insert_index].bus_addr = 0;
				mutex_unlock(&mstar_kmalloc_lock);
				printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] %s %d Success 0x%lx\033[m\n",__func__,__LINE__,addr);
				break;
			}
		}
		if(insert_index >= MSTAR_KMALLOC_CNT){
			mutex_unlock(&mstar_kmalloc_lock);
			printk(CMA_ERR "\033[0;32;31m [Mstar kmalloc] ERROR %s %d PFN 0x%lx Address 0x%p not in mstar_kmalloc_mapping list\033[m\n",__func__,__LINE__,page_to_pfn(page),addr);
			kfree(addr);
		}
	}
	else{
		printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] %s %d WARNING kfree 0x%lx\033[m\n",__func__,__LINE__,addr);
		kfree(addr);
	}
}

bool is_mstar_kmalloc(struct page *check_page)
{
	int insert_index;

	if(check_page && is_default_cma_buffer(__page_to_pfn(check_page) << PAGE_SHIFT))
	{
		mutex_lock(&mstar_kmalloc_lock);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
		{
			if(mstar_kmalloc_mapping[insert_index].used &&
				mstar_kmalloc_mapping[insert_index].bus_addr == (__page_to_pfn(check_page) << PAGE_SHIFT))
			{
				mutex_unlock(&mstar_kmalloc_lock);
				return TRUE;
			}
		}

		/* not @ mstar_kmalloc_mapping */
		mutex_unlock(&mstar_kmalloc_lock);
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

void dump_mstar_kmalloc_mapping(int dump_count)
{
	int insert_index;
	printk("\033[35mFunction = %s, Line = %d, dump start\033[m\n", __PRETTY_FUNCTION__, __LINE__);

	if(dump_count == 0)
		dump_count = MSTAR_KMALLOC_CNT;

	mutex_lock(&mstar_kmalloc_lock);
	for(insert_index = 0; insert_index < dump_count; insert_index++)
	{
		if(mstar_kmalloc_mapping[insert_index].used)
		{
			printk("\033[35mFunction = %s, Line = %d, allocated ba is 0x%lX\033[m\n", __PRETTY_FUNCTION__, __LINE__, mstar_kmalloc_mapping[insert_index].bus_addr);
		}
	}
	mutex_unlock(&mstar_kmalloc_lock);
	printk("\033[35mFunction = %s, Line = %d, dump done\033[m\n", __PRETTY_FUNCTION__, __LINE__);
}

/* alloc cma_memory from a specified device, this device should have a cma_area,
   we must alloc pages from cma_area, if failed, we will retry or just return NULL */
void *mstar_device_kmalloc(struct device *cma_dev, size_t size, gfp_t flags)
{
	struct page *page = NULL;
	int insert_index;
	int alloc_page_cnt;
	int retry_cnt = 0;
	void *addr;

	/* we must get memory from cma */
	if(flags & GFP_ATOMIC || flags & GFP_NOWAIT || in_interrupt()){
		printk(CMA_ERR "\033[0;32;31m [Mstar kmalloc] WARNING %s %d kmalloc 0x%lx\033[m\n", __func__, __LINE__, addr);
		return addr;
	}

	if(size & (PAGE_SIZE - 1))
		alloc_page_cnt = (size >> PAGE_SHIFT) + 1;
	else
		alloc_page_cnt = (size >> PAGE_SHIFT);

	mutex_lock(&mstar_kmalloc_lock);
	for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
	{
		if(mstar_kmalloc_mapping[insert_index].used)
			continue;
		else
		{
retry_cma_alloc:
			page = dma_alloc_from_contiguous(cma_dev, alloc_page_cnt, get_order(size));
			if(page)
			{
				__dma_remap(page, alloc_page_cnt << PAGE_SHIFT, PAGE_KERNEL_EXEC);
				mstar_kmalloc_mapping[insert_index].used = 1;
				mstar_kmalloc_mapping[insert_index].bus_addr = __page_to_pfn(page) << PAGE_SHIFT;
				mstar_kmalloc_mapping[insert_index].alloc_page_cnt = alloc_page_cnt;

				if(flags & __GFP_ZERO)
					memset(page_address(page), 0, (alloc_page_cnt << PAGE_SHIFT));

				printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] %s %d Success 0x%lx\033[m\n",__func__,__LINE__,page_address(page));
				mutex_unlock(&mstar_kmalloc_lock);
				return page;
			}
			else
			{
				retry_cnt++;
				printk("\033[35mFunction = %s, Line = %d, retry_cnt: %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, retry_cnt);
				if(retry_cnt >= 10)
				{
					printk("\033[35mFunction = %s, Line = %d, error, can not get device_cma!!\033[m\n", __PRETTY_FUNCTION__, __LINE__);
					mutex_unlock(&mstar_kmalloc_lock);
					return page;
				}
				goto retry_cma_alloc;
			}
		}
	}
	mutex_unlock(&mstar_kmalloc_lock);
	printk(CMA_ERR "\033[0;32;31m [Mstar kmalloc] WARNING %s %d List Full !!\033[m\n", __func__, __LINE__);
	return page;
}

void mstar_device_kfree(struct device *cma_dev, const void *addr)
{
	struct page *page = NULL;
	int insert_index;

	page = virt_to_head_page(addr);

	if(page && is_device_cma_buffer(cma_dev, __page_to_pfn(page) << PAGE_SHIFT))
	{
		mutex_lock(&mstar_kmalloc_lock);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
		{
			if(mstar_kmalloc_mapping[insert_index].used && mstar_kmalloc_mapping[insert_index].bus_addr == (__page_to_pfn(page) << PAGE_SHIFT))
			{
				dma_release_from_contiguous(cma_dev, page, mstar_kmalloc_mapping[insert_index].alloc_page_cnt);
				mstar_kmalloc_mapping[insert_index].alloc_page_cnt = 0;
				mstar_kmalloc_mapping[insert_index].used = 0;
				mstar_kmalloc_mapping[insert_index].bus_addr = 0;
				mutex_unlock(&mstar_kmalloc_lock);
				printk(CMA_DEBUG "\033[0;32;31m [Mstar kmalloc] %s %d Success 0x%lx\033[m\n", __func__, __LINE__, addr);
				break;
			}
		}

		if(insert_index >= MSTAR_KMALLOC_CNT)
		{
			mutex_unlock(&mstar_kmalloc_lock);
			printk(CMA_ERR "\033[0;32;31m [Mstar kmalloc] ERROR %s %d PFN 0x%lx Address 0x%p not in mstar_kmalloc_mapping list\033[m\n", __func__, __LINE__, page_to_pfn(page), addr);
			BUG_ON(1);
		}
	}
	else
	{
		printk(CMA_ERR "\033[0;32;31m [Mstar kmalloc] %s %d WARNING kfree 0x%lx\033[m\n", __func__, __LINE__, addr);
		BUG_ON(1);
	}
}

#ifdef CONFIG_MP_ZRAM_ZRAM_USING_CMA_PAGES
struct page *mstar_zram_alloc_cma(size_t size, gfp_t flags)
{
	int insert_index;
	int alloc_page_cnt;
	int i, zram_cma_buffer_index, retry_index;
	int zram_cma_remain_page_cnt = 0;
	struct page *page = NULL;	

	if(zram_device_cnt == 0)
	{
		printk("\033[35mFunction = %s, Line = %d, Error, no zram_cma_buffer\033[m\n", __PRETTY_FUNCTION__, __LINE__);
		BUG_ON(1);
	}

	if(flags & GFP_ATOMIC || flags & GFP_NOWAIT || in_interrupt()){
		printk(KERN_ERR "\033[0;32;31m [Mstar kmalloc] WARNING %s %d, gfp is 0x%lX\033[m\n", __func__, __LINE__, flags);
		BUG_ON(1);
	}

	if(size & (PAGE_SIZE - 1))
		alloc_page_cnt = (size >> PAGE_SHIFT) + 1;
	else
		alloc_page_cnt = (size >> PAGE_SHIFT);

	for(i = 0; i < zram_device_cnt; i++)
	{
		if(zram_cma_page_cnt[i] > zram_cma_remain_page_cnt)
		{
			zram_cma_remain_page_cnt = zram_cma_page_cnt[i];
			retry_index = zram_cma_buffer_index = i;
		}
	}

	if(get_order(size) == 0)
	{
		mutex_lock(&mstar_kmalloc_lock);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
		{
			if(mstar_kmalloc_mapping[insert_index].used)
				continue;
			else
			{
retry_zram_alloc:
				page = dma_alloc_from_contiguous(zram_cma_device[zram_cma_buffer_index], alloc_page_cnt, get_order(size));
				if(page)
				{
					__dma_remap(page, alloc_page_cnt << PAGE_SHIFT, PAGE_KERNEL_EXEC);
					mstar_kmalloc_mapping[insert_index].used = 1;
					mstar_kmalloc_mapping[insert_index].bus_addr = __page_to_pfn(page) << PAGE_SHIFT;
					mstar_kmalloc_mapping[insert_index].alloc_page_cnt = alloc_page_cnt;
					
					if(flags & __GFP_ZERO)
						memset(page_address(page),0,size);

					/* decrease one page cnt for the allocated buffer */
					zram_cma_page_cnt[zram_cma_buffer_index]--;

					//printk("\033[31mFunction = %s, Line = %d, get zram pfn: 0x%lX, from %s\033[m\n", __PRETTY_FUNCTION__, __LINE__, __page_to_pfn(page), zram_cma_device[zram_cma_buffer_index]->init_name);
					mutex_unlock(&mstar_kmalloc_lock);
					return page;
				}
				else
				{
					zram_cma_buffer_index++;
					zram_cma_buffer_index %= zram_device_cnt;
					if(zram_cma_buffer_index != retry_index)
					{
						printk(KERN_ERR "\033[31mFunction = %s, Line = %d, retry zram_alloc_cma from zram%d to zram%d\033[m\n", __PRETTY_FUNCTION__, __LINE__, retry_index, zram_cma_buffer_index);
						goto retry_zram_alloc;
					}
					else
					{
						printk(KERN_ERR "\033[31mFunction = %s, Line = %d, [Retry Error] zram_alloc_cma from zram%d to zram%d\033[m\n", __PRETTY_FUNCTION__, __LINE__, retry_index, zram_cma_buffer_index);
					}

					mutex_unlock(&mstar_kmalloc_lock);
					printk(KERN_ERR "\033[35mFunction = %s, Line = %d, error while dma_alloc_from_contiguous\033[m\n", __PRETTY_FUNCTION__, __LINE__);
					return page;	// return NULL page, and zram will WRITE_ERROR
				}
			}
		}

		mutex_unlock(&mstar_kmalloc_lock);
		printk(KERN_ERR "\033[0;32;31m [Mstar kmalloc] WARNING %s %d List Full, insert_index is %d\033[m\n", __func__, __LINE__, insert_index);
		BUG_ON(1);
	}
	else
	{
		printk(KERN_ERR "\033[0;32;31m [Mstar kmalloc] WARNING %s %d, zram alloc page with order %d\033[m\n", __func__, __LINE__, get_order(size));
		BUG_ON(1);
	}
}

void mstar_zram_free_cma(struct page *free_page)
{
	int insert_index;
	int i;
	struct device *zram_free_cma_device;
	struct cma *zram_cma;
	unsigned long free_pfn;

	if(free_page)
	{
		mutex_lock(&mstar_kmalloc_lock);
		free_pfn = __page_to_pfn(free_page);
		for(insert_index = 0; insert_index < MSTAR_KMALLOC_CNT; insert_index++)
		{
			if(mstar_kmalloc_mapping[insert_index].used &&
				mstar_kmalloc_mapping[insert_index].bus_addr == (free_pfn << PAGE_SHIFT))
			{
				for(i = 0; i < zram_device_cnt; i++)
				{
					zram_free_cma_device = zram_cma_device[i];
					zram_cma = dev_get_cma_area(zram_free_cma_device);
					if( (zram_cma->base_pfn <= free_pfn) && (free_pfn < zram_cma->base_pfn + zram_cma->count) )	/* this free_page is located at this zram_cma */
						break;
				}
			
				if(i >= zram_device_cnt)
				{
					printk("\033[35mFunction = %s, Line = %d\033[m\n", __PRETTY_FUNCTION__, __LINE__);
					BUG_ON(1);
				}

				dma_release_from_contiguous(zram_free_cma_device, free_page, mstar_kmalloc_mapping[insert_index].alloc_page_cnt);
				mstar_kmalloc_mapping[insert_index].alloc_page_cnt = 0;
				mstar_kmalloc_mapping[insert_index].used = 0;
				mstar_kmalloc_mapping[insert_index].bus_addr = 0;
				
				/* increase one page cnt for the allocated buffer */
				zram_cma_page_cnt[i]++;

				//printk("\033[31mFunction = %s, Line = %d, free zram pfn: 0x%lX, from %s\033[m\n", __PRETTY_FUNCTION__, __LINE__, free_pfn, zram_free_cma_device->init_name);
				mutex_unlock(&mstar_kmalloc_lock);
				break;
			}
		}
		
		if(insert_index >= MSTAR_KMALLOC_CNT)
		{
			printk(KERN_ERR "\033[0;32;31m [Mstar kmalloc] %s %d ,WARNING, ba is 0x%lX\033[m\n", __func__, __LINE__, free_pfn << PAGE_SHIFT);
			mutex_unlock(&mstar_kmalloc_lock);
			BUG_ON(1);
		}
	}
	else
	{
		printk(KERN_ERR "\033[0;32;31m [Mstar kmalloc] %s %d , NO FREE_PAGE\033[m\n", __func__, __LINE__);
		BUG_ON(1);
	}
}
#endif
#endif
