#include "rwpch.h"

#include "wrap_Math.h"
#include "glm/glm.hpp"

#include "Rosewood/Maths/Structs.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "sol/sol.hpp"

namespace Rosewood
{

    const char* wrap_Math::Name = "Math";

    wrap_Math::wrap_Math(lua_State* L)
    {
        sol::state_view lua(L);

        { //VEC2
            auto vec2_mult_overloads = sol::overload(
                [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1*v2; },
                [](const glm::vec2& v1, float f) -> glm::vec2 { return v1*f; },
                [](float f, const glm::vec2& v1) -> glm::vec2 { return f*v1; }
            );
            auto vec2_div_overloads = sol::overload(
                [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1/v2; },
                [](const glm::vec2& v1, float f) -> glm::vec2 { return v1/f; }
            );
            auto vec2_addition = [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1+v2; };

            auto vec2_subtraction = [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1-v2; };

            lua.new_usertype<glm::vec2>("vec2",
                sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
                "x", &glm::vec2::x,
                "y", &glm::vec2::y,
                sol::meta_function::to_string, [](const glm::vec2& v) -> std::string { return "{ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " }"; },
                "add", vec2_addition,
                "sub", vec2_subtraction,
                "div", vec2_div_overloads,
                "mul", vec2_mult_overloads,
                "dot", [](const glm::vec2& v1, const glm::vec2& v2) -> float { return glm::dot(v1, v2); },
                "normalize", [](const glm::vec2& v) -> glm::vec2 { return glm::normalize(v); },
                "length", [](const glm::vec2& v) -> float { return glm::length(v); },
                "distance", [](const glm::vec2& v1, const glm::vec2& v2) -> float { return glm::distance(v1, v2); },
                sol::meta_function::addition, vec2_addition,
                sol::meta_function::subtraction, vec2_subtraction,
                sol::meta_function::division, vec2_div_overloads,
                sol::meta_function::multiplication, vec2_mult_overloads
            );
        }

        { //VEC3
            auto vec3_mult_overloads = sol::overload(
                [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1*v2; },
                [](const glm::vec3& v1, float f) -> glm::vec3 { return v1*f; },
                [](float f, const glm::vec3& v1) -> glm::vec3 { return f*v1; }
            );
            auto vec3_div_overloads = sol::overload(
                [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1/v2; },
                [](const glm::vec3& v1, float f) -> glm::vec3 { return v1/f; }
            );
            auto vec3_addition = [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1+v2; };

            auto vec3_subtraction = [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1-v2; };

            lua.new_usertype<glm::vec3>("vec3",
                sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
                "x", &glm::vec3::x,
                "y", &glm::vec3::y,
                "z", &glm::vec3::z,
                "r", &glm::vec3::x,
                "g", &glm::vec3::y,
                "b", &glm::vec3::z,
                sol::meta_function::to_string, [](const glm::vec3& v) -> std::string { return "{ " + std::to_string(v.x) + ", " + std::to_string(v.y)+ ", " + std::to_string(v.z) + " }"; },
                "add", vec3_addition,
                "sub", vec3_subtraction,
                "div", vec3_div_overloads,
                "mul", vec3_mult_overloads,
                "dot", [](const glm::vec3& v1, const glm::vec3& v2) -> float { return glm::dot(v1, v2); },
                "cross", [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return glm::cross(v1, v2); },
                "normalize", [](const glm::vec3& v) -> glm::vec3 { return glm::normalize(v); },
                "length", [](const glm::vec3& v) -> float { return glm::length(v); },
                "distance", [](const glm::vec3& v1, const glm::vec3& v2) -> float { return glm::distance(v1, v2); },
                sol::meta_function::addition, vec3_addition,
                sol::meta_function::subtraction, vec3_subtraction,
                sol::meta_function::division, vec3_div_overloads,
                sol::meta_function::multiplication, vec3_mult_overloads
            );
        }

        { //VEC4
            auto vec4_mult_overloads = sol::overload(
                [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1*v2; },
                [](const glm::vec4& v1, float f) -> glm::vec4 { return v1*f; },
                [](float f, const glm::vec4& v1) -> glm::vec4 { return f*v1; }
            );
            auto vec4_div_overloads = sol::overload(
                [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1/v2; },
                [](const glm::vec4& v1, float f) -> glm::vec4 { return v1/f; }
            );
            auto vec4_addition = [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1+v2; };

            auto vec4_subtraction = [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1-v2; };

            lua.new_usertype<glm::vec4>("vec4",
                sol::constructors<glm::vec4(), glm::vec4(float), glm::vec4(float, float, float, float)>(),
                "x", &glm::vec4::x,
                "y", &glm::vec4::y,
                "z", &glm::vec4::z,
                "w", &glm::vec4::w,
                "r", &glm::vec4::x,
                "g", &glm::vec4::y,
                "b", &glm::vec4::z,
                "a", &glm::vec4::w,
                sol::meta_function::to_string, [](const glm::vec4& v) -> std::string { return "{ " + std::to_string(v.x) + ", " + std::to_string(v.y)+ ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + " }"; },
                "add", vec4_addition,
                "sub", vec4_subtraction,
                "div", vec4_div_overloads,
                "mul", vec4_mult_overloads,
                "dot", [](const glm::vec4& v1, const glm::vec4& v2) -> float { return glm::dot(v1, v2); },
                "normalize", [](const glm::vec4& v) -> glm::vec4 { return glm::normalize(v); },
                "length", [](const glm::vec4& v) -> float { return glm::length(v); },
                "distance", [](const glm::vec4& v1, const glm::vec4& v2) -> float { return glm::distance(v1, v2); },
                sol::meta_function::addition, vec4_addition,
                sol::meta_function::subtraction, vec4_subtraction,
                sol::meta_function::division, vec4_div_overloads,
                sol::meta_function::multiplication, vec4_mult_overloads
            );
        }

        { //Transform
            lua.new_usertype<Transform>("Transform",
                sol::constructors<Transform(), Transform(glm::vec3, glm::vec3, glm::vec3)>(),
                "Position", &Transform::Position,
                "Rotation", &Transform::Rotation,
                "Scale",    &Transform::Scale
            );
        }
       
        { //Rect
            lua.new_usertype<Rect>("Rect",
                sol::constructors<Rect(glm::vec2, glm::vec2), Rect(float, float, float, float), 
                                Rect(float), Rect(glm::vec2)>(),
                "Position", sol::property(&Rect::Position, &Rect::SetPosition),
                "Size",     sol::property(&Rect::Size, &Rect::SetSize),
                "Left",     &Rect::Left,
                "Right",    &Rect::Right,
                "Top",      &Rect::Top,
                "Bottom",   &Rect::Bottom,
                "Width",    &Rect::Width,
                "Height",   &Rect::Height
            );
        }

        { //Circle
            lua.new_usertype<Circle>("Circle",
                sol::constructors<Circle(glm::vec2, float)>(),
                "Position", &Circle::Position,
                "Radius",   &Circle::Radius
            );
        }

        { //Ray2D
            lua.new_usertype<Ray2D>("Ray2D",
                sol::constructors<Ray2D(glm::vec2, glm::vec2)>(),
                "Position",  &Ray2D::Position,
                "Direction", &Ray2D::Direction
            );
        }

        auto lerp_mult_overloads = sol::overload(
            [](sol::table t, const glm::vec4& v1, const glm::vec4& v2, float f) -> glm::vec4 { return glm::mix(v1, v2, f); },
            [](sol::table t, const glm::vec3& v1, const glm::vec3& v2, float f) -> glm::vec3 { return glm::mix(v1, v2, f); },
            [](sol::table t, const glm::vec2& v1, const glm::vec2& v2, float f) -> glm::vec2 { return glm::mix(v1, v2, f); },
            [](sol::table t, float f1, float f2, float f) -> float { return glm::mix(f1, f2, f); }
        );
        auto clamp_mult_overloads = sol::overload(
            [](sol::table t, const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3) -> glm::vec4 { return glm::clamp(v1, v2, v3); },
            [](sol::table t, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) -> glm::vec3 { return glm::clamp(v1, v2, v3); },
            [](sol::table t, const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& v3) -> glm::vec2 { return glm::clamp(v1, v2, v3); },
            [](sol::table t, float f1, float f2, float f3) -> float { return glm::clamp(f1, f2, f3); }
        );
        auto min_mult_overloads = sol::overload(
            [](sol::table t, const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return glm::min(v1, v2); },
            [](sol::table t, const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return glm::min(v1, v2); },
            [](sol::table t, const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return glm::min(v1, v2); },
            [](sol::table t, float f1, float f2) -> float { return glm::min(f1, f2); }
        );
        auto max_mult_overloads = sol::overload(
            [](sol::table t, const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return glm::min(v1, v2); },
            [](sol::table t, const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return glm::min(v1, v2); },
            [](sol::table t, const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return glm::min(v1, v2); },
            [](sol::table t, float f1, float f2) -> float { return glm::min(f1, f2); }
        );
        lua["vmath"] = lua.create_table_with(
            "lerp",    lerp_mult_overloads,
            "clamp",   clamp_mult_overloads,
            "min",     min_mult_overloads,
            "max",     max_mult_overloads
        );

        
    }
}