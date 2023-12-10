#ifndef CV1_OBJECTCOMPONENT_H
#define CV1_OBJECTCOMPONENT_H


class DrawableObject;
class ObjectComponent {
public:
    virtual void init(DrawableObject *object);

    virtual void beforeDraw(DrawableObject *object);

    virtual void afterDraw(DrawableObject *object);
};


#endif //CV1_OBJECTCOMPONENT_H
