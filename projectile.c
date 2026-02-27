#include <stdio.h>
#include <math.h>

#define PI 3.14
#define G  9.8

// colro codes
#define CLR_CYAN    "\033[96m"
#define CLR_GREEN   "\033[92m"
#define CLR_YELLOW  "\033[93m"
#define CLR_RESET   "\033[0m"
#define CLR_BOLD    "\033[1m"

void runProjectileSimulator() {
    double v, angle, rad;
    
    printf("\n%s--- Projectile Motion Simulator ---%s\n", CLR_CYAN, CLR_RESET);
    printf("Enter initial velocity (m/s): ");
    scanf("%lf", &v);
    printf("Enter launch angle (degrees): ");
    scanf("%lf", &angle);

    rad = angle * PI / 180.0;

    double time = (2 * v * sin(rad)) / G;
    double range = (v * v * sin(2 * rad)) / G;
    double height = (v * v * pow(sin(rad), 2)) / (2 * G);

    printf("\n%sCalculation Results:%s\n", CLR_YELLOW, CLR_RESET);
    printf("  Time of Flight : %.2f s\n", time);
    printf("  Max Range      : %.2f m\n", range);
    printf("  Max Height     : %.2f m\n", height);

    printf("\n%sTrajectory Visualization:%s\n", CLR_BOLD, CLR_RESET);
    
    // Simple Graph
    int rows = 10, cols = 40;
    for (int i = rows; i >= 0; i--) {
        printf("%2d |", i);
        for (int j = 0; j <= cols; j++) {j
            double t = (double)j / cols * time;
            double y = v * sin(rad) * t - 0.5 * G * t * t;
            int scaledY = (int)((y / height) * rows);
            
            if (scaledY == i) printf("%s*%s", CLR_GREEN, CLR_RESET);
            else if (i == 0) printf("_");
            else printf(" ");
        }
        printf("\n");
    }
    printf("    0");
    for(int j=0; j<cols; j++) printf("-");
    printf(" Time\n");

    printf("\nPress Enter to return...");
    while (getchar() != '\n'); getchar();
}
