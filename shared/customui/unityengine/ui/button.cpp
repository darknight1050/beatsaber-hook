#include "../../customui.hpp"

namespace CustomUI::UnityEngine::UI {

    void Button::SetButtonText(std::string text){
        Component* localizer = GetComponentInChildren(il2cpp_utils::GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
        if(localizer != nullptr)
            Object::Destroy(localizer);
        TMPro::TextMeshProUGUI* tmpUGui = (TMPro::TextMeshProUGUI*)GetComponentInChildren(il2cpp_utils::GetSystemType("TMPro", "TextMeshProUGUI"));
        if (tmpUGui != nullptr)
            tmpUGui->set_text(text);
    }
}