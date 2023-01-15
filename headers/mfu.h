//
// Created by Jakub Górski on 14/01/2023.
//

#ifndef CPU_SCHEDULING_MFU_H
#define CPU_SCHEDULING_MFU_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <array>

class MFU {
public:
    MFU(int no_frames, std::vector<int> pages);
    ~MFU() = default;

    void run();
    int getPageFaults() const { return page_faults; }
    int getHits() const { return hits; }
private:
    int m_no_frames{}, page_faults{}, time{}, hits{};
    std::vector<std::pair<int, int>> frames;
    std::vector<int> m_pages;
    std::vector<std::array<int, 3>> page_stats;

    bool framesEmpty();
    bool isCached(int p);
    int findMFU(int p);
    static void printFrames(const std::vector<std::pair<int,int>>& frames);
};

#endif //CPU_SCHEDULING_MFU_H
