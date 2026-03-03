#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_NODES 1000
#define MAX_ID 50
#define MAX_LINE 512
#define FAN_THRESHOLD 3
#define MAX_CYCLE_DEPTH 5

// ================================
// DATA STRUCTURES
// ================================

typedef struct Edge {
    int to;
    double amount;
    time_t timestamp;
    struct Edge* next;
} Edge;

typedef struct {
    char id[MAX_ID];
    int inDeg;
    int outDeg;
    double totalIn;
    double totalOut;
    Edge* adj;
} Node;

Node nodes[MAX_NODES];
int nodeCount = 0;

// ================================
// HELPER FUNCTIONS
// ================================

void pause_screen() {
    printf("\nPress ENTER to continue...");
    getchar();
}

void clear_screen() {
    system(CLEAR);
}

void print_banner() {
    printf("=============================================\n");
    printf("     FORENSIC FLOW - AML DEMO ENGINE\n");
    printf("     Graph Based Fraud Detection (C)\n");
    printf("=============================================\n\n");
}

int get_node_index(char* id) {
    for (int i = 0; i < nodeCount; i++) {
        if (strcmp(nodes[i].id, id) == 0)
            return i;
    }

    strcpy(nodes[nodeCount].id, id);
    nodes[nodeCount].inDeg = 0;
    nodes[nodeCount].outDeg = 0;
    nodes[nodeCount].totalIn = 0;
    nodes[nodeCount].totalOut = 0;
    nodes[nodeCount].adj = NULL;

    return nodeCount++;
}

time_t parse_time(char* str) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    int year, month, day, hour, min, sec;

    if (sscanf(str, "%d-%d-%d %d:%d:%d",
               &year, &month, &day,
               &hour, &min, &sec) != 6) {
        return 0;
    }

    tm.tm_year = year - 1900;
    tm.tm_mon  = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min  = min;
    tm.tm_sec  = sec;

    return mktime(&tm);
}

void add_edge(int from, int to, double amount, time_t ts) {
    Edge* e = malloc(sizeof(Edge));
    e->to = to;
    e->amount = amount;
    e->timestamp = ts;
    e->next = nodes[from].adj;
    nodes[from].adj = e;

    nodes[from].outDeg++;
    nodes[to].inDeg++;
    nodes[from].totalOut += amount;
    nodes[to].totalIn += amount;
}

void load_csv(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        char tx[50], sender[50], receiver[50], amountStr[50], timestamp[50];

        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
               tx, sender, receiver, amountStr, timestamp);

        int s = get_node_index(sender);
        int r = get_node_index(receiver);
        double amount = atof(amountStr);
        time_t ts = parse_time(timestamp);

        add_edge(s, r, amount, ts);
    }

    fclose(file);
}

// ================================
// DETECTION LOGIC
// ================================

void detect_smurfing() {
    printf("\n--- SMURFING DETECTION ---\n\n");

    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].inDeg >= FAN_THRESHOLD)
            printf("Fan-In  : %-10s | InDeg: %d\n", nodes[i].id, nodes[i].inDeg);

        if (nodes[i].outDeg >= FAN_THRESHOLD)
            printf("Fan-Out : %-10s | OutDeg: %d\n", nodes[i].id, nodes[i].outDeg);
    }
}

int visited[MAX_NODES];
int path[MAX_NODES];

void dfs_cycle(int start, int current, int depth) {
    if (depth > MAX_CYCLE_DEPTH)
        return;

    visited[current] = 1;
    path[depth] = current;

    Edge* e = nodes[current].adj;
    while (e) {
        if (e->to == start && depth >= 2) {
            printf("Cycle Found: ");
            for (int i = 0; i <= depth; i++)
                printf("%s -> ", nodes[path[i]].id);
            printf("%s\n", nodes[start].id);
        }
        else if (!visited[e->to]) {
            dfs_cycle(start, e->to, depth + 1);
        }
        e = e->next;
    }

    visited[current] = 0;
}

void detect_cycles() {
    printf("\n--- CYCLE DETECTION ---\n\n");

    for (int i = 0; i < nodeCount; i++) {
        memset(visited, 0, sizeof(visited));
        dfs_cycle(i, i, 0);
    }
}

void calculate_scores() {
    printf("\n--- SUSPICION SCORES ---\n\n");

    for (int i = 0; i < nodeCount; i++) {
        int score = 0;

        if (nodes[i].inDeg >= FAN_THRESHOLD) score += 20;
        if (nodes[i].outDeg >= FAN_THRESHOLD) score += 20;

        if (nodes[i].totalIn > 0 && nodes[i].totalOut > 0) {
            double ratio = nodes[i].totalIn / nodes[i].totalOut;
            if (ratio > 0.8 && ratio < 1.2)
                score += 10;
        }

        if (score > 0)
            printf("Account: %-10s | Risk Score: %d\n", nodes[i].id, score);
    }
}

// ================================
// MENU SYSTEM
// ================================

void show_menu() {
    printf("\n================ MENU ================\n");
    printf("1. Detect Smurfing Patterns\n");
    printf("2. Detect Cycles (3-5 length)\n");
    printf("3. Calculate Suspicion Scores\n");
    printf("4. Run Full Analysis\n");
    printf("5. Exit\n");
    printf("======================================\n");
    printf("Enter choice: ");
}

// ================================
// MAIN
// ================================

int main() {

    char filepath[256];

    clear_screen();
    print_banner();

    printf("Enter CSV file path: ");
    fgets(filepath, sizeof(filepath), stdin);
    filepath[strcspn(filepath, "\n")] = 0;

    load_csv(filepath);

    printf("\nLoaded %d accounts successfully!\n", nodeCount);
    pause_screen();

    int choice;

    while (1) {
        clear_screen();
        print_banner();
        show_menu();
        scanf("%d", &choice);
        getchar(); // clear newline

        clear_screen();
        print_banner();

        switch (choice) {
            case 1:
                detect_smurfing();
                pause_screen();
                break;

            case 2:
                detect_cycles();
                pause_screen();
                break;

            case 3:
                calculate_scores();
                pause_screen();
                break;

            case 4:
                detect_smurfing();
                detect_cycles();
                calculate_scores();
                pause_screen();
                break;

            case 5:
                printf("Exiting ForensicFlow...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    }

    return 0;
}