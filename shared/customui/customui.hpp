#ifndef CUSTOMUI_DEFINED
#define CUSTOMUI_DEFINED

#include <string.h>
#include "../utils/utils.h"
#include "methodwrapper.hpp"
#include "unityengine/object.hpp"
#include "unityengine/gameobject.hpp"
#include "unityengine/component.hpp"
#include "unityengine/transform.hpp"
#include "unityengine/recttransform.hpp"
#include "unityengine/material.hpp"
#include "unityengine/sprite.hpp"
#include "unityengine/scriptableobject.hpp"
#include "unityengine/behaviour.hpp"
#include "unityengine/monobehaviour.hpp"
#include "unityengine/canvas.hpp"

#include "unityengine/eventsystems/uibehaviour.hpp"

#include "unityengine/ui/selectable.hpp"
#include "unityengine/ui/button.hpp"
#include "unityengine/ui/canvasscaler.hpp"
#include "unityengine/ui/graphic.hpp"
#include "unityengine/ui/maskablegraphic.hpp"
#include "unityengine/ui/image.hpp"

#include "tmpro/tmp_asset.hpp"
#include "tmpro/tmp_fontasset.hpp"
#include "tmpro/tmp_text.hpp"
#include "tmpro/textmeshprougui.hpp"

#include "unityengine/resources.hpp"

namespace CustomUI {

    UnityEngine::Canvas* CreateCanvas();
    UnityEngine::UI::Button* CreateButton(Vector2 size, UnityEngine::Transform* parentTransform);
    UnityEngine::UI::Button* CreateUIButton(UnityEngine::Transform* parentTransform, std::string buttonTemplate, Vector2 anchoredPosition, Vector2 size, std::string buttonText = "BUTTON");
    TMPro::TextMeshProUGUI* CreateTextMeshProUGUI(std::string text, UnityEngine::Transform* parentTransform = nullptr, float fontSize = 12.0f, Color color = {1.0, 1.0, 1.0, 1.0});

    // Except where mentioned, original code by Rugtveit and only slight modifications by zoller27osu.
    class RawImageObject : public Il2CppObject {
        private:
            // This counter increments every time a CustomUIRawImage object is created by the same mod.
            static int counter;
            // This is the name prefix of the CustomUIRawImage object. It has the counter appended to it.
            std::string name = "CustomUIRawImage";
            // This is the texture2D object.
            Il2CppObject *recievedTexture2D;
            // This is the WebRequest object. Used throughout the create to create texture2D used in rawImage.
            Il2CppObject *WWW;
            // This is the SendWebRequest object. We use callback in SendWebRequest to create an action that is called whenever we get the response back.
            Il2CppObject *sendWebRequestObj;

        public:
            // The RawImage Il2CppObject* of the created object.
            Il2CppObject *rawImage = nullptr;
            // The GameObject Il2CppObject* of the created object.
            Il2CppObject *gameObj = nullptr;
            // The desired Color of the rawImage object.
            Color color = {1.0, 1.0, 1.0, 1.0};
            // The desired parent transform of the rawImage object.
            Il2CppObject *parentTransform = nullptr;
            // The desired anchorMin position of the rawImage object.
            Vector2 anchorMin = {0.5, 0.5};
            // The desired anchorMax position of the rawImage object.
            Vector2 anchorMax = {0.5, 0.5};
            // The desired sizeDelta position of the rawImage object.
            Vector2 sizeDelta = {0.0, 0.0};
            // The desired anchoredPosition of the rawImage object.
            Vector2 anchoredPosition = {0.0, 0.0};
            // The desired url of the rawImage object;
            std::string url = "!NoUrl!";
            // Monitors and logs the download progress. Will block the thread it is run in!
            // Written by zoller27osu.
            static void monitorProgress(RawImageObject* obj);
            // Creates the rawImage object in game.
            // Returns true on success, false otherwise.
            static bool textureWebRequestComplete(RawImageObject* obj, Il2CppObject* asyncOp);
            bool create();
    };
} // namespace CustomUI

#endif /* CUSTOMUI_DEFINED */
