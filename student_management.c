#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_PHONE 15

// Structure to store student information
typedef struct {
    char id[10];
    char name[MAX_NAME];
    char class[10];
    int age;
    char gender[10];
    char phone[MAX_PHONE];
} Student;

// Global array to store students
Student students[MAX_STUDENTS];
int studentCount = 0;

// Function declarations
void displayMenu();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void displayStats();
void clearScreen();

int main() {
    int choice;
    
    loadFromFile(); // Load existing data on startup
    
    while(1) {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                displayStats();
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                saveToFile();
                printf("\n\nThank you for using Student Management System!\n");
                printf("Data saved successfully.\n\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}

void displayMenu() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║     STUDENT MANAGEMENT SYSTEM - MENU           ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  1. Add New Student\n");
    printf("  2. Display All Students\n");
    printf("  3. Search Student\n");
    printf("  4. Update Student Information\n");
    printf("  5. Delete Student\n");
    printf("  6. Display Statistics\n");
    printf("  7. Save Data to File\n");
    printf("  8. Exit\n");
    printf("\n");
    printf("════════════════════════════════════════════════\n");
    printf("Total Students: %d\n", studentCount);
    printf("════════════════════════════════════════════════\n");
}

void addStudent() {
    clearScreen();
    
    if (studentCount >= MAX_STUDENTS) {
        printf("\n❌ Database is full! Cannot add more students.\n");
        return;
    }
    
    Student newStudent;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           ADD NEW STUDENT                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    printf("Enter Student ID: ");
    scanf("%s", newStudent.id);
    getchar();
    
    // Check if ID already exists
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, newStudent.id) == 0) {
            printf("\n❌ Student ID already exists!\n");
            return;
        }
    }
    
    printf("Enter Full Name: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    printf("Enter Class (e.g., 10th): ");
    scanf("%s", newStudent.class);
    
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    getchar();
    
    printf("Enter Gender (Male/Female/Other): ");
    scanf("%s", newStudent.gender);
    getchar();
    
    printf("Enter Phone Number: ");
    scanf("%s", newStudent.phone);
    getchar();
    
    students[studentCount++] = newStudent;
    
    printf("\n✅ Student added successfully!\n");
    saveToFile();
}

void displayAllStudents() {
    clearScreen();
    
    if (studentCount == 0) {
        printf("\n❌ No students in the database.\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    ALL STUDENTS RECORD                                         ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("%-10s %-25s %-10s %-5s %-10s %-15s\n", 
           "ID", "Name", "Class", "Age", "Gender", "Phone");
    printf("────────────────────────────────────────────────────────────────────────────────────────────────\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-25s %-10s %-5d %-10s %-15s\n",
               students[i].id,
               students[i].name,
               students[i].class,
               students[i].age,
               students[i].gender,
               students[i].phone);
    }
    
    printf("\nTotal Students: %d\n", studentCount);
}

void searchStudent() {
    clearScreen();
    
    if (studentCount == 0) {
        printf("\n❌ No students in the database.\n");
        return;
    }
    
    char searchTerm[MAX_NAME];
    int found = 0;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           SEARCH STUDENT                       ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    printf("Enter Student ID or Name to search: ");
    fgets(searchTerm, MAX_NAME, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;
    
    printf("\n%-10s %-25s %-10s %-5s %-10s %-15s\n", 
           "ID", "Name", "Class", "Age", "Gender", "Phone");
    printf("────────────────────────────────────────────────────────────────────────────────────────────────\n");
    
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].id, searchTerm) != NULL || 
            strstr(students[i].name, searchTerm) != NULL) {
            printf("%-10s %-25s %-10s %-5d %-10s %-15s\n",
                   students[i].id,
                   students[i].name,
                   students[i].class,
                   students[i].age,
                   students[i].gender,
                   students[i].phone);
            found = 1;
        }
    }
    
    if (!found) {
        printf("\n❌ No student found with the given search term.\n");
    }
}

void updateStudent() {
    clearScreen();
    
    if (studentCount == 0) {
        printf("\n❌ No students in the database.\n");
        return;
    }
    
    char id[10];
    int found = -1;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║         UPDATE STUDENT INFORMATION             ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    printf("Enter Student ID to update: ");
    scanf("%s", id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("\n❌ Student not found!\n");
        return;
    }
    
    printf("\nCurrent Information:\n");
    printf("Name: %s\n", students[found].name);
    printf("Class: %s\n", students[found].class);
    printf("Age: %d\n", students[found].age);
    printf("Gender: %s\n", students[found].gender);
    printf("Phone: %s\n", students[found].phone);
    
    printf("\n\nEnter New Information:\n");
    
    printf("Enter Full Name: ");
    fgets(students[found].name, MAX_NAME, stdin);
    students[found].name[strcspn(students[found].name, "\n")] = 0;
    
    printf("Enter Class: ");
    scanf("%s", students[found].class);
    
    printf("Enter Age: ");
    scanf("%d", &students[found].age);
    getchar();
    
    printf("Enter Gender: ");
    scanf("%s", students[found].gender);
    getchar();
    
    printf("Enter Phone Number: ");
    scanf("%s", students[found].phone);
    getchar();
    
    printf("\n✅ Student information updated successfully!\n");
    saveToFile();
}

void deleteStudent() {
    clearScreen();
    
    if (studentCount == 0) {
        printf("\n❌ No students in the database.\n");
        return;
    }
    
    char id[10];
    int found = -1;
    char confirm;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           DELETE STUDENT                       ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    printf("Enter Student ID to delete: ");
    scanf("%s", id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("\n❌ Student not found!\n");
        return;
    }
    
    printf("\nStudent Information:\n");
    printf("ID: %s\n", students[found].id);
    printf("Name: %s\n", students[found].name);
    printf("Class: %s\n", students[found].class);
    
    printf("\nAre you sure you want to delete this student? (y/n): ");
    scanf("%c", &confirm);
    getchar();
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = found; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("\n✅ Student deleted successfully!\n");
        saveToFile();
    } else {
        printf("\n❌ Deletion cancelled.\n");
    }
}

void displayStats() {
    clearScreen();
    
    if (studentCount == 0) {
        printf("\n❌ No students in the database.\n");
        return;
    }
    
    int maleCount = 0, femaleCount = 0, otherCount = 0;
    int totalAge = 0;
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].gender, "Male") == 0) {
            maleCount++;
        } else if (strcmp(students[i].gender, "Female") == 0) {
            femaleCount++;
        } else {
            otherCount++;
        }
        totalAge += students[i].age;
    }
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           STUDENT STATISTICS                   ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    printf("📊 Total Students: %d\n\n", studentCount);
    printf("👨 Male Students: %d (%.1f%%)\n", maleCount, 
           (float)maleCount/studentCount*100);
    printf("👩 Female Students: %d (%.1f%%)\n", femaleCount, 
           (float)femaleCount/studentCount*100);
    printf("⚥  Other: %d (%.1f%%)\n\n", otherCount, 
           (float)otherCount/studentCount*100);
    printf("📈 Average Age: %.1f years\n", (float)totalAge/studentCount);
}

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    
    if (file == NULL) {
        printf("\n❌ Error saving data to file!\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    
    if (file == NULL) {
        return; // File doesn't exist yet
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}