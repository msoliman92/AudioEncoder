#pragma once
#define HAVE_STRUCT_TIMESPEC
#include <vector>
#include <iostream>
#include <string>
#include <pthread.h> 
#include <thread> 
#include <mutex>
#include <algorithm> 

class MultiThreadHandler
{
private:
	unsigned int numOfSystemCores;
	std::vector<pthread_t> threads;
	std::vector<std::string>* myQueue;
	pthread_mutex_t queue_quard;
	void (*consumer)(std::string&);
	static void* ThreadOperation(void* thread_instance);
	unsigned int numberOfInputFiles;
	unsigned int numberOfAvialableThreads;
	MultiThreadHandler(); // to obselete the default constructor

public:
	MultiThreadHandler(std::vector<std::string>& queue, void (*fn)(std::string&));;
	~MultiThreadHandler();
};
