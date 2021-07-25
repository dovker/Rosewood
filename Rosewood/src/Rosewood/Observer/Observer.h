#pragma once
#include "Subject.h"

namespace Rosewood
{
    class Observer
    {
    public:
        virtual ~Observer() {}
        virtual void OnNotify(std::any& sender, Signal signal) = 0;
    };
}