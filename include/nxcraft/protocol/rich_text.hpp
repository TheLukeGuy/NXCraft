#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace nxcraft {
namespace protocol {

class RichText {
    public:
    class Component {
        public:
        std::string text;

        bool bolded;
        bool italicized;
        bool underlined;
        bool struckthrough;
        bool obfuscated;
        
        std::string color;
        std::string insertion;

        std::pair<std::string, std::string> clickEvent;
        std::pair<std::string, std::string> hoverEvent;

        std::vector<Component> extraComponents;

        Component(std::string text);

        Component(
            std::string text,
            bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated
        );

        Component(
            std::string text,
            bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
            std::string color
        );

        Component(
            std::string text,
            bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
            std::string color,
            std::string insertion
        );

        Component(
            std::string text,
            bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
            std::string color, 
            std::string insertion,
            std::pair<std::string, std::string> clickEvent, std::pair<std::string, std::string> hoverEvent
        );

        template <typename ...Args>
        Component(
            std::string text,
            bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
            std::string color, 
            std::string insertion,
            std::pair<std::string, std::string> clickEvent, std::pair<std::string, std::string> hoverEvent,
            Args ...extraComponents
        );

        nlohmann::json toJson();
        std::string toString();

        static Component fromJson(nlohmann::json json);
        static Component fromString(std::string string);
    };

    std::string translationKey;
    std::vector<Component> components;

    RichText(std::string translationKey);
    template <typename ...Args>
    RichText(std::string translationKey, Args ...components);

    nlohmann::json toJson();
    std::string toString();

    static RichText fromJson(nlohmann::json json);
    static RichText fromString(std::string string);
};

} // namespace protocol
} // namespace nxcraft
