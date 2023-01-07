//
// Created by Jakub Górski on 17/12/2022.
//

#ifndef CPU_SCHEDULING_PROCESS_GENERATOR_H
#define CPU_SCHEDULING_PROCESS_GENERATOR_H

#include "CPU_Process.h"
#include <vector>
#include <random>

class PROCESS_GENERATOR {
public:
    explicit PROCESS_GENERATOR(int n = 0, int bt_range = 0, int at_range = 0)
        : m_no_processes(n), m_bt_range(bt_range), m_at_range(at_range){};
    ~PROCESS_GENERATOR() = default;

    std::vector<CPU_Process> GEN_PROCESSES(){
        CPU_Process temp{};
        std::random_device randomDevice;
        std::mt19937 range_bt(randomDevice());
        std::mt19937 range_at(randomDevice());
        std::uniform_int_distribution<std::mt19937::result_type> distBT(1,m_bt_range);
        std::uniform_int_distribution<std::mt19937::result_type> distAT(1, m_at_range);

        for (int i = 0; i < m_no_processes; i++){
            temp.ID = i;
            if (i == 0){
                temp.arrival_time = 0;
            }
            else{
                temp.arrival_time = (processes.at(i-1).arrival_time + (int)distAT(range_at));
            }
            temp.burst_time = (int)distBT(range_bt);
            processes.push_back(temp);
            temp.CLR();
        }
        return processes;
    }

    friend std::ostream& operator<<(std::ostream& os, const PROCESS_GENERATOR& PG){
        for (CPU_Process p : PG.processes){
            os << p.ID << ";" << p.burst_time << ";" << p.arrival_time << "\n";
        }
        return os;
    }

private:
    int m_no_processes{}, m_bt_range{}, m_at_range{};
    std::vector<CPU_Process> processes;
};

#endif //CPU_SCHEDULING_PROCESS_GENERATOR_H
