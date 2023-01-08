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

    friend std::ostream& operator<<(std::ostream& os, const CPU_Process& process){
        os << process.ID << " " << process.burst_time << " " << process.arrival_time << "\n";
        return os;
    }
};

#endif //CPU_SCHEDULING_CPU_PROCESS_H
