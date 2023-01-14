//
// Created by Jakub Górski on 08/01/2023.
//
#include <algorithm>
#include "sjf.h"

SJF::SJF(std::vector<CPU_Process> processes)
    : m_processes(std::move(processes)){
}

SJF::~SJF() = default;

void SJF::calculate() {
    while(!calculated) {
        if (allCompleted()){
            calcAvgTime();
            calculated = true;
            return;
        }
        long long int pid = findShortestJob();
        if (pid == -1)
            curr_time++;
        else {
            calcTimes(pid);

            m_processes.at(pid).completed = true;
            curr_time = m_processes.at(pid).completion_time;
        }
    }
}

bool SJF::allCompleted(){
    return std::all_of(m_processes.begin(), m_processes.end(), [](CPU_Process p) { return p.completed; });
}

void SJF::calcAvgTime() {
    avg_wt = (double)total_wt / (double)m_processes.size();
    avg_tt = (double)total_tt / (double)m_processes.size();
}

void SJF::calcTimes(long long int pid) {
    m_processes.at(pid).start_time = curr_time;
    m_processes.at(pid).completion_time = m_processes.at(pid).start_time + m_processes.at(pid).burst_time;
    m_processes.at(pid).turnaround_time = m_processes.at(pid).completion_time - m_processes.at(pid).arrival_time;
    m_processes.at(pid).waiting_time = m_processes.at(pid).turnaround_time - m_processes.at(pid).burst_time;

    total_tt += m_processes.at(pid).turnaround_time;
    total_wt += m_processes.at(pid).waiting_time;
}

long long int SJF::findShortestJob(){
    long long int minimum_bt = 100000, pid = -1;

    for (CPU_Process p : m_processes){
        if (p.arrival_time > curr_time || p.completed){
            continue;
        }
        if (p.burst_time < minimum_bt){
            minimum_bt = p.burst_time;
            pid = p.ID;
        }
        if (p.burst_time == minimum_bt && p.arrival_time < m_processes.at(pid).arrival_time){
            minimum_bt = p.burst_time;
            pid = p.ID;
        }
    }
    return pid;
}

std::ostream &operator<<(std::ostream &os, const SJF &sjf) {
    if (!sjf.calculated){
        os << "There has been an error during calculations.";
        return os;
    }
    os << std::left;
    os << "Processes;Burst Time;Arrival Time;Waiting Time;Turn-Around Time;Completion Time" << std::endl;
    for (const auto & p : sjf.m_processes) {
        long long int completion_time = p.turnaround_time + p.arrival_time;
        os << p.ID << ';'
           << p.burst_time << ';'
           << p.arrival_time<< ';'
           << p.waiting_time << ';'
           << p.turnaround_time << ';'
           << completion_time << std::endl;
    }
    os << "Avg. waiting time;" << sjf.avg_wt << "\n";
    os << "Avg. turn-around time;" << sjf.avg_tt;
    return os;
}
