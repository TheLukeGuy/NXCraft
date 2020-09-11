#pragma once

#include "../component.hpp"
#include "menu.hpp"

namespace nxcraft {
namespace game {

class LoadingScreen : public Component, public Menu {
    public:
    virtual std::string getName();

    virtual void onLoad();
    virtual void onUpdate();
    virtual void onUnload();
};

} // namespace game
} // namespace nxcraft
