#include "fcfs.h"
#include "PROCESS_GENERATOR.h"
#include <fstream>

int main() {
    PROCESS_GENERATOR PG(250000, 100, 100);
    std::vector<CPU_Process> processes = PG.GEN_PROCESSES();

    std::fstream process_scsv("processes.scsv", std::ios_base::out);
    process_scsv << "";
    process_scsv.close();
    process_scsv.open("processes.scsv", std::ios_base::app);
    process_scsv << PG;
    process_scsv.close();

    FCFS first_come_first_serve(processes, 'u');
    std::fstream FCFS_SCSV("fcfs.scsv", std::ios_base::out);
    FCFS_SCSV << "";
    FCFS_SCSV.close();
    FCFS_SCSV.open("fcfs.scsv", std::ios_base::app);
    FCFS_SCSV << first_come_first_serve;
    FCFS_SCSV.close();
    return 0;
}
