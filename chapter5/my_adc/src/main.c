#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

#define MY_ADC_NODE DT_NODELABEL(lpadc0)
#define ADC_VREF_MV DT_PROP(DT_CHILD(MY_ADC_NODE, channel_3), zephyr_vref_mv)
#define MY_ADC_CH_NODE DT_CHILD(MY_ADC_NODE, channel_3)

static const struct device *adc = DEVICE_DT_GET(MY_ADC_NODE);
static const struct adc_channel_cfg ch_cfg = ADC_CHANNEL_CFG_DT(MY_ADC_CH_NODE);

int main(void)
{
	int err;
	uint32_t buf = 0;
	struct adc_sequence sequence = {
		.channels = BIT(ch_cfg.channel_id),
		.buffer = &buf,
		.buffer_size = sizeof(buf),
		.resolution = DT_PROP_OR(MY_ADC_CH_NODE, zephyr_resolution, 12),
	};
	if (!device_is_ready(adc))
	{
		printk("ADC device not ready\n");
		return 0;
	}
	err = adc_channel_setup(adc, &ch_cfg);
	if (err < 0)
	{
		printk("Could not setup ADC channel (%d)\n", err);
		return 0;
	}
	while (1)
	{
		int32_t val_mv;
		buf = 0;
		err = adc_read(adc, &sequence);
		if (err < 0)
		{
			printk("Could not read ADC (%d)\n", err);
			k_sleep(K_MSEC(1000));
			continue;
		}
		if (ch_cfg.differential)
		{
			val_mv = (int32_t)((int16_t)buf);
		}
		else
		{
			val_mv = (int32_t)buf;
		}
		printk("ADC raw: %" PRId32, val_mv);
		err = adc_raw_to_millivolts(ADC_VREF_MV, ch_cfg.gain,
									sequence.resolution, &val_mv);
		if (err < 0)
		{
			printk(" (voltage conversion not available)\n");
		}
		else
		{
			printk(" Voltage: %" PRId32 " mV\n", val_mv);
		}
		k_sleep(K_MSEC(1000));
	}
	return 0;
}