#ifndef _ASM_ARM_KASAN_H
#define _ASM_ARM_KASAN_H

#include <asm/memory.h>

#define KASAN_SHADOW_SCALE_SHIFT _AC(3, UL)
#define KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
/* 128MB for area higher than PAGE_OFFSET and 2MB for 16MB module area */
#define KASAN_SHADOW_SIZE	UL(SZ_128M)

/*
 * MODULES_VADDR is the lowest address that kernel can access. See
 * help text for KASAN_SHADOW_OFFSET in lib/Kconfing.kasan.
 */
#define KASAN_SHADOW_START	(KASAN_SHADOW_OFFSET + \
				(MODULES_VADDR >> KASAN_SHADOW_SCALE_SHIFT))
#define KASAN_SHADOW_END	(KASAN_SHADOW_START + KASAN_SHADOW_SIZE)

#ifndef __ASSEMBLY__

#ifdef CONFIG_KASAN

struct map_desc;

void __init kasan_init(void);
void __init kasan_shadow_area_init(struct map_desc *md);

#else

static inline void kasan_init(void) { }

#endif

#endif

#endif
