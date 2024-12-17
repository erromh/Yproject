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

        outputCallback("Executing Process (Round Robin):  " + process.processName + " for " +
                       std::to_string(executionTime) + " units of time.");

        process.burstTime -= executionTime;

        if (process.burstTime > 0)
        {
            highPriorityQueue.push(process);
        }
        else
        {
            outputCallback("\nProcess ID " + std::to_string(process.id) + " completed.");
        }
    }
}

void CourseLib::executeFCFS(std::function<void(const std::string &)> outputCallback)
{
    while (!lowPriorityQueue.empty())
    {
        Process process = lowPriorityQueue.front();

        lowPriorityQueue.pop();

        outputCallback("Executing Process (FCFS): " + process.processName + " for " +
                       std::to_string(process.burstTime) + " units of time.\n");
        outputCallback("Process ID " + std::to_string(process.id) + " completed.");
    }
}
