#include "component_loader.hpp"

#include <iostream>
#include <algorithm>

namespace nxcraft {

std::vector<Component *> ComponentLoader::components = {};

void ComponentLoader::loadComponent(Component *component) {
    components.push_back(component);
    component->onLoad();
    std::cout << "[*] Loaded component " << component->getName() << ".\n";
}

void ComponentLoader::unloadComponent(Component *component) {
    component->onUnload();
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
    std::cout << "[*] Unloaded component " << component->getName() << ".\n";
}

void ComponentLoader::unloadComponent(std::string name) {
    Component *component = getComponentByName(name);
    unloadComponent(component);
}

Component * ComponentLoader::getComponentByName(std::string name) {
    for (Component *component : components) {
        if (component->getName() == name) {
            return component;
        }
    }
    return nullptr;
}

} // namespace nxcraft
