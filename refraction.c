#include <stdio.h>
#include <math.h>

#define PI 3.14
#define CLR_CYAN    "\033[96m"
#define CLR_YELLOW  "\033[93m"
#define CLR_GREEN   "\033[92m"
#define CLR_RED     "\033[91m"
#define CLR_MAGENTA "\033[95m"
#define CLR_WHITE   "\033[97m"
#define CLR_BLUE    "\033[94m"
#define CLR_BOLD    "\033[1m"
#define CLR_RESET   "\033[0m"


#define ROWS   21          /* total rows  */
#define COLS   51          /* total cols  */
#define HALF   (ROWS / 2)  /* row index of the interface*/
#define HALF_C (COLS / 2)  /* col index of the normal*/

void runRefractionSimulator() {
    double n1, n2, angleI;

    printf("\n  %s%s========================================================%s\n",
           CLR_BOLD, CLR_CYAN, CLR_RESET);
    printf("  %s%s       LIGHT REFRACTION & REFLECTION (Snell's Law)     %s\n",
           CLR_BOLD, CLR_WHITE, CLR_RESET);
    printf("  %s%s========================================================%s\n",
           CLR_BOLD, CLR_CYAN, CLR_RESET);

    printf("\n  %sEnter Refractive Index n1%s (e.g. Air = 1.0)    : ", CLR_YELLOW, CLR_RESET);
    scanf("%lf", &n1);
    printf("  %sEnter Refractive Index n2%s (e.g. Water = 1.33) : ", CLR_YELLOW, CLR_RESET);
    scanf("%lf", &n2);
    printf("  %sEnter Angle of Incidence%s  (degrees, 0-90)     : ", CLR_YELLOW, CLR_RESET);
    scanf("%lf", &angleI);

    /* clamp to 0-90 */
    if (angleI < 0)  angleI = 0;
    if (angleI > 90) angleI = 90;

    double radI = angleI * PI / 180.0;
    double sinR = (n1 / n2) * sin(radI);
    int    tir  = (sinR > 1.0 || sinR < -1.0);   /* total internal reflection */

    double angleR_deg = 0;
    double radR       = 0;
    if (!tir) {
        radR       = asin(sinR);
        angleR_deg = radR * 180.0 / PI;
    }

    /* ---------- Results ---------- */
    printf("\n  %s---------------------------------------%s\n", CLR_CYAN, CLR_RESET);
    printf("  | n1                       : %s%.4f%s\n", CLR_WHITE, n1, CLR_RESET);
    printf("  | n2                       : %s%.4f%s\n", CLR_WHITE, n2, CLR_RESET);
    printf("  | Angle of Incidence  (i)  : %s%.2f°%s\n", CLR_WHITE, angleI, CLR_RESET);
    printf("  | Angle of Reflection (r)  : %s%.2f°%s\n", CLR_WHITE, angleI, CLR_RESET);

    if (tir) {
        printf("  | Angle of Refraction      : %sTOTAL INTERNAL REFLECTION%s\n",
               CLR_RED, CLR_RESET);
        double critAngle = asin(n2 / n1) * 180.0 / PI;
        printf("  | Critical Angle           : %s%.2f°%s\n", CLR_WHITE, critAngle, CLR_RESET);
        printf("  | Snell's Law              : %sn1*sin(i) = n2*sin(r)%s\n",
               CLR_CYAN, CLR_RESET);
        printf("  | Note                     : %ssin(r) = %.4f > 1 => TIR%s\n",
               CLR_RED, sinR, CLR_RESET);
    } else {
        printf("  | Angle of Refraction (R)  : %s%.2f°%s\n", CLR_WHITE, angleR_deg, CLR_RESET);
        printf("  | Snell's Law              : %sn1*sin(i) = n2*sin(r)%s\n",
               CLR_CYAN, CLR_RESET);
        printf("  |   %.4f * sin(%.2f) = %.4f * sin(%.2f)\n",
               n1, angleI, n2, angleR_deg);
    }
    printf("  %s---------------------------------------%s\n", CLR_CYAN, CLR_RESET);

    /* ========== Build the diagram ========== */
    char  grid[ROWS][COLS];
    char  colr[ROWS][COLS];   /* 0=default, 1=yellow(incident), 2=magenta(reflect), 3=green(refract), 4=cyan(normal), 5=blue(interface) */

    /* fill blank */
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = ' ';
            colr[r][c] = 0;
        }

    /* draw the normal (vertical dashed line) */
    for (int r = 0; r < ROWS; r++) {
        grid[r][HALF_C] = '|';
        colr[r][HALF_C] = 4;   /* cyan */
    }

    /* draw the interface (horizontal line) */
    for (int c = 0; c < COLS; c++) {
        grid[HALF][c] = '-';
        colr[HALF][c] = 5;     /* blue */
    }
    grid[HALF][HALF_C] = '+';
    colr[HALF][HALF_C] = 5;

    /* slopes:  columns per row  =  tan(angle) */
    double slopeI = tan(radI);       /* incident */
    double slopeR_refl = tan(radI);  /* reflected (same angle, other side) */
    double slopeRefr   = tir ? 0 : tan(radR);

    int rayLen = HALF;  /* number of rows to draw each ray */

    /* --- Incident ray: upper half, going UP from center, left side --- */
    for (int step = 1; step <= rayLen; step++) {
        int r = HALF - step;                          /* row above interface */
        int c = HALF_C - (int)(step * slopeI + 0.5);  /* to the left */
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
            grid[r][c] = '\\';
            colr[r][c] = 1;   /* yellow */
        }
    }

    /* --- Reflected ray: upper half, going UP from center, right side --- */
    for (int step = 1; step <= rayLen; step++) {
        int r = HALF - step;
        int c = HALF_C + (int)(step * slopeR_refl + 0.5);
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
            grid[r][c] = '/';
            colr[r][c] = 2;   /* magenta */
        }
    }

    /* --- Refracted ray (or TIR reflected back into medium 1) --- */
    if (tir) {
        /* TIR: all light reflects, draw a stronger reflected ray (already drawn) */
        /* optionally draw a faint indication on the lower half -- skip for clarity */
    } else {
        for (int step = 1; step <= rayLen; step++) {
            int r = HALF + step;                            /* row below */
            int c = HALF_C + (int)(step * slopeRefr + 0.5); /* bends right */
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                grid[r][c] = '\\';
                colr[r][c] = 3;   /* green */
            }
        }
    }

    /* ========== Print the diagram ========== */
    printf("\n  %s%sRay Diagram:%s\n\n", CLR_BOLD, CLR_YELLOW, CLR_RESET);

    /* legend */
    printf("    %s\\%s Incident   %s/%s Reflected   ",
           CLR_YELLOW, CLR_RESET, CLR_MAGENTA, CLR_RESET);
    if (!tir) printf("%s\\%s Refracted", CLR_GREEN, CLR_RESET);
    else      printf("%s(TIR - no refracted ray)%s", CLR_RED, CLR_RESET);
    printf("\n\n");

    for (int r = 0; r < ROWS; r++) {
        /* medium label on the left */
        if (r == 2)          printf("  %sn1=%.2f%s  ", CLR_YELLOW, n1, CLR_RESET);
        else if (r == ROWS-3) printf("  %sn2=%.2f%s  ", CLR_GREEN,  n2, CLR_RESET);
        else                  printf("          ");

        for (int c = 0; c < COLS; c++) {
            const char* cc;
            switch (colr[r][c]) {
                case 1: cc = CLR_YELLOW;  break;
                case 2: cc = CLR_MAGENTA; break;
                case 3: cc = CLR_GREEN;   break;
                case 4: cc = CLR_CYAN;    break;
                case 5: cc = CLR_BLUE;    break;
                default: cc = CLR_RESET;  break;
            }
            printf("%s%c%s", cc, grid[r][c], CLR_RESET);
        }

        /* label the normal at top */
        if (r == 0) printf("  Normal");
        printf("\n");
    }

    printf("\n  Press Enter to return...");
    while (getchar() != '\n');
    getchar();
}
