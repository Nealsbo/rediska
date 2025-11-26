#include <iostream>

#include "threadPool.h"

void ThreadPool::SpawnThreads(int count) {
    std::cout << "INFO: ThreadPool, spawn " << count << "threads\n";
    wrk_threads.reserve(count);
        while(count--) {
        wrk_threads.emplace_back(std::thread(&ThreadPool::Worker, this));
    }
}

void ThreadPool::StopThreads() {
    std::cout << "INFO: ThreadPool stops\n";
    std::lock_guard lk(mtx);
    stopWorkers = true;
    for(auto &a: wrk_threads) {
        a.join();
    }
}

void test_job() {
    std::cout << "INFO: Test Job Call\n";
}

void ThreadPool::AddWork(int fd) {
    {
        std::lock_guard lk(mtx);
        wrk_q.push(&test_job);
    }
    cv_empty.notify_one();
}

void ThreadPool::Worker() {
    std::cout << "INFO: Worker (id:" << std::this_thread::get_id() << ") on start\n";
    while(!stopWorkers) {
        std::unique_lock lk(mtx);
        cv_empty.wait(lk, [this](){return !wrk_q.empty();});

        auto task = std::move(wrk_q.front());
        wrk_q.pop();
        task();
    }
    std::cout << "INFO: Worker (id:" << std::this_thread::get_id() << ") on stop\n";
}