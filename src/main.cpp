#include "fcfs.h"
#include "PROCESS_GENERATOR.h"
#include <fstream>
#include "sjf.h"
#include "lfu.h"
#include "mfu.h"

int main() {
    PROCESS_GENERATOR PG(10000, 75, 75);
    std::vector<CPU_Process> processes = PG.GEN_PROCESSES();

    std::fstream process_scsv("processes.scsv", std::ios_base::out);
    process_scsv << PG;
    process_scsv.close();

    std::fstream FCFS_SCSV("fcfs10k_5.scsv", std::ios_base::out);
    std::fstream SJF_SCSV("sjf10k_5.scsv", std::ios_base::out);

    FCFS first_come_first_serve(processes);
    first_come_first_serve.calculate();
    FCFS_SCSV << first_come_first_serve;
    FCFS_SCSV.close();

    SJF sjf(processes);
    sjf.calculate();
    SJF_SCSV << sjf;
    SJF_SCSV.close();


    std::vector<int> pages;
    int n = 500;
    int f = 5;

    std::random_device randomDevice;
    std::mt19937 range(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,7);

    for (int i = 0; i < n; i++){
        pages.push_back(int(dist(range)));
    }

    std::cout << "n = " << n << " f = " << f << std::endl;

    LFU lfu(f, pages);
    lfu.run();
    std::cout << "LFU" << std::endl;
    std::cout << "Page Faults: " << lfu.getPageFaults() << std::endl;
    std::cout << "Hits: "<< lfu.getHits() << std::endl;

    MFU mfu(f, pages);
    mfu.run();
    std::cout << "MFU" << std::endl;
    std::cout << "Page Faults: " << mfu.getPageFaults() << std::endl;
    std::cout << "Hits: " << mfu.getHits();
    return 0;
}
