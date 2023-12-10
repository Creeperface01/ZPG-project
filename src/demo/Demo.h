//
// Created by Jan Bednář on 04.11.2023.
//

#ifndef CV1_DEMO_H
#define CV1_DEMO_H

#include <vector>
#include <memory>

#include "../window/Window.h"

class Demo {
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    decltype(scenes)::iterator sceneIterator;

    void initScenes(Window *window);
public:
    void run(Window *window);
};


#endif //CV1_DEMO_H
