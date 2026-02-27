#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define CLR_RESET   "\033[0m"
#define CLR_BOLD    "\033[1m"
#define CLR_RED     "\033[91m"
#define CLR_GREEN   "\033[92m"
#define CLR_YELLOW  "\033[93m"
#define CLR_BLUE    "\033[94m"
#define CLR_MAGENTA "\033[95m"
#define CLR_CYAN    "\033[96m"
#define CLR_WHITE   "\033[97m"


void runProjectileSimulator();
void runResistorSimulator();
void runSHMSimulator();
void runWaveSuperposition();
void runRefractionSimulator();


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const char* title) {
    clearScreen();
    printf("\n  %s========================================================%s\n", CLR_CYAN, CLR_RESET);
    printf("  %s%s           PHYSICS CONCEPT EXPLORER %s\n", CLR_BOLD, CLR_WHITE, CLR_RESET);
    printf("  %s========================================================%s\n", CLR_CYAN, CLR_RESET);
    if (title) {
        printf("  %s  >> %s %s\n", CLR_YELLOW, title, CLR_RESET);
        printf("  %s--------------------------------------------------------%s\n", CLR_CYAN, CLR_RESET);
    }
}

void animateLoading(const char* label) {
    printf("\n  %s", label);
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        SLEEP(200);
    }
    printf(" [DONE]\n");
}

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | 0x0004);
#endif

    int choice;
    do {
        printHeader("MAIN MENU");
        printf("\n  %s1.%s Projectile Motion Simulator\n", CLR_GREEN, CLR_RESET);
        printf("  %s2.%s Resistor Network Simulator (Series/Parallel)\n", CLR_GREEN, CLR_RESET);
        printf("  %s3.%s Simple Harmonic Motion (SHM) Visualizer\n", CLR_GREEN, CLR_RESET);
        printf("  %s4.%s Wave Superposition (Interference)\n", CLR_GREEN, CLR_RESET);
        printf("  %s5.%s Light Refraction & Reflection\n", CLR_GREEN, CLR_RESET);
        printf("  %s0.%s Exit Program\n", CLR_RED, CLR_RESET);
        
        printf("\n  %sEnter Choice:%s ", CLR_CYAN, CLR_RESET);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: animateLoading("Initializing Projectile Simulator"); runProjectileSimulator(); break;
            case 2: animateLoading("Loading Circuit Data"); runResistorSimulator(); break;
            case 3: animateLoading("Starting SHM Visualizer"); runSHMSimulator(); break;
            case 4: animateLoading("Starting Wave Superposition"); runWaveSuperposition(); break;
            case 5: animateLoading("Starting Refraction Simulator"); runRefractionSimulator(); break;
            case 0: 
                printf("\n  %sClosing Physics Explorer. Goodbye!%s\n", CLR_MAGENTA, CLR_RESET);
                SLEEP(500);
                break;
            default:
                printf("\n  %sInvalid Choice!%s\n", CLR_RED, CLR_RESET);
                SLEEP(1000);
        }
    } while (choice != 0);

    return 0;
}
