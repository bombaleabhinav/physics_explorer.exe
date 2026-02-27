#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define CLR_CYAN    "\033[96m"
#define CLR_GREEN   "\033[92m"
#define CLR_MAGENTA "\033[95m"
#define CLR_RESET   "\033[0m"

void runSHMSimulator() {
    double A, freq, t;
    
    printf("\n%s--- SHM Visualizer (Sine Wave) ---%s\n", CLR_CYAN, CLR_RESET);
    printf("Enter Amplitude (A): ");
    scanf("%lf", &A);
    printf("Enter Frequency (f) in Hz: ");
    scanf("%lf", &freq);

    printf("\n%sWaveform Generation:%s\n", CLR_MAGENTA, CLR_RESET);
    
    int rows = 12;
    int cols = 60;
    
    for (int i = rows; i >= -rows; i--) {
        if (i == 0) printf("  0 |");
        else if (i == rows) printf(" +A |");
        else if (i == -rows) printf(" -A |");
        else printf("    |");

        for (int j = 0; j < cols; j++) {
            t = (double)j / cols;
            double displacement = A * sin(2 * PI * freq * t);
            int scaledVal = (int)((displacement / A) * rows);
            
            if (scaledVal == i) printf("%s#%s", CLR_GREEN, CLR_RESET);
            else if (i == 0) printf("-");
            else printf(" ");
        }
        printf("\n");
    }
    printf("     0");
    for(int j=0; j<cols; j++) printf("-");
    printf(" Time ->\n");

    printf("\nPress Enter to return...");
    while (getchar() != '\n'); getchar();
}
