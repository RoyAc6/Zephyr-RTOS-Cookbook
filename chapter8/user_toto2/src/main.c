#include <zephyr/kernel.h>
#include <zephyr/app_memory/app_memdomain.h>
#include <zephyr/sys/libc-hooks.h>

K_APPMEM_PARTITION_DEFINE(part_a);
K_APPMEM_PARTITION_DEFINE(part_b);
K_APPMEM_PARTITION_DEFINE(part_shared);

K_APP_DMEM(part_a) int a_var = 11;
K_APP_DMEM(part_b) int b_var = 22;
K_APP_DMEM(part_shared) int s_var = 99;

static void app_a_thread(void *p1, void *p2, void *p3)
{
	printk("a=%d s=%d\n", a_var, s_var);

	printk("b=%d\n", b_var);

	while (1)
	{
		k_sleep(K_SECONDS(1));
	}
}

static struct k_mem_domain domain_a;

static struct k_mem_partition *domain_a_parts[] = {
#ifdef CONFIG_CPU_CORTEX_M
	&z_libc_partition,
#endif
	&part_a,
	&part_shared
};

K_THREAD_DEFINE(a_tid, 512, app_a_thread,
	NULL, NULL, NULL, 5, K_USER, 0);

int main(void)
{
	k_mem_domain_init(
		&domain_a,
		ARRAY_SIZE(domain_a_parts),
		domain_a_parts);

	k_mem_domain_add_thread(&domain_a, a_tid);
	
	return 0;
}