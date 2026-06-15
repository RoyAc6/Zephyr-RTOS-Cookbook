#include <zephyr/kernel.h>

int app_b_cnt = 0;

extern int shared_value;

void app_b_thread(void *a, void *b, void *c)
{
    while (1)
    {
        printf("app_b %d, shared %d\n", app_b_cnt++, shared_value);
        k_sleep(K_SECONDS(1));
    }
}

K_THREAD_DEFINE(
    b_tid,
    1024,
    app_b_thread,
    NULL,
    NULL,
    NULL,
    10,
    K_USER,
    0);