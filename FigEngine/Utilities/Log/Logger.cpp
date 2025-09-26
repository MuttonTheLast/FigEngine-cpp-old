#include "pch.h"
#include "Logger.h"
#include "quill/LogMacros.h"


namespace Fig
{
	std::shared_ptr<::quill::Sink> Logger::m_FileSink;
	std::shared_ptr<::quill::Sink> Logger::m_LogSink;

	::ankerl::unordered_dense::map< std::string_view, ::quill::Logger*> Logger::m_ConsoleLoggers;
	::ankerl::unordered_dense::map< std::string_view, ::quill::Logger*> Logger::m_FileLoggers;

	bool Logger::m_Debug = false;
	bool Logger::m_FileLogger = false;


	void Logger::Init(bool debug, bool fileLogger)
	{
		::quill::Backend::start();
		m_Debug = debug;
		m_FileLogger = fileLogger;
		if (fileLogger)
		{

			quill::RotatingFileSinkConfig cfg;
			cfg.set_overwrite_rolled_files(true);

			m_FileSink = quill::Frontend::create_or_get_sink<quill::RotatingFileSink>(
				"logs/log.txt",
				[]()
				{
					// See RotatingFileSinkConfig for more options
					quill::RotatingFileSinkConfig cfg;
					cfg.set_open_mode('w');
					cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
					cfg.set_rotation_max_file_size(1024 * 1024 * 5); // small value to demonstrate the example
					return cfg;
				}());

			m_FileLoggers.insert({ "App",
				::quill::Frontend::create_or_get_logger("App_File", m_FileSink) });
		}
		m_LogSink = ::quill::Frontend::create_or_get_sink<::quill::ConsoleSink>("console_sink");

		m_ConsoleLoggers.insert({ "App",
			::quill::Frontend::create_or_get_logger("App_Log", m_LogSink) });
		if (debug)
		{
			GetConsoleLogger("App")->set_log_level(::quill::LogLevel::TraceL3);
		}

	}

	::quill::Logger* Logger::GetFileLogger(std::string_view name)
	{
		if (auto it = m_FileLoggers.find(name); it != m_FileLoggers.end()) {
			return it->second;
		}
		return GetFileLogger("App");
	}

	::quill::Logger* Logger::GetConsoleLogger(std::string_view name)
	{
		if (auto it = m_ConsoleLoggers.find(name); it != m_ConsoleLoggers.end()) {
			return it->second;
		}
		return GetConsoleLogger("App");
	}
	void Logger::CreateLogger(std::string name, bool fileLogger)
	{
		if (fileLogger)
		{
			m_FileLoggers.insert({ name,
				::quill::Frontend::create_or_get_logger(name + "_File", m_FileSink) });
		}
		m_ConsoleLoggers.insert({ name,
			::quill::Frontend::create_or_get_logger(name + "_Log", m_LogSink) });
		if (m_Debug)
		{
			GetConsoleLogger(name)->set_log_level(::quill::LogLevel::TraceL3);
		}
	}
	void Logger::Info(std::string message, std::string_view loggerName, bool logTOFile)
	{

		if (m_FileLogger && logTOFile)
		{
			LOG_INFO(GetFileLogger(loggerName), "{}", message);
		}
		LOG_INFO(GetConsoleLogger(loggerName), "{}", message);
	}
	void Logger::Debug(std::string message, std::string_view loggerName)
	{
		LOG_DEBUG(GetConsoleLogger(loggerName), "{}", message);
	}
	void Logger::Warn(std::string message, std::string_view loggerName, bool logTOFile)
	{
		if (m_FileLogger && logTOFile)
		{
			LOG_WARNING(GetFileLogger(loggerName), "{}", message);
		}
		LOG_WARNING(GetConsoleLogger(loggerName), "{}", message);
	}
	void Logger::Error(std::string message, std::string_view loggerName, bool logTOFile)
	{
		if (m_FileLogger && logTOFile)
		{
			LOG_ERROR(GetFileLogger(loggerName), "{}", message);
		}
		LOG_ERROR(GetConsoleLogger(loggerName), "{}", message);
	}
	void Logger::Critical(std::string message, std::string_view loggerName, bool logTOFile)
	{
		if (m_FileLogger && logTOFile)
		{
			LOG_CRITICAL(GetFileLogger(loggerName), "{}", message);
		}
		LOG_CRITICAL(GetConsoleLogger(loggerName), "{}", message);
	}
}