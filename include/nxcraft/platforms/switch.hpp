#pragma once

#include <string>

#include "platform.hpp"

namespace nxcraft {
namespace platforms {

class Switch : public Platform {
    public:
    virtual std::string getName();
    virtual std::pair<int, int> getDefaultWindowSize();
    virtual std::string getResourcePath();

    virtual void init();
    virtual void deinit();
};

} // namespace platforms
} // namespace nxcraft
