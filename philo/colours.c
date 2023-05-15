#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\033[37m\033[41m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main()
{
    printf("%sred\n", KRED);
    printf("%sgreen\n", KGRN);
    printf("%syellow\n", KYEL);
    printf("%sblue\n", KBLU);
    printf("%smagenta\n", KMAG);
    printf("%scyan\n", KCYN);
    printf("%swhite\n", KWHT);
    printf("%snormal\n", KNRM);

	printf("%sHello 42\n", KCYN);

	printf("\033[37m\033[41m"); // White foreground / Red background
	printf("Something\n");
	printf("\033[0m"); 
    return 0;
}