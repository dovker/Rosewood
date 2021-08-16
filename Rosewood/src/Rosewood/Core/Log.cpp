#include "rwpch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Rosewood
{

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_LuaLogger;


	void Log::Init()
	{
        
		spdlog::set_pattern("[%L]%^[%T] %n: %v%$");
		
		
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		spdlog::set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		spdlog::set_level(spdlog::level::trace);
	
		s_LuaLogger = spdlog::stdout_color_mt("LUA");
		spdlog::set_level(spdlog::level::trace);
		
	}
}
