#pragma once

class Time
{
public:
    static void begin();
    static void end();
    static float delta();

private:
    static float deltaTime;
    static float frameTime;

    Time() = delete;
    Time(Time const&) = delete;
    void operator=(Time const&) = delete;
};
