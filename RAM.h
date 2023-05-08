//Viet Dinh

#ifndef RAM_
#define RAM_

#include <iostream>
#include <iomanip>
#include <vector>

struct Row
{
    int frame_;
    int page_;
    int PID_;
    int time_;

    Row(int frame = -1, int page = -1, int PID = -1, int time = -1)
        : frame_(frame), page_(page), PID_(PID), time_(time) {}
};

class RAM
{
    private:
        //data
        int numFrames_;
        int timeCounter_ = 0;
        int occupancy_ = 0;
        std::vector<Row> pageTable_;

        //functions
        bool IsFull() const;

        /// @return available empty frames
        int FindAvailableFrame() const;
        int FindExistingFrame(int page, int PID) const;
        int FindOldestFrame() const;
        void ReplaceOldestFrame(int page, int PID);
        void SetFrame(int frame, int page, int PID, int time);

    public:
        RAM(int numFrames = 0);
        ~RAM();

        //functions
        void AddToRAM(int page, int PID);
        void FetchFrom(int page, int PID);
        void RemoveProcess(int PID); 

        //printers
        void PrintRAM() const;
};

#endif