#include <iostream>
#include <string>
using namespace std;

const int DAYS = 7;
const string dayNames[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

struct Member {
    string name;
    bool waterPumpWorking[DAYS];
    bool electricianVisited; 
    bool electricityBillPaid;
};

string answerWaterSupply(bool pumpWorking, const string& day) {
    return !pumpWorking ?
        "Water supply was not available on " + day + " due to water pump maintenance." :
        "No issue reported with the water supply on " + day + ".";
}

string answerLights(bool electricianVisited, bool billPaid, const string& day) {
    if (!billPaid)
        return "Lights were off on " + day + " due to unpaid electricity bill.";
    if (!electricianVisited)
        return "Lights were off on " + day + " as electrician did not visit.";
    return "No issue reported with the lights in the common passage on " + day + ".";
}

int main() {
    int n;
    cout << "=== Society Maintenance Expert System ===\n";
    cout << "Enter number of members to evaluate: ";
    cin >> n;

    Member members[n];
    char input;

    for (int i = 0; i < n; ++i) {
        cin.ignore();
        cout << "\nEnter name of member " << i + 1 << ": ";
        getline(cin, members[i].name);

        cout << "Is the electricity bill paid? (y/n): ";
        cin >> input;
        members[i].electricityBillPaid = (input == 'y' || input == 'Y');

        for (int d = 0; d < DAYS; ++d) {
            cout << "\n--- " << dayNames[d] << " ---\n";
            cout << "Was the water pump working? (y/n): ";
            cin >> input;
            members[i].waterPumpWorking[d] = (input == 'y' || input == 'Y');
        }

        cout << "\n--- Monday ---\n";
        cout << "Did the electrician visit this week? (y/n): ";
        cin >> input;
        members[i].electricianVisited = (input == 'y' || input == 'Y');
    }

    cout << "\n=== Weekly Maintenance Report ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "\n--- Report for " << members[i].name << " ---\n";
        for (int d = 0; d < DAYS; ++d) {
            cout << "\n[" << dayNames[d] << "]\n";
            cout << "Water Supply: " << answerWaterSupply(members[i].waterPumpWorking[d], dayNames[d]) << "\n";
            cout << "Lights: " << answerLights(members[i].electricianVisited, members[i].electricityBillPaid, dayNames[d]) << "\n";
        }
    }

    return 0;
}
