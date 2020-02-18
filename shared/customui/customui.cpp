// To use, simply add customui.cpp to your Android.mk, and #include customui.hpp
// CUSTOM UI

#include "../utils/utils.h"
#include "customui.hpp"
using namespace il2cpp_utils;
using namespace CustomUI::UnityEngine;
using namespace CustomUI::UnityEngine::UI;
using namespace CustomUI::TMPro;

namespace CustomUI
{   
    Button* CreateButton(){
        GameObject* gameObj = (GameObject*)NewUnsafe(GetClassFromName("UnityEngine", "GameObject"), createcsstr("CustomUICanvas"));
        gameObj->SetActive(false);
        gameObj->AddComponent(GetSystemType("UnityEngine", "CanvasRenderer"));
        Button* buttonComponent = (Button*)gameObj->AddComponent(GetSystemType("UnityEngine.UI", "Button"));
        Image* imageComponent = (Image*)gameObj->AddComponent(GetSystemType("UnityEngine.UI", "Image"));
        Array<Sprite*> *allSpriteObjects = (Array<Sprite*>*)Resources::FindObjectsOfTypeAll("UnityEngine", "Sprite");
        int match = -1;
        for (int i = 0; i < allSpriteObjects->Length(); i++)
        {
            if (strcmp(allSpriteObjects->values[i]->get_name().c_str(), "RoundRectNormal") == 0)
            {
                match = i;
                break;
            }
        }
        if (match == -1)
        {
            log(DEBUG, "CreateButton: Could not find matching Sprite!");
            return nullptr;
        }
        imageComponent->set_sprite(allSpriteObjects->values[match]);
        imageComponent->set_type(Image::Type::Sliced);
        buttonComponent->set_image(imageComponent);
        gameObj->SetActive(true);
        return buttonComponent;
    }

    TextMeshProUGUI* CreateTextMeshProUGUI(std::string text, UnityEngine::Transform* parentTransform, float fontSize, Color color){
        GameObject* gameObj = (GameObject*)NewUnsafe(GetClassFromName("UnityEngine", "GameObject"), createcsstr("CustomUITextMeshProUGUI"));
        gameObj->SetActive(false);
        Array<TMP_FontAsset*>* allFontObjects = (Array<TMP_FontAsset*>*)Resources::FindObjectsOfTypeAll("TMPro", "TMP_FontAsset");
        int fontMatch = -1;
        for (int i = 0; i < allFontObjects->Length(); i++)
        {
            if (strcmp(allFontObjects->values[i]->get_name().c_str(), "Teko-Medium SDF No Glow") == 0)
            {
                fontMatch = i;
                break;
            }
        }
        if (fontMatch == -1)
        {
            log(DEBUG, "CreateTextMeshProUGUI: Could not find matching TMP_FontAsset!");
            return nullptr;
        }
        TMP_FontAsset* font = (TMP_FontAsset*)Object::Instantiate(allFontObjects->values[fontMatch]);
        TextMeshProUGUI* textMeshComponent = (TextMeshProUGUI*)gameObj->AddComponent(GetSystemType("TMPro", "TextMeshProUGUI"));
        RectTransform* rectTransform = textMeshComponent->get_rectTransform();
        if(parentTransform != nullptr){
            textMeshComponent->get_rectTransform()->SetParent(parentTransform, false);
        }
        textMeshComponent->set_text(text);
        textMeshComponent->set_font(font);
        textMeshComponent->set_fontSize(fontSize);
        textMeshComponent->set_color(color);
        rectTransform->set_anchorMin({0.5f, 0.5f});
        rectTransform->set_anchorMax({0.5f, 0.5f});
        rectTransform->set_pivot({0.5f, 0.5f});
        rectTransform->set_sizeDelta({0.0f, 0.0f});
        rectTransform->set_anchoredPosition({0.0f, 0.0f});
        rectTransform->set_localScale({1.0f, 1.0f, 1.0f});
        gameObj->SetActive(true);
        return textMeshComponent;
    }

    static auto findDataSize(Il2CppObject* downloadHandler) {
        Array<uint8_t>* data;
        auto meth = il2cpp_utils::FindMethod("UnityEngine.Networking", "DownloadHandler", "InternalGetByteArray", 1);
        if (il2cpp_utils::RunMethod(&data, nullptr, meth, downloadHandler)) {
            return data->Length();
        }
        return 0;
    }

    void RawImageObject::monitorProgress(RawImageObject* obj) {
        log(ERROR, "MonitorProgress start");
        Il2CppObject* downloadHandler = il2cpp_utils::GetFieldValue(obj->WWW, "m_DownloadHandler");
        if (!downloadHandler) return;

        bool isDone = false;
        auto prevCap = findDataSize(downloadHandler);
        float prevProg = -1;
        std::vector<decltype(Array<int>::max_length)> recvLens;
        while (!isDone) {
            il2cpp_utils::RunMethod(&isDone, obj->WWW, "get_isDone");
            float prog;
            if (il2cpp_utils::RunMethod(&prog, obj->WWW, "GetDownloadProgress")) {
                if (prog != prevProg) {
                    auto dataLen = findDataSize(downloadHandler);
                    decltype(Array<int>::max_length) cap = std::round(((float)dataLen) / prog);
                    if (cap != prevCap || prog < prevProg) {
                        log(INFO, "prog is %i / %i", dataLen, cap);
                    }
                    log(INFO, "wrAsyncOp progress: %f (raw = 0x%llX)", prog, *reinterpret_cast<float**>(&prog));
                    prevProg = prog;
                    recvLens.push_back(dataLen);
                    prevCap = cap;
                }
            }

            std::chrono::nanoseconds nanoTime((long)round(500000L));
            std::this_thread::sleep_for(nanoTime);
        }
        std::stringstream ss;
        auto finalLen = findDataSize(downloadHandler);
        for (auto r : recvLens) {
            ss << ((float) r) / finalLen << " ";
        }
        ss << std::endl;
        log(INFO, "real progs (out of %i): %s", finalLen, ss.str().c_str());

        log(INFO, "webRequest isDone.");
        Il2CppString* str;
        if (RunMethod(&str, obj->WWW, "get_error")) {
            if (str != nullptr) {
                log(ERROR, "webRequest error: %s", to_utf8(csstrtostr(str)).c_str());
            } else {
                log(DEBUG, "webRequest had no error.");
            }
        }
    }

