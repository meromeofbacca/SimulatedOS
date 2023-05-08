//Viet Dinh

#include "SimulatedOS.h"

//constructors
SimulatedOS::SimulatedOS(int numberOfDisks, int amountOfRAM, int pageSize) : 
    numberOfDisks_(numberOfDisks), amountOfRAM_(amountOfRAM), pageSize_(pageSize)
{ 
    cpu_ = CPU();
    ram_ = RAM(amountOfRAM/pageSize);

    //populates disk list
    for(int i = 0; i < numberOfDisks; i++){
        diskList_.push_back(Disk(i));
    }
}

SimulatedOS::~SimulatedOS()
{
    //empty ram, empty disk, disk queue, empty cpu, cpu queue
}

//member functions
void SimulatedOS::NewProcess(int priority) {
    if(priority >= 0) {
        cpu_.CPURequestHandler(Process(priority, PIDCounter_));
        ram_.AddToRAM(0, PIDCounter_);
        PIDCounter_++;
    }
}

/// @brief process in cpu is removed, memory deleted and freed
void SimulatedOS::Exit() {
    if(!cpu_.IsIdle()){ 
        bool isRQEmpty = cpu_.RQIsEmpty(); //done before removeFromCPU due to readyQueue implementation
        ram_.RemoveProcess(cpu_.GetCpuPID());
        cpu_.RemoveFromCPU();   

        //update cpu process if there is one
        if(!isRQEmpty)
            ram_.AddToRAM(cpu_.GetCPUPage(), cpu_.GetCpuPID());
    }
}

/// @brief removes process from cpu, send to disk for read_request
void SimulatedOS::DiskReadRequested(int diskNumber, std::string fileName) {
    if(!ValidDiskNumber(diskNumber))
        std::cout << invalidDiskErrorMessage << std::endl;

    else if(!cpu_.IsIdle()){ 
        bool isRQEmpty = cpu_.RQIsEmpty(); //done before removeFromCPU due to readyQueue implementation
        diskList_.at(diskNumber).ReadRequestHandler(cpu_.GetCPUProcess(), fileName);
        cpu_.RemoveFromCPU();
        
        //update new cpu process if there is one
        if(!isRQEmpty)
            ram_.AddToRAM(cpu_.GetCPUPage(), cpu_.GetCpuPID());
    }
}

/// @brief removes process from disk, send to cpu ready_queue
void SimulatedOS::DiskJobCompleted(int diskNumber) {
    if(!ValidDiskNumber(diskNumber))
        std::cout << invalidDiskErrorMessage << std::endl;
    else{
        Process process = diskList_.at(diskNumber).DiskJobCompleted();

        if(cpu_.IsIdle()){ 
            cpu_.CPURequestHandler(process);
            ram_.AddToRAM(process.getPage(), process.getPID());
        }
        else{ //pre-emption
            int previousPID = cpu_.GetCpuPID();
            cpu_.CPURequestHandler(process);
            
            if(previousPID != cpu_.GetCpuPID()) 
                ram_.AddToRAM(process.getPage(), process.getPID());
        }
    }
}

/// @brief updates cpu process's program counter, adds page into ram, updates process freshest page
void SimulatedOS::FetchFrom(unsigned int memoryAddress) {
    if(memoryAddress >= 0 && !cpu_.IsIdle()){
        int page = memoryAddress/pageSize_;
        ram_.FetchFrom(page, cpu_.GetCpuPID());
        cpu_.SetCPUPage(page);
        cpu_.UpdatePC(memoryAddress);
    }
}

//printers
void SimulatedOS::PrintCPU() const {
    cpu_.PrintCPU();
}

void SimulatedOS::PrintReadyQueue() const {
    cpu_.PrintReadyQueue();
}

void SimulatedOS::PrintRAM() const {
    ram_.PrintRAM();
}

void SimulatedOS::PrintDisk(int diskNumber) const {
    if(!ValidDiskNumber(diskNumber))
        std::cout << invalidDiskErrorMessage << std::endl;
    else
        diskList_.at(diskNumber).PrintDisk();
}

void SimulatedOS::PrintDiskQueue(int diskNumber) const {
    if(!ValidDiskNumber(diskNumber))
        std::cout << invalidDiskErrorMessage << std::endl;
    else
        diskList_.at(diskNumber).PrintDiskQueue();
}

//validator
bool SimulatedOS::ValidDiskNumber(int diskNumber) const{
    return (diskNumber <= diskList_.size() - 1) && (diskNumber >= 0);
}
