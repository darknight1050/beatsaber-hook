// To use, simply add customui.cpp to your Android.mk, and #include customui.hpp
// CUSTOM UI

#include "../utils/utils.h"
#include "../utils/utils-functions.h"
#include "customui.hpp"

using namespace il2cpp_utils;

int CustomUI::TextObject::counter = 0;
namespace CustomUI
{
    bool TextObject::create()
    {
        // gameobj = new GameObject("CustomTextUI");
        log(DEBUG, "TextObject::create: Creating gameObject: %s (object number: %i)", name.data(), counter);
        gameObj = NewUnsafe(GetClassFromName("UnityEngine", "GameObject"), createcsstr(name.data()));

        // gameObj.SetActive(false);
        bool active = false;
        log(DEBUG, "TextObject::create: Setting gameObject.active to false");
        if (!RunMethod(gameObj, "SetActive", &active))
        {
            log(DEBUG, "TextObject::create: Failed to set active to false");
            return false;
        }

        // gameObj.AddComponent<TextMeshProUGUI>();
        log(DEBUG, "TextObject::create: Getting type of TMPro.TextMeshProUGUI");
        Il2CppObject *type_tmpugui = GetSystemType(GetClassFromName("TMPro", "TextMeshProUGUI"));
        
        log(DEBUG, "TextObject::create: Adding component TMPro.TextMeshProUGUI");
        if (!RunMethod(&textMesh, gameObj, "AddComponent", type_tmpugui))
        {
            log(DEBUG, "TextObject::create: Failed to add Component TMPro.TextMeshProUGUI");
            return false;
        }
        // textMesh.font = GameObject.Instantiate(Resources.FindObjectsOfTypeAll<TMP_FontAsset>().First(t => t.name == "Teko-Medium SDF No Glow"));
        log(DEBUG, "TextObject::create: Getting type of TMPro.TMP_FontAsset");
        Il2CppObject *type_fontasset = GetSystemType(GetClassFromName("TMPro", "TMP_FontAsset"));
        log(DEBUG, "TextObject::create: Gotten the type!");
        Array<Il2CppObject *> *allObjects;

        // Find Objects of type TMP_fontAsset
        if (!RunMethod(&allObjects, nullptr, FindMethod("UnityEngine", "Resources", "FindObjectsOfTypeAll", 1), type_fontasset))
        {
            // EXCEPTION
            log(DEBUG, "TextObject::create: Failed to Find Objects of type TMP_fontAsset");
            return false;
        }
        int match = -1;
        for (int i = 0; i < allObjects->Length(); i++)
        {
            // Treat it as a UnityEngine.Object (which it is) and call the name getter
            Il2CppString *assetName;
            if (!RunMethod(&assetName, allObjects->values[i], "get_name"))
            {
                // EXCEPTION
                log(DEBUG, "TextObject::create: Failed to run get_name of assetName");
                return false;
            }
            if (strcmp(to_utf8(csstrtostr(assetName)).c_str(), "Teko-Medium SDF No Glow") == 0)
            {
                // Found matching asset
                match = i;
                break;
            }
        }
        if (match == -1)
        {
            log(DEBUG, "TextObject::create: Could not find matching TMP_FontAsset!");
            return false;
        }

        // Instantiating the font
        log(DEBUG, "TextObject::create: Instantiating the font");
        Il2CppObject *font;
        if (!RunMethod(&font, nullptr, FindMethod("UnityEngine", "Object", "Instantiate", 1), allObjects->values[match]))
        {
            log(DEBUG, "TextObject::create: Failed to Instantiate font!");
            return false;
        }

        // Setting the font
        log(DEBUG, "TextObject::create: Setting the font");
        if (!RunMethod(textMesh, "set_font", font))
        {
            log(DEBUG, "TextObject::create: Failed to set font!");
            return false;
        }

        // textMesh.rectTransform.SetParent(parent, false);
        log(DEBUG, "TextObject::create: Getting rectTransform");
        Il2CppObject *rectTransform;
        if (!RunMethod(&rectTransform, textMesh, "get_rectTransform"))
        {
            log(DEBUG, "TextObject::create: Failed to get rectTransform");
            return false;
        }
        
        log(DEBUG, "TextObject::create: Setting Parent");
        bool value = false;
        if (!RunMethod(rectTransform, "SetParent", parentTransform, &value))
        {
            log(DEBUG, "TextObject::create: Failed to set parent!");
            if (parentTransform == nullptr)
            {
                log(DEBUG, "TextObject::create: parentTransform is null! Fix it!");
            }
            return false;
        }
        // textMesh.text = text;
        log(DEBUG, "TextObject::create: Setting Text");
        if (!RunMethod(textMesh, "set_text", createcsstr(text.data())))
        {
            log(DEBUG, "TextObject::create: Failed to set text!");
            return false;
        }

        // textmesh.fontSize = fontSize;
        log(DEBUG, "TextObject::create: Setting fontSize");
        if (!RunMethod(textMesh, "set_fontSize", &fontSize))
        {
            log(DEBUG, "TextObject::create: Failed to set fontSize!");
            return false;
        }

        // textMesh.color = Color.white;
        log(DEBUG, "TextObject::create: Setting color");
        if (!RunMethod(textMesh, "set_color", &color))
        {
            log(DEBUG, "TextObject::create: Failed to set color!");
            return false;
        }
    
        // textMesh.rectTransform.anchorMin = anchorMin
        log(DEBUG, "TextObject::create: Setting anchorMin");
        if (!RunMethod(rectTransform, "set_anchorMin", &anchorMin))
        {
            log(DEBUG, "TextObject::create: Failed to set anchorMin");
            return false;
        }

        // textMesh.rectTransform.anchorMax = anchorMax
        log(DEBUG, "TextObject::create: Setting anchorMax");
        if (!RunMethod(rectTransform, "set_anchorMax", &anchorMax))
        {
            log(DEBUG, "TextObject::create: Failed to set anchorMax");
            return false;
        }
        
        // textMesh.rectTransform.sizeDelta = sizeDelta
        log(DEBUG, "TextObject::create: Setting sizeDelta");
        if (!RunMethod(rectTransform, "set_sizeDelta", &sizeDelta))
        {
            log(DEBUG, "TextObject::create: Failed to set sizeDelta");
            return false;
        }

        // textMesh.rectTransform.anchoredPosition = anchoredPosition
        log(DEBUG, "TextObject::create: Setting anchoredPosition");
        if (!RunMethod(rectTransform, "set_anchoredPosition", &anchoredPosition))
        {
            log(DEBUG, "TextObject::create: failed to set anchoredPosition");
            return false;
        }

        // gameObj.SetActive(true);
        log(DEBUG, "TextObject::create: Setting gameObject active to true");
        active = true;
        if (!RunMethod(gameObj, "SetActive", &active))
        {
            log(DEBUG, "TextObject::create: Failed to set active to true");
            return false;
        }
        log(DEBUG, "TextObject::create: Succesfully created gameObj: %s", name.c_str());
        counter++;
        return true;
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
            if (!RunMethod(&obj->rawImage, obj->gameObj, "AddComponent", GetSystemType(GetClassFromName("UnityEngine.UI", "RawImage"))))
            {
                log(DEBUG, "Failed to AddComponent rawImage");
            }
            if (!RunMethod(obj->rawImage, "set_texture", obj->recievedTexture2D))
            {
                log(DEBUG, "Failed to set recievedTexture2D");
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
        usleep(100);
        // TODO: if debug, play a sound or sound-making menu transition?
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
