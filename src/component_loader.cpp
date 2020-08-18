#include <algorithm>
#include "component_loader.hpp"

namespace nc {

void ComponentLoader::loadComponent(Component *component) {
    components.push_back(component);
    component->onLoad();
}

void ComponentLoader::unloadComponent(Component *component) {
    component->onUnload();
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
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

} // namespace nc
