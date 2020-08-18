#pragma once

#include <string>

namespace nc {

class Component {
    public:
    virtual std::string getName() = 0;

    virtual void onLoad() = 0;
    virtual void onUpdate() = 0;
    virtual void onUnload() = 0;
};

} // namespace nc
