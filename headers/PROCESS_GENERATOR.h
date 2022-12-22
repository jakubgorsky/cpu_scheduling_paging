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
    PROCESS_GENERATOR() = default;
    ~PROCESS_GENERATOR() = default;

    std::vector<CPU_Process> GEN_PROCESSES(int n, int bt_range, int at_range){
        std::vector<CPU_Process> processes;
        CPU_Process temp{};
        std::random_device randomDevice;
        std::mt19937 range_bt(randomDevice());
        std::mt19937 range_at(randomDevice());
        std::uniform_int_distribution<std::mt19937::result_type> distBT(1,bt_range);
        std::uniform_int_distribution<std::mt19937::result_type> distAT(1, at_range);

        for (int i = 0; i < n; i++){
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

private:
};

#endif //CPU_SCHEDULING_PROCESS_GENERATOR_H
