#pragma once

#include "Fig/Utilities/GLMath.h"
namespace Fig
{



    // Example concrete vertex type
    struct PositionColorVertex {
        Vector3 Position;
        Vector3 Color;
    };

    struct PositionUVVertex
    {
        Vector3 Position;
        Vector2 UV;
    };

}
