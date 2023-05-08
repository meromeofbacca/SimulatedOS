    //Viet Dinh

    #ifndef DISK_
    #define DISK_

    #include "Process.h"
    #include <iostream>
    #include <vector>
    #include <queue>
    #include <string> 

    struct Job
    {
        Process process_;
        int jobPID_;
        std::string jobFileName_;

        Job(const Process& process, std::string jobFileName = "");
    };

    class Disk
    {
        private:     
            //data
            int id_;
            //FIFO queue
            std::queue<Job> diskQueue_;        
            
        public:
            //constructors
            Disk(int id);
            ~Disk();

            //functions
            void ReadRequestHandler(const Process& process, std::string jobFileName);
            Process DiskJobCompleted(); //returns PID

            //getters
            int GetDiskID() const;
            int GetDiskJobPID() const;
            std::string GetDiskJobFileName() const;

            //printers
            void PrintDisk() const;
            void PrintDiskQueue() const;
            void CopyQueue(std::queue<Job> tempQueue) const; 
    };

    #endif