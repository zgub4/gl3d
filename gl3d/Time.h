#pragma once

class Time {
public:

    Time() {
    }

    ~Time() {
    }

    static void begin();
    static void end();
    static float delta();

private:
    static float deltaTime;
    static float frameTime;
};