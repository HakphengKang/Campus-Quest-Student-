#ifndef CAMPUS_QUEST_H
#define CAMPUS_QUEST_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define NAME_LEN 40
#define LINE_LEN 160

typedef struct {
    int id;
    char name[NAME_LEN];
    int score;
    int missions;
} Team;

int ensureCapacity(Team **teams, int *capacity, int required);
int findTeamIndex(const Team teams[], int size, int id);

#endif