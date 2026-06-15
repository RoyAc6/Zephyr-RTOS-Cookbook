#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
	printk("Hello World from Zephyr!\n");
#if defined(CONFIG_LOG)
	printk("CONFIG_LOG is enabled (level=%d)\n", CONFIG_LOG_DEFAULT_LEVEL);
#else
	printk("CONFIG_LOG is disabled\n");
#endif
	return 0;
}