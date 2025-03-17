#include "input/InputManager.hpp"

std::vector<InputObserver *> observers;

std::map<int, Action> key_to_action =
{
    {'a', Action::MOVE_LEFT},
    {'d', Action::MOVE_RIGHT},
    {'w', Action::JUMP}
};

std::map<int, bool> key_states;

void InputManager::subscribe(InputObserver *observer)
{
    observers.push_back(observer);
}

void InputManager::unsubscribe(InputObserver *observer)
{
    std::erase(observers, observer);
}

void InputManager::initialize()
{
    for (auto &[key, action] : key_to_action) {
        key_states.insert({key, false});
    }
}

void InputManager::update()
{
    for (auto &[key, state] : key_states) {
        bool new_state = get_key_state(key);

        if (state != new_state) {
            state = new_state;

            for (auto &observer : observers) {
                observer->on_input_change(key_to_action.at(key), state);
            }
        }
    }
}

bool InputManager::get_key_state(int key)
{
    return GetAsyncKeyState(VkKeyScan(key));
}
