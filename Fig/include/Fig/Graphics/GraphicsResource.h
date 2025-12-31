#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
namespace Fig{
    class GraphicsResource
    {
    public:
        GraphicsResource(GraphicsDevice* gd);

        virtual void Dispose() = 0;

    protected:
        GraphicsDevice* m_GraphicsDevice;
        bool m_Disposed = false; // To track if the resource has been disposed
    };
}
