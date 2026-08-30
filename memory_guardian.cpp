#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "campus_quest.h"

int ensureCapacity(Team **teams, int *capacity, int required)
{
    if (*capacity >= required) {
        return 1; // Already enough capacity
    }

    // Calculate new capacity (double until sufficient)
    int newCapacity = *capacity;
    if (newCapacity < 1) newCapacity = 1;
    while (newCapacity < required) {
        newCapacity *= 2;
    }

    // Reallocate memory
    Team *temp = static_cast<Team*>(std::realloc(*teams, newCapacity * sizeof(Team)));
    if (temp == nullptr) {
        return 0; // Allocation failed
    }

    *teams = temp;
    *capacity = newCapacity;
    return 1;
}

void readText(const char *prompt, char text[], int limit)
{
    std::cout << prompt;
    if (fgets(text, limit, stdin) != NULL)
        text[std::strcspn(text, "\n")] = '\0';
}

int readInt(const char *prompt, int *value)
{
    char line[LINE_LEN], extra;
    std::cout << prompt;
    if (fgets(line, sizeof line, stdin) == NULL) return 0;
    return sscanf(line, "%d %c", value, &extra) == 1;
}