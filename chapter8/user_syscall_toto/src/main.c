#include <zephyr/kernel.h>

K_SEM_DEFINE(g_sem, 0, 1);

void a_thread(void *p1, void *p2, void *p3)
{
	printk("A ctx: %d\n", k_is_user_context());
	printk("A take: %d\n", k_sem_take(&g_sem, K_SECONDS(1)));
}
K_THREAD_DEFINE(
	a_tid,
	1024,
	a_thread,
	NULL,
	NULL,
	NULL,
	5,
	K_USER,
	0);
void b_thread(void *p1, void *p2, void *p3)
{
	printk("B ctx: %d\n", k_is_user_context());
	
	/* comment this following line */
	printk("B take: %d\n", k_sem_take(&g_sem, K_SECONDS(1)));
}
K_THREAD_DEFINE(
	b_tid,
	1024,
	b_thread,
	NULL,
	NULL,
	NULL,
	6,
	K_USER,
	0);
int main(void)
{
	k_object_access_grant(&g_sem, a_tid);
	k_sleep(K_MSEC(200));
	k_sem_give(&g_sem);
}