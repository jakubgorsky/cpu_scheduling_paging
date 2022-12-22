#include "fcfs.h"
#include "PROCESS_GENERATOR.h"
#include <fstream>
#include <Windows.h>

#pragma execution_character_set("utf-8")

int main() {
    SetConsoleOutputCP(65001);
    PROCESS_GENERATOR PG;
    std::vector<CPU_Process> processes = PG.GEN_PROCESSES(100000, 100, 100);
    FCFS first_come_first_serve(processes, 'u');
    std::fstream FCFS_SCSV("fcfs.scsv", std::ios_base::app);
    FCFS_SCSV << first_come_first_serve;
    FCFS_SCSV.close();
    return 0;
}
