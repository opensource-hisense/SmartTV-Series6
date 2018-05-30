#include <linux/bootmem.h>
#include <linux/kasan.h>
#include <linux/kdebug.h>
#include <linux/kernel.h>
#include <linux/memblock.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include <asm/mach/map.h>

#ifdef CONFIG_KASAN_INLINE
static int
kasan_die_handler(struct notifier_block *self, unsigned long val, void *data)
{
	if (val == DIE_GPF) {
		pr_emerg("CONFIG_KASAN_INLINE enabled\n");
		pr_emerg("GPF could be caused by NULL-ptr deref or "
			 "user memory access\n");
	}
	return NOTIFY_OK;
}

static struct notifier_block kasan_die_notifier = {
	.notifier_call = kasan_die_handler,
};
#endif

void __init kasan_init(void)
{
	size_t size = ALIGN(KASAN_SHADOW_SIZE, SECTION_SIZE);
#if 0
	phys_addr_t phys = memblock_alloc(size, SECTION_SIZE);
#else
	phys_addr_t phys = 0x30000000;
	memblock_reserve(phys, size);
#endif
	struct map_desc md;

	md.virtual = KASAN_SHADOW_START;
	md.pfn     = __phys_to_pfn(phys);
	md.length  = size;
	md.type    = MT_MEMORY;
	iotable_init(&md, 1);

	memset((void *)KASAN_SHADOW_START, 0, size);

#ifdef CONFIG_KASAN_INLINE
	register_die_notifier(&kasan_die_notifier);
#endif

	pr_info("kasan is initialized: shadow %#lx - %#lx\n",
	        KASAN_SHADOW_START, KASAN_SHADOW_START + KASAN_SHADOW_SIZE);

	kasan_initialized = true;
	current->kasan_depth = 0;
}
