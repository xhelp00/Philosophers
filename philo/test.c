#include <stdio.h>

int main (void)
{
	printf("%-7d %-7s %-7s\n", 77777777, "1", "\e[1;31mhas died\e[0m");
	printf("%-5d %-5s %-5s\n", 77777777, "1", "\e[1;31mhas died\e[0m");

	return 0;
}