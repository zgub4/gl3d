#pragma once

#include <vector>

class Input
{
public:
    Input();
    ~Input();

    void addKey(int key);
    void removeKey(int key);

private:
    std::vector <int> keys;
};

