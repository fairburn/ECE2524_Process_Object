#include <iostream>
#include <cstdlib>
#include "Process.h"

Process::Process(const std::string &args) {
	m_name = args;
	
	pipe(readpipe);
	pipe(writepipe);
	
	m_pid = fork();
	
	//child
	if(m_pid == 0)
	{
		// replace stdin with output from parent
		dup2(readpipe[0], 0);
		
		//close output part of pipe
		close(readpipe[1]);
		
		// pipe output to parent
		dup2(writepipe[1], 1);
		
		//close input part of pipe
		close(writepipe[0]);
		
		exec();
	} else { //parent
		std::cout << "Parent[" << getpid() << "] Process constructor";
		// pipe stdout to child
		dup2(readpipe[1], 1);
		
		// close input part of pipe
		close(readpipe[0]);
		
		// replace stdin with output from child
		dup2(writepipe[0], 0);
		
		//close output part of pipe
		close(writepipe[1]);
	}
}

Process::~Process() {
	// wait for child to terminate
	if(m_pid) wait(NULL);
}

void Process::write(const std::string &input) {
	// make sure child does nothing
	if(m_pid == 0) return;
	
	// push string to pipe
	else {
		std::cout << input; // since stdout is connected to pipe
	}
}

std::string Process::readline() {
	// make sure child does nothing
	if(m_pid == 0) return "";
	
	else {
		std::string out = "";
		char buf;
		
		// read from pipe and store in char
		// append char to output string
		while( read(writepipe[0], &buf, 1) )
			out = out + buf;
		
		return out;
	}
}

void Process::exec() {
	// execute the program given in m_name
	execv(m_name.c_str(), NULL);
}























