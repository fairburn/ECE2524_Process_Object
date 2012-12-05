#include <unistd.h>
#include <sys/wait.h>

#include <string>
#include <vector>

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    /* Initialize the process, create input/output pipes */
    Process(const std::string &args);
    
    /* Close any open file streams or file descriptors,
       insure that the child has terminated */
    virtual ~Process();
    
    /* write a string to the child process */
    void write(const std::string &input);

    /* read a full line from child process, 
       if no line is available, block until one becomes available */
    std::string readline();
    
    pid_t pid() const { return m_pid; };

private:
    void exec();
    
    std::string m_name;
    int readpipe[2];    
    int writepipe[2];
    FILE* m_pread;
    pid_t m_pid;
};

#endif