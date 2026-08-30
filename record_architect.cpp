#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "campus_quest.h"

/* Record architecture functions */
int findTeamIndex(const Team teams[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (teams[i].id == id) {
            return i;
        }
    }
    return -1;
}

int addTeam(Team **teams, int *size, int *capacity, Team candidate) {
    // Validate ID (positive)
    if (candidate.id <= 0) {
        return 0;
    }

    // Check for duplicate ID
    if (findTeamIndex(*teams, *size, candidate.id) != -1) {
        return 0;
    }

    // Ensure capacity
    if (!ensureCapacity(teams, capacity, *size + 1)) {
        return 0;
    }

    // Add the team
    (*teams)[*size] = candidate;
    (*size)++;
    return 1;
}

int recordMission(Team teams[], int size, int id, int points) {
    // Validate points (1-100)
    if (points < 1 || points > 100) {
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        return 0;
    }

    // Update score and missions
    teams[index].score += points;
    teams[index].missions++;
    return 1;
}

int deleteTeam(Team teams[], int *size, int id) {
    int index = findTeamIndex(teams, *size, id);
    if (index == -1) {
        return 0;
    }

    // Shift elements left
    for (int i = index; i < *size - 1; i++) {
        teams[i] = teams[i + 1];
    }

    (*size)--;
    return 1;
}

void sortLeaderboard(Team teams[], int size) {
    // Sort by descending score
    std::sort(teams, teams + size, [](const Team& a, const Team& b) {
        return a.score > b.score;
    });
}

void displayTeams(const Team teams[], int size) {
    if (size == 0) {
        std::cout << "No teams to display.\n";
        return;
    }

    // Print header
    std::cout << "\n=== LEADERBOARD ===\n";
    std::cout << "ID\tName\t\tScore\tMissions\n";
    std::cout << "----------------------------------------\n";

    // Print each team
    for (int i = 0; i < size; i++) {
        std::cout << teams[i].id << "\t"
                  << teams[i].name << "\t\t"
                  << teams[i].score << "\t"
                  << teams[i].missions << "\n";
    }
    std::cout << std::endl;
}

int loadTeams(const char *filename, Team **teams, int *size, int *capacity) {
    FILE *file = std::fopen(filename, "r");
    if (file == nullptr) {
        // File doesn't exist yet - that's OK
        *teams = nullptr;
        *size = 0;
        *capacity = 0;
        return 1;
    }

    // Free existing memory
    if (*teams != nullptr) {
        std::free(*teams);
        *teams = nullptr;
    }

    *size = 0;
    *capacity = 0;

    char line[LINE_LEN];
    while (std::fgets(line, sizeof(line), file) != nullptr) {
        // Remove newline
        line[std::strcspn(line, "\n")] = '\0';

        // Parse id|name|score|missions
        Team temp;
        char *token = std::strtok(line, "|");
        if (token == nullptr) continue;
        temp.id = std::atoi(token);

        token = std::strtok(nullptr, "|");
        if (token == nullptr) continue;
        std::strncpy(temp.name, token, NAME_LEN - 1);
        temp.name[NAME_LEN - 1] = '\0';

        token = std::strtok(nullptr, "|");
        if (token == nullptr) continue;
        temp.score = std::atoi(token);

        token = std::strtok(nullptr, "|");
        if (token == nullptr) continue;
        temp.missions = std::atoi(token);

        // Ensure capacity and add
        if (!ensureCapacity(teams, capacity, *size + 1)) {
            std::fclose(file);
            return 0;
        }

        (*teams)[*size] = temp;
        (*size)++;
    }

    std::fclose(file);
    return 1;
}

int saveTeams(const char *filename, const Team teams[], int size) {
    FILE *file = std::fopen(filename, "w");
    if (file == nullptr) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (std::fprintf(file, "%d|%s|%d|%d\n",
                         teams[i].id, teams[i].name,
                         teams[i].score, teams[i].missions) < 0) {
            std::fclose(file);
            return 0;
        }
    }

    if (std::fclose(file) != 0) {
        return 0;
    }

    return 1;
}