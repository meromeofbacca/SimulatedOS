//Viet Dinh

#ifndef SIMULATED_OS_
#define SIMULATED_OS_

#include "CPU.h"
#include "Disk.h"
#include "RAM.h"
#include "Process.h"

#include <string>
#include <vector>

class SimulatedOS
{
    private:
        CPU cpu_;
        RAM ram_;
        int pageSize_;
        std::vector<Disk> diskList_;
        int numberOfDisks_;
        int amountOfRAM_;
        int PIDCounter_ = 1;

        //error message
        std::string invalidDiskErrorMessage = "Instruction ignored: no disk with such number exists";
        //validator
        bool ValidDiskNumber(int diskNumber) const;

    public:
        //constructors
        SimulatedOS(int numberOfDisks, int amountOfRAM, int pageSize);
        ~SimulatedOS();

        //functions
        void NewProcess(int priority);
        void Exit();
        void DiskReadRequested(int diskNumber, std::string fileName);
        void DiskJobCompleted(int diskNumber);
        void FetchFrom(unsigned int memoryAddress);
        
        //printers
        void PrintCPU() const;
        void PrintReadyQueue() const;
        void PrintRAM() const;
        void PrintDisk(int diskNumber) const;
        void PrintDiskQueue(int diskNumber) const;
};

#endif 