#include "fcfs.h"
#include "PROCESS_GENERATOR.h"
#include <fstream>
#include "sjf.h"
#include "lfu.h"
#include "mfu.h"

int main() {
    PROCESS_GENERATOR PG(10000, 50, 50);
//    std::vector<CPU_Process> processes = PG.GEN_PROCESSES();
//
//    std::fstream process_scsv("processes.scsv", std::ios_base::out);
//    process_scsv << PG;
//    process_scsv.close();

//    std::vector<CPU_Process> processes = PG.READ_PROCESSES("processes.scsv");
//
//    FCFS first_come_first_serve(processes);
//    first_come_first_serve.calculate();
//    std::fstream FCFS_SCSV("fcfs.scsv", std::ios_base::out);
//    FCFS_SCSV << first_come_first_serve;
//    FCFS_SCSV.close();
//
////    std::cout << *PG.getProcess(9899);
//
//    SJF sjf(processes);
//    sjf.calculate();
//    std::fstream SJF_SCSV("sjf.scsv", std::ios_base::out);
//    SJF_SCSV << sjf;
//    SJF_SCSV.close();

    LFU lfu(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2});
    lfu.run();
    std::cout << lfu.getPageFaults() << std::endl;
    std::cout << lfu.getHits();

    MFU mfu(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2});
    mfu.run();
    std::cout << mfu.getPageFaults() << std::endl;
    std::cout << mfu.getHits();
    return 0;
}
