#include <zephyr/kernel.h>

int post_kernel_cb(void)
{
	printk("[POST_KERNEL:10] Called automatically by the kernel\n");
	return 0;
}

int post_kernel_cb2(void)
{
	printk("[POST_KERNEL:20] Called after priority 10\n");
	return 0;
}

int application_cb(void)
{
	printk("[APPLICATION] Called automatically before main()\n");
	return 0;
}

SYS_INIT(post_kernel_cb, POST_KERNEL, 10);
SYS_INIT(post_kernel_cb2, POST_KERNEL, 20);
SYS_INIT(application_cb, APPLICATION, 10);

int main(void)
{
	printk("[main] running\n");
	return 0;
}