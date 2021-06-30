#include "rwpch.h"

#include "wrap_Input.h"

#include "Rosewood/Input/Input.h"
#include "Rosewood/Input/KeyCodes.h"
#include "Rosewood/Input/MouseButtonCodes.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "sol/sol.hpp"

namespace Rosewood
{

    const char* wrap_Input::Name = "Input";

    wrap_Input::wrap_Input(lua_State* L)
    {
        sol::state_view lua(L);
        //KeyCodes
        {
            lua.new_enum( "Keys",
                "UNKNOWN",          KEY_UNKNOWN,
                "SPACE",            KEY_SPACE,
                "APOSTROPHE",       KEY_APOSTROPHE, 
                "COMMA",            KEY_COMMA, 
                "MINUS",            KEY_MINUS, 
                "PERIOD",           KEY_PERIOD, 
                "SLASH",            KEY_SLASH, 
                "0",                KEY_0,
                "1",                KEY_1,
                "2",                KEY_2,
                "3",                KEY_3,
                "4",                KEY_4,
                "5",                KEY_5,
                "6",                KEY_6,
                "7",                KEY_7,
                "8",                KEY_8,
                "9",                KEY_9,
                "SEMICOLON",        KEY_SEMICOLON, 
                "EQUAL",            KEY_EQUAL, 
                "A",                KEY_A,
                "B",                KEY_B,
                "C",                KEY_C,
                "D",                KEY_D,
                "E",                KEY_E,
                "F",                KEY_F,
                "G",                KEY_G,
                "H",                KEY_H,
                "I",                KEY_I,
                "J",                KEY_J,
                "K",                KEY_K,
                "L",                KEY_L,
                "M",                KEY_M,
                "N",                KEY_N,
                "O",                KEY_O,
                "P",                KEY_P,
                "Q",                KEY_Q,
                "R",                KEY_R,
                "S",                KEY_S,
                "T",                KEY_T,
                "U",                KEY_U,
                "V",                KEY_V,
                "W",                KEY_W,
                "X",                KEY_X,
                "Y",                KEY_Y,
                "Z",                KEY_Z,
                "LEFT_BRACKET ",    KEY_LEFT_BRACKET,
                "BACKSLASH",        KEY_BACKSLASH,
                "RIGHT_BRACKET",    KEY_RIGHT_BRACKET, 
                "GRAVE_ACCENT",     KEY_GRAVE_ACCENT, 
                "WORLD_1",          KEY_WORLD_1, 
                "WORLD_2",          KEY_WORLD_2, 
                "ESCAPE",           KEY_ESCAPE,
                "ENTER",            KEY_ENTER,
                "TAB",              KEY_TAB,
                "BACKSPACE",        KEY_BACKSPACE,
                "INSERT",           KEY_INSERT,
                "DELETE",           KEY_DELETE,
                "RIGHT",            KEY_RIGHT,
                "LEFT",             KEY_LEFT,
                "DOWN",             KEY_DOWN,
                "UP",               KEY_UP,
                "PAGE_UP",          KEY_PAGE_UP,
                "PAGE_DOWN",        KEY_PAGE_DOWN,
                "HOME",             KEY_HOME,
                "END",              KEY_END,
                "CAPS_LOCK",        KEY_CAPS_LOCK,
                "SCROLL_LOCK",      KEY_SCROLL_LOCK,
                "NUM_LOCK",         KEY_NUM_LOCK,
                "PRINT_SCREEN",     KEY_PRINT_SCREEN,
                "PAUSE",            KEY_PAUSE,
                "F1",               KEY_F1,
                "F2",               KEY_F2,
                "F3",               KEY_F3,
                "F4",               KEY_F4,
                "F5",               KEY_F5,
                "F6",               KEY_F6,
                "F7",               KEY_F7,
                "F8",               KEY_F8,
                "F9",               KEY_F9,
                "F10",              KEY_F10,
                "F11",              KEY_F11,
                "F12",              KEY_F12,
                "F13",              KEY_F13,
                "F14",              KEY_F14,
                "F15",              KEY_F15,
                "F16",              KEY_F16,
                "F17",              KEY_F17,
                "F18",              KEY_F18,
                "F19",              KEY_F19,
                "F20",              KEY_F20,
                "F21",              KEY_F21,
                "F22",              KEY_F22,
                "F23",              KEY_F23,
                "F24",              KEY_F24,
                "F25",              KEY_F25,
                "KP_0",             KEY_KP_0,
                "KP_1",             KEY_KP_1,
                "KP_2",             KEY_KP_2,
                "KP_3",             KEY_KP_3,
                "KP_4",             KEY_KP_4,
                "KP_5",             KEY_KP_5,
                "KP_6",             KEY_KP_6,
                "KP_7",             KEY_KP_7,
                "KP_8",             KEY_KP_8,
                "KP_9",             KEY_KP_9,
                "KP_DECIMAL",       KEY_KP_DECIMAL,
                "KP_DIVIDE",        KEY_KP_DIVIDE,
                "KP_MULTIPLY",      KEY_KP_MULTIPLY,
                "KP_SUBTRACT",      KEY_KP_SUBTRACT,
                "KP_ADD",           KEY_KP_ADD,
                "KP_ENTER",         KEY_KP_ENTER,
                "KP_EQUAL",         KEY_KP_EQUAL,
                "LEFT_SHIFT",       KEY_LEFT_SHIFT,
                "LEFT_CONTROL",     KEY_LEFT_CONTROL,
                "LEFT_ALT",         KEY_LEFT_ALT,
                "LEFT_SUPER",       KEY_LEFT_SUPER,
                "RIGHT_SHIFT",      KEY_RIGHT_SHIFT,
                "RIGHT_CONTROL",    KEY_RIGHT_CONTROL,
                "RIGHT_ALT",        KEY_RIGHT_ALT,
                "RIGHT_SUPER",      KEY_RIGHT_SUPER,
                "MENU",             KEY_MENU         
            );
        }

        //MouseButton Codes
        {
            lua.new_enum( "MouseButton",
                "1",        MOUSE_BUTTON_1,
                "2",        MOUSE_BUTTON_2,
                "3",        MOUSE_BUTTON_3,
                "4",        MOUSE_BUTTON_4,
                "5",        MOUSE_BUTTON_5,
                "6",        MOUSE_BUTTON_6,
                "7",        MOUSE_BUTTON_7,
                "8",        MOUSE_BUTTON_8,
                "LAST",     MOUSE_BUTTON_LAST,
                "LEFT",     MOUSE_BUTTON_LEFT,
                "RIGHT",    MOUSE_BUTTON_RIGHT,
                "MIDDLE",   MOUSE_BUTTON_MIDDLE
            );
        }

        auto ns = lua["Rosewood"].get_or_create<sol::table>();

        ns["Input"] = lua.create_table_with(
            "GetMouseX", &Input::GetMouseX,
            "GetMouseY", &Input::GetMouseY,
            "IsKeyPressed", wrap_Input::w_isKeyPressed,
            "IsMouseButtonPressed", wrap_Input::w_isMouseButtonPressed
        );
        
    }

    int wrap_Input::w_isKeyPressed(lua_State* L)
    {
        lua_pushboolean(L, Input::IsKeyPressed(lua_tointeger(L, -1)));
        return 1;
    }

    int wrap_Input::w_isMouseButtonPressed(lua_State* L)
    {
        lua_pushboolean(L, Input::IsMouseButtonPressed(lua_tointeger(L, -1)));
        return 1;
    }
}