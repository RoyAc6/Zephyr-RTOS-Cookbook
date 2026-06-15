#include <zephyr/kernel.h>
#include <zephyr/app_memory/app_memdomain.h>
#include <zephyr/sys/libc-hooks.h>

K_APPMEM_PARTITION_DEFINE(part_a);
K_APPMEM_PARTITION_DEFINE(part_b);
K_APPMEM_PARTITION_DEFINE(part_shared);

static struct k_mem_domain dom_a;
static struct k_mem_domain dom_b;

static struct k_mem_partition *a_parts[] = {
#ifdef CONFIG_CPU_CORTEX_M
	&z_libc_partition,
#endif
	&part_a,
	&part_shared
};
static struct k_mem_partition *b_parts[] = {
#ifdef CONFIG_CPU_CORTEX_M
	&z_libc_partition,
#endif
	&part_b,
	&part_shared
};

int main(void)
{
	extern k_tid_t a_tid, b_tid;
	k_mem_domain_init(&dom_a, ARRAY_SIZE(a_parts), a_parts);
	k_mem_domain_init(&dom_b, ARRAY_SIZE(b_parts), b_parts);
	k_mem_domain_add_thread(&dom_a, a_tid);
	k_mem_domain_add_thread(&dom_b, b_tid);

	return 0;
}