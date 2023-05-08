//Viet Dinh

#include "Process.h"

//constructors
Process::Process(int priority, int PID, int lastPageUsed, int programCounter):
    priority_(priority), PID_(PID), lastPageUsed_(lastPageUsed), programCounter_(programCounter)
{
}

Process::~Process()
{
}

//comparator
bool operator<(const Process& lhs, const Process& rhs) { return lhs.priority_ < rhs.priority_; }

//getters
int Process::getPriority() const { 
    return priority_; 
}
int Process::getPID() const { 
    return PID_; 
}
int Process::getPage() const { 
    return lastPageUsed_; 
}
int Process::getPC() const { 
    return programCounter_; 
}

//setters
void Process::setPage(int page) { 
    lastPageUsed_ = page; 
}
void Process::updatePC(int memoryAddress) { 
    programCounter_ = memoryAddress;
}