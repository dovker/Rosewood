#pragma once
#include "rwpch.h"
#include "Event.h"

namespace Rosewood {

    // class EventPool
    // {
    // public:
    //     EventPool() {}

    //     void QueueEvent(Event e) { m_Queue.push_back(&e); }
    //     Event DequeueEvent()
    //     {
    //         Event* e = m_Queue.front();
    //         m_Queue.pop_front();
    //         return &e;
    //     }
    //     bool IsEmpty()
    //     {
    //         return m_Queue.size() <= 0;
    //     }


    // private:
    //     std::deque<Event*> m_Queue; //TODO: SWAP WITH RING BUFFER LATER
    // };

}
