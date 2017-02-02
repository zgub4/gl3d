#include "Input.h"

#include <algorithm>

Input::Input() {
}


Input::~Input() {
}

void Input::addKey(int key) {
    auto val = std::find(keys.begin(), keys.end(), key);
    if(val == keys.end()) {
        keys.push_back(key);
    }
}

void Input::removeKey(int key) {
    auto val = std::find(keys.begin(), keys.end(), key);
    if(val != keys.end()) {
        keys.erase(val);
    }
}
