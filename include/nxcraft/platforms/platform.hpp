#pragma once

#include <string>

namespace nxcraft {
namespace platforms {

class Platform {
    public:
    virtual std::string getName() = 0;
    virtual std::pair<int, int> getDefaultWindowSize() = 0;
    virtual std::string getResourcePath() = 0;

    virtual void init() = 0;
    virtual void deinit() = 0;
};

} // namespace platforms
} // namespace nxcraft
