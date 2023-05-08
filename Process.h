//Viet Dinh

#ifndef PROCESS_
#define PROCESS_

class Process
{
    private:
        int priority_;
        int PID_;
        int programCounter_;
        int lastPageUsed_;

        /// @brief comparator for cpu priorityqueue
        friend bool operator<(const Process& lhs, const Process& rhs);
        
    public:
        //constructors
        Process(int priority, int PID, int lastPageUsed = 0, int programCounter = 0);
        ~Process();

        //getters
        int getPriority() const;
        int getPID() const;
        int getPage() const;
        int getPC() const;

        //setters
        void setPage(int page);
        void updatePC(int memoryAddress);
};

#endif