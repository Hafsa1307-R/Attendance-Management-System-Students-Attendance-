/*
 * Project:       ATTENDANCE MANAGEMENT SYSTEM
 * Contributors:  Hafsa Imran (CS-26013) 
                  Afshan Waheed (CS-26007) 
                  Noor ul Huda (CS-26015) 
                  Anoosha Qamar(CS-26020) 
 * Date:          27/11/2026
 */


#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define REQUIRED_ATTENDANCE 75.0
#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

// FUNCTION PROTOTYPES

struct Student;
struct Course;
struct Attendance;

void clear_input();
int read_int(const char *prompt, int *value);

int read_student(FILE *fp, struct Student *ptr);
int read_course(FILE *fp, struct Course *ptr);
int read_attendance(FILE *fp, struct Attendance *ptr);

int replace_file(const char *original, const char *temporary);

void Main_Login_Menu();

void Student_Login();
void Teacher_Login();
void Student_Dashboard();
void Teacher_Dashboard();

int student_exists(int id);
int course_exists(int id);
int get_student(int id, struct Student *ptr);
int get_course(int id, struct Course *ptr);

void create_student_login();
void remove_student_login();
void viewMyProfile();
void display_student_details(struct Student *ptr);

void Student_Management_Module();
int count_students();
void add_student();
void display_students();
void search_student();
void update_student();
void delete_student();

void Course_Management_Module();
int count_courses();
void add_course();
void display_courses();
void search_course();
void update_course();
void delete_course();

void Attendance_Management_Module();
int valid_date(char date[]);
const char *get_day_name(char date[]);
int attendance_exists(int studentID, int courseID, char date[]);
int student_has_attendance(int id);
int course_has_attendance(int id);

void mark_attendance();
void search_attendance();
void view_course_attendance();
void display_all_attendance();
void update_attendance();
void delete_attendance();

void view_attendance_percentage();


// STRUCTURE DECLARATIONS

struct Student
{
    int id;
    char name[50];
    char department[30];
    int semester;
    char gender[15];
} s;


struct Course
{
    int courseID;
    char courseTitle[50];
    char courseCode[20];
    char department[30];
    int semester;
};


struct Attendance
{
    int studentID;
    int courseID;
    char date[15];
    char status[10];
};


// GLOBAL VARIABLE

int loggedInStudentID;


// MAIN FUNCTION

