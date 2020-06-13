#include "rwpch.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGL.h"

namespace Rosewood
{
	
    Graphics::API Graphics::s_API = Graphics::API::OpenGL;

    Scope<Graphics> Graphics::Create()
    {
        switch (s_API)
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None API is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateScope<OpenGL>();
        }

        RW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
