#include <stdio.h>
#include <string.h>
#include "../include/models.h"
#include "../include/constraints.h"
#include "../include/scheduler.h"

Course courses[MAX_COURSES];
Faculty faculty[MAX_FACULTY];
StudentGroup groups[MAX_GROUPS];
Room rooms[MAX_ROOMS];
TimeSlot slots[MAX_SLOTS];
Assignment timetable[MAX_ASSIGNMENTS];

int courseCount = 0;
int facultyCount = 0;
int groupCount = 0;
int roomCount = 0;
int slotCount = 0;
int assignmentCount = 0;

const char *getRoomTypeName(int roomType) {
    if (roomType == ROOM_CLASSROOM)
        return "Classroom";
    else if (roomType == ROOM_LAB)
        return "Lab";
    else if (roomType == ROOM_AUDITORIUM)
        return "Auditorium";
    else
        return "Unknown";
}

const char *getDayName(int day) {
    if (day == 0)
        return "Monday";
    else if (day == 1)
        return "Tuesday";
    else if (day == 2)
        return "Wednesday";
    else if (day == 3)
        return "Thursday";
    else if (day == 4)
        return "Friday";
    else
        return "Unknown";
}

void initializeSampleData() {
    int i, day, period;

    groupCount = 2;

    groups[0].groupId = 1;
    strcpy(groups[0].program, "BTech CSE");
    groups[0].semester = 3;
    groups[0].section = 'A';
    groups[0].strength = 52;

    groups[1].groupId = 2;
    strcpy(groups[1].program, "BTech CSE");
    groups[1].semester = 3;
    groups[1].section = 'B';
    groups[1].strength = 45;

    facultyCount = 5;

    faculty[0].facultyId = 101;
    strcpy(faculty[0].facultyName, "Prof. Sharma");

    faculty[1].facultyId = 102;
    strcpy(faculty[1].facultyName, "Prof. Verma");

    faculty[2].facultyId = 103;
    strcpy(faculty[2].facultyName, "Prof. Singh");

    faculty[3].facultyId = 104;
    strcpy(faculty[3].facultyName, "Prof. Gupta");

    faculty[4].facultyId = 105;
    strcpy(faculty[4].facultyName, "Prof. Mehta");

    for (i = 0; i < facultyCount; i++) {
        for (day = 0; day < DAYS; day++) {
            for (period = 0; period < PERIODS_PER_DAY; period++) {
                faculty[i].availability[day][period] = 1;
            }
        }
    }

    // some unavailable slots
    faculty[0].availability[0][2] = 0;
    faculty[1].availability[1][0] = 0;
    faculty[2].availability[2][3] = 0;
    faculty[3].availability[3][1] = 0;
    faculty[4].availability[4][4] = 0;

    roomCount = 5;

    rooms[0].roomId = 1;
    strcpy(rooms[0].roomName, "C101");
    rooms[0].capacity = 60;
    rooms[0].roomType = ROOM_CLASSROOM;

    rooms[1].roomId = 2;
    strcpy(rooms[1].roomName, "C102");
    rooms[1].capacity = 50;
    rooms[1].roomType = ROOM_CLASSROOM;

    rooms[2].roomId = 3;
    strcpy(rooms[2].roomName, "C103");
    rooms[2].capacity = 40;
    rooms[2].roomType = ROOM_CLASSROOM;

    rooms[3].roomId = 4;
    strcpy(rooms[3].roomName, "LAB1");
    rooms[3].capacity = 60;
    rooms[3].roomType = ROOM_LAB;

    rooms[4].roomId = 5;
    strcpy(rooms[4].roomName, "AUD1");
    rooms[4].capacity = 150;
    rooms[4].roomType = ROOM_AUDITORIUM;

    courseCount = 10;

    courses[0] = (Course){1, "CSEG3053", "Design and Analysis of Algorithms", 101, 1, 3, ROOM_CLASSROOM};
    courses[1] = (Course){2, "CSEG3002", "Operating Systems", 102, 1, 3, ROOM_CLASSROOM};
    courses[2] = (Course){3, "CSEG3003", "Database Management Systems", 103, 1, 3, ROOM_CLASSROOM};
    courses[3] = (Course){4, "CSEG3004", "Computer Networks", 104, 1, 3, ROOM_CLASSROOM};
    courses[4] = (Course){5, "CSEG3005L", "Programming Laboratory", 105, 1, 2, ROOM_LAB};

    courses[5] = (Course){6, "CSEG3053", "Design and Analysis of Algorithms", 101, 2, 3, ROOM_CLASSROOM};
    courses[6] = (Course){7, "CSEG3002", "Operating Systems", 102, 2, 3, ROOM_CLASSROOM};
    courses[7] = (Course){8, "CSEG3003", "Database Management Systems", 103, 2, 3, ROOM_CLASSROOM};
    courses[8] = (Course){9, "CSEG3004", "Computer Networks", 104, 2, 3, ROOM_CLASSROOM};
    courses[9] = (Course){10, "CSEG3005L", "Programming Laboratory", 105, 2, 2, ROOM_LAB};

    slotCount = 0;

    for (day = 0; day < DAYS; day++) {
        for (period = 0; period < PERIODS_PER_DAY; period++) {
            slots[slotCount].slotId = slotCount + 1;
            slots[slotCount].day = day;
            slots[slotCount].period = period;
            slotCount++;
        }
    }

    assignmentCount = 0;
}

