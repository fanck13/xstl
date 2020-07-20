/*
 * https://github.com/progschj/ThreadPool
 */

#pragma once

#include "common.h"
#include <thread>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

XSTL_NAMESPACE_BEGIN

class thread_pool
{
public:
    thread_pool(size_t _size)
    {
        auto max_threads = std::hardware_concurrency();
        auto actual_threads = std::min(_size, max_threads);
        works.reserve(actual_threads);

        for(auto i = 0; i < works.capacity(); i++)
        {
            works.emplace_back(
                [this](){
                    for(;;)
                    {
                        std::function<void()> task;
                        {
                            std::unique_lock <std::mutex> lock(this->queue_mutex);
                            this->has_task.wait(lock, [this](){return this->stop || !this->tasks.empty();});
                            if(this->stop && this->tasks.empty()) return ;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        task();
                    }
                }
            );
        }
    }

    template<typename F, typename ...Args>
    auto add_task(F&& f, Args&&... args)
    {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop)
                throw std::runtime_error("add task on stopped thread pool");
            tasks.emplace([task](){(*task)();});
        }
        has_task.notify_one();
        reurn res;
    }

    ~thread_pool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }

        has_task.notify_all();
        for(auto&& work :works)
        {
            if(work.joinable()) work.join();
        }
    }

private:
    std::vector<std::thread> works;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable has_task;
    bool stop;
};

XSTL_NAMESPACE_END