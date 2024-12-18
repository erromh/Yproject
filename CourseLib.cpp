#include "CourseLib.h"

CourseLib::CourseLib()
{
}

CourseLib::~CourseLib()
{
}

void CourseLib::addProcess(int id, int burstTime, std::string &priority, std::string &taskName)
{
    Process process{id, burstTime, priority, taskName};

    if (priority == "high")
    {
        highPriorityQueue.push(process);
    }

    else
    {
        lowPriorityQueue.push(process);
    }
}

int CourseLib::customMin(int a, int b)
{
    return (a < b) ? a : b;
}

void CourseLib::executeRoundRobin(int quantum, std::function<void(const std::string &)> outputCallback)
{
    while (!highPriorityQueue.empty())
    {
        Process process = highPriorityQueue.front();
        highPriorityQueue.pop();

        int executionTime = customMin(process.burstTime, quantum);

        outputCallback("Executing Process (Round Robin): ID " + std::to_string(process.id) + " for " +
                       std::to_string(executionTime) + " time units.");

        std::this_thread::sleep_for(std::chrono::milliseconds(executionTime * 100));

        process.burstTime -= executionTime;

        if (process.burstTime > 0)
        {
            highPriorityQueue.push(process);
        }
        else
        {
            outputCallback("Process ID " + std::to_string(process.id) + " completed.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void CourseLib::executeFCFS(std::function<void(const std::string &)> outputCallback)
{
    while (!lowPriorityQueue.empty())
    {
        Process process = lowPriorityQueue.front();
        lowPriorityQueue.pop();

        outputCallback("Executing Process (FCFS): ID " + std::to_string(process.id) + " for " +
                       std::to_string(process.burstTime) + " time units.");

        std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime * 100));

        outputCallback("Process ID " + std::to_string(process.id) + " completed.");

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
