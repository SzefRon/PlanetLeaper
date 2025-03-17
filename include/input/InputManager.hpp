#pragma once

#include <vector>
#include <map>
#include <Windows.h>

#include "input/InputObserver.hpp"
#include "input/Action.hpp"

namespace InputManager
{
    void subscribe(InputObserver *observer);
    void unsubscribe(InputObserver *observer);

    void initialize();
    void update();

    bool get_key_state(int key);
}