int main()
{
    int choice;

    printf("\n==============================================");
    printf("\n       STUDENT ATTENDANCE MANAGEMENT SYSTEM");
    printf("\n==============================================\n");

    while(1)
    {
        Main_Login_Menu();

        if(!read_int("Enter your choice: ", &choice))
        {
            continue;
        }

        switch(choice)
        {
            case 1:
                Student_Login();
                break;

            case 2:
                Teacher_Login();
                break;

            case 3:
                printf("\nExiting System...\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}




// =====================================================
// MAIN LOGIN MENU
// =====================================================

void Main_Login_Menu()
{
    printf("\n========== MAIN LOGIN MENU ==========");
    printf("\n1. Student Login");
    printf("\n2. Teacher Login");
    printf("\n3. Exit\n");
}


// =====================================================
// LOGIN AND DASHBOARD FUNCTIONS
// =====================================================


// Check if student exists

int student_exists(int id)
{
    struct Student temp;

    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_student(fp, &temp))
    {
        if(temp.id == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


// Check if course exists

int course_exists(int id)
{
    struct Course c;

    FILE *fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_course(fp, &c))
    {
        if(c.courseID == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


// Get course details using Course ID

int get_course(int id, struct Course *ptr)
{
    FILE *fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_course(fp, ptr))
    {
        if(ptr->courseID == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}
// Get student details using Student ID

int get_student(int id, struct Student *ptr)
{
    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_student(fp, ptr))
    {
        if(ptr->id == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

// STUDENT LOGIN

void Student_Login()
{
    int id, fileID, found = 0;

    char password[50], filePassword[50], line[100];

    FILE *fp;

    printf("\n========== STUDENT LOGIN ==========\n");

    if(!read_int("Enter Student ID: ", &id))
    {
        return;
    }

    printf("Enter Password: ");

    if(scanf("%49s", password) != 1)
    {
        clear_input();
        return;
    }

    if(student_exists(id) == 0)
    {
        printf("\nStudent ID not registered! Add student first.\n");
        return;
    }

    fp = fopen("Login.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo login accounts found!\n");
        return;
    }

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line, "%d,%49[^\n]", &fileID, filePassword) == 2)
        {
            if(fileID == id && strcmp(password, filePassword) == 0)
            {
                found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if(found)
    {
        loggedInStudentID = id;

        printf("\nLogin Successful!\n");

        Student_Dashboard();
    }
    else
    {
        printf("\nInvalid ID or Password!\n");
    }
}


// TEACHER LOGIN

void Teacher_Login()
{
    char adminID[30], password[30];

    printf("\n========== TEACHER LOGIN ==========\n");

    printf("Enter Admin ID: ");
    if(scanf("%29s", adminID) != 1)
    {
        clear_input();
        return;
    }

    printf("Enter Password: ");
    if(scanf("%29s", password) != 1)
    {
        clear_input();
        return;
    }

    if(strcmp(adminID, "ADMIN01") == 0 &&
       strcmp(password, "admin123") == 0)
    {
        printf("\nTeacher Login Successful!\n");

        Teacher_Dashboard();
    }
    else
    {
        printf("\nInvalid Admin ID or Password!\n");
    }
}


// STUDENT DASHBOARD

void Student_Dashboard()
{
    int choice;

    do
    {
        printf("\n========== STUDENT DASHBOARD ==========\n");

        printf("1. View My Profile\n");
        printf("2. View My Attendance\n");
        printf("3. Logout\n");

        if(!read_int("Enter choice: ", &choice))
        {
            choice = 0;
            continue;
        }

        switch(choice)
        {
            case 1:
                viewMyProfile();
                break;

            case 2:
                view_attendance_percentage();
                break;

            case 3:
                printf("\nLogging Out...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 3);
}


// Display student details using structure pointer

void display_student_details(struct Student *ptr)
{
    printf("\nStudent ID: %d", ptr->id);
    printf("\nName: %s", ptr->name);
    printf("\nDepartment: %s", ptr->department);
    printf("\nSemester: %d", ptr->semester);
    printf("\nGender: %s\n", ptr->gender);
}


// VIEW MY PROFILE

void viewMyProfile()
{
    struct Student student;

    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    while(read_student(fp, &student))
    {
        if(student.id == loggedInStudentID)
        {
            printf("\n--- MY PROFILE ---\n");

            display_student_details(&student);

            fclose(fp);
            return;
        }
    }

    fclose(fp);

    printf("\nStudent profile not found!\n");
}


// TEACHER DASHBOARD

void Teacher_Dashboard()
{
    int choice;

    do
    {
        printf("\n========== TEACHER DASHBOARD ==========\n");

        printf("1. Student Management\n");
        printf("2. Create Student Login\n");
        printf("3. Remove Student Login\n");
        printf("4. Course Management\n");
        printf("5. Attendance Management\n");
        printf("6. View All Students\n");
        printf("7. Logout\n");

        if(!read_int("Enter choice: ", &choice))
        {
            choice = 0;
            continue;
        }

        switch(choice)
        {
            case 1:
                Student_Management_Module();
                break;

            case 2:
                create_student_login();
                break;

            case 3:
                remove_student_login();
                break;

            case 4:
                Course_Management_Module();
                break;

            case 5:
                Attendance_Management_Module();
                break;

            case 6:
                display_students();
                break;

            case 7:
                printf("\nLogging Out...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);
}


// =====================================================
// STUDENT LOGIN MANAGEMENT
// =====================================================


// CREATE STUDENT LOGIN

void create_student_login()
{
    int id, fileID;

    char password[50], line[100];

    FILE *fp;

    printf("\n========== CREATE STUDENT LOGIN ==========\n");

    if(!read_int("Enter Student ID: ", &id))
    {
        return;
    }

    if(student_exists(id) == 0)
    {
        printf("\nStudent Record Not Found! Add student first.\n");
        return;
    }

    fp = fopen("Login.csv", "r");

    if(fp != NULL)
    {
        while(fgets(line, sizeof(line), fp))
        {
            if(sscanf(line, "%d", &fileID) == 1 && fileID == id)
            {
                printf("\nLogin Already Exists!\n");
                fclose(fp);
                return;
            }
        }

        fclose(fp);
    }

    printf("Create Password: ");

    if(scanf("%49s", password) != 1)
    {
        clear_input();
        return;
    }

    fp = fopen("Login.csv", "a");

    if(fp == NULL)
    {
        printf("\nError opening Login.csv!\n");
        return;
    }

    fprintf(fp, "%d,%s\n", id, password);

    fclose(fp);

    printf("\nStudent Login Created Successfully!\n");
}


// REMOVE STUDENT LOGIN

void remove_student_login()
{
    int id, fileID, found = 0;

    char password[50], line[100];

    FILE *fp = fopen("Login.csv", "r");

    FILE *temp = fopen("TempLogin.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Login Records!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("TempLogin.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        fclose(fp);
        printf("\nError opening temporary file!\n");
        return;
    }

    if(!read_int("Enter Student ID to remove login: ", &id))
    {
        fclose(fp);
        fclose(temp);
        remove("TempLogin.csv");
        return;
    }

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line, "%d,%49[^\n]", &fileID, password) == 2)
        {
            if(fileID == id)
            {
                found = 1;
            }
            else
            {
                fprintf(temp, "%d,%s\n", fileID, password);
            }
        }
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nLogin Not Found!\n");
        remove("TempLogin.csv");
        return;
    }

    if(replace_file("Login.csv", "TempLogin.csv"))
    {
        printf("\nLogin Removed Successfully!\n");
    }
}


// =====================================================
// STUDENT MANAGEMENT MODULE
// =====================================================


// STUDENT MANAGEMENT MENU

void Student_Management_Module()
{
    int choice;

    do
    {
        printf("\n========== STUDENT MANAGEMENT ==========\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit Module\n");

        if(!read_int("Enter choice: ", &choice))
        {
            choice = 0;
            continue;
        }

        switch(choice)
        {
            case 1:
                add_student();
                break;

            case 2:
                display_students();
                break;

            case 3:
                search_student();
                break;

            case 4:
                update_student();
                break;

            case 5:
                delete_student();
                break;

            case 6:
                printf("\nExiting Student Management...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 6);
}


// COUNT STUDENTS

int count_students()
{
    int total = 0;

    struct Student student;

    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_student(fp, &student))
    {
        total++;
    }

    fclose(fp);

    return total;
}


// ADD STUDENT

void add_student()
{
    struct Student student;

    FILE *fp;

    printf("\n========== ADD STUDENT ==========\n");

    if(count_students() >= MAX_STUDENTS)
    {
        printf("\nStudent Limit Reached!\n");
        return;
    }

    if(!read_int("Enter Student ID: ", &student.id) || student.id <= 0)
    {
        printf("\nInvalid Student ID!\n");
        return;
    }

    if(student_exists(student.id))
    {
        printf("\nStudent ID Already Exists!\n");
        return;
    }

    printf("Enter Student Name: ");
    if(scanf(" %49[^\n]", student.name) != 1)
    {
        clear_input();
        return;
    }

    printf("Enter Department: ");
    if(scanf(" %29[^\n]", student.department) != 1)
    {
        clear_input();
        return;
    }

    if(!read_int("Enter Semester: ", &student.semester) ||
       student.semester <= 0)
    {
        printf("\nInvalid Semester!\n");
        return;
    }

    printf("Enter Gender (Male/Female): ");
    if(scanf(" %14[^\n]", student.gender) != 1)
    {
        clear_input();
        return;
    }

    fp = fopen("Students.csv", "a");

    if(fp == NULL)
    {
        printf("\nError opening Students.csv!\n");
        return;
    }

    fprintf(fp, "%d,%s,%s,%d,%s\n",
            student.id, student.name, student.department,
            student.semester, student.gender);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}


// DISPLAY STUDENTS


// DISPLAY STUDENT RECORDS

void display_students()
{
    struct Student students[1000];
    struct Student temp;

    int count = 0;

    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        printf("\nStudents.csv file not found!\n");
        return;
    }

    // READ ALL STUDENT RECORDS

    while(count < 1000 && read_student(fp, &students[count]))
    {
        count++;
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nNo Student Records Available!\n");
        return;
    }

    // SORT BY DEPARTMENT, SEMESTER AND STUDENT ID

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(students[j].department,
                      students[j + 1].department) > 0 ||

               (strcmp(students[j].department,
                       students[j + 1].department) == 0 &&
                students[j].semester > students[j + 1].semester) ||

               (strcmp(students[j].department,
                       students[j + 1].department) == 0 &&
                students[j].semester == students[j + 1].semester &&
                students[j].id > students[j + 1].id))
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // DISPLAY STUDENT TABLE

    printf("\n================ STUDENT RECORDS ================\n");

    printf("\n%-10s %-20s %-22s %-12s %-10s\n",
           "ID", "Name", "Department", "Semester", "Gender");
    printf("----------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        // DOTTED LINE WHEN DEPARTMENT OR SEMESTER CHANGES

        if(i > 0 &&
           (strcmp(students[i].department,
                   students[i - 1].department) != 0 ||
            students[i].semester != students[i - 1].semester))
        {
            printf("..........................................................................\n");
        }

        printf("%-10d %-20s %-22s %-12d %-10s\n",
               students[i].id,
               students[i].name,
               students[i].department,
               students[i].semester,
               students[i].gender);
    }

    printf("-----------------------------------------------------------------------------\n");
}

// SEARCH STUDENT

void search_student()
{
    struct Student student;

    int id, found = 0;

    FILE *fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Student Records Found!\n");
        return;
    }

    if(!read_int("Enter Student ID to Search: ", &id))
    {
        fclose(fp);
        return;
    }

    while(read_student(fp, &student))
    {
        if(student.id == id)
        {
            printf("\nStudent Found!\n");

            display_student_details(&student);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nStudent Not Found!\n");
    }
}


// UPDATE STUDENT

void update_student()
{
    struct Student student;

    int id, found = 0;

    FILE *fp = fopen("Students.csv", "r");
    FILE *temp = fopen("Temporary.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Student Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("Temporary.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Student ID to Update: ", &id))
    {
        fclose(fp);
        fclose(temp);
        remove("Temporary.csv");
        return;
    }

    while(read_student(fp, &student))
    {
        if(student.id == id)
        {
            found = 1;

            printf("\nEnter New Name: ");
            if(scanf(" %49[^\n]", student.name) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("Temporary.csv");
                return;
            }

            printf("Enter New Department: ");
            if(scanf(" %29[^\n]", student.department) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("Temporary.csv");
                return;
            }

            if(!read_int("Enter New Semester: ", &student.semester) ||
               student.semester <= 0)
            {
                printf("\nInvalid Semester! Update Cancelled.\n");

                fclose(fp);
                fclose(temp);
                remove("Temporary.csv");
                return;
            }

            printf("Enter New Gender: ");
            if(scanf(" %14[^\n]", student.gender) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("Temporary.csv");
                return;
            }
        }

        fprintf(temp, "%d,%s,%s,%d,%s\n",
                student.id, student.name, student.department,
                student.semester, student.gender);
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nStudent Not Found!\n");
        remove("Temporary.csv");
        return;
    }

    if(replace_file("Students.csv", "Temporary.csv"))
    {
        printf("\nStudent Updated Successfully!\n");
    }
}


// CHECK IF STUDENT HAS ATTENDANCE

int student_has_attendance(int id)
{
    struct Attendance a;

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_attendance(fp, &a))
    {
        if(a.studentID == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


// DELETE STUDENT

void delete_student()
{
    struct Student student;

    int id, found = 0;

    FILE *fp = fopen("Students.csv", "r");
    FILE *temp = fopen("Temporary.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Student Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("Temporary.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Student ID to Delete: ", &id))
    {
        fclose(fp);
        fclose(temp);
        remove("Temporary.csv");
        return;
    }

    if(student_has_attendance(id))
    {
        printf("\nCannot delete this student because attendance records exist!\n");

        fclose(fp);
        fclose(temp);
        remove("Temporary.csv");
        return;
    }

    while(read_student(fp, &student))
    {
        if(student.id == id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%d,%s\n",
                    student.id, student.name, student.department,
                    student.semester, student.gender);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nStudent Not Found!\n");
        remove("Temporary.csv");
        return;
    }

    if(replace_file("Students.csv", "Temporary.csv"))
    {
        printf("\nStudent Deleted Successfully!\n");
    }
}


// =====================================================
// COURSE MANAGEMENT MODULE
// =====================================================


// COURSE MANAGEMENT MENU

void Course_Management_Module()
{
    int choice;

    do
    {
        printf("\n========== COURSE MANAGEMENT ==========\n");

        printf("1. Add Course\n");
        printf("2. Display Courses\n");
        printf("3. Search Course\n");
        printf("4. Update Course\n");
        printf("5. Delete Course\n");
        printf("6. Count Courses\n");
        printf("7. Exit Module\n");

        if(!read_int("Enter choice: ", &choice))
        {
            choice = 0;
            continue;
        }

        switch(choice)
        {
            case 1:
                add_course();
                break;

            case 2:
                display_courses();
                break;

            case 3:
                search_course();
                break;

            case 4:
                update_course();
                break;

            case 5:
                delete_course();
                break;

            case 6:
                printf("\nTotal Courses: %d\n", count_courses());
                break;

            case 7:
                printf("\nExiting Course Management...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);
}


// COUNT COURSES

int count_courses()
{
    int total = 0;

    struct Course course;

    FILE *fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_course(fp, &course))
    {
        total++;
    }

    fclose(fp);

    return total;
}


// ADD COURSE

void add_course()
{
    struct Course course;

    FILE *fp;

    printf("\n========== ADD COURSE ==========\n");

    if(!read_int("Enter Course ID: ", &course.courseID) ||
       course.courseID <= 0)
    {
        printf("\nInvalid Course ID!\n");
        return;
    }

    if(course_exists(course.courseID))
    {
        printf("\nCourse ID Already Exists!\n");
        return;
    }

    printf("Enter Course Title: ");
    if(scanf(" %49[^\n]", course.courseTitle) != 1)
    {
        clear_input();
        return;
    }

    printf("Enter Course Code: ");
    if(scanf("%19s", course.courseCode) != 1)
    {
        clear_input();
        return;
    }

    printf("Enter Department: ");
    if(scanf(" %29[^\n]", course.department) != 1)
    {
        clear_input();
        return;
    }

    if(!read_int("Enter Semester: ", &course.semester) ||
       course.semester <= 0)
    {
        printf("\nInvalid Semester!\n");
        return;
    }

    fp = fopen("Courses.csv", "a");

    if(fp == NULL)
    {
        printf("\nError opening Courses.csv!\n");
        return;
    }

    fprintf(fp, "%d,%s,%s,%s,%d\n",
            course.courseID, course.courseTitle,
            course.courseCode, course.department,
            course.semester);

    fclose(fp);

    printf("\nCourse Added Successfully!\n");
}


// DISPLAY COURSES


// DISPLAY COURSE RECORDS

void display_courses()
{
    struct Course courses[1000];
    struct Course temp;

    int count = 0;

    FILE *fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        printf("\nCourses.csv file not found!\n");
        return;
    }

    // READ ALL COURSE RECORDS

    while(count < 1000 && read_course(fp, &courses[count]))
    {
        count++;
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nNo Course Records Available!\n");
        return;
    }

    // SORT BY DEPARTMENT, SEMESTER AND COURSE ID

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(courses[j].department,
                      courses[j + 1].department) > 0 ||

               (strcmp(courses[j].department,
                       courses[j + 1].department) == 0 &&
                courses[j].semester > courses[j + 1].semester) ||

               (strcmp(courses[j].department,
                       courses[j + 1].department) == 0 &&
                courses[j].semester == courses[j + 1].semester &&
                courses[j].courseID > courses[j + 1].courseID))
            {
                temp = courses[j];
                courses[j] = courses[j + 1];
                courses[j + 1] = temp;
            }
        }
    }

    // DISPLAY COURSE TABLE

    printf("\n================ COURSE RECORDS ================\n");

    printf("\n%-10s %-25s %-15s %-20s %-10s\n",
           "ID", "Course Title", "Code", "Department", "Semester");

    printf("-----------------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        // DOTTED LINE WHEN DEPARTMENT OR SEMESTER CHANGES

        if(i > 0 &&
           (strcmp(courses[i].department,
                   courses[i - 1].department) != 0 ||
            courses[i].semester != courses[i - 1].semester))
        {
            printf(".................................................................................\n");
        }

        printf("%-10d %-25s %-15s %-20s %-10d\n",
               courses[i].courseID,
               courses[i].courseTitle,
               courses[i].courseCode,
               courses[i].department,
               courses[i].semester);
    }

    printf("-----------------------------------------------------------------------------------\n");
}


// SEARCH COURSE

void search_course()
{
    struct Course course;

    int id, found = 0;

    FILE *fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Course Records Found!\n");
        return;
    }

    if(!read_int("Enter Course ID to Search: ", &id))
    {
        fclose(fp);
        return;
    }

    while(read_course(fp, &course))
    {
        if(course.courseID == id)
        {
            printf("\nCourse Found!\n");

            printf("\nCourse ID: %d", course.courseID);
            printf("\nCourse Title: %s", course.courseTitle);
            printf("\nCourse Code: %s", course.courseCode);
            printf("\nDepartment: %s", course.department);
            printf("\nSemester: %d\n", course.semester);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nCourse Not Found!\n");
    }
}


// UPDATE COURSE

void update_course()
{
    struct Course course;

    int id, found = 0;

    FILE *fp = fopen("Courses.csv", "r");
    FILE *temp = fopen("TemporaryCourses.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Course Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("TemporaryCourses.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary course file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Course ID to Update: ", &id))
    {
        fclose(fp);
        fclose(temp);
        remove("TemporaryCourses.csv");
        return;
    }

    while(read_course(fp, &course))
    {
        if(course.courseID == id)
        {
            found = 1;

            printf("\nEnter New Course Title: ");
            if(scanf(" %49[^\n]", course.courseTitle) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("TemporaryCourses.csv");
                return;
            }

            printf("Enter New Course Code: ");
            if(scanf("%19s", course.courseCode) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("TemporaryCourses.csv");
                return;
            }

            printf("Enter New Department: ");
            if(scanf(" %29[^\n]", course.department) != 1)
            {
                clear_input();
                fclose(fp);
                fclose(temp);
                remove("TemporaryCourses.csv");
                return;
            }

            if(!read_int("Enter New Semester: ", &course.semester) ||
               course.semester <= 0)
            {
                printf("\nInvalid Semester! Update Cancelled.\n");

                fclose(fp);
                fclose(temp);
                remove("TemporaryCourses.csv");
                return;
            }
        }

        fprintf(temp, "%d,%s,%s,%s,%d\n",
                course.courseID, course.courseTitle,
                course.courseCode, course.department,
                course.semester);
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nCourse Not Found!\n");
        remove("TemporaryCourses.csv");
        return;
    }

    if(replace_file("Courses.csv", "TemporaryCourses.csv"))
    {
        printf("\nCourse Updated Successfully!\n");
    }
}


// CHECK IF COURSE HAS ATTENDANCE

int course_has_attendance(int id)
{
    struct Attendance a;

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_attendance(fp, &a))
    {
        if(a.courseID == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


// DELETE COURSE

void delete_course()
{
    struct Course course;

    int id, found = 0;

    FILE *fp = fopen("Courses.csv", "r");
    FILE *temp = fopen("TemporaryCourses.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Course Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("TemporaryCourses.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary course file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Course ID to Delete: ", &id))
    {
        fclose(fp);
        fclose(temp);
        remove("TemporaryCourses.csv");
        return;
    }

    if(course_has_attendance(id))
    {
        printf("\nCannot delete this course because attendance records exist!\n");

        fclose(fp);
        fclose(temp);
        remove("TemporaryCourses.csv");
        return;
    }

    while(read_course(fp, &course))
    {
        if(course.courseID == id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%s,%d\n",
                    course.courseID, course.courseTitle,
                    course.courseCode, course.department,
                    course.semester);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nCourse Not Found!\n");
        remove("TemporaryCourses.csv");
        return;
    }

    if(replace_file("Courses.csv", "TemporaryCourses.csv"))
    {
        printf("\nCourse Deleted Successfully!\n");
    }
}


// =====================================================
// DATE FUNCTIONS
// =====================================================


// CHECK DATE FORMAT: YYYY-MM-DD

int valid_date(char date[])
{
    int year, month, day;
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int i;

    if(strlen(date) != 10)
    {
        return 0;
    }

    if(date[4] != '-' || date[7] != '-')
    {
        return 0;
    }

    for(i = 0; i < 10; i++)
    {
        if(i != 4 && i != 7)
        {
            if(date[i] < '0' || date[i] > '9')
            {
                return 0;
            }
        }
    }

    if(sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        return 0;
    }

    if(year < 1 || month < 1 || month > 12)
    {
        return 0;
    }

    if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
        daysInMonth[1] = 29;
    }

    if(day < 1 || day > daysInMonth[month - 1])
    {
        return 0;
    }

    return 1;
}


// GET DAY NAME FROM DATE

const char *get_day_name(char date[])
{
    int year, month, day;
    int monthCode[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    const char *days[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };

    sscanf(date, "%4d-%2d-%2d", &year, &month, &day);

    if(month < 3)
    {
        year--;
    }

    int result = (year + year / 4 - year / 100 + year / 400 +
                  monthCode[month - 1] + day) % 7;

    return days[result];
}


// =====================================================
// ATTENDANCE MANAGEMENT MODULE
// =====================================================


// CHECK DUPLICATE ATTENDANCE

int attendance_exists(int studentID, int courseID, char date[])
{
    struct Attendance a;

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        return 0;
    }

    while(read_attendance(fp, &a))
    {
        if(a.studentID == studentID &&
           a.courseID == courseID &&
           strcmp(a.date, date) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


// ATTENDANCE MANAGEMENT MENU

void Attendance_Management_Module()
{
    int choice;

    do
    {
        printf("\n========== ATTENDANCE MANAGEMENT ==========\n");

        printf("1. Mark Attendance\n");
        printf("2. Search Attendance by Student ID\n");
        printf("3. View Attendance by Course and Date\n");
        printf("4. Display All Attendance Records\n");
        printf("5. Update Attendance\n");
        printf("6. Delete Attendance Record\n");
        printf("7. Exit Module\n");

        if(!read_int("Enter choice: ", &choice))
        {
            choice = 0;
            continue;
        }

        switch(choice)
        {
            case 1:
                mark_attendance();
                break;

            case 2:
                search_attendance();
                break;

            case 3:
                view_course_attendance();
                break;

            case 4:
                display_all_attendance();
                break;

            case 5:
                update_attendance();
                break;

            case 6:
                delete_attendance();
                break;

            case 7:
                printf("\nExiting Attendance Management...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);
}


// MARK ATTENDANCE

void mark_attendance()
{
    struct Student student;
    struct Course course;
    struct Attendance a;

    int courseID, statusChoice;
    int candidateFound = 0, marked = 0;

    FILE *fp;
    FILE *out;

    printf("\n========== MARK ATTENDANCE ==========\n");

    display_courses();

    if(!read_int("\nEnter Course ID: ", &courseID))
    {
        return;
    }

    if(!get_course(courseID, &course))
    {
        printf("\nCourse Not Found!\n");
        return;
    }

    printf("\nCourse: %s (%s)\n",
           course.courseTitle, course.courseCode);
    printf("Department: %s\n", course.department);
    printf("Semester: %d\n", course.semester);

    printf("Enter Date (YYYY-MM-DD): ");

    if(scanf("%14s", a.date) != 1)
    {
        clear_input();
        return;
    }

    if(!valid_date(a.date))
    {
        printf("\nInvalid Date!\n");
        return;
    }

    printf("\n==============================================================================================\n");
    printf("%-13s %-12s %-15s %-18s %-12s %-12s\n",
           "Date", "Day", "Student ID", "Course Code", "Present", "Absent");
    printf("==============================================================================================\n");

    fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Students Found!\n");
        return;
    }

    while(read_student(fp, &student))
    {
        if(strcmp(student.department, course.department) == 0 &&
           student.semester == course.semester)
        {
            candidateFound = 1;

            if(attendance_exists(student.id, courseID, a.date))
            {
                printf("\nAttendance Already Marked for %s!\n", student.name);
                continue;
            }

            printf("\nStudent ID: %d", student.id);
            printf("\nStudent Name: %s\n", student.name);

            printf("1. Present\n");
            printf("2. Absent\n");

            if(!read_int("Enter status: ", &statusChoice))
            {
                continue;
            }

            if(statusChoice == 1)
            {
                strcpy(a.status, "Present");
            }
            else if(statusChoice == 2)
            {
                strcpy(a.status, "Absent");
            }
            else
            {
                printf("\nInvalid Status! Student Skipped.\n");
                continue;
            }

            out = fopen("Attendance.csv", "a");

            if(out == NULL)
            {
                printf("\nError opening Attendance.csv!\n");
                fclose(fp);
                return;
            }

            a.studentID = student.id;
            a.courseID = courseID;

            fprintf(out, "%d,%d,%s,%s\n",
                    a.studentID, a.courseID,
                    a.date, a.status);

            fclose(out);

            printf("%-13s %-12s %-15d %-18s %-12s %-12s\n",
                   a.date, get_day_name(a.date), a.studentID,
                   course.courseCode,
                   strcmp(a.status, "Present") == 0 ? "Yes" : "",
                   strcmp(a.status, "Absent") == 0 ? "Yes" : "");

            marked++;
        }
    }

    fclose(fp);

    printf("==============================================================================================\n");

    if(!candidateFound){
    printf("\nNo students found for this course's department and semester!\n");
    printf("Please check that the course department and semester exactly match the student records.\n");
    }
    else if(marked == 0)
    {
        printf("\nNo New Attendance Records Were Added!\n");
    }
    else
    {
        printf("\nAttendance Marked Successfully!\n");
    }
}


// SEARCH ATTENDANCE BY STUDENT ID

void search_attendance()
{
    struct Attendance a;
    struct Course course;

    int id, found = 0;
    char courseCode[20];

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Attendance Records Found!\n");
        return;
    }

    if(!read_int("Enter Student ID: ", &id))
    {
        fclose(fp);
        return;
    }

    printf("\n================ STUDENT ATTENDANCE RECORDS ================\n");
    printf("%-13s %-12s %-15s %-18s %-12s %-12s\n",
           "Date", "Day", "Student ID", "Course Code", "Present", "Absent");
    printf("------------------------------------------------------------------------------------------\n");

    while(read_attendance(fp, &a))
    {
        if(a.studentID == id)
        {
            strcpy(courseCode, "Unknown");

            if(get_course(a.courseID, &course))
            {
                strcpy(courseCode, course.courseCode);
            }

            printf("%-13s %-12s %-15d %-18s %-12s %-12s\n",
                   a.date, get_day_name(a.date), a.studentID, courseCode,
                   strcmp(a.status, "Present") == 0 ? "Yes" : "",
                   strcmp(a.status, "Absent") == 0 ? "Yes" : "");
            found = 1;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nAttendance Not Found!\n");
    }
}


// VIEW ATTENDANCE BY COURSE AND DATE

void view_course_attendance()
{
    struct Attendance a;
    struct Course course;

    int courseID, found = 0;
    char date[15], courseCode[20];

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Attendance Records Found!\n");
        return;
    }

    if(!read_int("Enter Course ID: ", &courseID))
    {
        fclose(fp);
        return;
    }

    printf("Enter Date (YYYY-MM-DD): ");

    if(scanf("%14s", date) != 1)
    {
        clear_input();
        fclose(fp);
        return;
    }

    if(!valid_date(date))
    {
        printf("\nInvalid Date!\n");
        fclose(fp);
        return;
    }

    strcpy(courseCode, "Unknown");
    if(get_course(courseID, &course))
    {
        strcpy(courseCode, course.courseCode);
    }

    printf("\n================ COURSE ATTENDANCE RECORDS ================\n");
    printf("%-13s %-12s %-15s %-18s %-12s %-12s\n",
           "Date", "Day", "Student ID", "Course Code", "Present", "Absent");
    printf("------------------------------------------------------------------------------------------\n");

    while(read_attendance(fp, &a))
    {
        if(a.courseID == courseID && strcmp(a.date, date) == 0)
        {
            printf("%-13s %-12s %-15d %-18s %-12s %-12s\n",
                   a.date, get_day_name(a.date), a.studentID, courseCode,
                   strcmp(a.status, "Present") == 0 ? "Yes" : "",
                   strcmp(a.status, "Absent") == 0 ? "Yes" : "");
            found = 1;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nNo Attendance Found for This Course and Date!\n");
    }
}

// DISPLAY ALL ATTENDANCE RECORDS

void display_all_attendance()
{
    struct Attendance records[1000];
    struct Attendance temp;
    struct Course course;
    struct Student student;

    int semesters[1000];
    int count = 0;
    int filteredCount = 0;
    int selectedSemester;

    char department[30];

    FILE *fp = fopen("Attendance.csv", "r");

    if(fp == NULL)
    {
        printf("\nAttendance.csv file not found!\n");
        return;
    }

    // READ ALL ATTENDANCE RECORDS

    while(count < 1000 && read_attendance(fp, &records[count]))
    {
        count++;
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nNo Attendance Records Available!\n");
        return;
    }

    // SELECT DEPARTMENT

    printf("\nEnter Department: ");

    if(scanf(" %29[^\n]", department) != 1)
    {
        clear_input();
        return;
    }

    // SELECT SEMESTER

    if(!read_int("Enter Semester (1-8): ", &selectedSemester))
    {
        return;
    }

    if(selectedSemester < 1 || selectedSemester > 8)
    {
        printf("\nInvalid Semester!\n");
        return;
    }

    // FILTER RECORDS BY DEPARTMENT AND SEMESTER

    for(int i = 0; i < count; i++)
    {
        if(get_student(records[i].studentID, &student))
        {
            if(strcmp(student.department, department) == 0 &&
               student.semester == selectedSemester)
            {
                records[filteredCount] = records[i];
                semesters[filteredCount] = student.semester;

                filteredCount++;
            }
        }
    }

    count = filteredCount;

    if(count == 0)
    {
        printf("\nNo attendance records found for this department and semester!\n");
        return;
    }

    // SORT BY DATE, SEMESTER, COURSE ID AND STUDENT ID

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(records[j].date, records[j + 1].date) > 0 ||
               (strcmp(records[j].date, records[j + 1].date) == 0 &&
                semesters[j] > semesters[j + 1]) ||
               (strcmp(records[j].date, records[j + 1].date) == 0 &&
                semesters[j] == semesters[j + 1] &&
                records[j].courseID > records[j + 1].courseID) ||
               (strcmp(records[j].date, records[j + 1].date) == 0 &&
                semesters[j] == semesters[j + 1] &&
                records[j].courseID == records[j + 1].courseID &&
                records[j].studentID > records[j + 1].studentID))
            {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;

                int tempSemester = semesters[j];
                semesters[j] = semesters[j + 1];
                semesters[j + 1] = tempSemester;
            }
        }
    }

    // DISPLAY ATTENDANCE TABLE

    printf("\n========================== ALL ATTENDANCE RECORDS ==========================\n");

    printf("Department: %s\n", department);
    printf("Semester: %d\n\n", selectedSemester);

    printf("%-13s %-12s %-10s %-15s %-18s %-12s %-12s\n",
           "Date", "Day", "Semester", "Student ID",
           "Course Code", "Present", "Absent");

    printf("-----------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        // DISPLAY DATE AND DAY ONLY ONCE

        if(i == 0 || strcmp(records[i].date, records[i - 1].date) != 0)
        {
            if(i != 0)
            {
                printf("-----------------------------------------------------------------------------------------------\n");
            }

            printf("%-13s %-12s ",
                   records[i].date, get_day_name(records[i].date));
        }
        else
        {
            printf("%-13s %-12s ", "", "");
        }

        // DISPLAY SEMESTER ONLY ONCE

        if(i == 0 ||
           strcmp(records[i].date, records[i - 1].date) != 0 ||
           semesters[i] != semesters[i - 1])
        {
            printf("%-10d ", semesters[i]);
        }
        else
        {
            printf("%-10s ", "");
        }

        // DISPLAY COURSE CODE ONLY ONCE

        if(i == 0 ||
           strcmp(records[i].date, records[i - 1].date) != 0 ||
           semesters[i] != semesters[i - 1] ||
           records[i].courseID != records[i - 1].courseID)
        {
            if(get_course(records[i].courseID, &course))
            {
                printf("%-15d %-18s ",
                       records[i].studentID, course.courseCode);
            }
            else
            {
                printf("%-15d %-18s ",
                       records[i].studentID, "Unknown");
            }
        }
        else
        {
            printf("%-15d %-18s ",
                   records[i].studentID, "");
        }

        // DISPLAY PRESENT OR ABSENT

        printf("%-12s %-12s\n",
               strcmp(records[i].status, "Present") == 0 ? "Yes" : "",
               strcmp(records[i].status, "Absent") == 0 ? "Yes" : "");

        // DOTTED LINE BETWEEN COURSES

        if(i < count - 1 &&
           strcmp(records[i].date, records[i + 1].date) == 0 &&
           semesters[i] == semesters[i + 1] &&
           records[i].courseID != records[i + 1].courseID)
        {
            printf("%-37s .........................................................\n", "");
        }
    }

    printf("------------------------------------------------------------------------------------------------\n");
}

// UPDATE ATTENDANCE

void update_attendance()
{
    struct Attendance a;

    int id, courseID, choice, found = 0;

    char date[15];

    FILE *fp = fopen("Attendance.csv", "r");
    FILE *temp = fopen("TemporaryAttendance.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Attendance Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("TemporaryAttendance.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Student ID: ", &id) ||
       !read_int("Enter Course ID: ", &courseID))
    {
        fclose(fp);
        fclose(temp);
        remove("TemporaryAttendance.csv");
        return;
    }

    printf("Enter Date (YYYY-MM-DD): ");

    if(scanf("%14s", date) != 1 || !valid_date(date))
    {
        printf("\nInvalid Date!\n");
        clear_input();

        fclose(fp);
        fclose(temp);

        remove("TemporaryAttendance.csv");

        return;
    }

    while(read_attendance(fp, &a))
    {
        if(a.studentID == id &&
           a.courseID == courseID &&
           strcmp(a.date, date) == 0)
        {
            found = 1;

            printf("\nCurrent Status: %s\n", a.status);

            printf("1. Present\n");
            printf("2. Absent\n");

            if(!read_int("Enter New Status: ", &choice) ||
               (choice != 1 && choice != 2))
            {
                printf("\nInvalid Status! Update Cancelled.\n");

                fclose(fp);
                fclose(temp);

                remove("TemporaryAttendance.csv");

                return;
            }

            if(choice == 1)
            {
                strcpy(a.status, "Present");
            }
            else
            {
                strcpy(a.status, "Absent");
            }
        }

        fprintf(temp, "%d,%d,%s,%s\n",
                a.studentID, a.courseID,
                a.date, a.status);
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nAttendance Record Not Found!\n");
        remove("TemporaryAttendance.csv");
        return;
    }

    if(replace_file("Attendance.csv", "TemporaryAttendance.csv"))
    {
        printf("\nAttendance Updated Successfully!\n");
    }
}


// DELETE ATTENDANCE RECORD

void delete_attendance()
{
    struct Attendance a;

    int id, courseID, found = 0;

    char date[15];

    FILE *fp = fopen("Attendance.csv", "r");
    FILE *temp = fopen("TemporaryAttendance.csv", "w");

    if(fp == NULL)
    {
        printf("\nNo Attendance Records Found!\n");

        if(temp != NULL)
        {
            fclose(temp);
            remove("TemporaryAttendance.csv");
        }

        return;
    }

    if(temp == NULL)
    {
        printf("\nError opening temporary file!\n");
        fclose(fp);
        return;
    }

    if(!read_int("Enter Student ID: ", &id) ||
       !read_int("Enter Course ID: ", &courseID))
    {
        fclose(fp);
        fclose(temp);
        remove("TemporaryAttendance.csv");
        return;
    }

    printf("Enter Date (YYYY-MM-DD): ");

    if(scanf("%14s", date) != 1 || !valid_date(date))
    {
        printf("\nInvalid Date!\n");
        clear_input();

        fclose(fp);
        fclose(temp);

        remove("TemporaryAttendance.csv");

        return;
    }

    while(read_attendance(fp, &a))
    {
        if(a.studentID == id &&
           a.courseID == courseID &&
           strcmp(a.date, date) == 0)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d,%d,%s,%s\n",
                    a.studentID, a.courseID,
                    a.date, a.status);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!found)
    {
        printf("\nAttendance Record Not Found!\n");
        remove("TemporaryAttendance.csv");
        return;
    }

    if(replace_file("Attendance.csv", "TemporaryAttendance.csv"))
    {
        printf("\nAttendance Deleted Successfully!\n");
    }
}


// =====================================================
// STUDENT ATTENDANCE VIEW
// =====================================================


// VIEW SUBJECT-WISE AND OVERALL ATTENDANCE PERCENTAGE

void view_attendance_percentage()
{
    struct Student student;
    struct Course course;
    struct Attendance a;

    int found = 0;
    int subjectCount = 0;

    int present, held;

    int totalPresent = 0;
    int totalHeld = 0;

    double percentage;
    double overallPercentage;

    FILE *fp;
    FILE *attendanceFile;

    // Find logged-in student's details

    fp = fopen("Students.csv", "r");

    if(fp == NULL)
    {
        printf("\nStudent Records Not Found!\n");
        return;
    }

    while(read_student(fp, &student))
    {
        if(student.id == loggedInStudentID)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nStudent Record Not Found!\n");
        return;
    }

    // Open courses file

    fp = fopen("Courses.csv", "r");

    if(fp == NULL)
    {
        printf("\nNo Courses Found!\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("              MY COURSE-WISE ATTENDANCE REPORT\n");
    printf("===============================================================\n");

    printf("\nStudent ID   : %d", student.id);
    printf("\nStudent Name : %s", student.name);
    printf("\nDepartment   : %s", student.department);
    printf("\nSemester     : %d\n", student.semester);

   printf("\n---------------------------------------------------------------------------------\n");

    printf("%-5s %-15s %-25s %-10s %-10s %-10s\n",
           "S.No", "Course Code", "Subject",
           "Present", "Held", "Percentage");

    printf("----------------------------------------------------------------------------------\n");
    // Read courses belonging to student's department and semester

    while(read_course(fp, &course))
    {
        if(strcmp(course.department, student.department) == 0 &&
           course.semester == student.semester)
        {
            present = 0;
            held = 0;

            attendanceFile = fopen("Attendance.csv", "r");

            if(attendanceFile != NULL)
            {
                while(read_attendance(attendanceFile, &a))
                {
                    if(a.studentID == loggedInStudentID &&
                       a.courseID == course.courseID)
                    {
                        held++;

                        if(strcmp(a.status, "Present") == 0)
                        {
                            present++;
                        }
                    }
                }

                fclose(attendanceFile);
            }

            if(held > 0)
            {
                percentage = (present * 100.0) / held;
            }
            else
            {
                percentage = 0;
            }

            subjectCount++;

            totalPresent += present;
            totalHeld += held;

            printf("%-5d %-15s %-25s %-10d %-10d ",
                   subjectCount,
                   course.courseCode,
                   course.courseTitle,
                   present,
                   held);

            if(present == held)
            {
            printf("%s%.2f%%%s\n", GREEN, percentage, RESET);
            }
            else if(percentage < REQUIRED_ATTENDANCE)
            {   
            printf("%s%.2f%% LOW%s\n", RED, percentage, RESET);
            }
            else
            {
            printf("%.2f%%\n", percentage);
            }
        }
    }

    fclose(fp);
   printf("----------------------------------------------------------------------------------\n");

    if(subjectCount == 0)
    {
        printf("\nNo Courses Found for Your Department and Semester!\n");
        return;
    }

    if(totalHeld > 0)
    {
        overallPercentage = (totalPresent * 100.0) / totalHeld;
    }
    else
    {
        overallPercentage = 0;
    }

    printf("\nTotal Present Classes : %d", totalPresent);
    printf("\nTotal Held Classes    : %d", totalHeld);

    printf("\n\n===============================================================\n");

    printf("                 OVERALL ATTENDANCE: ");

    if(totalHeld > 0 && totalPresent == totalHeld)
    {
    printf("%s%.2f%%%s\n", GREEN, overallPercentage, RESET);
    }
    else if(overallPercentage < REQUIRED_ATTENDANCE)
    {
    printf("%s%.2f%% LOW%s\n", RED, overallPercentage, RESET);
    }
    else
    {
    printf("%.2f%%\n", overallPercentage);
    }

    printf("===============================================================\n");

    printf("\nRequired Attendance: %.2f%%\n", REQUIRED_ATTENDANCE);
}
// =====================================================
// COMMON HELPER FUNCTIONS
// =====================================================

// Clear remaining characters from input

void clear_input()
{
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}


// Read an integer safely

int read_int(const char *prompt, int *value)
{
    printf("%s", prompt);

    if(scanf("%d", value) != 1)
    {
        printf("\nInvalid Input! Enter a number.\n");
        clear_input();
        return 0;
    }

    clear_input();

    return 1;
}


// Read one student record from file

int read_student(FILE *fp, struct Student *ptr)
{
    return fscanf(fp, "%d,%49[^,],%29[^,],%d,%14[^\n]",
                  &ptr->id, ptr->name, ptr->department,
                  &ptr->semester, ptr->gender) == 5;
}


// Read one course record from file


// Read one valid course record from file

int read_course(FILE *fp, struct Course *ptr)
{
    char line[200];

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line, "%d,%49[^,],%19[^,],%29[^,],%d",
                  &ptr->courseID, ptr->courseTitle,
                  ptr->courseCode, ptr->department,
                  &ptr->semester) == 5)
        {
            return 1;
        }
    }

    return 0;
}



// Read one attendance record from file

int read_attendance(FILE *fp, struct Attendance *ptr)
{
    return fscanf(fp, "%d,%d,%14[^,],%9[^\n]",
                  &ptr->studentID, &ptr->courseID,
                  ptr->date, ptr->status) == 4;
}


// Replace original file with temporary file

int replace_file(const char *original, const char *temporary)
{
    if(remove(original) != 0)
    {
        printf("\nError removing original file!\n");
        return 0;
    }

    if(rename(temporary, original) != 0)
    {
        printf("\nError renaming temporary file!\n");
        return 0;
    }

    return 1;
}
