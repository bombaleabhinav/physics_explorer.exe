#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define CLR_CYAN    "\033[96m"
#define CLR_YELLOW  "\033[93m"
#define CLR_RESET   "\033[0m"
#define CLR_BOLD    "\033[1m"

void runRefractionSimulator() {
    double n1, n2, angleI, angleR;

    printf("\n%s--- Light Refraction (Snell's Law) ---%s\n", CLR_CYAN, CLR_RESET);
    printf("Enter Refractive Index n1 (e.g., Air=1.0): ");
    scanf("%lf", &n1);
    printf("Enter Refractive Index n2 (e.g., Water=1.33): ");
    scanf("%lf", &n2);
    printf("Enter Angle of Incidence (degrees): ");
    scanf("%lf", &angleI);

    double radI = angleI * PI / 180.0;
    double sinR = (n1 / n2) * sin(radI);

    if (sinR > 1.0) {
        printf("\n%s[!] Total Internal Reflection Occurs!%s\n", CLR_YELLOW, CLR_RESET);
    } else {
        angleR = asin(sinR) * 180.0 / PI;
        printf("\n%sResults:%s\n", CLR_BOLD, CLR_RESET);
        printf("  Angle of Refraction: %.2f degrees\n", angleR);
    }

    printf("\n%sVisual Diagram:%s\n", CLR_YELLOW, CLR_RESET);
    printf("        \\   |   (Normal)\n");
    printf("         \\  |  /\n");
    printf("  (n1)    \\ | /\n");
    printf("  ----------+---------- (Interface)\n");
    printf("  (n2)      | \\\n");
    printf("            |  \\\n");
    printf("            |   \\\n");

    printf("\nPress Enter to return...");
    while (getchar() != '\n'); getchar();
}
