//Viet Dinh

#include "RAM.h"

//constructors
/// @brief initializes frames
RAM::RAM(int numFrames)
    : numFrames_(numFrames)
{
    for(int i = 0; i < numFrames; i++){
        pageTable_.push_back(Row(i));
    }
}

RAM::~RAM()
{
}

// public functions
void RAM::AddToRAM(int page, int PID){
    //if table isn't full and no existing frame
    if(!IsFull() && FindExistingFrame(page, PID) == -1){
        timeCounter_++;
        SetFrame(FindAvailableFrame(), page, PID, timeCounter_);   
        occupancy_++;
    }
    //if table is full and no existing frame => need to update TS or replace 
    else if(FindExistingFrame(page, PID) != -1){ //found existing frame
        timeCounter_++;
        pageTable_.at(FindExistingFrame(page, PID)).time_ = timeCounter_;
    }
    else
        ReplaceOldestFrame(page, PID);
}

void RAM::FetchFrom(int page, int PID){
    AddToRAM(page, PID);
}

/// @brief frees up frame, sets page, pid, timestamp to -1
void RAM::RemoveProcess(int PID) {
    for(auto& element: pageTable_){
        if(element.PID_ == PID)
            pageTable_.at(element.frame_) = Row(element.frame_);
    }
    occupancy_--;
}

// private functions
/// @return available empty frames
int RAM::FindAvailableFrame() const { //use if pageTable has available empty frames
    if(!IsFull()){
        for(auto& element: pageTable_){
            if (element.page_ == -1)
                return element.frame_;
        }
    }
    
    return -1;
}

int RAM::FindExistingFrame(int page, int PID) const { 
    for(auto& element: pageTable_){
        if (element.page_ == page && element.PID_ == PID)
            return element.frame_;
    }
    
    return -1;
}

int RAM::FindOldestFrame() const {
    auto oldestFrame = pageTable_.at(0).frame_;

    for(auto& element: pageTable_){
        if(element.time_ < pageTable_.at(oldestFrame).time_)
            oldestFrame = element.frame_;
    }

    return oldestFrame;
}

void RAM::ReplaceOldestFrame(int page, int PID){
    int oldestFrame = FindOldestFrame();
    timeCounter_++;
    pageTable_.at(oldestFrame) = Row(oldestFrame, page, PID, timeCounter_);
}

//utility
bool RAM::IsFull() const { 
    return occupancy_ == numFrames_; 
}

//setters
void RAM::SetFrame(int frame, int page, int PID, int time) {
    pageTable_.at(frame) = Row(frame, page, PID, time);
}

//printers
void RAM::PrintRAM() const {
    //table header
    std::cout << std::setw(5) << "Frame" << std::left << "\t" << std::setw(4) << "Page" << std::left << "\t" << std::setw(3) << "PID" << std::left << std::endl;

    //table elements
    for(auto& element: pageTable_){
        std::cout << std::setw(5) << element.frame_ << std::left << "\t"; 
        
        //if frame "empty"
        if(element.page_ == -1)
            std::cout << std::setw(4) << "" << std::left << "\t" << std::setw(3) << "" << std::left << std::endl;
        else
            std::cout << std::setw(4) << element.page_ << std::left << "\t" << std::setw(3) << element.PID_ << std::left << std::endl;
    }
}