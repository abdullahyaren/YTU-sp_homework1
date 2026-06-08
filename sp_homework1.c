#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char courseName[50];
    char courseCode[10];
    int credit;
    int midtermGrade;
    int finalGrade;
    float average;
} Course;
typedef struct {
    char name[50];
    int studentNo;
    Course *courses;
    int courseCount;
    float overallAverage;
} Student;
void initStudent(Student *stu, char *name, int no);
void addCourse(Student *stu, char *name, char *code, int credit);
void deleteCourse(Student *stu, char *code);
void freeSystem(Student *stu);
void enterGrades(Student *stu, char *code, int midterm, int final);
void calculateOverallAverage(Student *stu);
void updateCourse(Student *stu, char *code, char *newName, int newCredit);
int searchCourse(Student *stu, char *code);
void findHighestGradeCourse(Student stu);
void listFailedCourses(Student stu);
void printReportCard(Student stu);
void creditLoadReport(Student stu);
void sortCoursesAlphabetically(Student *stu);
void updateStudentInfo(Student *stu, char *newName, int newNo);
void copyCourses(Student *target, Student source);
int main(){
    Student stu1;
    Student stu2;
    int selection=-1;
    char tempname[50];
    char tempcode[10];
    int tempcredit, tempmidterm, tempfinal, tempnumber;
    initStudent(&stu2, "Spare Student", 0);
    printf("- WELCOME TO THE STUDENT COURSE MANAGEMENT SYSTEM - \n");
    while(selection!=0){
        printf("1. Initialize Student \n");
        printf("2. Add Course \n");
        printf("3. Delete Course \n");
        printf("4. Enter Grade \n");
        printf("5. Update Course \n");
        printf("6. Update Student Info \n");
        printf("7. Print Report Card \n");
        printf("8. Credit Load Report \n");
        printf("9. Find Highest Grade Course \n");
        printf("10. List Failed Courses \n");
        printf("11. Sort Courses Alphabetically \n");
        printf("12. Copy Courses to Another Student \n");
        printf("0. Free System and Exit \n");
        printf("----- \n");
        printf("Your Selection: \n");
        scanf("%d", &selection);
        switch(selection){
            case 1:
                printf("Student name? \n");
                scanf(" %[^\n]", tempname);
                printf("Student number? \n");
                scanf("%d", &tempnumber);
                initStudent(&stu1, tempname, tempnumber);
                printf("Student initialized successfully. \n");
                break;
            case 2:
                printf("Name of the course to be added? \n");
                scanf(" %[^\n]", tempname);
                printf("Course code? \n");
                scanf("%s", tempcode);
                printf("Course Credit? \n");
                scanf("%d", &tempcredit);
                addCourse(&stu1, tempname, tempcode, tempcredit);
                printf("Course added successfully. \n");
                break;
            case 3:
                printf("Course code to be deleted? \n");
                scanf("%s", tempcode);
                deleteCourse(&stu1, tempcode);
                calculateOverallAverage(&stu1);
                printf("Course deleted successfully. \n");
                break;
            case 4:
                printf("Course code to be entered grade? \n");
                scanf("%s", tempcode);
                printf("Midterm grade? \n");
                scanf("%d", &tempmidterm);
                printf("Final grade? \n");
                scanf("%d", &tempfinal);
                enterGrades(&stu1, tempcode, tempmidterm, tempfinal);
                calculateOverallAverage(&stu1);
                printf("Grades were entered and the student's overall average was updated successfully. \n");
                break;
            case 5:
                printf("Course code to be updated? \n");
                scanf("%s", tempcode);
                printf("New course name? \n");
                scanf(" %[^\n]", tempname);
                printf("New credit? \n");
                scanf("%d", &tempcredit);
                updateCourse(&stu1, tempcode, tempname, tempcredit);
                printf("Course information has been updated successfully. \n");
                break;
            case 6:
                printf("New student name? \n");
                scanf(" %[^\n]", tempname);
                printf("Student number? \n");
                scanf("%d", &tempnumber);
                updateStudentInfo(&stu1, tempname, tempnumber);
                printf("Student information has been updated successfully. \n");
                break;
            case 7:
                printReportCard(stu1);
                printf("Report Card printed successfully. \n");
                break;
            case 8:
                creditLoadReport(stu1);
                printf("Credit Load reported successfully. \n");
                break;
            case 9:
                findHighestGradeCourse(stu1);
                printf("Highest grade course has been found successfully. \n");
                break;
            case 10:
                listFailedCourses(stu1);
                printf("Failed courses listed successfully. \n");
                break;
            case 11:
                sortCoursesAlphabetically(&stu1);
                printf("Courses sorted alphabetically successfully. \n");
                break;
            case 12:
                copyCourses(&stu2, stu1);
                printf("The student's courses were copied to the spare student successfully. \n");
                break;
            case 0:
                printf("The system is shutting down, dynamic memory is being cleared. \n");
                freeSystem(&stu1);
                freeSystem(&stu2);
                break;
            default:
                printf("Invalid selection! Please enter one of the numbers from the menu. \n");
                break;
        }
    }
    return 0;
}
void initStudent(Student *stu, char *name, int no){
    strcpy(stu->name, name);
    stu->studentNo=no;
    stu->courseCount=0;
    stu->overallAverage=0.0;
    stu->courses=NULL;
}
void addCourse(Student *stu, char *name, char *code, int credit){
    Course *temp=(Course*)realloc(stu->courses, (stu->courseCount+1)*sizeof(Course));
    if(temp==NULL){
        printf("Error! Memory could not be allocated for the new course.");
        return;
    }
    stu->courses=temp;
    int index=stu->courseCount;
    strcpy(stu->courses[index].courseName, name);
    strcpy(stu->courses[index].courseCode, code);
    stu->courses[index].credit=credit;
    stu->courses[index].midtermGrade=0;
    stu->courses[index].finalGrade=0;
    stu->courses[index].average=0.0;
    stu->courseCount++;
}
void deleteCourse(Student *stu, char *code){
    int foundindex=-1;
    int i=0;
    while(i<stu->courseCount && foundindex==-1){
        if(strcmp(stu->courses[i].courseCode, code)==0){
            foundindex=i;
        }
        i++;
    }
    if(foundindex==-1){
        printf("Error! Course code %s not found. \n", code);
        return;
    }
    int j;
    for(j=foundindex;j<stu->courseCount-1;j++){
        stu->courses[j]=stu->courses[j+1];
    }
    stu->courseCount--;
    if(stu->courseCount==0){
        free(stu->courses);
        stu->courses=NULL;
    } else{
        Course *temp=(Course*)realloc(stu->courses, stu->courseCount*sizeof(Course));
        if(temp!=NULL){
            stu->courses=temp;
        } else{
            printf("Error! The course was deleted, but the memory reduction operation failed.");
        }
    }
}
void freeSystem(Student *stu){
    if(stu->courses!=NULL){
        free(stu->courses);
        stu->courses=NULL;
        stu->courseCount=0;
        stu->overallAverage=0.0;
    }
}
void enterGrades(Student *stu, char *code, int midterm, int final){
    int foundindex=-1;
    int i=0;
    while(i<stu->courseCount && foundindex==-1){
        if(strcmp(stu->courses[i].courseCode, code)==0){
            foundindex=i;
        }
        i++;
    }
    if(foundindex==-1){
        printf("Error! Course code %s not found for grade entry. \n", code);
        return;
    }
    stu->courses[foundindex].midtermGrade=midterm;
    stu->courses[foundindex].finalGrade=final;
    stu->courses[foundindex].average=(midterm*0.4)+(final*0.6);
}
void calculateOverallAverage(Student *stu){
    float totalpoint=0.0;
    int totalcredit=0;
    int i;
    for(i=0;i<stu->courseCount;i++){
        totalcredit+=stu->courses[i].credit;
        totalpoint+=(stu->courses[i].average*stu->courses[i].credit);
    }
    if(totalcredit>0){
        stu->overallAverage=totalpoint/totalcredit;
    } else{
        stu->overallAverage=0.0;
    }
}
void updateCourse(Student *stu, char *code, char *newName, int newCredit){
    int foundindex=-1;
    int i=0;
    while(i<stu->courseCount && foundindex==-1){
        if(strcmp(stu->courses[i].courseCode, code)==0){
            foundindex=i;
        }
        i++;
    }
    if(foundindex==-1){
        printf("Error! The course with code %s that needs to be updated could not be found. \n", code);
        return;
    }
    strcpy(stu->courses[foundindex].courseName, newName);
    stu->courses[foundindex].credit=newCredit;
    calculateOverallAverage(stu);
}
int searchCourse(Student *stu, char *code){
    int foundindex=-1;
    int i=0;
    while(i<stu->courseCount && foundindex==-1){
        if(strcmp(stu->courses[i].courseCode, code)==0){
            foundindex=i;
        }
        i++;
    }
    return foundindex;
}
void findHighestGradeCourse(Student stu){
    if(stu.courseCount==0){
        printf("The student has no registered courses! \n");
        return;
    }
    int maxindex=0;
    int i;
    for(i=1;i<stu.courseCount;i++){
        if(stu.courses[i].average>stu.courses[maxindex].average){
            maxindex=i;
        }
    }
    printf("The course  with the highest grade: %s (Average: %.2f) \n", stu.courses[maxindex].courseName, stu.courses[maxindex].average);
}
void listFailedCourses(Student stu){
    int failedcount=0;
    printf("\t - Failed Courses (Average<50) - \n");
    int i;
    for(i=0;i<stu.courseCount;i++){
        if(stu.courses[i].average<50){
            printf("- %s (%s): Average= %.2f (Failed) \n", stu.courses[i].courseName, stu.courses[i].courseCode, stu.courses[i].average);
            failedcount++;
        }
    }
    if(failedcount==0 && stu.courseCount>0){
        printf("Congratulations, you have no failing courses. \n");
    } else if(stu.courseCount==0){
        printf("No courses were found registered in the system. \n");
    }
}
void printReportCard(Student stu){
    printf("\t --- STUDENT REPORT CARD --- \n");
    printf("Student Name   : %s \n", stu.name);
    printf("Student Number : %d \n", stu.studentNo);
    if(stu.courseCount==0){
        printf("This student has no courses registered in the system. \n");
        return;
    }
    printf("%-20s %-10s %-5s %-5s %-5s %-10s \n", "Course Name", "Code", "Credit", "Midterm", "Final", "Average");
    int i;
    for(i=0;i<stu.courseCount;i++){
        printf("%-20s %-10s %-5d %-5d %-5d %-10.2f \n", stu.courses[i].courseName, stu.courses[i].courseCode, stu.courses[i].credit, stu.courses[i].midtermGrade, stu.courses[i].finalGrade, stu.courses[i].average);
    }
    printf("Overall Average: %.2f \n", stu.overallAverage);
}
void creditLoadReport(Student stu){
    int totalcreditload=0;
    int i;
    for(i=0;i<stu.courseCount;i++){
        totalcreditload+=stu.courses[i].credit;
    }
    printf("\t - Credit Load Report - \n");
    printf("Student Name: %s \n", stu.name);
    printf("Total Number of Courses: %d \n", stu.courseCount);
    printf("Total Credit Load: %d \n", totalcreditload);
}
void sortCoursesAlphabetically(Student *stu){
    Course temp;
    int i, j;
    for(i=0;i<stu->courseCount-1;i++){
        for(j=0;j<stu->courseCount-i-1;j++){
            if(strcmp(stu->courses[j].courseName, stu->courses[j+1].courseName)>0){
                temp=stu->courses[j];
                stu->courses[j]=stu->courses[j+1];
                stu->courses[j+1]=temp;
            }
        }
    }
    printf("\t - Alphabetically Ordered Course List - \n");
    for(i=0;i<stu->courseCount;i++){
        printf("%d. %s (%s) \n", i+1, stu->courses[i].courseName, stu->courses[i].courseCode);
    }
}
void updateStudentInfo(Student *stu, char *newName, int newNo){
    strcpy(stu->name, newName);
    stu->studentNo=newNo;
}
void copyCourses(Student *target, Student source){
    if(source.courseCount==0){
        if(target->courses!=NULL){
            free(target->courses);
            target->courses=NULL;
        }
        target->courseCount=0;
        target->overallAverage=0.0;
        return;
    }
    Course *temp=(Course*)realloc(target->courses, source.courseCount*sizeof(Course));
    if(temp==NULL){
        printf("Error! Memory could not be allocated for the copy operation.");
        return;
    }
    target->courses=temp;
    int i;
    for(i=0;i<source.courseCount;i++){
        target->courses[i]=source.courses[i];
    }
    target->courseCount=source.courseCount;
    target->overallAverage=source.overallAverage;
    printf("Successful! The lessons of student %s have been copied to student %s. \n", source.name, target->name);
}
