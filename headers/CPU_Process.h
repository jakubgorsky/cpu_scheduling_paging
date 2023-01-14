//
// Created by Jakub Górski on 17/12/2022.
//

#ifndef CPU_SCHEDULING_CPU_PROCESS_H
#define CPU_SCHEDULING_CPU_PROCESS_H

struct CPU_Process{
public:
    CPU_Process() = default;
    CPU_Process(long long int id, long long int burstTime, long long int arrivalTime, long long int startTime,
                long long int completionTime, long long int turnaroundTime, long long int waitingTime, bool completed)
            : ID(id), burst_time(burstTime), arrival_time(arrivalTime), start_time(startTime),
              completion_time(completionTime), turnaround_time(turnaroundTime), waiting_time(waitingTime),
              completed(completed) {}

    long long int ID{}, burst_time{}, arrival_time{}, start_time{}, completion_time{}, turnaround_time{}, waiting_time{};
    bool completed = false;
    void CLR(){
        ID = 0;
        burst_time = 0;
        arrival_time = 0;
        start_time = 0;
        completion_time = 0;
        turnaround_time = 0;
        waiting_time = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const CPU_Process& process){
        os << process.ID << " " << process.burst_time << " " << process.arrival_time << "\n";
        return os;
    }
};

#endif //CPU_SCHEDULING_CPU_PROCESS_H
