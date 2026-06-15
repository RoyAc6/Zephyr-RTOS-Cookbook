#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define TOTO_NODE DT_ALIAS(mytotoled)

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(TOTO_NODE, toto_gpios);

#define BLINK_DELAY_MS DT_PROP(TOTO_NODE, my_delay_ms)

int main(void)
{
	int ret;
	if (!device_is_ready(led.port))
	{
		printk("LED GPIO device not ready\n");
		return 0;
	}
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret != 0)
	{
		printk("Failed to configure LED: %d\n", ret);
		return 0;
	}
	printk("Blinking with delay %d ms\n", BLINK_DELAY_MS);
	while (1)
	{
		gpio_pin_toggle_dt(&led);
		k_sleep(K_MSEC(BLINK_DELAY_MS));
	}
	return 0;
}