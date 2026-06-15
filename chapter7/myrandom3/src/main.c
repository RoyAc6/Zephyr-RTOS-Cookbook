#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/random/random.h>

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
							   SHELL_CMD(help, NULL, "Show command help", cmd_random_help),
							   SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(myrandom, &sub_myrandom, "Random number commands", NULL);