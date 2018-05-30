/*
 * PGD allocation/freeing
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/list.h>

#include <asm/pgalloc.h>
#include <asm/page.h>
#include <asm/tlbflush.h>

#include "mm.h"
#ifdef CONFIG_MP_PAGE_GLOBAL_DIRECTORY_SPEEDUP
#define PGD_SIZE	(PTRS_PER_PGD * sizeof(pgd_t))
#define PGD_CACHE_SIZE 512

LIST_HEAD(pgd_cache_list);
DEFINE_SPINLOCK(pgd_cache_list_spin_lock);
atomic_t pgd_cache_list_cnt = ATOMIC_INIT(0);
#endif

pgd_t *pgd_alloc(struct mm_struct *mm)
{
#ifdef CONFIG_MP_PAGE_GLOBAL_DIRECTORY_SPEEDUP
	unsigned long flags;
#endif
	if (PGD_SIZE == PAGE_SIZE)
		return (pgd_t *)get_zeroed_page(GFP_KERNEL);
	else{
#ifdef CONFIG_MP_PAGE_GLOBAL_DIRECTORY_SPEEDUP
		spin_lock_irqsave(&pgd_cache_list_spin_lock, flags);
		if(atomic_add_unless(&pgd_cache_list_cnt, -1, 0)){
			struct list_head *list;
			BUG_ON(list_empty(&pgd_cache_list));
			list = pgd_cache_list.next;
			list_del(list);
			spin_unlock_irqrestore(&pgd_cache_list_spin_lock, flags);
			return (pgd_t *)list;
		}
		spin_unlock_irqrestore(&pgd_cache_list_spin_lock, flags);
#endif
		return kzalloc(PGD_SIZE, GFP_KERNEL);
}
}

void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
#ifdef CONFIG_MP_PAGE_GLOBAL_DIRECTORY_SPEEDUP
	unsigned long flags;
#endif
	if (PGD_SIZE == PAGE_SIZE)
		free_page((unsigned long)pgd);
	else{
#ifdef CONFIG_MP_PAGE_GLOBAL_DIRECTORY_SPEEDUP
		spin_lock_irqsave(&pgd_cache_list_spin_lock, flags);
		if(atomic_add_unless(&pgd_cache_list_cnt, 1, PGD_CACHE_SIZE)){
			struct list_head *list = (struct list_head *)pgd;
			list_add(list, &pgd_cache_list);
			spin_unlock_irqrestore(&pgd_cache_list_spin_lock, flags);
			return;
		}
		spin_unlock_irqrestore(&pgd_cache_list_spin_lock, flags);
#endif
		kfree(pgd);
}
}
