#include<bits/stdc++.h>
using namespace std;

class process {
    private:
        string name;
        int arv_time;
        int burst_time;
        int tat;
        int wt;
        int comp_time;
        int priority;

    public:
        process() {
            name = "";
            arv_time = 0;
            burst_time = 0;
            comp_time = 0;
            tat = 0;
            wt = 0;
            priority = 0;
        }

        void create() {
            cout << "Enter the name of process : ";
            cin >> name;
            cout << "Enter the arrival time of " << name << " : ";
            cin >> arv_time;
            cout << "Enter the burst time of process " << name << ": ";
            cin >> burst_time;
        }

        friend class Scheduler;
};

class Scheduler {
    private:
        vector<process> Processes;
        int n;

    public:
        Scheduler() {
            cout << "Enter the number of processes :";
            cin >> n;
            Processes.resize(n);
        }

        void insertDetails() {
            for (int i = 0; i < n; i++) {
                Processes[i].create();
            }
        }

        void display(vector<process> temp, int n, float avg_tat, float avg_wt) {
            cout << endl << "name\tat\tbt\tct\tTAT\tWT" << endl;
            for (int i = 0; i < n; i++) {
                cout << temp[i].name << "\t"
                     << temp[i].arv_time << "\t"
                     << temp[i].burst_time << "\t"
                     << temp[i].comp_time << "\t"
                     << temp[i].tat << "\t"
                     << temp[i].wt << "\n";
            }
            cout << "Average Turn Around Time  : " << avg_tat << endl;
            cout << "Average Waiting Time : " << avg_wt;
        }

        void FCFS() {
            vector<process> temp(Processes);
            sort(temp.begin(), temp.end(), [](const process& a, const process& b) {
                return a.arv_time < b.arv_time;
            });
            int ct = 0;
            for (int i = 0; i < n; i++) {
                if (ct < temp[i].arv_time) ct = temp[i].arv_time;
                ct += temp[i].burst_time;
                temp[i].comp_time = ct;
                temp[i].tat = temp[i].comp_time - temp[i].arv_time;
                temp[i].wt = temp[i].tat - temp[i].burst_time;
            }
            float avg_tat = 0, avg_wt = 0;
            for (int i = 0; i < n; i++) {
                avg_tat += temp[i].tat;
                avg_wt += temp[i].wt;
            }
            avg_tat /= n;
            avg_wt /= n;
            display(temp, n, avg_tat, avg_wt);
        }

        void SJF_preemptive() {
            vector<process> temp(Processes);
            vector<int> remaining(n);
            for (int i = 0; i < n; i++) remaining[i] = temp[i].burst_time;
            sort(temp.begin(), temp.end(), [](const process& a, const process& b) {
                return a.arv_time < b.arv_time;
            });
            vector<string> gantt;
            int time = 0, completed = 0;
            vector<bool> done(n, false);
            while (completed < n) {
                int idx = -1;
                int min_bt = INT_MAX;
                for (int i = 0; i < n; i++) {
                    if (temp[i].arv_time <= time && remaining[i] > 0 && remaining[i] < min_bt) {
                        min_bt = remaining[i];
                        idx = i;
                    }
                }
                if (idx != -1) {
                    if (gantt.empty() || gantt.back() != temp[idx].name) gantt.push_back(temp[idx].name);
                    remaining[idx]--;
                    if (remaining[idx] == 0) {
                        temp[idx].comp_time = time + 1;
                        temp[idx].tat = temp[idx].comp_time - temp[idx].arv_time;
                        temp[idx].wt = temp[idx].tat - temp[idx].burst_time;
                        completed++;
                    }
                    time++;
                } else {
                    time++;
                }
            }
            float avg_tat = 0, avg_wt = 0;
            for (int i = 0; i < n; i++) {
                avg_tat += temp[i].tat;
                avg_wt += temp[i].wt;
            }
            avg_tat /= n;
            avg_wt /= n;
            display(temp, n, avg_tat, avg_wt);
            cout << "\nGantt chart : \t";
            for (auto& p : gantt) cout << p << " ";
            cout << endl;
        }

