#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "Process.h"

class CourseLib
{
  public:
    CourseLib();
    ~CourseLib();

    void addProcess(int id, int burstTime, std::string &priority, std::string &taskName);

    void executeRoundRobin(int quantum, std::function<void(const std::string &)> outputCallback);
    void executeFCFS(std::function<void(const std::string &)> outputCallback);

    int customMin(int a, int b);

  private:
    std::queue<Process> highPriorityQueue;
    std::queue<Process> lowPriorityQueue;
};
