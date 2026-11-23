#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "models.h"

int findFacultyIndex(int facultyId);
int findGroupIndex(int groupId);
int findRoomIndex(int roomId);
int findSlotIndex(int slotId);
int findCourseIndex(int courseId);

int isRoomCapacityValid(int courseId, int roomId);
int isRoomTypeValid(int courseId, int roomId);
int isFacultyAvailable(int facultyId, int slotId);
int isRoomFree(int roomId, int slotId);
int isFacultyFree(int facultyId, int slotId);
int isGroupFree(int groupId, int slotId);
int isCourseFreeOnDay(int courseId, int slotId);

int isValidAssignment(int courseId, int roomId, int slotId);
void explainInvalidAssignment(int courseId, int roomId, int slotId);

#endif