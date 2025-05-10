#include <iostream>
#include <string>
using namespace std;

struct Employee {
    string name;
    int id;
    float punctuality;
    float taskCompletion;
    float teamwork;
    float initiative;
    float communication;
    float creativity;
    float finalScore;
    string grade;
};


float calculateScore(float p, float t, float tw, float i, float c, float cr) {
    return (p * 0.15) + (t * 0.30) + (tw * 0.15) + (i * 0.15) + (c * 0.15) + (cr * 0.10);
}


string classify(float score) {
    if (score >= 90) 
        return "Outstanding";
    else if (score >= 80) 
        return "Excellent";
    else if (score >= 70) 
        return "Very Good";
    else if (score >= 60) 
        return "Good";
    else if (score >= 50) 
        return "Average";
    else 
        return "Needs Improvement";
}

int main() {
    int n;
    Employee e[100];

    cout << "=== Employee Performance Expert System ===\n";
    cout << "Enter number of employees to evaluate: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Employee " << i + 1 << ":\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, e[i].name);
        // cin>>e[i].name;

        cout << "ID: ";
        cin >> e[i].id;

        cout << "Punctuality (out of 100): ";
        cin >> e[i].punctuality;
        cout << "Task Completion: ";
        cin >> e[i].taskCompletion;
        cout << "Teamwork: ";
        cin >> e[i].teamwork;
        cout << "Initiative: ";
        cin >> e[i].initiative;
        cout << "Communication: ";
        cin >> e[i].communication;
        cout << "Creativity: ";
        cin >> e[i].creativity;

        e[i].finalScore = calculateScore(e[i].punctuality, e[i].taskCompletion, e[i].teamwork,
                                         e[i].initiative, e[i].communication, e[i].creativity);
        e[i].grade = classify(e[i].finalScore);
    }

    cout << "\n=== Summary Report ===\n";
    for (int i = 0; i < n; i++) {
        cout << "\n--- Employee " << i + 1 << " ---\n";
        cout << "Name: " << e[i].name << "\n";
        cout << "ID: " << e[i].id << "\n";
        cout << "Final Score: " << e[i].finalScore << "\n";
        cout << "Grade: " << e[i].grade << "\n";
    }

    return 0;
}
