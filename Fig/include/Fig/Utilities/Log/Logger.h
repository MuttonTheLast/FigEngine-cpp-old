#pragma once

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/Logger.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/RotatingFileSink.h"
#include <string_view>
#include "Fig/Utilities/HashMap/ankerl/unordered_dense.h"

namespace Fig
{
	class Logger
	{
	public:
		static void Init(bool debug = false, bool fileLogger = true);
		static ::quill::Logger* GetFileLogger(std::string_view name);
		static ::quill::Logger* GetConsoleLogger(std::string_view name);

		static void CreateLogger(std::string name, bool fileLogger = false);

		static void Info(std::string message, std::string_view loggerName, bool logTOFile = false);
		static void Debug(std::string message, std::string_view loggerName);
		static void Warn(std::string message, std::string_view loggerName, bool logTOFile = false);
		static void Error(std::string message, std::string_view loggerName, bool logTOFile = false);
		static void Critical(std::string message, std::string_view loggerName, bool logTOFile = false);

	private:
		static std::shared_ptr<::quill::Sink> m_FileSink;
		static std::shared_ptr<::quill::Sink> m_LogSink;

		static ::ankerl::unordered_dense::map< std::string_view, ::quill::Logger*> m_ConsoleLoggers;
		static ::ankerl::unordered_dense::map< std::string_view, ::quill::Logger*> m_FileLoggers;

		static bool m_Debug;
		static bool m_FileLogger;
	};
}
