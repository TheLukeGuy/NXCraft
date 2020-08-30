#pragma once

#include <vector>
#include <string>

#include "component.hpp"

namespace nxcraft {

class ComponentLoader {
    public:
    static std::vector<Component *> components;

    static void loadComponent(Component *component);

    static void unloadComponent(Component *component);
    static void unloadComponent(std::string name);

    static Component * getComponentByName(std::string name);
};

} // namespace nxcraft
