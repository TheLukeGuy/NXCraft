#include "rich_text.hpp"

namespace nc {
namespace protocol {

RichText::RichText(std::string translationKey) : translationKey(translationKey) {}

template <typename ...Args>
RichText::RichText(std::string translationKey, Args ...components) : RichText(translationKey) {
    (this->components.push_back(components), ...);
}

nlohmann::json RichText::toJson() {
    nlohmann::json json;
    json["translate"] = translationKey;
    json["with"] = nlohmann::json::array();

    for (Component component : components) {
        json["with"] += component.toJson();
    }

    return json;
}

std::string RichText::toString() {
    std::string string;
    for (Component component : components) {
        string += "§r" + component.toString();
    }
    return string;
}

RichText RichText::fromJson(nlohmann::json json) {
    RichText richText(json["translate"]);
    for (nlohmann::json component : json["with"]) {
        richText.components.push_back(Component::fromJson(component));
    }
    return richText;
}

RichText::Component::Component(
    std::string text
) : Component(text, false, false, false, false, false, "reset", "", {"", ""}, {"", ""}) {}

RichText::Component::Component(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated
) : Component(text, bolded, italicized, underlined, struckthrough, obfuscated, "reset", "", {"", ""}, {"", ""}) {}

RichText::Component::Component(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
    std::string color
) : Component(text, bolded, italicized, underlined, struckthrough, obfuscated, color, "", {"", ""}, {"", ""}) {}

RichText::Component::Component(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
    std::string color,
    std::string insertion
) : Component(text, bolded, italicized, underlined, struckthrough, obfuscated, color, insertion, {"", ""}, {"", ""}) {}

RichText::Component::Component(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
    std::string color, 
    std::string insertion,
    std::pair<std::string, std::string> clickEvent, std::pair<std::string, std::string> hoverEvent
) : text(text),
    bolded(bolded), italicized(italicized), underlined(underlined), struckthrough(struckthrough), obfuscated(obfuscated),
    color(color),
    insertion(insertion),
    clickEvent(clickEvent), hoverEvent(hoverEvent) {}

template <typename ...Args>
RichText::Component::Component(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
    std::string color, 
    std::string insertion,
    std::pair<std::string, std::string> clickEvent, std::pair<std::string, std::string> hoverEvent,
    Args ...extraComponents
) : Component(text, bolded, italicized, underlined, struckthrough, obfuscated, color, insertion, clickEvent, hoverEvent) {
    (this->extraComponents.push_back(extraComponents), ...);
}

nlohmann::json RichText::Component::toJson() {
    nlohmann::json json;
    json["text"] = text;

    json["bold"] = bolded;
    json["italic"] = italicized;
    json["underlined"] = underlined;
    json["strikethough"] = struckthrough;
    json["obfuscated"] = obfuscated;
    json["color"] = color;

    if (insertion != "") {
        json["insertion"] = insertion;
    }

    if (clickEvent.first != "") {
        json["clickEvent"] = {
            {"action", clickEvent.first},
            {"value", clickEvent.second}
        };
    }

    if (hoverEvent.first != "") {
        json["hoverEvent"] = {
            {"action", hoverEvent.first},
            {"value", hoverEvent.second}
        };
    }

    if (!extraComponents.empty()) {
        json["extra"] = nlohmann::json::array();
        for (Component component : extraComponents) {
            json["extra"] += component.toJson();
        }
    }

    return json;
}

RichText::Component RichText::Component::fromJson(nlohmann::json json) {
    RichText::Component component(json["text"]);

    if (json.contains("bold")) {
        component.bolded = json["bold"];
    }
    if (json.contains("italic")) {
        component.italicized = json["italicized"];
    }
    if (json.contains("underlined")) {
        component.underlined = json["underlined"];
    }
    if (json.contains("strikethrough")) {
        component.struckthrough = json["strikethrough"];
    }
    if (json.contains("obfuscated")) {
        component.obfuscated = json["obfuscated"];
    }
    if (json.contains("color")) {
        component.color = json["color"];
    }
    if (json.contains("insertion")) {
        component.insertion = json["insertion"];
    }

    if (json.contains("clickEvent")) {
        component.clickEvent = {
            json["clickEvent"]["action"],
            json["clickEvent"]["value"]
        };
    }

    if (json.contains("hoverEvent")) {
        component.hoverEvent = {
            json["hoverEvent"]["action"],
            json["hoverEvent"]["value"]
        };
    }

    if (json.contains("extra")) {
        for (nlohmann::json extraJson : json["extra"]) {
            Component extra = Component::fromJson(extraJson);
            component.extraComponents.push_back(extra);
        }
    }

    return component;
}

template RichText::RichText<RichText::Component>(std::string translationKey, RichText::Component components);

template RichText::Component::Component<RichText::Component>(
    std::string text,
    bool bolded, bool italicized, bool underlined, bool struckthrough, bool obfuscated,
    std::string color, 
    std::string insertion,
    std::pair<std::string, std::string> clickEvent, std::pair<std::string, std::string> hoverEvent,
    RichText::Component extraComponents
);

} // namespace protocol
} // namespace nc
