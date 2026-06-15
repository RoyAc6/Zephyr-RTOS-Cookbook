#include <zephyr/kernel.h>

#define MY_ADC_NODE DT_ALIAS(myadc)

#define ADC_VREF_MV DT_PROP(DT_CHILD(MY_ADC_NODE, channel_3), zephyr_vref_mv)

#define MY_ADC_CH_NODE DT_CHILD(MY_ADC_NODE, channel_3)

#define ADC_RESOLUTION DT_PROP_OR(MY_ADC_CH_NODE, zephyr_resolution, 12)

#define ADC_ENABLED DT_NODE_HAS_STATUS(MY_ADC_NODE, okay)

int main(void)
{
	printk("ADC vref: %d mV\n", ADC_VREF_MV);
	printk("ADC resolution: %d bits\n", ADC_RESOLUTION);
	printk("ADC enabled? %s\n", ADC_ENABLED ? "yes" : "no");
	return 0;
}