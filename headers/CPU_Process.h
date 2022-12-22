//
// Created by Jakub Górski on 17/12/2022.
//

#ifndef CPU_SCHEDULING_CPU_PROCESS_H
#define CPU_SCHEDULING_CPU_PROCESS_H

struct CPU_Process{
public:
    int ID{}, burst_time{}, arrival_time{};
    void CLR(){
        ID = 0;
        burst_time = 0;
        arrival_time = 0;
    }
};

#endif //CPU_SCHEDULING_CPU_PROCESS_H
