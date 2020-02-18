namespace CustomUI::UnityEngine {

    class Transform;
    class GameObject;

    class Component : public Object {
        public:
            PROPERTY_GET(transform, Transform*);
            PROPERTY_GET_SET(tag, std::string);
            PROPERTY_GET(gameObject, GameObject*);
    };

}