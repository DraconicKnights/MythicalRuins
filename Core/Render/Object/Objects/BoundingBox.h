#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../Object.h"

namespace MythicalRuins {

    class BoundingBox : public Object {
    public:
        BoundingBox() {
            SetName("Bounding Box");
            IsTrigger = true;
        }

        void Render() override;
        void OnTrigger(Object* other) override;
        void OnTriggerEnter(Object *other);
    };

} // MythicalRuins

#endif //BOUNDINGBOX_H
