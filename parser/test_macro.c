#include<stdio.h>
#define f_enum(x) x
#define f_arr(#x) x

enum bharat {satvik, ayush};

int main(void)
{
    printf("%d\n", f_arr("ayush"));
}