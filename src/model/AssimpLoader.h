#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <string>

class AssimpLoader {
public:
    void load(const std::string &modelName, const std::string &fileName);
};

#endif //ASSIMPLOADER_H
