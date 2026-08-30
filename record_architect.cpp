#include <cstring>

typedef struct {
    int id;
    char name[40];
    int score;
    int missions;
} Team;

const int TEAM_NAME_CAPACITY = 40;
const int MIN_MISSION_POINTS = 1;
const int MAX_MISSION_POINTS = 100;

bool isValidName(const char* name) {
    if (name == NULL)      return false;
    if (name[0] == '\0')   return false;
    if (std::strlen(name) >= TEAM_NAME_CAPACITY) return false;
    return true;
}

bool isValidTeam(int id, const char* name, int score, int missions) {
    if (id <= 0)                 return false;
    if (!isValidName(name))      return false;
    if (score < 0)               return false;
    if (missions < 0)            return false;
    return true;
}

bool isValidMissionPoints(int points) {
    return points >= MIN_MISSION_POINTS && points <= MAX_MISSION_POINTS;
}

bool idAlreadyTaken(const Team* teams, int size, int id) {
    for (int i = 0; i < size; ++i) {
        if (teams[i].id == id) {
            return true;
        }
    }
    return false;
}

void copyTeam(Team* dest, const Team* src) {
    dest->id = src->id;
    std::strncpy(dest->name, src->name, TEAM_NAME_CAPACITY - 1);
    dest->name[TEAM_NAME_CAPACITY - 1] = '\0';
    dest->score = src->score;
    dest->missions = src->missions;
}

bool buildCandidate(Team* out, int id, const char* name, int score, int missions) {
    if (!isValidTeam(id, name, score, missions)) {
        return false;
    }
    out->id = id;
    std::strncpy(out->name, name, TEAM_NAME_CAPACITY - 1);
    out->name[TEAM_NAME_CAPACITY - 1] = '\0';
    out->score = score;
    out->missions = missions;
    return true;
}

void swapTeam(Team* a, Team* b) {
    Team temp;
    copyTeam(&temp, a);
    copyTeam(a, b);
    copyTeam(b, &temp);
}

void shiftLeft(Team* teams, int from, int size) {
    for (int i = from; i < size - 1; ++i) {
        teams[i] = teams[i + 1];
    }
}
