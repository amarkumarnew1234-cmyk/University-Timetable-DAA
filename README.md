# University Timetable and Classroom Allocation Engine

## Project Information

**Course:** Design and Analysis of Algorithms  
**Project:** University Timetable and Classroom Allocation Engine  
**Language:** C  
**Type:** Individual Project  

## 1. Project Overview

The University Timetable and Classroom Allocation Engine is a C-based application developed to automatically generate a clash-free timetable for university courses.

The system considers courses, faculty members, student groups, classrooms, room capacities, room types, faculty availability and time slots while generating the timetable.

Two algorithmic approaches are implemented for timetable generation:

1. Greedy Algorithm
2. Backtracking Algorithm

The project also compares these algorithms using the number of assignment attempts, execution time and successful class allocations.

## 2. Problem Statement

Creating a university timetable manually becomes difficult when the number of courses, faculty members, student groups and classrooms increases.

A valid timetable must satisfy several constraints such as:

- A room cannot be assigned to two classes at the same time.
- A faculty member cannot teach two classes at the same time.
- A student group cannot attend two classes at the same time.
- Room capacity must be sufficient for the student group.
- The required room type must match the course requirement.
- Faculty must be available during the selected time slot.
- The same course should not be scheduled multiple times on the same day.

The aim of this project is to generate a valid timetable automatically while satisfying these constraints.

## 3. Main Data Structures

The project uses structures and arrays to represent university data.

### Course

Stores:

- Course ID
- Course code
- Course name
- Faculty ID
- Student group ID
- Hours per week
- Required room type

### Faculty

Stores:

- Faculty ID
- Faculty name
- Availability for different days and periods

### Student Group

Stores:

- Group ID
- Program
- Semester
- Section
- Number of students

### Room

Stores:

- Room ID
- Room name
- Capacity
- Room type

### Time Slot

Stores:

- Slot ID
- Day
- Period

### Assignment

Represents one timetable entry containing:

- Course
- Faculty
- Student group
- Room
- Time slot

## 4. Constraints Implemented

The following constraints are checked before an assignment is added to the timetable:

1. Room capacity constraint
2. Room type constraint
3. Faculty availability constraint
4. Room collision constraint
5. Faculty collision constraint
6. Student group collision constraint
7. Same course once per day constraint

The `isValidAssignment()` function acts as the central constraint checker.

## 5. Greedy Algorithm

The Greedy algorithm checks available time slots and rooms and selects the first valid combination for every required lecture.

Once an assignment is selected, the Greedy algorithm does not reconsider the previous decision.

### Advantage

- Simple
- Fast
- Easy to implement

### Limitation

A locally valid choice may create difficulty for later assignments because previous choices are not reconsidered.

## 6. Backtracking Algorithm

The Backtracking algorithm assigns a valid room and time slot and then recursively attempts to schedule the remaining lectures.

If a later assignment reaches a dead end, the algorithm removes the previous assignment and tries another possible choice.

The basic process is:

Choose -> Check -> Explore -> Undo if required -> Try another choice

### Advantage

It can reconsider previous decisions and explore alternative schedules.

### Limitation

The worst-case running time can become very high for large scheduling problems.

## 7. Greedy vs Backtracking

Both algorithms are tested using the same university dataset and the same constraints.

The comparison considers:

- Successful or failed timetable generation
- Number of classes scheduled
- Assignment attempts
- Execution time
- Number of backtracks for the Backtracking algorithm

### Current Normal Dataset Result

| Measure | Greedy | Backtracking |
|---|---:|---:|
| Classes Scheduled | 28/28 | 28/28 |
| Assignment Attempts | 1100 | 1100 |
| Backtracks | Not Applicable | 0 |
| Status | Success | Success |

Both algorithms generated a complete timetable for the current dataset.

The Backtracking algorithm produced zero backtracks because the first sequence of valid choices successfully generated the complete timetable. Therefore, no previous assignment had to be removed.

The measured execution time for the current small dataset may appear as `0.000000 seconds` because the program completes faster than the available timer resolution.

