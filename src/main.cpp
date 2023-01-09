#include "fcfs.h"
#include "PROCESS_GENERATOR.h"
#include <fstream>
#include "sjf.h"

int main() {
    PROCESS_GENERATOR PG(10000, 50, 50);
    std::vector<CPU_Process> processes = PG.GEN_PROCESSES();

    std::fstream process_scsv("processes.scsv", std::ios_base::out);
    process_scsv << "";
    process_scsv.close();
    process_scsv.open("processes.scsv", std::ios_base::app);
    process_scsv << PG;
    process_scsv.close();

//    std::vector<CPU_Process> processes = PG.READ_PROCESSES("processes.scsv");

    FCFS first_come_first_serve(processes);
    first_come_first_serve.calculate();
    std::fstream FCFS_SCSV("fcfs.scsv", std::ios_base::out);
    FCFS_SCSV << "";
    FCFS_SCSV.close();
    FCFS_SCSV.open("fcfs.scsv", std::ios_base::app);
    FCFS_SCSV << first_come_first_serve;
    FCFS_SCSV.close();

    SJF sjf(processes);
    sjf.calculate();
    std::fstream SJF_SCSV("sjf.scsv", std::ios_base::out);
    SJF_SCSV << "";
    SJF_SCSV.close();
    SJF_SCSV.open("sjf.scsv", std::ios_base::app);
    SJF_SCSV << sjf;
    SJF_SCSV.close();

    return 0;
}
