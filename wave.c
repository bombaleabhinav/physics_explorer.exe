#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define CLR_CYAN    "\033[96m"
#define CLR_GREEN   "\033[92m"
#define CLR_YELLOW  "\033[93m"
#define CLR_RESET   "\033[0m"

void runWaveSuperposition() {
    double a1, f1, a2, f2;

    printf("\n%s--- Wave Superposition (Interference) ---%s\n", CLR_CYAN, CLR_RESET);
    printf("Wave 1 -> Enter Amplitude & Freq: ");
    scanf("%lf %lf", &a1, &f1);
    printf("Wave 2 -> Enter Amplitude & Freq: ");
    scanf("%lf %lf", &a2, &f2);

    printf("\n%sResultant Wave Pattern (y = y1 + y2):%s\n", CLR_YELLOW, CLR_RESET);

    int rows = 12;
    int cols = 60;
    double maxA = a1 + a2;

    for (int i = rows; i >= -rows; i--) {
        printf("    |");
        for (int j = 0; j < cols; j++) {
            double t = (double)j / cols;
            double y1 = a1 * sin(2 * PI * f1 * t);
            double y2 = a2 * sin(2 * PI * f2 * t);
            double yVal = y1 + y2;
            
            int scaledVal = (int)((yVal / maxA) * rows);
            
            if (scaledVal == i) printf("%s@%s", CLR_GREEN, CLR_RESET);
            else if (i == 0) printf("-");
            else printf(" ");
        }
        printf("\n");
    }

    printf("\nPress Enter to return...");
    while (getchar() != '\n'); getchar();
}
