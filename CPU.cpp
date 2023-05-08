//Viet Dinh

#include "CPU.h"

//constructors
CPU::CPU()
{
}
CPU::~CPU()
{
    readyQueue = std::priority_queue<Process, std::vector<Process>, std::less<Process>>();
}

//functions

/// @brief handles cpu queue and who uses it
void CPU::CPURequestHandler(const Process& process){
    readyQueue.push(process);
}
void CPU::RemoveFromCPU(){
    readyQueue.pop();
}

//getters
int CPU::GetCpuPID() const { 
    return readyQueue.top().getPID(); 
}
int CPU::GetCPUPage() const { 
    return readyQueue.top().getPage(); 
}
Process CPU::GetCPUProcess() const { 
    return readyQueue.top(); 
}
bool CPU::IsIdle() const { 
    return readyQueue.empty(); 
}
bool CPU::RQIsEmpty() const
{
    std::priority_queue<Process, std::vector<Process>, std::less<Process>> temp = readyQueue;
    if(temp.empty())
        return true;
    else    
        temp.pop();

    return temp.empty();
}

//setters
void CPU::SetCPUPage(int page) { 
    //does it this way bc top() returns const value
    Process temp = readyQueue.top();
    readyQueue.pop();
    readyQueue.push(Process(temp.getPriority(), temp.getPID(), page));
}
void CPU::UpdatePC(int memoryAddress)
{
    //does it this way bc top() returns const value
    Process temp = readyQueue.top();
    readyQueue.pop();
    readyQueue.push(Process(temp.getPriority(), temp.getPID(), temp.getPage(), memoryAddress));
}

//printers
void CPU::PrintCPU() const{
    if(readyQueue.empty())
        std::cout << "CPU: Idle" << std::endl;
    else
        std::cout << "CPU: " << readyQueue.top().getPID() << std::endl;
}
void CPU::PrintReadyQueue() const{
    CopyQueue(readyQueue);
}

/// @brief prints copy of readyQueue bc printing a std::priority_queue requires mutation
void CPU::CopyQueue(std::priority_queue<Process, std::vector<Process>, std::less<Process>> tempQueue) const{
    //if CPU and readyQueue are empty
    if(tempQueue.empty()){
        std::cout << "CPU Ready-Queue: Empty" << std::endl;
    }
    else {
        tempQueue.pop();

        //if readyQueue empty
        if(tempQueue.empty()){
            std::cout << "CPU Ready-Queue: Empty" << std::endl;
        }

        //if readyQueue non-empty
        else{ 
            std::cout << "Ready-Queue:";

            while(!tempQueue.empty()){ 
                std::cout << " " << tempQueue.top().getPID();           
                tempQueue.pop();
            }
            std::cout << std::endl;
        }
    }
}