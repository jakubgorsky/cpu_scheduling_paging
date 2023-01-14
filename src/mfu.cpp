//
// Created by Jakub Górski on 14/01/2023.
//
#include "mfu.h"

//
// Created by Jakub Górski on 09/01/2023.
//

#include "mfu.h"
MFU::MFU(int no_frames, std::vector<int> pages)
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

void MFU::run(){
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
            int pid = findMFU(p);
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

bool MFU::framesEmpty(){
    return std::any_of(frames.begin(), frames.end(),
                       [](const std::pair<int, int>& c){ return c.second == -1; });
}

bool MFU::isCached(int p) {
    return p == std::find_if(frames.begin(), frames.end(),
                             [&p](const std::pair<int, int> &element) { return element.second == p; })->second;
}

void MFU::printFrames(const std::vector<std::pair<int, int>>& frames){
    for (auto f : frames){
        std::cout << f.second << " ";
    }
    std::cout << std::endl;
}

int MFU::findMFU(int p){
    int max_time = 0;
    int max_count = 0;

    // get least count
    for (auto page : page_stats){
        if(page[0] == p){
            continue;
        }
        if(page[1] > max_count && page[1] > 0){
            max_count = page[1];
            max_time = page[2];
            p = page[0];
        }
    }

    // check if any page with same count has been insterted prior to the one stored in p variable
    for (auto page : page_stats){
        if(page[0] == p){
            continue;
        }
        if(page[2] > max_time && page[1] == max_count){
            max_time = page[2];
            p = page[0];
        }
    }
    return p;
}