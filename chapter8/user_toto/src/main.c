#include <zephyr/kernel.h>

K_THREAD_STACK_DEFINE(u_stack, 1024);

static struct k_thread u_thread;

static void u_fn(void *a, void *b, void *c)
{
	ARG_UNUSED(a);
	ARG_UNUSED(b);
	ARG_UNUSED(c);
	printk("user ctx: %d\n", k_is_user_context());
	while (1)
	{
		k_sleep(K_SECONDS(1));
	}
}

int main(void)
{
	printk("userspace enabled? %d\n", IS_ENABLED(CONFIG_USERSPACE));
	printk("main ctx: %d\n", k_is_user_context());
	k_thread_create(
		&u_thread,
		u_stack,
		K_THREAD_STACK_SIZEOF(u_stack),
		u_fn,
		NULL,
		NULL,
		NULL,
		5,
		K_USER,
		K_NO_WAIT);
	return 0;
}