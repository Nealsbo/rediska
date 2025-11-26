#pragma once

#include <vector>
#include <queue>
#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>

struct ThreadPool {
    std::vector<std::thread> wrk_threads;
    std::queue<std::function<void()>> wrk_q;
    std::mutex mtx;
    std::condition_variable cv_empty;

    void SpawnThreads(int count);
    void StopThreads();
    void AddWork(int fd);
    void Worker();

    bool stopWorkers;
};