//
// Created by Jakub Górski on 17/12/2022.
//

#include <fcfs.h>

void FCFS::calcWaitingTime(){
    service_time.push_back(m_processes[0].arrival_time);
    waiting_time.push_back(0);

    for (int i = 1; i < m_processes.size(); i++){
        service_time.push_back(service_time.at(i-1) + m_processes.at(i-1).burst_time);
        waiting_time.push_back(service_time.at(i) - m_processes.at(i).arrival_time);
        if (waiting_time.at(i) < 0) { waiting_time.at(i) = 0; }
    }
}

void FCFS::calcTurnaroundTime(){
    for (int i = 0; i < m_processes.size(); i++){
        turnaround_time.push_back(m_processes.at(i).burst_time + waiting_time.at(i));
    }
}

void FCFS::calcAvgTime(){
    calcWaitingTime();
    calcTurnaroundTime();
    for (int i = 0; i < m_processes.size(); i++){
        total_wt += waiting_time.at(i);
        total_tt += turnaround_time.at(i);
    }
}

std::ostream &operator<<(std::ostream &os, const FCFS &fcfs) {
    os << std::left;
    os << "Processes;Burst Time;Arrival Time;Waiting Time;Turn-Around Time;Completion Time" << std::endl;
    for (int i = 0; i < fcfs.m_processes.size(); i++) {
        int completion_time = fcfs.turnaround_time.at(i) + fcfs.m_processes.at(i).arrival_time;
        os << fcfs.m_processes.at(i).ID << ';'
            << fcfs.m_processes.at(i).burst_time << ';'
            << fcfs.m_processes.at(i).arrival_time<< ';'
            << fcfs.waiting_time.at(i)<< ';'
            << fcfs.turnaround_time.at(i) << ';'
            << completion_time << std::endl;
    }
    os << "Avg. waiting time: " << (float)fcfs.total_wt / (float)fcfs.m_processes.size() << fcfs.m_unit << "\n";
    os << "Avg. turn-around time: " << (float)fcfs.total_tt / (float)fcfs.m_processes.size() << fcfs.m_unit;
    return os;
}
