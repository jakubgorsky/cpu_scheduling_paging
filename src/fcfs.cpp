//
// Created by Jakub Górski on 17/12/2022.
//

#include <fcfs.h>
#include <fstream>

void FCFS::calcWaitingTime(){
    service_time.push_back(m_processes[0].arrival_time);
    m_processes.at(0).waiting_time = 0;

    for (int i = 1; i < m_processes.size(); i++){
        service_time.push_back(service_time.at(i-1) + m_processes.at(i-1).burst_time);
        m_processes.at(i).waiting_time = service_time.at(i) - m_processes.at(i).arrival_time;
        if (m_processes.at(i).waiting_time < 0)
        {
            m_processes.at(i).waiting_time = 0;
        }
    }
}

void FCFS::calcTurnaroundTime(){
    for (auto & p : m_processes){
        p.turnaround_time = p.burst_time + p.waiting_time;
    }
}

void FCFS::calcAvgTime(){
    long long int total_tt{}, total_wt{};
    calcWaitingTime();
    calcTurnaroundTime();
    for (auto & p : m_processes){
        total_wt += p.waiting_time;
        total_tt += p.turnaround_time;
    }
    avg_tt = (double)total_tt / (double)m_processes.size();
    avg_wt = (double)total_wt / (double)m_processes.size();
}

std::ostream &operator<<(std::ostream &os, const FCFS &fcfs) {
    if (!fcfs.calculated){
        os << "There has been an error during calculations.";
        return os;
    }
    os << std::left;
    os << "Processes;Burst Time;Arrival Time;Waiting Time;Turn-Around Time;Completion Time" << std::endl;
    for (const auto & p : fcfs.m_processes) {
        int completion_time = p.turnaround_time + p.arrival_time;
        os << p.ID << ';'
            << p.burst_time << ';'
            << p.arrival_time<< ';'
            << p.waiting_time << ';'
            << p.turnaround_time << ';'
            << completion_time << std::endl;
    }
    os << "Avg. waiting time;" << fcfs.avg_wt << "\n";
    os << "Avg. turn-around time;" << fcfs.avg_tt;
    return os;
}

void FCFS::calculate() {
    calcAvgTime();
    calculated = true;
}