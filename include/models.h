#ifndef MODELS_H
#define MODELS_H

#define MAX_NAME 100
#define MAX_CODE 20
#define MAX_COURSES 50
#define MAX_FACULTY 30
#define MAX_GROUPS 30
#define MAX_ROOMS 30
#define MAX_SLOTS 50
#define MAX_ASSIGNMENTS 200

#define DAYS 5
#define PERIODS_PER_DAY 6

#define ROOM_CLASSROOM 1
#define ROOM_LAB 2
#define ROOM_AUDITORIUM 3

typedef struct {
    int courseId;
    char courseCode[MAX_CODE];
    char courseName[MAX_NAME];
    int facultyId;
    int groupId;
    int hoursPerWeek;
    int requiredRoomType;
} Course;

typedef struct {
    int facultyId;
    char facultyName[MAX_NAME];
    int availability[DAYS][PERIODS_PER_DAY];
} Faculty;

typedef struct {
    int groupId;
    char program[MAX_NAME];
    int semester;
    char section;
    int strength;
} StudentGroup;

typedef struct {
    int roomId;
    char roomName[MAX_NAME];
    int capacity;
    int roomType;
} Room;

typedef struct {
    int slotId;
    int day;
    int period;
} TimeSlot;

typedef struct {
    int courseId;
    int facultyId;
    int groupId;
    int roomId;
    int slotId;
} Assignment;

extern Course courses[MAX_COURSES];
extern Faculty faculty[MAX_FACULTY];
extern StudentGroup groups[MAX_GROUPS];
extern Room rooms[MAX_ROOMS];
extern TimeSlot slots[MAX_SLOTS];
extern Assignment timetable[MAX_ASSIGNMENTS];

extern int courseCount;
extern int facultyCount;
extern int groupCount;
extern int roomCount;
extern int slotCount;
extern int assignmentCount;

void initializeSampleData();

void displayCourses();
void displayFaculty();
void displayGroups();
void displayRooms();
void displayTimeSlots();

void addCourse();
void addRoom();
void changeGroupStrength();

const char *getRoomTypeName(int roomType);
const char *getDayName(int day);

#endif