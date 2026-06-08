# 📚 Student Course Management System

A terminal-based student course management system written in **ANSI C**, developed as a homework assignment for the **Structured Programming** course at Yıldız Technical University.

---

## 📋 Description

This program simulates a simple student information system where users can manage a student's courses, grades, and academic records through an interactive menu-driven interface. It makes use of dynamic memory allocation (`malloc`/`realloc`/`free`) to handle a variable number of courses.

---

## ✨ Features

| # | Feature |
|---|---------|
| 1 | **Initialize Student** – Set student name and number |
| 2 | **Add Course** – Dynamically add a course with name, code, and credit |
| 3 | **Delete Course** – Remove a course by code, with memory shrinking |
| 4 | **Enter Grades** – Record midterm & final grades; auto-calculates weighted average |
| 5 | **Update Course** – Modify course name and credit hours |
| 6 | **Update Student Info** – Change student name and number |
| 7 | **Print Report Card** – Tabular view of all courses and overall GPA |
| 8 | **Credit Load Report** – Total credit hours summary |
| 9 | **Find Highest Grade Course** – Locate the best-performing course |
| 10 | **List Failed Courses** – Show courses with average below 50 |
| 11 | **Sort Courses Alphabetically** – Bubble sort by course name |
| 12 | **Copy Courses to Another Student** – Deep copy to a secondary student struct |
| 0 | **Free System & Exit** – Release all heap memory and terminate |

---

## 🧮 Grade Calculation

Course averages are computed using the standard weighted formula:

```
Average = (Midterm × 0.4) + (Final × 0.6)
```

The overall GPA is a **credit-weighted average** across all courses:

```
Overall Average = Σ(course_average × credit) / Σ(credit)
```

A course is considered **failed** if its average is below **50**.

---

## 🗂️ Data Structures

```c
typedef struct {
    char courseName[50];
    char courseCode[10];
    int  credit;
    int  midtermGrade;
    int  finalGrade;
    float average;
} Course;

typedef struct {
    char   name[50];
    int    studentNo;
    Course *courses;      /* dynamic array */
    int    courseCount;
    float  overallAverage;
} Student;
```

---

## 🔧 Build & Run

Requires a C compiler with C89/ANSI C support (e.g., GCC).

```bash
gcc -ansi -Wall -o sp_homework1 sp_homework1.c
./sp_homework1
```

---

## 📁 File Structure

```
YTU-sp_homework1/
├── sp_homework1.c   # Main source file (all logic in a single file)
└── README.md
```

---

## 🏫 Course Info

| Field | Detail |
|-------|--------|
| University | Yıldız Technical University |
| Department | Computer Engineering |
| Course | Structured Programming (SP) |
| Language | ANSI C (C89) |

---

## 📌 Notes

- The program manages **two students**: a primary (`stu1`) and a spare (`stu2`) used for the copy operation.
- All dynamic memory is allocated with `realloc` and properly freed on exit.
- Input is handled via `scanf`; course names support spaces using `%[^\n]` format.
