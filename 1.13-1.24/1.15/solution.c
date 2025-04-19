#include <stdio.h>

float convertf(float f);
float convertc(float c);

int main() {

    int fahr;
    int cels;

    printf("FAHRENHEIT\tCELSIUS\n");
    for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%d\t\t%.1f\n", fahr, convertf((float) fahr));
    }

    printf("\nCELSIUS\t\tFAHRENHEIT\n");
    for (cels = 0; cels <= 300; cels = cels + 20) {
        printf("%d\t\t%.1f\n", cels, convertc((float) cels));
    }

    return 0;
}

float convertf(float fahr) {
/* convert a temperature from fahrenheit to celsius */
    float cels;
    cels = ((5.0/9.0) * (fahr - 32.0));
    return cels;
}

float convertc(float cels) {
/* convert a temperature from celsius to fahrenheit */
    float fahr;
    fahr = ((cels * (9.0/5.0)) + 32.0);
    return fahr;
}