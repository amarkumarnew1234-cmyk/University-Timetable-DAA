#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "models.h"

void clearTimetable();
int addAssignment(int courseId, int roomId, int slotId);
int generateGreedyTimetable();
void displayTimetable();
void displayTimetableByGroup(int groupId);
int countRequiredClasses();

long getGreedyAttempts();
void resetGreedyAttempts();

#endif