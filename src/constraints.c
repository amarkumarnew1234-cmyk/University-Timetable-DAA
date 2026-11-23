#include <stdio.h>
#include "../include/constraints.h"

int findFacultyIndex(int facultyId) {
    int i;

    for (i = 0; i < facultyCount; i++) {
        if (faculty[i].facultyId == facultyId)
            return i;
    }

    return -1;
}

int findGroupIndex(int groupId) {
    int i;

    for (i = 0; i < groupCount; i++) {
        if (groups[i].groupId == groupId)
            return i;
    }

    return -1;
}

int findRoomIndex(int roomId) {
    int i;

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomId == roomId)
            return i;
    }

    return -1;
}

int findSlotIndex(int slotId) {
    int i;

    for (i = 0; i < slotCount; i++) {
        if (slots[i].slotId == slotId)
            return i;
    }

    return -1;
}

int findCourseIndex(int courseId) {
    int i;

    for (i = 0; i < courseCount; i++) {
        if (courses[i].courseId == courseId)
            return i;
    }

    return -1;
}

int isRoomCapacityValid(int courseId, int roomId) {
    int courseIndex = findCourseIndex(courseId);
    int roomIndex = findRoomIndex(roomId);
    int groupIndex;

    if (courseIndex == -1 || roomIndex == -1)
        return 0;

    groupIndex = findGroupIndex(courses[courseIndex].groupId);

    if (groupIndex == -1)
        return 0;

    if (rooms[roomIndex].capacity >= groups[groupIndex].strength)
        return 1;

    return 0;
}

int isRoomTypeValid(int courseId, int roomId) {
    int courseIndex = findCourseIndex(courseId);
    int roomIndex = findRoomIndex(roomId);

    if (courseIndex == -1 || roomIndex == -1)
        return 0;

    if (courses[courseIndex].requiredRoomType == rooms[roomIndex].roomType)
        return 1;

    return 0;
}

int isFacultyAvailable(int facultyId, int slotId) {
    int facultyIndex = findFacultyIndex(facultyId);
    int slotIndex = findSlotIndex(slotId);
    int day, period;

    if (facultyIndex == -1 || slotIndex == -1)
        return 0;

    day = slots[slotIndex].day;
    period = slots[slotIndex].period;

    return faculty[facultyIndex].availability[day][period];
}

int isRoomFree(int roomId, int slotId) {
    int i;

    for (i = 0; i < assignmentCount; i++) {
        if (timetable[i].roomId == roomId &&
            timetable[i].slotId == slotId)
            return 0;
    }

    return 1;
}

int isFacultyFree(int facultyId, int slotId) {
    int i;

    for (i = 0; i < assignmentCount; i++) {
        if (timetable[i].facultyId == facultyId &&
            timetable[i].slotId == slotId)
            return 0;
    }

    return 1;
}

int isGroupFree(int groupId, int slotId) {
    int i;

    for (i = 0; i < assignmentCount; i++) {
        if (timetable[i].groupId == groupId &&
            timetable[i].slotId == slotId)
            return 0;
    }

    return 1;
}

int isCourseFreeOnDay(int courseId, int slotId) {
    int i;
    int newSlotIndex = findSlotIndex(slotId);

    if (newSlotIndex == -1)
        return 0;

    for (i = 0; i < assignmentCount; i++) {
        if (timetable[i].courseId == courseId) {
            int oldSlotIndex = findSlotIndex(timetable[i].slotId);

            if (oldSlotIndex != -1 &&
                slots[oldSlotIndex].day == slots[newSlotIndex].day) {
                return 0;
            }
        }
    }

    return 1;
}

int isValidAssignment(int courseId, int roomId, int slotId) {
    int courseIndex = findCourseIndex(courseId);
    int facultyId;
    int groupId;

    if (courseIndex == -1)
        return 0;

    if (findRoomIndex(roomId) == -1)
        return 0;

    if (findSlotIndex(slotId) == -1)
        return 0;

    facultyId = courses[courseIndex].facultyId;
    groupId = courses[courseIndex].groupId;

    if (!isRoomCapacityValid(courseId, roomId))
        return 0;

    if (!isRoomTypeValid(courseId, roomId))
        return 0;

    if (!isFacultyAvailable(facultyId, slotId))
        return 0;

    if (!isRoomFree(roomId, slotId))
        return 0;

    if (!isFacultyFree(facultyId, slotId))
        return 0;

    if (!isGroupFree(groupId, slotId))
        return 0;

    if (!isCourseFreeOnDay(courseId, slotId))
        return 0;

    return 1;
}

void explainInvalidAssignment(int courseId, int roomId, int slotId) {
    int courseIndex = findCourseIndex(courseId);
    int facultyId;
    int groupId;

    if (courseIndex == -1) {
        printf("Invalid course ID.\n");
        return;
    }

    if (findRoomIndex(roomId) == -1) {
        printf("Invalid room ID.\n");
        return;
    }

    if (findSlotIndex(slotId) == -1) {
        printf("Invalid time slot.\n");
        return;
    }

    facultyId = courses[courseIndex].facultyId;
    groupId = courses[courseIndex].groupId;

    if (!isRoomCapacityValid(courseId, roomId))
        printf("- Room capacity is not enough.\n");

    if (!isRoomTypeValid(courseId, roomId))
        printf("- Required room type does not match.\n");

    if (!isFacultyAvailable(facultyId, slotId))
        printf("- Faculty is unavailable in this time slot.\n");

    if (!isRoomFree(roomId, slotId))
        printf("- Room is already occupied in this time slot.\n");

    if (!isFacultyFree(facultyId, slotId))
        printf("- Faculty already has another class in this time slot.\n");

    if (!isGroupFree(groupId, slotId))
        printf("- Student group already has another class in this time slot.\n");

    if (!isCourseFreeOnDay(courseId, slotId))
        printf("- Same course is already scheduled on this day.\n");
}