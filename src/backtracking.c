#include "../include/backtracking.h"
#include "../include/models.h"
#include "../include/constraints.h"
#include "../include/scheduler.h"

static long backtrackingAttempts = 0;
static long backtrackCount = 0;

static int scheduleCourse(int courseIndex, int lectureNumber) {
    int slotIndex, roomIndex;
    int nextCourse;
    int nextLecture;
    int courseId;
    int facultyId;
    int groupId;

    if (courseIndex >= courseCount)
        return 1;

    courseId = courses[courseIndex].courseId;
    facultyId = courses[courseIndex].facultyId;
    groupId = courses[courseIndex].groupId;

    for (slotIndex = 0; slotIndex < slotCount; slotIndex++) {
        for (roomIndex = 0; roomIndex < roomCount; roomIndex++) {
            backtrackingAttempts++;

            if (isValidAssignment(courseId,
                                  rooms[roomIndex].roomId,
                                  slots[slotIndex].slotId)) {

                if (assignmentCount >= MAX_ASSIGNMENTS)
                    return 0;

                timetable[assignmentCount].courseId = courseId;
                timetable[assignmentCount].facultyId = facultyId;
                timetable[assignmentCount].groupId = groupId;
                timetable[assignmentCount].roomId = rooms[roomIndex].roomId;
                timetable[assignmentCount].slotId = slots[slotIndex].slotId;

                assignmentCount++;

                if (lectureNumber + 1 < courses[courseIndex].hoursPerWeek) {
                    nextCourse = courseIndex;
                    nextLecture = lectureNumber + 1;
                } else {
                    nextCourse = courseIndex + 1;
                    nextLecture = 0;
                }

                if (scheduleCourse(nextCourse, nextLecture))
                    return 1;

                assignmentCount--;
                backtrackCount++;
            }
        }
    }

    return 0;
}

int generateBacktrackingTimetable() {
    clearTimetable();

    backtrackingAttempts = 0;
    backtrackCount = 0;

    if (courseCount == 0)
        return 0;

    return scheduleCourse(0, 0);
}

long getBacktrackingAttempts() {
    return backtrackingAttempts;
}

long getBacktrackCount() {
    return backtrackCount;
}