#include <stdio.h>

#if !defined(ENUMS_FILE)
#define ENUMS_FILE "./enums.txt"
#endif

typedef enum {
    #include ENUMS_FILE
} KW;

int main()
{
    printf("%d\n", declare);
    return 0;
}
