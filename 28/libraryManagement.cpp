#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    string subject;
    string projectType;
    string recommendedBook;
};

string toLower(string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}

string recommendBook(string subject, string projectType) {
    subject = toLower(subject);
    projectType = toLower(projectType);

    if (subject == "computer" && projectType == "ai")
        return "Artificial Intelligence: A Modern Approach - Stuart Russell";
    else if (subject == "computer" && projectType == "web")
        return "Web Technologies - Uttam K. Roy";
    else if (subject == "computer" && projectType == "ml")
        return "Hands-On Machine Learning - Aurélien Géron";
    else if (subject == "electronics" && projectType == "iot")
        return "Internet of Things - Arshdeep Bahga";
    else if (subject == "electronics" && projectType == "embedded")
        return "Embedded Systems - Raj Kamal";
    else if (subject == "mechanical" && projectType == "design")
        return "Machine Design - R.S. Khurmi";
    else if (subject == "mechanical" && projectType == "automobile")
        return "Automobile Engineering - Kirpal Singh";
    else if (subject == "civil" && projectType == "construction")
        return "Building Construction - Sushil Kumar";
    else if (subject == "civil" && projectType == "environment")
        return "Environmental Engineering - Peavy & Rowe";
    else if (subject == "electrical" && projectType == "automation")
        return "Industrial Automation and Robotics - Mikell Groover";
    else if (subject == "electrical" && projectType == "power")
        return "Power System Analysis - Hadi Saadat";
    else
        return "No recommendation found. Please consult the librarian.";
}

int main() {
    int n;
    Student students[100];

    cout << "=== Library Book Recommendation Expert System ===\n";
    cout << "Enter number of students: ";
    cin >> n;

    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\n--- Enter details for student " << i + 1 << " ---\n";

        cout << "Name: ";
        getline(cin, students[i].name);

        cout << "Subject (e.g., Computer, Electronics, Mechanical, Civil, Electrical): ";
        getline(cin, students[i].subject);

        cout << "Project Type (e.g., AI, Web, IoT, Design, Automation, etc.): ";
        getline(cin, students[i].projectType);

        students[i].recommendedBook = recommendBook(students[i].subject, students[i].projectType);
    }

    cout << "\n=== Recommendation Report ===\n";

    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: " << students[i].name << "\n";
        cout << "Subject: " << students[i].subject << "\n";
        cout << "Project Type: " << students[i].projectType << "\n";
        cout << "Recommended Book: " << students[i].recommendedBook << "\n";
    }

    return 0;
}
