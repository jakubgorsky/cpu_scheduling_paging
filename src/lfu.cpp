//
// Created by Jakub Górski on 09/01/2023.
//

#include "lfu.h"
LFU::LFU(int no_frames, std::vector<int> pages)
    : m_no_frames(no_frames), m_pages(std::move(pages)){
    for (int i = 0; i < m_no_frames; i++){
        frames.emplace_back(i, -1);
    }
    for (auto& p : m_pages){
        if(std::none_of(page_stats.begin(), page_stats.end(),
                        [&p](const std::array<int, 3>& c){return c[0] == p;})){
            page_stats.push_back({p, 0, -1});
        }
    }
}

void LFU::run(){
    time = 0;
    for (auto& p : m_pages){
        // if the page is already in cache, increase it's counter
        if (isCached(p) && !framesEmpty()){
            auto it = std::find_if(page_stats.begin(), page_stats.end(),
                         [&p](std::array<int, 3> a){ return a[0] == p; });
            it->at(1) += 1;
            hits++;
            printFrames(frames);
            time++;
            continue;
        }
        // if page is cached and frames are empty increase it's counter and increase page fault
        if (isCached(p) && framesEmpty()) {
            std::find_if(page_stats.begin(), page_stats.end(),
                         [&p](const std::array<int, 3>& a){ return a[0] == p; })->at(1)++;
            page_faults++;
            printFrames(frames);
            time++;
            continue;
        }
        // if page is not cached and the frames are not empty
        // find page that came in earlier, swap the pages and increase page fault;
        if (!isCached(p) && !framesEmpty()){
            int pid = findLFU(p);
            auto pid_it = std::find_if(page_stats.begin(), page_stats.end(),
                                   [&pid](const std::array<int, 3>& a){ return a[0] == pid; });
            if (pid != p){
                pid_it->at(2) = -1;
            }
            // reset counter
            pid_it->at(1)--;
            // replace page
            std::find_if(frames.begin(), frames.end(),
                         [&pid](const std::pair<int, int> &c) { return c.second == pid; })->second = p;
            auto new_pid_it = std::find_if(page_stats.begin(), page_stats.end(),
                         [&p](const std::array<int, 3> &a) { return a[0] == p; });
            new_pid_it->at(1)++;
            new_pid_it->at(2) = time;
            page_faults++;
            printFrames(frames);
            time++;
            continue;
        }
        // if any of the frames are empty put the page in the first free frame, increase it's counter and increase page fault
        if (framesEmpty()){
            // find first empty frame
            std::find_if(frames.begin(), frames.end(),
                         [](const std::pair<int, int> &c) { return c.second == -1; })->second = p;
            auto it = std::find_if(page_stats.begin(), page_stats.end(),
                                   [&p](const std::array<int, 3>& a){ return a[0] == p; });
            it->at(1)++;
            it->at(2) = time;
            page_faults++;
            printFrames(frames);
            time++;
            continue;
        }
        printFrames(frames);
        time++;
    }
}

bool LFU::framesEmpty(){
    return std::any_of(frames.begin(), frames.end(),
                       [](const std::pair<int, int>& c){ return c.second == -1; });
}

bool LFU::isCached(int p) {
    return p == std::find_if(frames.begin(), frames.end(),
                             [&p](const std::pair<int, int> &element) { return element.second == p; })->second;
}

void LFU::printFrames(const std::vector<std::pair<int, int>>& frames){
    for (auto f : frames){
        std::cout << f.second << " ";
    }
    std::cout << std::endl;
}

int LFU::findLFU(int p){
    int min_time = 20000;
    int min_count = 20000;

    // get least count
    for (auto page : page_stats){
        if(page[0] == p){
            continue;
        }
        if(page[1] < min_count && page[1] > 0){
            min_count = page[1];
            min_time = page[2];
            p = page[0];
        }
    }

    // check if any page with same count has been insterted prior to the one stored in p variable
    for (auto page : page_stats){
        if(page[0] == p){
            continue;
        }
        if(page[2] < min_time && page[2] > -1 && page[1] == min_count){
            min_time = page[2];
            p = page[0];
        }
    }
    return p;
}
