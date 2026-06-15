#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

int main(void)
{
	while (1)
	{
		uint32_t value = sys_rand32_get();
		printk("Random value: %u\n", value);
		k_sleep(K_MSEC(1000));
	}
	return 0;
}