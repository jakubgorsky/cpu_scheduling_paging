//
// Created by Jakub Górski on 17/12/2022.
//

#ifndef CPU_SCHEDULING_FCFS_H
#define CPU_SCHEDULING_FCFS_H
#include <utility>
#include <vector>
#include <string>
#include "CPU_Process.h"

class FCFS {
public:
    FCFS(std::vector<CPU_Process> processes, char unit='m')
        : m_processes(std::move(processes)){
        switch(unit){
            case 'm':
                m_unit = "ms";
                break;
            case 'n':
                m_unit = "ns";
                break;
            case 'u':
                m_unit = "μs";
                break;
            case 's':
                m_unit = "s";
                break;
            default:
                m_unit = "ms";
                break;
        }
        calcAvgTime();
    };
    void calcAvgTime();

    void insertProcesses(std::string filename);

    ~FCFS() = default;

    friend std::ostream& operator<<(std::ostream& os, const FCFS& fcfs);

private:
    std::string m_unit;
    int total_tt{}, total_wt{};
    void calcWaitingTime();
    void calcTurnaroundTime();
    std::vector<CPU_Process> m_processes;
    std::vector<int> service_time, waiting_time, turnaround_time;
};




#endif //CPU_SCHEDULING_FCFS_H