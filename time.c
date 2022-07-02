#include "costume.h"

unsigned long long	_time(unsigned long long	*init)
{
	struct timeval				struci;
	static unsigned long long	ref;

	if (init)
	{
		ref = *init;
		free(init);
	}
	gettimeofday(&struci, NULL);
	return (struci.tv_usec / 1000 + struci.tv_sec * 1000 - ref);
}

unsigned long long	entire_time(unsigned long long	*init)
{
	struct timeval				struci;
	static unsigned long long	ref;

	if (init)
	{
		ref = *init;
		free(init);
	}
	gettimeofday(&struci, NULL);
	return (struci.tv_usec / 1000 + struci.tv_sec * 1000 - ref);
}

void	init_entire_time(void)
{
	struct timeval		struci;
	unsigned long long	*res;

	gettimeofday(&struci, NULL);
	res = malloc(sizeof(unsigned long long));
	*res = struci.tv_usec / 1000 + struci.tv_sec * 1000;
	entire_time(res);
}

void	init_time(void)
{
	struct timeval		struci;
	unsigned long long	*res;

	gettimeofday(&struci, NULL);
	res = malloc(sizeof(unsigned long long));
	*res = struci.tv_usec / 1000 + struci.tv_sec * 1000;
	_time(res);
}
