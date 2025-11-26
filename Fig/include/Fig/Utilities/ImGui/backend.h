#pragma "once"

#include "imgui.h"

namespace Fig
{
    class ImGuiBackend
    {
    private:
        static ImGuiBackend* m_Instance;
    public:
        static ImGuiBackend* Instance();
        



    };
}
