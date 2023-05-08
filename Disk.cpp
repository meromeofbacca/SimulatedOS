//Viet Dinh

#include "Disk.h" 

//constructors

/// @brief disk holds jobs
Job::Job(const Process& process, std::string jobFileName)
    : process_(process), jobFileName_(jobFileName) 
{ 
    jobPID_ = process.getPID();
}

Disk::Disk(int id) : id_(id)
{

}

Disk::~Disk()
{
    diskQueue_ = std::queue<Job>();
}

//functions

/// @brief adds processes to disk/diskqueue
void Disk::ReadRequestHandler(const Process& process, std::string jobFileName) { 
    diskQueue_.push(Job(process, jobFileName));
}

/// @brief removes job from disk
/// @return the process to return to cpu.readyqueue
Process Disk::DiskJobCompleted() { 
    Process process = diskQueue_.front().process_;
    diskQueue_.pop();

    return process;
}

//getters
int Disk::GetDiskID() const { 
    return id_; 
}
int Disk::GetDiskJobPID() const { 
    return diskQueue_.front().jobPID_; 
}
std::string Disk::GetDiskJobFileName() const { 
    return diskQueue_.front().jobFileName_; 
}

//printers
void Disk::PrintDisk() const {
    if(diskQueue_.empty())
        std::cout << "Disk " << id_ << ": Idle" << std::endl;
    else
        std::cout << "Disk " << id_ << ": PID " << GetDiskJobPID() << ", \"" << GetDiskJobFileName() << "\"" << std::endl;
}
void Disk::PrintDiskQueue() const {
    CopyQueue(diskQueue_); //this doesn't require mutating diskQueue
}

/// @brief prints copy of queue bc printing a std::queue requires mutation
void Disk::CopyQueue(std::queue<Job> tempQueue) const {
    //if all disk empty
    if(tempQueue.empty())
        std::cout << "Disk " << id_ << " I/O-queue: Empty" << std::endl;
        
    else {
        tempQueue.pop();

        //if queue empty
        if(tempQueue.empty())
            std::cout << "Disk " << id_ << " I/O-queue: Empty" << std::endl;

        //if queue non-empty
        else{ 
            std::cout << "Disk Queue:";

            while(!tempQueue.empty()){ 
                std::cout << " " << tempQueue.front().jobPID_;           
                tempQueue.pop();
            }
            std::cout << std::endl;
        }
    }
}