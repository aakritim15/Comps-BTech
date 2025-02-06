#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completion;
    int start;
};

bool compareArrival(const Process& p1, const Process& p2) {
    return p1.arrival < p2.arrival;
}

void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        
        processes[i].start = currentTime;
        processes[i].completion = currentTime + processes[i].burst;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        currentTime = processes[i].completion;
    }
}

void findAvgTime(vector<Process>& processes) {
    int n = processes.size();

    calculateTimes(processes);

    int total_wt = 0, total_tat = 0;

    cout << setw(10) << "Process ID" << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time" << setw(15) << "Waiting Time"
         << setw(20) << "Turnaround Time" << setw(15) << "Completion Time" << endl;

    for (const auto& process : processes) {
        total_wt += process.waiting;
        total_tat += process.turnaround;
        cout << setw(10) << process.id << setw(15) << process.arrival
             << setw(15) << process.burst << setw(15) << process.waiting
             << setw(20) << process.turnaround << setw(15) << process.completion << endl;
    }

    double avg_wt = static_cast<double>(total_wt) / n;
    double avg_tat = static_cast<double>(total_tat) / n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_wt << endl;
    cout << "Average Turnaround Time: " << avg_tat << endl;
}

void printGanttChart(const vector<Process>& processes) {
    int n = processes.size();

    int maxBurstTime = 0;
    int maxCompletionTime = 0;
    for (const auto& process : processes) {
        if (process.burst > maxBurstTime) {
            maxBurstTime = process.burst;
        }
        if (process.completion > maxCompletionTime) {
            maxCompletionTime = process.completion;
        }
    }

    int width = maxBurstTime + 3;

    cout << "\nGantt Chart:" << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(width) << setfill('-') << " ";
    }
    cout << setfill(' ') << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(width) << processes[i].start << " ";
    }
    cout << setw(width) << processes.back().completion << endl;

    cout << "|";
    for (const auto& process : processes) {
        cout << setw(width) << process.id << " |";
    }
    cout << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(width) << setfill('-') << " ";
    }
    cout << setfill(' ') << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(width) << processes[i].completion << " ";
    }
    cout << endl;
}

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    findAvgTime(processes);

    printGanttChart(processes);

    return 0;
}
