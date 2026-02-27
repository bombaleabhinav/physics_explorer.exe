#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define CLR_CYAN    "\033[96m"
#define CLR_GREEN   "\033[92m"
#define CLR_YELLOW  "\033[93m"
#define CLR_MAGENTA "\033[95m"
#define CLR_RED     "\033[91m"
#define CLR_BLUE    "\033[94m"
#define CLR_WHITE   "\033[97m"
#define CLR_BOLD    "\033[1m"
#define CLR_RESET   "\033[0m"

static void drawWave(double amp, double freq, const char* color,
                     const char* tag, int rows, int cols)
{
    double maxA = (amp > 0) ? amp : 1;

    for (int i = rows; i >= -rows; i--) {
        if      (i == rows)  printf("  %s+A%s |", color, CLR_RESET);
        else if (i == 0)     printf("   0 |");
        else if (i == -rows) printf("  %s-A%s |", color, CLR_RESET);
        else                 printf("     |");

        for (int j = 0; j < cols; j++) {
            double t = (double)j / cols;
            double y = amp * sin(2 * PI * freq * t);
            int sv   = (int)((y / maxA) * rows);

            if (sv == i)      printf("%s%s%s", color, tag, CLR_RESET);
            else if (i == 0)  printf("-");
            else              printf(" ");
        }
        printf("\n");
    }
    printf("      ");
    for (int j = 0; j < cols; j++) printf("-");
    printf(" t ->\n");
}

static void drawResultant(double a1, double f1,
                          double a2, double f2,
                          const char* color, const char* tag,
                          int rows, int cols)
{
    double maxA = fabs(a1) + fabs(a2);
    if (maxA == 0) maxA = 1;

    for (int i = rows; i >= -rows; i--) {
        if      (i == rows)  printf("  %s+A%s |", color, CLR_RESET);
        else if (i == 0)     printf("   0 |");
        else if (i == -rows) printf("  %s-A%s |", color, CLR_RESET);
        else                 printf("     |");

        for (int j = 0; j < cols; j++) {
            double t  = (double)j / cols;
            double y1 = a1 * sin(2 * PI * f1 * t);
            double y2 = a2 * sin(2 * PI * f2 * t);
            double y  = y1 + y2;
            int sv    = (int)((y / maxA) * rows);

            if (sv == i)      printf("%s%s%s", color, tag, CLR_RESET);
            else if (i == 0)  printf("-");
            else              printf(" ");
        }
        printf("\n");
    }
    printf("      ");
    for (int j = 0; j < cols; j++) printf("-");
    printf(" t ->\n");
}

static void printWaveInfo(const char* label, const char* color,
                          double amp, double freq)
{
    double omega  = 2 * PI * freq;
    double period = (freq != 0) ? 1.0 / freq : 0;

    printf("\n  %s%s%s %s%s%s\n", CLR_BOLD, color, label, CLR_RESET, "", "");
    printf("  %s---------------------------------------%s\n", color, CLR_RESET);
    printf("  | Amplitude  (A) : %s%.4f%s\n", CLR_WHITE, amp,   CLR_RESET);
    printf("  | Frequency  (f) : %s%.4f Hz%s\n", CLR_WHITE, freq,  CLR_RESET);
    printf("  | Ang. Freq  (w) : %s%.4f rad/s%s\n", CLR_WHITE, omega, CLR_RESET);
    printf("  | Period     (T) : %s%.4f s%s\n", CLR_WHITE, period, CLR_RESET);
    printf("  | Equation       : %sy = %.2f * sin(2pi * %.2f * t)%s\n",
           color, amp, freq, CLR_RESET);
    printf("  %s---------------------------------------%s\n", color, CLR_RESET);
}