    bool RawImageObject::textureWebRequestComplete(RawImageObject* obj, Il2CppObject* asyncOp)
    {
        // Notes: The field named "<webRequest>k__BackingField" on asyncOp is a pointer that should match obj->WWW
        log(DEBUG, "Entering textureWebRequestComplete!");

        Il2CppObject *rawImageRectTransform;
        bool valueBool = false;

        if (RunMethod(&obj->recievedTexture2D, il2cpp_utils::GetClassFromName("UnityEngine.Networking", "DownloadHandlerTexture"), "GetContent", obj->WWW))
        {
            obj->gameObj = NewUnsafe(GetClassFromName("UnityEngine", "GameObject"), createcsstr("RandomImage"));
            if (!RunMethod(obj->gameObj, "SetActive", &valueBool))
            {
                log(DEBUG, "Failed to set gameObj active to false");
            }
            if (!RunMethod(&obj->rawImage, obj->gameObj, "AddComponent", GetSystemType("UnityEngine.UI", "RawImage")))
            {
                log(DEBUG, "Failed to AddComponent rawImage");
            }
            if (!RunMethod(obj->rawImage, "set_texture", obj->recievedTexture2D))
            {
                log(DEBUG, "Failed to set receivedTexture2D");
            }
            if (!RunMethod(&rawImageRectTransform, obj->rawImage, "get_rectTransform"))
            {
                log(DEBUG, "Failed to get rectTransform");
            }
            if (!RunMethod(rawImageRectTransform, "SetParent", obj->parentTransform, &valueBool))
            {
                log(DEBUG, "Failed to set Parent");
            }

            // textMesh.rectTransform.anchorMin = anchorMin
            log(DEBUG, "RawImageObject::textureWebRequestComplete: Setting anchorMin");
            if (!RunMethod(rawImageRectTransform, "set_anchorMin", &obj->anchorMin))
            {
                log(DEBUG, "RawImageObject::textureWebRequestComplete: Failed to set anchorMin");
                return false;
            }

            // textMesh.rectTransform.anchorMax = anchorMax
            log(DEBUG, "RawImageObject::textureWebRequestComplete: Setting anchorMax");
            if (!RunMethod(rawImageRectTransform, "set_anchorMax", &obj->anchorMax))
            {
                log(DEBUG, "RawImageObject::textureWebRequestComplete: Failed to set anchorMax");
                return false;
            }

            // textMesh.rectTransform.sizeDelta = sizeDelta
            log(DEBUG, "RawImageObject::textureWebRequestComplete: Setting sizeDelta");
            if (!RunMethod(rawImageRectTransform, "set_sizeDelta", &obj->sizeDelta))
            {
                log(DEBUG, "RawImageObject::textureWebRequestComplete: Failed to set sizeDelta");
                return false;
            }

            // textMesh.rectTransform.anchoredPosition = anchoredPosition
            log(DEBUG, "RawImageObject::textureWebRequestComplete: Setting anchoredPosition");
            if (!RunMethod(rawImageRectTransform, "set_anchoredPosition", &obj->anchoredPosition))
            {
                log(DEBUG, "RawImageObject::textureWebRequestComplete: failed to set anchoredPosition");
                return false;
            }
            valueBool = true;
            if (!RunMethod(obj->gameObj, "SetActive", &valueBool))
            {
                log(DEBUG, "Failed to set gameObj active to true");
                return false;
            }
        } else {
            log(DEBUG, "Failed to get recievedTexture2D from DownloadHandler!");
            return false;
        }
        log(INFO, "Callback success!");
        // TODO: if debug, play a sound?
        return true;
    }

    bool RawImageObject::create()
    {
        auto getTextureMethod = FindMethod("UnityEngine.Networking", "UnityWebRequestTexture", "GetTexture", "System", "String");
        if (!getTextureMethod) return false;

        if (!RunMethod(&WWW, nullptr, getTextureMethod, createcsstr(url))) {
            log(ERROR, "Failed to run UnityWebRequestTexture.GetTexture!");
            return false;
        }

        // If only we could use UnityEngine.WWW and its WaitUntilDoneIfPossible() :(
        auto method = il2cpp_utils::FindMethod("UnityEngine.Networking", "UnityWebRequestAsyncOperation", "add_completed", 1);
        if (!method) return false;
        auto fieldType = il2cpp_functions::method_get_param(method, 0);

        if (!RunMethod(&sendWebRequestObj, WWW, "SendWebRequest")) {
            log(ERROR, "Failed to SendWebRequest");
            return false;
        }

        auto action = il2cpp_utils::MakeAction(this, textureWebRequestComplete, fieldType);
        if (action == nullptr) {
            log(ERROR, "Couldn't make textureWebRequestComplete Action");
            return false;
        }
        if (!il2cpp_utils::RunMethod(sendWebRequestObj, method, action)) {
            log(ERROR, "Couldn't set textureWebRequestComplete Action");
            return false;
        }

        // Uncomment this to watch the progress for debugging purposes (backtracks a lot):
        // StartCoroutine(monitorProgress, this);

        return true;
    }

} // namespace CustomUI