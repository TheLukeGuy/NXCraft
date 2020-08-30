#pragma once

#include <string>

namespace nxcraft {

class Component {
    public:
    virtual std::string getName() = 0;

    virtual void onLoad() = 0;
    virtual void onUpdate() = 0;
    virtual void onUnload() = 0;
};

} // namespace nxcraft
