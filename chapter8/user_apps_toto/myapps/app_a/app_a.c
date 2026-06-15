#include <zephyr/kernel.h>

int app_a_cnt = 0;

extern int shared_value;

void app_a_thread(void *a, void *b, void *c)
{
    while (1)
    {
        printf("app_a %d, shared %d\n", app_a_cnt++, shared_value);
        k_sleep(K_SECONDS(1));
    }
}

K_THREAD_DEFINE(
    a_tid,
    1024,
    app_a_thread,
    NULL,
    NULL,
    NULL,
    10,
    K_USER,
    0);