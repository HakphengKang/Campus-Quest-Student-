#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "campus_quest.h"

int addTeam(Team **teams, int *size, int *capacity, Team candidate);
int recordMission(Team teams[], int size, int id, int points);
int deleteTeam(Team teams[], int *size, int id);
void sortLeaderboard(Team teams[], int size);
void displayTeams(const Team teams[], int size);
int loadTeams(const char *filename, Team **teams, int *size, int *capacity);
int saveTeams(const char *filename, const Team teams[], int size);
void readText(const char *prompt, char text[], int limit);
int readInt(const char *prompt, int *value);

int main(void)
{
    Team *teams = nullptr;
    int size = 0;
    int capacity = 0;
    int choice = 0;

    loadTeams("teams.txt", &teams, &size, &capacity);

    do {
        std::cout << "\n=== CAMPUS QUEST LEADERBOARD ===\n"
                  << "1. Register a team\n2. Record mission points\n3. Find a team\n"
                  << "4. Remove a team\n5. Show leaderboard\n6. Save and exit\n";

        if (!readInt("Choose: ", &choice)) {
            std::cout << "Invalid menu input.\n";
            continue;
        }

        if (choice == 1) {
            Team candidate = {0, "", 0, 0};

            while (true) {
                if (!readInt("Team ID: ", &candidate.id)) {
                    std::cout << "Invalid team ID. Please enter a number.\n";
                    continue;
                }

                if (findTeamIndex(teams, size, candidate.id) != -1) {
                    std::cout << "Duplicate ID: that team ID already exists. Please enter a different ID.\n";
                    continue;
                }

                break;
            }

            readText("Team name: ", candidate.name, NAME_LEN);

            if (addTeam(&teams, &size, &capacity, candidate)) {
                if (!saveTeams("teams.txt", teams, size)) {
                    std::cout << "Team registered successfully, but failed to save to file.\n";
                } else {
                    std::cout << "Team registered successfully.\n";
                }
            } else {
                std::cout << "Failed to register team. Invalid ID or duplicate.\n";
            }
        } else if (choice == 2) {
            int id, points;
            readInt("Team ID: ", &id);
            readInt("Mission points (1-100): ", &points);
            if (recordMission(teams, size, id, points)) {
                std::cout << "Mission points recorded successfully.\n";
            } else {
                std::cout << "Failed to record mission points. Invalid team ID or points.\n";
            }
        } else if (choice == 3) {
            int id;
            readInt("Team ID: ", &id);
            int index = findTeamIndex(teams, size, id);
            if (index != -1) {
                std::cout << "Team found:\n";
                std::cout << "ID: " << teams[index].id << "\n";
                std::cout << "Name: " << teams[index].name << "\n";
                std::cout << "Score: " << teams[index].score << "\n";
                std::cout << "Missions: " << teams[index].missions << "\n";
            } else {
                std::cout << "Team not found.\n";
            }
        } else if (choice == 4) {
            int id;
            readInt("Team ID: ", &id);
            if (deleteTeam(teams, &size, id)) {
                std::cout << "Team removed successfully.\n";
            } else {
                std::cout << "Failed to remove team. Team not found.\n";
            }
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            displayTeams(teams, size);
        } else if (choice == 6) {
            if (!saveTeams("teams.txt", teams, size))
                std::cout << "Warning: data could not be saved.\n";
        } else {
            std::cout << "Choose a number from 1 to 6.\n";
        }
    } while (choice != 6);

    std::free(teams);
    teams = nullptr;
    return 0;
}