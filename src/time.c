#include "../includes/costume.h"

unsigned long long	_time(void)
{
	struct timeval				struci;

	gettimeofday(&struci, NULL);
	return (struci.tv_usec / 1000 + struci.tv_sec * 1000);
}
