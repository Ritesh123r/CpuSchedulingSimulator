# CpuSchedulingSimulator
A C++ project simulating CPU scheduling algorithms


# CPU Scheduling Simulator (C++)

This project simulates various CPU scheduling algorithms in C++. The user can input process information and choose among:

- FCFS (First Come First Serve)
- SJF (Non-Preemptive)
- SJF (Preemptive)
- SRTF (Shortest Remaining Time First)
- Priority Scheduling (Non-Preemptive)
- Priority Scheduling (Preemptive)
- Round Robin Scheduling

- ### Data Structures:
- `vector<Process>` – to store process list
- `priority_queue` – used in SJF, SRTF, and Priority scheduling for efficient selection
- `queue<int>` – used in Round Robin to simulate circular queue
- `pair`, `tuple` – for maintaining Gantt chart and priority-based queues
- ### Algorithm:
Sorting Algorithm

std::sort()
➤ Used to sort processes based on arrival time before scheduling.

Min Heap (Priority Queue)

std::priority_queue with greater<>
➤ Used to select process with:

Minimum burst time (in SJF/SRTF)

Highest priority (in Priority Scheduling)

Queue (FIFO)

std::queue<int>
➤ Used for Round Robin to manage process order in cyclic manner.

Greedy Logic
➤ Used in all scheduling techniques to always pick the best possible process based on current time and condition (shortest/priority/first-arrived).

Condition Checks and Simulation Loops
➤ Custom time simulation using while loops and conditions based on process readiness.


## How to Run

1. Compile:
```bash
g++ main.cpp -o scheduler
