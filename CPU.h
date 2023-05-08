//Viet Dinh

#ifndef CPU_
#define CPU_

#include "Process.h"
#include <iostream>
#include <queue>
#include <vector>

class CPU
{
    private:
        std::priority_queue<Process, std::vector<Process>, std::less<Process>> readyQueue;
    public:
        //constructors
        CPU();
        ~CPU();

        //functions
        void CPURequestHandler(const Process& process);
        void RemoveFromCPU();

        //getters
        int GetCpuPID() const;
        int GetCPUPage() const;
        bool IsIdle() const;
        bool RQIsEmpty() const;
        Process GetCPUProcess() const;
        
        //setters
        void SetCPUPage(int page);
        void UpdatePC(int memoryAddress);

        //printers
        void PrintCPU() const;
        void PrintReadyQueue() const;
        void CopyQueue(std::priority_queue<Process, std::vector<Process>, std::less<Process>> tempQueue) const;
};

#endif 