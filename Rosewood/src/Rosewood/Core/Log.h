#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Rosewood
{
	class  Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetLuaLogger() { return s_LuaLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_LuaLogger;
	};

}

// Core log macros
#define RW_CORE_TRACE(...)    ::Rosewood::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RW_CORE_INFO(...)     ::Rosewood::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RW_CORE_WARN(...)     ::Rosewood::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RW_CORE_ERROR(...)    ::Rosewood::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RW_CORE_CRITICAL(...) ::Rosewood::Log::GetCoreLogger()->critical(__VA_ARGS__)
								
// Client log macros		
#define RW_TRACE(...)         ::Rosewood::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RW_INFO(...)          ::Rosewood::Log::GetClientLogger()->info(__VA_ARGS__)
#define RW_WARN(...)          ::Rosewood::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RW_ERROR(...)         ::Rosewood::Log::GetClientLogger()->error(__VA_ARGS__)
#define RW_CRITICAL(...)      ::Rosewood::Log::GetClientLogger()->critical(__VA_ARGS__)

// Lua log LUA_macros		
#define RW_LUA_TRACE(...)         ::Rosewood::Log::GetLuaLogger()->trace(__VA_ARGS__)
#define RW_LUA_INFO(...)          ::Rosewood::Log::GetLuaLogger()->info(__VA_ARGS__)
#define RW_LUA_WARN(...)          ::Rosewood::Log::GetLuaLogger()->warn(__VA_ARGS__)
#define RW_LUA_ERROR(...)         ::Rosewood::Log::GetLuaLogger()->error(__VA_ARGS__)
#define RW_LUA_CRITICAL(...)      ::Rosewood::Log::GetLuaLogger()->critical(__VA_ARGS__)