//
// Created by Jakub Górski on 17/12/2022.
//

#ifndef CPU_SCHEDULING_FCFS_H
#define CPU_SCHEDULING_FCFS_H
#include <utility>
#include <vector>
#include <iostream>
#include "CPU_Process.h"

class FCFS {
public:
    FCFS(std::vector<CPU_Process> processes)
        : m_processes(std::move(processes)){
    };
    ~FCFS() = default;
    void calculate();
    friend std::ostream& operator<<(std::ostream& os, const FCFS& fcfs);

private:
    int total_tt{}, total_wt{};
    bool calculated = false;
    void calcAvgTime();
    void calcWaitingTime();
    void calcTurnaroundTime();
    std::vector<CPU_Process> m_processes;
    std::vector<int> service_time, waiting_time, turnaround_time;
};




#endif //CPU_SCHEDULING_FCFS_H