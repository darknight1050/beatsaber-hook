namespace CustomUI::UnityEngine::UI {

    class Image;
    
    class Selectable : public EventSystems::UIBehaviour {
        public:
            PROPERTY_GET_SET(hasSelection, bool);
            PROPERTY_GET_SET(image, Image*);
            PROPERTY_GET_SET(interactable, bool);
    };

}