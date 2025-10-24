#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 10;
const int MAX_SUBJECTS = 5;

struct Subject {
    string subject_name;
    int credit;
    int mark;
    char grade;
};

struct Student {
    string name;
    int age;
    Subject subjects[MAX_SUBJECTS];
    int num_subjects;
    float gpa;
};

char calculateGrade(int mark) {
    if (mark >= 75) return 'A';
    else if (mark >= 60) return 'B';
    else if (mark >= 45) return 'C';
    else if (mark >= 30) return 'D';
    else return 'E';
}

void inputSubject(Subject &sub) {
    cout << "Enter subject name: ";
    getline(cin, sub.subject_name);

    cout << "Enter subject credit: ";
    cin >> sub.credit;

    do {
        cout << "Enter subject mark (0-100): ";
        cin >> sub.mark;
        if (sub.mark < 0 || sub.mark > 100) {
            cout << "Invalid mark! Please enter a value between 0 and 100." << endl;
        }
    } while (sub.mark < 0 || sub.mark > 100);

    sub.grade = calculateGrade(sub.mark);
    cin.ignore(); 
}

void inputStudent(Student &stud) {
    cout << "\nEnter student name: ";
    getline(cin, stud.name);

    cout << "Enter student age: ";
    cin >> stud.age;

    cout << "Enter number of subjects taken (max " << MAX_SUBJECTS << "): ";
    cin >> stud.num_subjects;
    if (stud.num_subjects > MAX_SUBJECTS) stud.num_subjects = MAX_SUBJECTS;

    cin.ignore(); 
    for (int i = 0; i < stud.num_subjects; i++) {
        cout << "\nSubject " << i + 1 << ":\n";
        inputSubject(stud.subjects[i]);
    }
}

float calculateGPA(const Student &stud) {
    float totalPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < stud.num_subjects; i++) {
        float point = 0;
        switch (stud.subjects[i].grade) {
            case 'A': point = 4.0; break;
            case 'B': point = 3.0; break;
            case 'C': point = 2.0; break;
            case 'D': point = 1.0; break;
            case 'E': point = 0.0; break;
        }
        totalPoints += point * stud.subjects[i].credit;
        totalCredits += stud.subjects[i].credit;
    }

    if (totalCredits == 0) return 0;
    return totalPoints / totalCredits;
}

void displayStudent(const Student &stud) {
    cout << "\n---------------------------------------";
    cout << "\nName: " << stud.name << "\nAge: " << stud.age << endl;
    cout << "Subjects:\n";
    for (int i = 0; i < stud.num_subjects; i++) {
        cout << "  " << i + 1 << ". " << stud.subjects[i].subject_name
             << " | Credit: " << stud.subjects[i].credit
             << " | Mark: " << stud.subjects[i].mark
             << " | Grade: " << stud.subjects[i].grade << endl;
    }
    cout << fixed << setprecision(2);
    cout << "GPA: " << stud.gpa << endl;
}

int main() {
    Student students[MAX_STUDENTS];
    int num_students;

    cout << "Enter number of students (max " << MAX_STUDENTS << "): ";
    cin >> num_students;
    if (num_students > MAX_STUDENTS) num_students = MAX_STUDENTS;
    cin.ignore();

    for (int i = 0; i < num_students; i++) {
        cout << "\n--- Student " << i + 1 << " ---\n";
        inputStudent(students[i]);
        students[i].gpa = calculateGPA(students[i]);
    }

    cout << "\n========== STUDENTS INFORMATION ==========\n";
    for (int i = 0; i < num_students; i++) {
        displayStudent(students[i]);
    }

    return 0;
}