void displayCourses() {
    int i;

    printf("\n--- Courses ---\n");
    printf("%-4s %-12s %-32s %-8s %-7s %-6s\n",
           "ID", "Code", "Course", "Faculty", "Group", "Hours");

    for (i = 0; i < courseCount; i++) {
        printf("%-4d %-12s %-32s %-8d %-7d %-6d\n",
               courses[i].courseId,
               courses[i].courseCode,
               courses[i].courseName,
               courses[i].facultyId,
               courses[i].groupId,
               courses[i].hoursPerWeek);
    }
}

void displayFaculty() {
    int i;

    printf("\n--- Faculty ---\n");

    for (i = 0; i < facultyCount; i++) {
        printf("%d - %s\n",
               faculty[i].facultyId,
               faculty[i].facultyName);
    }
}

void displayGroups() {
    int i;

    printf("\n--- Student Groups ---\n");

    for (i = 0; i < groupCount; i++) {
        printf("Group %d: %s Semester %d Section %c, Students: %d\n",
               groups[i].groupId,
               groups[i].program,
               groups[i].semester,
               groups[i].section,
               groups[i].strength);
    }
}

void displayRooms() {
    int i;

    printf("\n--- Rooms ---\n");

    for (i = 0; i < roomCount; i++) {
        printf("%d - %s, Capacity: %d, Type: %s\n",
               rooms[i].roomId,
               rooms[i].roomName,
               rooms[i].capacity,
               getRoomTypeName(rooms[i].roomType));
    }
}

void displayTimeSlots() {
    int i;

    printf("\n--- Time Slots ---\n");

    for (i = 0; i < slotCount; i++) {
        printf("Slot %d: %s, Period %d\n",
               slots[i].slotId,
               getDayName(slots[i].day),
               slots[i].period + 1);
    }
}

void addCourse() {
    Course newCourse;

    if (courseCount >= MAX_COURSES) {
        printf("Maximum course limit reached.\n");
        return;
    }

    printf("\n--- Add New Course ---\n");

    printf("Enter Course ID: ");
    scanf("%d", &newCourse.courseId);

    if (findCourseIndex(newCourse.courseId) != -1) {
        printf("Course ID already exists.\n");
        return;
    }

    printf("Enter Course Code: ");
    scanf(" %19s", newCourse.courseCode);

    printf("Enter Course Name: ");
    scanf(" %99[^\n]", newCourse.courseName);

    printf("Enter Faculty ID: ");
    scanf("%d", &newCourse.facultyId);

    if (findFacultyIndex(newCourse.facultyId) == -1) {
        printf("Faculty ID does not exist.\n");
        return;
    }

    printf("Enter Student Group ID: ");
    scanf("%d", &newCourse.groupId);

    if (findGroupIndex(newCourse.groupId) == -1) {
        printf("Student Group ID does not exist.\n");
        return;
    }

    printf("Enter Classes Per Week: ");
    scanf("%d", &newCourse.hoursPerWeek);

    if (newCourse.hoursPerWeek <= 0) {
        printf("Classes per week must be greater than 0.\n");
        return;
    }

    printf("Room Type:\n");
    printf("1. Classroom\n");
    printf("2. Lab\n");
    printf("3. Auditorium\n");
    printf("Enter Room Type: ");
    scanf("%d", &newCourse.requiredRoomType);

    if (newCourse.requiredRoomType < ROOM_CLASSROOM ||
        newCourse.requiredRoomType > ROOM_AUDITORIUM) {
        printf("Invalid room type.\n");
        return;
    }

    courses[courseCount] = newCourse;
    courseCount++;

    clearTimetable();

    printf("Course added successfully.\n");
    printf("Timetable cleared. Generate it again to include the new course.\n");
}

void addRoom() {
    Room newRoom;
    int i;

    if (roomCount >= MAX_ROOMS) {
        printf("Maximum room limit reached.\n");
        return;
    }

    printf("\n--- Add New Room ---\n");

    printf("Enter Room ID: ");
    scanf("%d", &newRoom.roomId);

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomId == newRoom.roomId) {
            printf("Room ID already exists.\n");
            return;
        }
    }

    printf("Enter Room Name: ");
    scanf(" %99[^\n]", newRoom.roomName);

    printf("Enter Capacity: ");
    scanf("%d", &newRoom.capacity);

    if (newRoom.capacity <= 0) {
        printf("Room capacity must be greater than 0.\n");
        return;
    }

    printf("Room Type:\n");
    printf("1. Classroom\n");
    printf("2. Lab\n");
    printf("3. Auditorium\n");
    printf("Enter Room Type: ");
    scanf("%d", &newRoom.roomType);

    if (newRoom.roomType < ROOM_CLASSROOM ||
        newRoom.roomType > ROOM_AUDITORIUM) {
        printf("Invalid room type.\n");
        return;
    }

    rooms[roomCount] = newRoom;
    roomCount++;

    clearTimetable();

    printf("Room added successfully.\n");
    printf("Timetable cleared. Generate it again to use the new room.\n");
}

void changeGroupStrength() {
    int groupId;
    int newStrength;
    int groupIndex;

    printf("\n--- Change Student Group Strength ---\n");

    printf("Enter Group ID: ");
    scanf("%d", &groupId);

    groupIndex = findGroupIndex(groupId);

    if (groupIndex == -1) {
        printf("Student Group does not exist.\n");
        return;
    }

    printf("Current strength: %d\n", groups[groupIndex].strength);

    printf("Enter New Strength: ");
    scanf("%d", &newStrength);

    if (newStrength <= 0) {
        printf("Strength must be greater than 0.\n");
        return;
    }

    groups[groupIndex].strength = newStrength;

    clearTimetable();

    printf("Student group strength updated successfully.\n");
    printf("Timetable cleared because room requirements may have changed.\n");
}