#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/random/random.h>

LOG_MODULE_REGISTER(myrandom_app);

int main(void)
{
	while (1)
	{
		uint32_t value = sys_rand32_get();
		LOG_DBG("Generated value: %u", value);
		LOG_INF("Random value: %u", value);
		LOG_WRN("Example warning message");
		LOG_ERR("Example error message");
		k_sleep(K_MSEC(1000));
	}
	return 0;
}