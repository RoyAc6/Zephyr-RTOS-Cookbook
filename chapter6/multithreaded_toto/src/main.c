#include <zephyr/kernel.h>

#define THREAD_A_STACK_SIZE 512
#define THREAD_A_PRIORITY 2
#define THREAD_B_STACK_SIZE 512
#define THREAD_B_PRIORITY 10

K_THREAD_STACK_DEFINE(thread_a_stack, THREAD_A_STACK_SIZE);

struct k_thread thread_a_data;

void thread_a_entry(void *p1, void *p2, void *p3)
{
	printk("thread_A: I am at high priority, value: %d \n",
		   k_thread_priority_get(k_current_get()));
}

void thread_b_entry(void *p1, void *p2, void *p3)
{
	printk("thread_B: I am at low priority, value: %d \n",
		   k_thread_priority_get(k_current_get()));
}

int main(void)
{
	k_tid_t thread_a_id = k_thread_create(&thread_a_data,
										  thread_a_stack, K_THREAD_STACK_SIZEOF(thread_a_stack),
										  thread_a_entry, NULL, NULL, NULL,
										  THREAD_A_PRIORITY, 0, K_NO_WAIT);
	return 0;
}

K_THREAD_DEFINE(thread_b_id, THREAD_B_STACK_SIZE,
				thread_b_entry, NULL, NULL, NULL,
				THREAD_B_PRIORITY, 0, 0);