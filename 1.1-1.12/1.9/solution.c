#define IN 1
#define OUT 0

#include <stdio.h>

main() {
    int c;
    int wflag = OUT;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (wflag == OUT) {
                putchar(c);
                wflag = IN;
            }
        } else {
            putchar(c);
            wflag = OUT;
        }
        
    }
}