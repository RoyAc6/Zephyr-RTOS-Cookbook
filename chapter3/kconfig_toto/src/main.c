#if defined(CONFIG_TOTO)
#include "toto.h"
#endif

int main(void)
{
#if defined(CONFIG_TOTO)
	toto_init();
#endif
	return 0;
}