        void roundRobin() {
            int tq;
            cout << "Enter the time Quantam : ";
            cin >> tq;
            vector<process> temp(Processes);
            vector<int> remaining(n);
            for (int i = 0; i < n; i++) remaining[i] = temp[i].burst_time;
            sort(temp.begin(), temp.end(), [](const process& a, const process& b) {
                return a.arv_time < b.arv_time;
            });
            queue<int> q;
            vector<bool> inQueue(n, false);
            vector<string> gantt;
            int time = 0, completed = 0;
            while (completed < n) {
                for (int i = 0; i < n; i++) {
                    if (temp[i].arv_time <= time && !inQueue[i] && remaining[i] > 0) {
                        q.push(i);
                        inQueue[i] = true;
                    }
                }
                if (!q.empty()) {
                    int idx = q.front(); q.pop();
                    if (gantt.empty() || gantt.back() != temp[idx].name) gantt.push_back(temp[idx].name);
                    int execTime = min(tq, remaining[idx]);
                    remaining[idx] -= execTime;
                    time += execTime;
                    for (int i = 0; i < n; i++) {
                        if (temp[i].arv_time <= time && !inQueue[i] && remaining[i] > 0) {
                            q.push(i);
                            inQueue[i] = true;
                        }
                    }
                    if (remaining[idx] > 0) {
                        q.push(idx);
                    } else {
                        temp[idx].comp_time = time;
                        temp[idx].tat = temp[idx].comp_time - temp[idx].arv_time;
                        temp[idx].wt = temp[idx].tat - temp[idx].burst_time;
                        completed++;
                    }
                } else {
                    time++;
                }
            }
            float avg_tat = 0, avg_wt = 0;
            for (int i = 0; i < n; i++) {
                avg_tat += temp[i].tat;
                avg_wt += temp[i].wt;
            }
            avg_tat /= n;
            avg_wt /= n;
            display(temp, n, avg_tat, avg_wt);
            cout << "\nGantt chart : \t";
            for (auto& p : gantt) cout << p << " ";
            cout << endl;
        }

        void priority_non_preemptive() {
            vector<process> temp(Processes);
            for (int i = 0; i < n; i++) {
                cout << "Enter the priority for " << temp[i].name << " : ";
                cin >> temp[i].priority;
            }
            sort(temp.begin(), temp.end(), [](const process& a, const process& b) {
                return a.arv_time < b.arv_time;
            });
            vector<string> gantt;
            vector<bool> done(n, false);
            int time = 0, completed = 0;
            while (completed < n) {
                int idx = -1;
                int highest = INT_MIN;
                for (int i = 0; i < n; i++) {
                    if (!done[i] && temp[i].arv_time <= time && temp[i].priority > highest) {
                        highest = temp[i].priority;
                        idx = i;
                    }
                }
                if (idx != -1) {
                    if (gantt.empty() || gantt.back() != temp[idx].name) gantt.push_back(temp[idx].name);
                    if (time < temp[idx].arv_time) time = temp[idx].arv_time;
                    time += temp[idx].burst_time;
                    temp[idx].comp_time = time;
                    temp[idx].tat = temp[idx].comp_time - temp[idx].arv_time;
                    temp[idx].wt = temp[idx].tat - temp[idx].burst_time;
                    done[idx] = true;
                    completed++;
                } else {
                    time++;
                }
            }
            float avg_tat = 0, avg_wt = 0;
            for (int i = 0; i < n; i++) {
                avg_tat += temp[i].tat;
                avg_wt += temp[i].wt;
            }
            avg_tat /= n;
            avg_wt /= n;
            display(temp, n, avg_tat, avg_wt);
            cout << "\nGantt chart : \t";
            for (auto& p : gantt) cout << p << " ";
            cout << endl;
        }
};

int main() {
    Scheduler scheduler;
    scheduler.insertDetails();
    cout << "\n1. FCFS\n";
    scheduler.FCFS();
    cout << "\n2. SJF Preemptive\n";
    scheduler.SJF_preemptive();
    cout << "\n3. Round Robin\n";
    scheduler.roundRobin();
    cout << "\n4. Priority Non Preemptive\n";
    scheduler.priority_non_preemptive();
    return 0;
}
