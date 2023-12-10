#include <memory>

#include "src/Application.h"

int main() {
    std::unique_ptr<Application> app(new Application());

    app->run();
}