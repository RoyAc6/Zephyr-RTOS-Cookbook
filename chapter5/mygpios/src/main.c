#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;
	if (!device_is_ready(led.port))
	{
		printk("GPIO device not ready: %s\n", led.port->name);
		return 0;
	}
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret != 0)
	{
		printk("gpio_pin_configure_dt() failed: %d\n", ret);
		return 0;
	}
	while (1)
	{
		gpio_pin_toggle_dt(&led);
		k_sleep(K_MSEC(500));
	}
	return 0;
}