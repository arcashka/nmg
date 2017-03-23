#include "Transform3D.h"

const QMatrix4x4 &Transform3D::toMatrix()
{
    if (dirty)
    {
        dirty = false;
        world.setToIdentity();
        world.translate(translation);
        world.rotate(rotation);
        world.scale(scale);
    }
    return world;
}
