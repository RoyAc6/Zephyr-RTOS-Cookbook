#include <zephyr/kernel.h>

struct toto_operation
{
	int event_id;
	int value;
	struct k_work work;
};

void toto_work_handler(struct k_work *work)
{
	struct toto_operation *op =
		CONTAINER_OF(work, struct toto_operation, work);
	printk("workqueue: processing event_id=%d value=%d\n",
		   op->event_id, op->value);
}

struct toto_operation op1 = {.event_id = 1, .value = 10};
struct toto_operation op2 = {.event_id = 2, .value = 20};
struct toto_operation op3 = {.event_id = 3, .value = 30};

int main(void)
{
	printk("main: initializing work items\n");
	k_work_init(&op1.work, toto_work_handler);
	k_work_init(&op2.work, toto_work_handler);
	k_work_init(&op3.work, toto_work_handler);
	printk("main: submitting op1\n");
	k_work_submit(&op1.work);
	printk("main: submitting op2\n");
	k_work_submit(&op2.work);
	k_sleep(K_MSEC(500));
	printk("main: submitting op3\n");
	k_work_submit(&op3.work);
	return 0;
}