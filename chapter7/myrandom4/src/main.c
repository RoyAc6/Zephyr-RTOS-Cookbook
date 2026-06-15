#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/random/random.h>
#include <zephyr/shell/shell.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_REGISTER(myrandom_app);

static bool random_validator(const void *msg, size_t msg_size)
{
	const int *value = msg;
	ARG_UNUSED(msg_size);
	return *value < 100;
}

static void random_listener_cb(const struct zbus_channel *chan)
{
	const int *value = zbus_chan_const_msg(chan);
	LOG_INF("listener noticed publication: %d", *value);
}

ZBUS_LISTENER_DEFINE(random_listener, random_listener_cb);
ZBUS_SUBSCRIBER_DEFINE(random_sub_a, 4);
ZBUS_SUBSCRIBER_DEFINE(random_sub_b, 4);

ZBUS_CHAN_DEFINE(random_chan,
				 int,
				 random_validator,
				 NULL,
				 ZBUS_OBSERVERS(random_listener, random_sub_a, random_sub_b),
				 ZBUS_MSG_INIT(0));

static void subscriber_a_thread(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);
	const struct zbus_channel *chan;
	int value;
	while (1)
	{
		if (zbus_sub_wait(&random_sub_a, &chan, K_FOREVER) == 0)
		{
			zbus_chan_read(chan, &value, K_MSEC(200));
			LOG_INF("subscriber A received: %d", value);
		}
	}
}

static void subscriber_b_thread(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);
	const struct zbus_channel *chan;
	int value;
	while (1)
	{
		if (zbus_sub_wait(&random_sub_b, &chan, K_FOREVER) == 0)
		{
			zbus_chan_read(chan, &value, K_MSEC(200));
			LOG_INF("subscriber B received: %d", value);
		}
	}
}

K_THREAD_DEFINE(sub_a_tid, 1024, subscriber_a_thread,
				NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(sub_b_tid, 1024, subscriber_b_thread,
				NULL, NULL, NULL, 5, 0, 0);

static int cmd_random_publish(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	int value = sys_rand32_get() % 120;
	if (zbus_chan_pub(&random_chan, &value, K_MSEC(100)) == 0)
	{
		shell_print(shell, "Published value: %d", value);
	}
	else
	{
		shell_print(shell, "Rejected value: %d", value);
	}
	return 0;
}

static int cmd_random_get(const struct shell *shell, size_t argc, char **argv)
{
	uint32_t value = sys_rand32_get();
	shell_print(shell, "Random value: %u", value);
	return 0;
}

static int cmd_random_help(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "myrandom get : generate a random value");
	shell_print(shell, "myrandom help : show this message");
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_myrandom,
							   SHELL_CMD(get, NULL, "Generate a random value", cmd_random_get),
							   SHELL_CMD(publish, NULL, "publish a random value", cmd_random_publish),
							   SHELL_CMD(help, NULL, "Show command help", cmd_random_help),
							   SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(myrandom, &sub_myrandom, "Random number commands", NULL);