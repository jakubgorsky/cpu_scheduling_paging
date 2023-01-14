//
// Created by Jakub Górski on 08/01/2023.
//

#ifndef CPU_SCHEDULING_SJF_H
#define CPU_SCHEDULING_SJF_H

#include <vector>
#include <iostream>
#include "CPU_Process.h"

class SJF {
public:
    SJF(std::vector<CPU_Process> processes);
    ~SJF();

    void calculate();

    friend std::ostream& operator<<(std::ostream& os, const SJF& sjf);
private:
    long long int total_tt{}, total_wt{}, curr_time{};
    long double avg_wt{}, avg_tt{};
    bool calculated = false;

    long long int findShortestJob();
    void calcAvgTime();
    void calcTimes(long long int pid);
    bool allCompleted();
    std::vector<CPU_Process> m_processes;
};

#endif //CPU_SCHEDULING_SJF_H
