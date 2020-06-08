#include "MultiThreadHandler.h"

void* MultiThreadHandler::ThreadOperation(void* thread_instance)
{
	MultiThreadHandler* myThread = (MultiThreadHandler*)thread_instance;
	for (;;)
	{
		if (!myThread->myQueue->empty())
		{
			pthread_mutex_lock(&myThread->queue_quard);
			std::string item = myThread->myQueue->back();
			myThread->myQueue->pop_back();
			pthread_mutex_unlock(&myThread->queue_quard);
			myThread->consumer(item);
		}
		else
		{
			pthread_mutex_unlock(&myThread->queue_quard);
			break;
		}
	}
	return nullptr;
}

MultiThreadHandler::MultiThreadHandler(std::vector<std::string>& queue, void(*fn)(std::string&))
{
	myQueue = &queue;
	consumer = fn;
	queue_quard = PTHREAD_MUTEX_INITIALIZER;
	numberOfInputFiles = myQueue->size();
	numOfSystemCores = std::thread::hardware_concurrency();
	numberOfAvialableThreads = std::min(numOfSystemCores, numberOfInputFiles);
	std::cout << "Total Number Of Created Threads will be " <<  numberOfAvialableThreads << '\n';
	threads.resize(numberOfAvialableThreads);
	int i = 0;
	for (auto& newThread : threads)
	{
		i++;
		int error = pthread_create(&newThread, nullptr, ThreadOperation, this);
		if (error)
		{
			std::cout << "Thread Creation Failed!";
		}
		else
		{
			std::cout << "Creating Thread: " << i << '\n';
		}
	}
}

MultiThreadHandler::~MultiThreadHandler()
{
	for (int i = 0; i < numberOfAvialableThreads; i++)
	{
		pthread_join(threads[i], nullptr); 
		std::cout << "Exiting Thread: " << i+1 << "\n";
	}	
}
