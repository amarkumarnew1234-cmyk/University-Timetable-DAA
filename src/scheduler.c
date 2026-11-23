#include <stdio.h>
#include "../include/scheduler.h"
#include "../include/constraints.h"

static long greedyAttempts = 0;

void clearTimetable() {
    assignmentCount = 0;
}

int countRequiredClasses() {
    int i;
    int total = 0;

    for (i = 0; i < courseCount; i++) {
        total += courses[i].hoursPerWeek;
    }

    return total;
}

void resetGreedyAttempts() {
    greedyAttempts = 0;
}

long getGreedyAttempts() {
    return greedyAttempts;
}

int addAssignment(int courseId, int roomId, int slotId) {
    int courseIndex;

    if (assignmentCount >= MAX_ASSIGNMENTS)
        return 0;

    courseIndex = findCourseIndex(courseId);

    if (courseIndex == -1)
        return 0;

    if (!isValidAssignment(courseId, roomId, slotId))
        return 0;

    timetable[assignmentCount].courseId = courseId;
    timetable[assignmentCount].facultyId = courses[courseIndex].facultyId;
    timetable[assignmentCount].groupId = courses[courseIndex].groupId;
    timetable[assignmentCount].roomId = roomId;
    timetable[assignmentCount].slotId = slotId;

    assignmentCount++;

    return 1;
}

int generateGreedyTimetable() {
    int i, lecture, s, r;
    int assigned;

    clearTimetable();
    resetGreedyAttempts();

    for (i = 0; i < courseCount; i++) {
        for (lecture = 0; lecture < courses[i].hoursPerWeek; lecture++) {
            assigned = 0;

            for (s = 0; s < slotCount && !assigned; s++) {
                for (r = 0; r < roomCount && !assigned; r++) {
                    greedyAttempts++;

                    if (addAssignment(courses[i].courseId,
                                      rooms[r].roomId,
                                      slots[s].slotId)) {
                        assigned = 1;
                    }
                }
            }

            if (!assigned) {
                printf("\nCould not schedule %s lecture %d.\n",
                       courses[i].courseName,
                       lecture + 1);
                return 0;
            }
        }
    }

    return 1;
}

void displayTimetable() {
    int i;
    int courseIndex;
    int facultyIndex;
    int groupIndex;
    int roomIndex;
    int slotIndex;

    if (assignmentCount == 0) {
        printf("\nNo timetable generated.\n");
        return;
    }

    printf("\n--- Generated Timetable ---\n");

    printf("%-10s %-8s %-12s %-12s %-12s %-12s %-12s\n",
           "Day",
           "Period",
           "Course",
           "Group",
           "Faculty",
           "Room",
           "Students");

    for (i = 0; i < assignmentCount; i++) {
        courseIndex = findCourseIndex(timetable[i].courseId);
        facultyIndex = findFacultyIndex(timetable[i].facultyId);
        groupIndex = findGroupIndex(timetable[i].groupId);
        roomIndex = findRoomIndex(timetable[i].roomId);
        slotIndex = findSlotIndex(timetable[i].slotId);

        if (courseIndex == -1 ||
            facultyIndex == -1 ||
            groupIndex == -1 ||
            roomIndex == -1 ||
            slotIndex == -1) {
            continue;
        }

        printf("%-10s %-8d %-12s %s-%d%c       %-12s %-12s %-12d\n",
               getDayName(slots[slotIndex].day),
               slots[slotIndex].period + 1,
               courses[courseIndex].courseCode,
               groups[groupIndex].program,
               groups[groupIndex].semester,
               groups[groupIndex].section,
               faculty[facultyIndex].facultyName,
               rooms[roomIndex].roomName,
               groups[groupIndex].strength);
    }

    printf("\nTotal classes scheduled: %d/%d\n",
           assignmentCount,
           countRequiredClasses());
}

void displayTimetableByGroup(int groupId) {
    int day, period, i;
    int found;
    int courseIndex;
    int slotIndex;
    int groupIndex;

    groupIndex = findGroupIndex(groupId);

    if (groupIndex == -1) {
        printf("Invalid group ID.\n");
        return;
    }

    printf("\nTimetable for %s Semester %d Section %c\n",
           groups[groupIndex].program,
           groups[groupIndex].semester,
           groups[groupIndex].section);

    printf("%-12s", "Day");

    for (period = 0; period < PERIODS_PER_DAY; period++) {
        printf("P%-11d", period + 1);
    }

    printf("\n");

    for (day = 0; day < DAYS; day++) {
        printf("%-12s", getDayName(day));

        for (period = 0; period < PERIODS_PER_DAY; period++) {
            found = 0;

            for (i = 0; i < assignmentCount; i++) {
                if (timetable[i].groupId != groupId)
                    continue;

                slotIndex = findSlotIndex(timetable[i].slotId);

                if (slotIndex == -1)
                    continue;

                if (slots[slotIndex].day == day &&
                    slots[slotIndex].period == period) {

                    courseIndex = findCourseIndex(timetable[i].courseId);

                    if (courseIndex != -1) {
                        printf("%-12s",
                               courses[courseIndex].courseCode);
                        found = 1;
                    }

                    break;
                }
            }

            if (!found)
                printf("%-12s", "-");
        }

        printf("\n");
    }
}