void runWaveSuperposition() {
    double a1, f1, a2, f2;
    int rows = 10;
    int cols = 60;

    printf("\n  %s%s========================================================%s\n",
           CLR_BOLD, CLR_CYAN, CLR_RESET);
    printf("  %s%s       WAVE SUPERPOSITION (INTERFERENCE)              %s\n",
           CLR_BOLD, CLR_WHITE, CLR_RESET);
    printf("  %s%s========================================================%s\n",
           CLR_BOLD, CLR_CYAN, CLR_RESET);

    printf("\n  %sWave 1 ->%s Enter Amplitude & Frequency (Hz): ", CLR_YELLOW, CLR_RESET);
    scanf("%lf %lf", &a1, &f1);
    printf("  %sWave 2 ->%s Enter Amplitude & Frequency (Hz): ", CLR_YELLOW, CLR_RESET);
    scanf("%lf %lf", &a2, &f2);

    printWaveInfo("WAVE 1", CLR_YELLOW, a1, f1);
    printf("\n  %s%sWaveform - Wave 1:%s\n\n", CLR_BOLD, CLR_YELLOW, CLR_RESET);
    drawWave(a1, f1, CLR_YELLOW, "#", rows, cols);

    printWaveInfo("WAVE 2", CLR_MAGENTA, a2, f2);
    printf("\n  %s%sWaveform - Wave 2:%s\n\n", CLR_BOLD, CLR_MAGENTA, CLR_RESET);
    drawWave(a2, f2, CLR_MAGENTA, "*", rows, cols);

    double aMax = fabs(a1) + fabs(a2);
    double aMin = fabs(fabs(a1) - fabs(a2));

    printf("\n  %s%s========================================================%s\n",
           CLR_BOLD, CLR_GREEN, CLR_RESET);
    printf("  %s%s            RESULTANT  WAVE  (y = y1 + y2)            %s\n",
           CLR_BOLD, CLR_WHITE, CLR_RESET);
    printf("  %s%s========================================================%s\n",
           CLR_BOLD, CLR_GREEN, CLR_RESET);

    printf("\n  %s---------------------------------------%s\n", CLR_GREEN, CLR_RESET);
    printf("  | Max Amplitude (A1+A2) : %s%.4f%s\n", CLR_WHITE, aMax, CLR_RESET);
    printf("  | Min Amplitude |A1-A2| : %s%.4f%s\n", CLR_WHITE, aMin, CLR_RESET);

    if (f1 == f2) {
        double aR = sqrt(a1*a1 + a2*a2 + 2*a1*a2);
        printf("  | Resultant Amp (same f): %s%.4f%s\n", CLR_WHITE, aR, CLR_RESET);
        printf("  | Frequency             : %s%.4f Hz%s\n", CLR_WHITE, f1, CLR_RESET);
        printf("  | Ang. Freq  (w)        : %s%.4f rad/s%s\n",
               CLR_WHITE, 2*PI*f1, CLR_RESET);
        printf("  | Period     (T)        : %s%.4f s%s\n",
               CLR_WHITE, (f1!=0?1.0/f1:0), CLR_RESET);
        printf("  | Type                  : %sConstructive Superposition%s\n",
               CLR_GREEN, CLR_RESET);
        printf("  | Equation              : %sy = %.2f * sin(2pi * %.2f * t)%s\n",
               CLR_GREEN, aR, f1, CLR_RESET);
    } else {
        double fBeat = fabs(f1 - f2);
        double fAvg  = (f1 + f2) / 2.0;
        printf("  | Beat Frequency        : %s%.4f Hz%s\n", CLR_WHITE, fBeat, CLR_RESET);
        printf("  | Avg  Frequency        : %s%.4f Hz%s\n", CLR_WHITE, fAvg,  CLR_RESET);
        printf("  | Type                  : %sBeat / Interference Pattern%s\n",
               CLR_YELLOW, CLR_RESET);
        printf("  | Equation              : %sy = %.2f*sin(2pi*%.2f*t) + %.2f*sin(2pi*%.2f*t)%s\n",
               CLR_GREEN, a1, f1, a2, f2, CLR_RESET);
    }
    printf("  %s---------------------------------------%s\n", CLR_GREEN, CLR_RESET);

    printf("\n  %s%sResultant Waveform:%s\n\n", CLR_BOLD, CLR_GREEN, CLR_RESET);
    drawResultant(a1, f1, a2, f2, CLR_GREEN, "@", rows, cols);

    printf("\n  Press Enter to return...");
    while (getchar() != '\n');
    getchar();
}
