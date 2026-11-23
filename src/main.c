#include <stdio.h>
#include <time.h>
#include "../include/models.h"
#include "../include/constraints.h"
#include "../include/scheduler.h"
#include "../include/backtracking.h"

void displayMenu() {
    printf("\n=== University Timetable and Classroom Allocation Engine ===\n");

    printf("\n--- View Data ---\n");
    printf("1. View Courses\n");
    printf("2. View Faculty\n");
    printf("3. View Student Groups\n");
    printf("4. View Rooms\n");
    printf("5. View Time Slots\n");

    printf("\n--- Manage Data ---\n");
    printf("6. Add New Course\n");
    printf("7. Add New Room\n");
    printf("8. Change Student Group Strength\n");

    printf("\n--- Timetable ---\n");
    printf("9. Test Assignment\n");
    printf("10. Generate Greedy Timetable\n");
    printf("11. Generate Backtracking Timetable\n");
    printf("12. View Complete Timetable\n");
    printf("13. View Timetable by Student Group\n");
    printf("14. Compare Greedy and Backtracking\n");

    printf("\n0. Exit\n");
}

void compareAlgorithms() {
    clock_t start, end;
    double greedyTime, backtrackingTime;
    int greedyResult, backtrackingResult;
    int greedyClasses, backtrackingClasses;
    long greedyAttempts;
    long backtrackingAttempts;
    long backtracks;

    start = clock();
    greedyResult = generateGreedyTimetable();
    end = clock();

    greedyTime = (double)(end - start) / CLOCKS_PER_SEC;
    greedyClasses = assignmentCount;
    greedyAttempts = getGreedyAttempts();

    start = clock();
    backtrackingResult = generateBacktrackingTimetable();
    end = clock();

    backtrackingTime = (double)(end - start) / CLOCKS_PER_SEC;
    backtrackingClasses = assignmentCount;
    backtrackingAttempts = getBacktrackingAttempts();
    backtracks = getBacktrackCount();

    printf("\n--- Greedy vs Backtracking Comparison ---\n");

    printf("\nGreedy Algorithm\n");
    printf("Status: %s\n", greedyResult ? "Success" : "Failed");
    printf("Classes scheduled: %d/%d\n",
           greedyClasses, countRequiredClasses());
    printf("Assignment attempts: %ld\n", greedyAttempts);
    printf("Execution time: %.6f seconds\n", greedyTime);

    printf("\nBacktracking Algorithm\n");
    printf("Status: %s\n", backtrackingResult ? "Success" : "Failed");
    printf("Classes scheduled: %d/%d\n",
           backtrackingClasses, countRequiredClasses());
    printf("Assignment attempts: %ld\n", backtrackingAttempts);
    printf("Backtracks: %ld\n", backtracks);
    printf("Execution time: %.6f seconds\n", backtrackingTime);

    printf("\nObservation:\n");

    if (greedyResult && backtrackingResult) {
        printf("Both algorithms generated a complete valid timetable.\n");
        printf("Greedy keeps its first valid choice, while backtracking can\n");
        printf("undo previous choices if a later assignment reaches a dead end.\n");
    } else if (!greedyResult && backtrackingResult) {
        printf("Greedy failed, but backtracking found a valid timetable.\n");
    } else if (greedyResult && !backtrackingResult) {
        printf("Greedy succeeded but backtracking did not complete successfully.\n");
    } else {
        printf("Neither algorithm generated a complete timetable.\n");
    }
}

int main() {
    int choice;

    initializeSampleData();

    while (1) {
        displayMenu();
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                displayCourses();
                break;

            case 2:
                displayFaculty();
                break;

            case 3:
                displayGroups();
                break;

            case 4:
                displayRooms();
                break;

            case 5:
                displayTimeSlots();
                break;

            case 6:
                addCourse();
                break;

            case 7:
                addRoom();
                break;

            case 8:
                changeGroupStrength();
                break;

            case 9: {
                int courseId, roomId, slotId;

                printf("Enter Course ID: ");
                scanf("%d", &courseId);

                printf("Enter Room ID: ");
                scanf("%d", &roomId);

                printf("Enter Slot ID: ");
                scanf("%d", &slotId);

                if (isValidAssignment(courseId, roomId, slotId)) {
                    printf("Assignment is valid.\n");
                } else {
                    printf("Assignment is invalid because:\n");
                    explainInvalidAssignment(courseId, roomId, slotId);
                }

                break;
            }

            case 10:
                if (generateGreedyTimetable()) {
                    printf("\nGreedy timetable generated successfully.\n");
                    printf("Classes scheduled: %d/%d\n",
                           assignmentCount, countRequiredClasses());
                    printf("Assignment attempts: %ld\n",
                           getGreedyAttempts());
                } else {
                    printf("\nGreedy algorithm could not generate complete timetable.\n");
                    printf("Classes scheduled before failure: %d/%d\n",
                           assignmentCount, countRequiredClasses());
                }
                break;

            case 11:
                if (generateBacktrackingTimetable()) {
                    printf("\nBacktracking timetable generated successfully.\n");
                    printf("Classes scheduled: %d/%d\n",
                           assignmentCount, countRequiredClasses());
                    printf("Assignment attempts: %ld\n",
                           getBacktrackingAttempts());
                    printf("Backtracks: %ld\n",
                           getBacktrackCount());
                } else {
                    printf("\nBacktracking could not generate complete timetable.\n");
                    printf("Assignment attempts: %ld\n",
                           getBacktrackingAttempts());
                    printf("Backtracks: %ld\n",
                           getBacktrackCount());
                }
                break;

            case 12:
                displayTimetable();
                break;

            case 13: {
                int groupId;

                printf("Enter Group ID: ");
                scanf("%d", &groupId);

                displayTimetableByGroup(groupId);
                break;
            }

            case 14:
                compareAlgorithms();
                break;

            case 0:
                printf("Program closed.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}