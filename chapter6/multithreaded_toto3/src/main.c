#include <zephyr/kernel.h>

#define THREAD_A_STACK_SIZE 512
#define THREAD_A_PRIORITY 2
#define THREAD_B_STACK_SIZE 512
#define THREAD_B_PRIORITY 10

K_THREAD_STACK_DEFINE(thread_a_stack, THREAD_A_STACK_SIZE);

struct k_thread thread_a_data;
k_tid_t thread_a_id;

struct toto_msg
{
	int tata;
	int titi;
};

K_MSGQ_DEFINE(toto_msgq, sizeof(struct toto_msg), 3, 4);

void thread_a_entry(void *p1, void *p2, void *p3)
{
	struct toto_msg msg = {
		.tata = 42,
		.titi = 100,
	};
	k_msgq_put(&toto_msgq, &msg, K_NO_WAIT);
	printk("thread_A: sent tata=%d titi=%d\n", msg.tata, msg.titi);
}

void thread_b_entry(void *p1, void *p2, void *p3)
{
	struct toto_msg msg;
	k_msgq_get(&toto_msgq, &msg, K_FOREVER);
	printk("thread_B: received tata=%d titi=%d\n", msg.tata, msg.titi);
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