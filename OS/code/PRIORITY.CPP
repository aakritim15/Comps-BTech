#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // for std::setw

using namespace std;

struct Process {
    int id;              // Process ID
    int burstTime;       // Burst time
    int priority;        // Priority (smaller number = higher priority)
    int arrivalTime;     // Arrival time
    int waitingTime;     // Waiting time
    int turnaroundTime;  // Turnaround time
};

// Function to sort by priority and arrival time
bool compareByPriority(Process a, Process b) {
    if (a.priority == b.priority)
        return a.arrivalTime < b.arrivalTime; // If priorities are the same, sort by arrival time
    return a.priority < b.priority;            // Higher priority first
}

// Function to calculate waiting and turnaround times
void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        // Calculate waiting time for the current process
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        if (processes[i].waitingTime < 0)
            processes[i].waitingTime = 0;

        // Calculate turnaround time for the current process
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        // Update current time
        currentTime += processes[i].burstTime;
    }
}

// Function to print the Gantt chart
void printGanttChart(const vector<Process>& processes) {
    int n = processes.size();
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; ++i) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|\n";

    for (int i = 0; i < n; ++i) {
        cout << processes[i].waitingTime << "\t";
    }
    cout << processes[n - 1].turnaroundTime + processes[n - 1].arrivalTime << endl;
}

// Function to calculate and print average waiting and turnaround times
void calculateAverageTimes(const vector<Process>& processes) {
    int n = processes.size();
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (const auto& process : processes) {
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << static_cast<float>(totalWaitingTime) / n << " ms" << endl;
    cout << "Average Turnaround Time: " << static_cast<float>(totalTurnaroundTime) / n << " ms" << endl;
}

// Function to print the process details table
void printProcessTable(const vector<Process>& processes) {
    int n = processes.size();
    cout << "\nProcess Details:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "| " << setw(8) << "Process"
         << " | " << setw(12) << "Arrival Time"
         << " | " << setw(10) << "Burst Time"
         << " | " << setw(8) << "Priority"
         << " | " << setw(15) << "Waiting Time"
         << " | " << setw(18) << "Turnaround Time"
         << " |\n";
    cout << "-------------------------------------------------------------\n";

    for (const auto& process : processes) {
        cout << "| " << setw(8) << "P" + to_string(process.id)
             << " | " << setw(12) << process.arrivalTime
             << " | " << setw(10) << process.burstTime
             << " | " << setw(8) << process.priority
             << " | " << setw(15) << process.waitingTime
             << " | " << setw(18) << process.turnaroundTime
             << " |\n";
    }
    cout << "-------------------------------------------------------------\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        
        cout << "Enter arrival time for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process P" << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process P" << i + 1 << " (smaller number = higher priority): ";
        cin >> processes[i].priority;
    }

    // Sort processes based on priority and arrival time
    sort(processes.begin(), processes.end(), compareByPriority);

    // Calculate waiting and turnaround times
    calculateTimes(processes);

    // Print the Gantt chart
    printGanttChart(processes);

    // Print the process details table
    printProcessTable(processes);

    // Calculate and print average waiting and turnaround times
    calculateAverageTimes(processes);

    return 0;
}
