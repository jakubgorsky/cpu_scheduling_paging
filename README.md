# CPU Scheduling and Paging algorithms simulation

As a part of Operating Systems course we were taksed to implement, simulate and compare different CPU Scheduling (in this case FCFS and SJF) and Page Swapping algorithms (the latter are not yet implemented)

# Usage

## Process Generator

Prequisites: 

CPU_Process Struct (included in this repo)

Syntax:

```cpp
PROCESS_GENERATOR PG(int no_processes, int burst_time_rand_range, int arrival_time_rand_range);
PROCESS_GENERATOR PG(10000, 50, 50);

std::vector<CPU_Process> processes = PG.GEN_PROCESSES();

// or you can read the processes from a file

std::vector<CPU_Process> processes = PG.READ_PROCESSES(std::string filepath);
```

Process Generator also has an overloaded standard output operator, therefore you can debug / write the processes to a file.

Example Processes file:
```
0;10;0
1;2;5
3;16;22
...
9998;27;25765
9999;12;25784
```

## FCFS / SJF

Prequisites:

Same as for Process Generator

Syntax:

```cpp
FCFS fcfs(std::vector<CPU_processes> processes);

FCFS first_come_first_serve(processes);
first_come_first_serve.calculate();

SJF sjf(std::vector<CPU_processes> processes);
SJF sjf(processes);
sjf.calculate();
```

Both algorithms have an overloaded standard output operator, therefore you can easily serialize them into an SCSV file:

```cpp
SJF_SCSV.open("sjf.scsv", std::ios_base::app);
SJF_SCSV << sjf;
SJF_SCSV.close();
```

Example lines from the output file:

```
Processes;Burst Time;Arrival Time;Waiting Time;Turn-Around Time;Completion Time
0;28;0;0;28;28
1;29;5;23;52;57
2;40;45;43;83;128
3;31;49;8;39;88
...
9999;48;257505;17;65;257570
Avg. waiting time;193.997
Avg. turn-around time;219.398
```
