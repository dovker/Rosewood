#pragma once

#include "rwpch.h"

namespace Rosewood
{
    template<typename T> 
    class TSQueue
    {
    public:
        TSQueue() = default;
        TSQueue(const TSQueue<T>&) = delete;
        virtual ~TSQueue() { Clear(); }

        const T& Front()
        {
            std::scoped_lock lock(m_MuxQueue);
            return m_DeqQueue.front;
        }
        const T& Back()
        {
            std::scoped_lock lock(m_MuxQueue);
            return m_DeqQueue.back;
        }
        void PushBack(const T& value)
        {
            std::scoped_lock lock(m_MuxQueue);
            m_DeqQueue.emplace_back(std::move(value));

            std::unique_lock<std::mutex> ul(m_MuxBlocking);
            m_Blocking.notify_one();
        }
        void PushFront(const T& value)
        {
            std::scoped_lock lock(m_MuxQueue);
            m_DeqQueue.emplace_front(std::move(value));

            std::unique_lock<std::mutex> ul(m_MuxBlocking);
            m_Blocking.notify_one();
        }

        bool IsEmpty()
        {
            std::scoped_lock lock(m_MuxQueue);
            return m_DeqQueue.empty();
        }

        size_t Count()
        {
            std::scoped_lock lock(m_MuxQueue);
            return m_DeqQueue.size();
        }

        void Clear()
        {
            std::scoped_lock lock(m_MuxQueue);
            m_DeqQueue.clear();
        }

        T PopFront()
        {
            std::scoped_lock lock(m_MuxQueue);
            auto t = std::move(m_DeqQueue.front());
            m_DeqQueue.pop_front();
            return t;
        }
        T PopBack()
        {
            std::scoped_lock lock(m_MuxQueue);
            auto t = std::move(m_DeqQueue.back());
            m_DeqQueue.pop_back();
            return t;
        }

        void Wait()
        {
            while(IsEmpty())
            {
                std::unique_lock<std::mutex> ul(m_MuxBlocking);
                m_Blocking.wait(ul);
            }
        }
    private:
        std::mutex m_MuxQueue;
        std::deque<T> m_DeqQueue;

        std::condition_variable m_Blocking;
        std::mutex m_MuxBlocking;
    };
}