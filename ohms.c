#include <stdio.h>

#define CLR_CYAN    "\033[96m"
#define CLR_GREEN   "\033[92m"
#define CLR_YELLOW  "\033[93m"
#define CLR_RESET   "\033[0m"

void runResistorSimulator() {
    int choice, n;
    double r, total = 0;

    printf("\n%s--- Resistor Network Simulator ---%s\n", CLR_CYAN, CLR_RESET);
    printf("  1. Series Configuration\n");
    printf("  2. Parallel Configuration\n");
    printf("Select configuration: ");
    scanf("%d", &choice);

    printf("Enter number of resistors: ");
    scanf("%d", &n);

    if (choice == 1) {
        for (int i = 1; i <= n; i++) {
            printf("  Enter resistance for R%d (Ohms): ", i);
            scanf("%lf", &r);
            total += r;
        }
        printf("\n%sResult:%s\n", CLR_YELLOW, CLR_RESET);
        printf("%s  Equivalent Resistance (Req) = %.2f Ohms%s\n", CLR_GREEN, total, CLR_RESET);
        printf("\n   [R1]--[R2]--...--[Rn]\n");
    } 
    else if (choice == 2) {
        double inverseTotal = 0;
        for (int i = 1; i <= n; i++) {
            printf("  Enter resistance for R%d (Ohms): ", i);
            scanf("%lf", &r);
            if (r != 0) inverseTotal += (1.0 / r);
        }
        total = 1.0 / inverseTotal;
        printf("\n%sResult:%s\n", CLR_YELLOW, CLR_RESET);
        printf("%s  Equivalent Resistance (Req) = %.2f Ohms%s\n", CLR_GREEN, total, CLR_RESET);
        printf("\n      /---[R1]---\\\n");
        printf("   --<----[R2]---->--\n");
        printf("      \\---[Rn]---/\n");
    }

    printf("\nPress Enter to return...");
    while (getchar() != '\n'); getchar();
}
