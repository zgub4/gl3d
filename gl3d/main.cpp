#include "Engine.h"

int main(int argc, char** argv) {

    Engine eg{};
    try {
        eg.run();
    } catch(const std::runtime_error& e) {
        e.what();
        system("pause");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
