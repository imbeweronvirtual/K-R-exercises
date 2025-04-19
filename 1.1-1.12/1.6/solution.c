#include <stdio.h>

main() {
    int c = getchar();
    printf("getchar() != EOF? %d\n", c != EOF);
}