## 8. Test Cases

### Test Case 1 - Valid Assignment

Course ID: 1  
Room ID: 1  
Slot ID: 1  

Result:

`Assignment is valid.`

### Test Case 2 - Insufficient Room Capacity

Course ID: 1  
Room ID: 3  
Slot ID: 1  

Result:

`Room capacity is not enough.`

### Test Case 3 - Wrong Room Type

Course ID: 5  
Room ID: 1  
Slot ID: 1  

Result:

`Required room type does not match.`

### Test Case 4 - Faculty Unavailable

Course ID: 1  
Room ID: 1  
Slot ID: 3  

Result:

`Faculty is unavailable in this time slot.`

### Test Case 5 - Normal Timetable Generation

The normal dataset contains:

- 2 student groups
- 5 faculty members
- 5 rooms
- 10 course records
- 30 available time slots
- 28 required weekly classes

Result:

`28/28 classes scheduled successfully.`

## 9. Time Complexity

### Greedy Algorithm

For every required lecture, the algorithm may check multiple time-slot and room combinations.

If:

- L = number of required lectures
- S = number of time slots
- R = number of rooms

the basic search is approximately:

`O(L * S * R)`

Since the current constraint checker may also scan existing assignments, the actual implementation can require additional work as the timetable grows.

### Backtracking Algorithm

Backtracking may explore many possible room and time-slot combinations.

If each lecture has approximately `S * R` possible choices, the worst-case search can grow exponentially with the number of lectures.

A simplified worst-case representation is:

`O((S * R)^L)`

Constraints help prune invalid choices and reduce the practical search space.

## 10. Project Structure

```text
University-Timetable-DAA/
|
|-- include/
|   |-- models.h
|   |-- constraints.h
|   |-- scheduler.h
|   `-- backtracking.h
|
|-- src/
|   |-- main.c
|   |-- models.c
|   |-- constraints.c
|   |-- scheduler.c
|   `-- backtracking.c
|
|-- data/
`-- README.md
```

## 11. Compilation

The project can currently be compiled using GCC with:

```bash
gcc -std=c11 -Wall -Wextra src/main.c src/models.c src/constraints.c src/scheduler.c src/backtracking.c -Iinclude -o timetable
```

Run on Windows using:

```bash
.\timetable.exe
```

The current local GCC installation recognizes C11 mode. The source code uses standard C features and can be migrated/tested with a C17-capable compiler as required by the project specification.

## 12. Main Menu

The application currently provides:

1. View Courses
2. View Faculty
3. View Student Groups
4. View Rooms
5. View Time Slots
6. Test Assignment
7. Generate Greedy Timetable
8. Generate Backtracking Timetable
9. View Complete Timetable
10. View Timetable by Student Group
11. Compare Greedy and Backtracking
0. Exit

## 13. Limitations

The current version uses a predefined sample university dataset.

The current implementation focuses mainly on clash-free timetable generation using Greedy and Backtracking approaches.

The current dataset is small, so execution-time differences between the algorithms are difficult to observe using the current timer resolution.

The normal dataset does not force the Backtracking algorithm to undo an assignment, therefore the backtrack count is zero for this scenario.

Advanced optimization objectives such as minimizing student gaps, balancing faculty workload and optimizing room utilization are not yet fully implemented.

## 14. Future Scope

The project can be extended by adding:

- Dynamic user input and file-based datasets
- Larger university datasets
- Alternative timetable generation
- Room utilization optimization
- Faculty preference handling
- Student gap minimization
- Exam timetable generation
- Automatic rescheduling when a room or faculty member becomes unavailable
- Branch and Bound optimization
- Additional DAA algorithms and comparative analysis
- CSV/JSON timetable export
- Graphical or web-based user interface

## 15. Conclusion

The project demonstrates how Design and Analysis of Algorithms concepts can be applied to a real scheduling problem.

The current system successfully models university scheduling constraints and generates clash-free timetables using Greedy and Backtracking approaches. It also provides algorithm comparison, constraint diagnostics and group-wise timetable visualization.