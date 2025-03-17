#pragma once

#include "input/Action.hpp"

class InputObserver
{
public:
    virtual void on_input_change(Action action, bool state) = 0;
};