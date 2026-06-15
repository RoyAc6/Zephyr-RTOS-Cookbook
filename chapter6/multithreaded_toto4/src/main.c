#include <zephyr/kernel.h>

#define THREAD_A_STACK_SIZE 512
#define THREAD_A_PRIORITY 2
#define THREAD_B_STACK_SIZE 512
#define THREAD_B_PRIORITY 10

K_THREAD_STACK_DEFINE(thread_a_stack, THREAD_A_STACK_SIZE);

struct k_thread thread_a_data;
k_tid_t thread_a_id;

K_SEM_DEFINE(sync_sem, 0, 1);

void thread_a_entry(void *p1, void *p2, void *p3)
{
	printk("thread_A: waiting for semaphore\n");
	k_sem_take(&sync_sem, K_FOREVER);
	printk("thread_A: semaphore received, continuing\n");
}

void thread_b_entry(void *p1, void *p2, void *p3)
{
	printk("thread_B: doing work\n");
	k_sleep(K_SECONDS(1));
	printk("thread_B: signaling semaphore\n");
	k_sem_give(&sync_sem);
}

int main(void)
{
	thread_a_id = k_thread_create(&thread_a_data,
								  thread_a_stack, K_THREAD_STACK_SIZEOF(thread_a_stack),
								  thread_a_entry, NULL, NULL, NULL,
								  THREAD_A_PRIORITY, 0, K_NO_WAIT);

	ARG_UNUSED(thread_a_id);

	return 0;
}

K_THREAD_DEFINE(thread_b_id, THREAD_B_STACK_SIZE,
				thread_b_entry, NULL, NULL, NULL,
				THREAD_B_PRIORITY, 0, 0);