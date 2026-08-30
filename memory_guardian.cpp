#include <cstdio>
#include <cstdlib>

typedef struct {
    int id;
    char name[40];
    int score;
    int missions;
} Team;

bool ensureCapacity(Team** teams, int* capacity, int required) {
    if (required <= *capacity) return true;

    int newCapacity = (*capacity == 0) ? 2 : *capacity * 2;
    while (newCapacity < required) {
        newCapacity *= 2;
    }

    Team* temp = (Team*)realloc(*teams, newCapacity * sizeof(Team));
    if (temp == NULL) {
        return false;
    }

    *teams = temp;
    *capacity = newCapacity;
    return true;
}

void cleanupTeams(Team** teams, int* size, int* capacity) {
    if (teams != NULL && *teams != NULL) {
        free(*teams);
        *teams = NULL;
    }
    if (size != NULL) *size = 0;
    if (capacity != NULL) *capacity = 0;
}

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;

    printf("=== MEMORY GUARDIAN CORE DEMO ===\n");
    printf("Initial State  : teams=%p, size=%d, capacity=%d\n\n", (void*)teams, size, capacity);

    if (ensureCapacity(&teams, &capacity, 3)) {
        printf("After Growth   : teams=%p, capacity=%d\n", (void*)teams, capacity);
        
        teams[0].id = 101;
        teams[1].id = 102;
        teams[2].id = 103;
        size = 3;
        
        printf("Active Records : size=%d (Logical Range: 0 to %d)\n\n", size, size - 1);
    }

    cleanupTeams(&teams, &size, &capacity);
    printf("After Cleanup  : teams=%p, size=%d, capacity=%d\n", (void*)teams, size, capacity);
    printf("Status         : Allocation safely freed, no dangling reference.\n");

    return 0;
}