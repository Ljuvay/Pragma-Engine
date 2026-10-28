#include "logging.h"

namespace LOGGING
{
	void Logger::createInstance(const std::string& lname)
	{
		if (m_instances.contains(lname))
		{
			std::cerr << "Logger Already contains instance: " << lname << std::endl;
			return;
		}
		logInstance inst;
		inst.name = lname;
		inst.start = std::chrono::steady_clock::now();
		m_instances[lname] = inst;
	}

	void Logger::stopInstance(const std::string& lname)
	{
		if (!m_instances.contains(lname))
		{
			std::cerr << "Logger cannot close unexistant instance: " << lname << std::endl;
			return;
		}
		m_instances[lname].stop = std::chrono::steady_clock::now();
	}

	void Logger::writeInstance(const std::string& lname)
	{
		if (!m_instances.contains(lname))
		{
			std::cerr << "Logger cannot write unexistant instance: " << lname << std::endl;
			return;
		}
		if (m_instances[lname].start == std::nullopt || m_instances[lname].stop == std::nullopt)
		{
			std::cerr << "Logger cannot write unfinished instance: " << lname << std::endl;
			return;
		}
		auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(m_instances[lname].stop.value() - m_instances[lname].start.value()).count();
		outputReadable(lname, timeDifference);
	}

	void Logger::writeAll()
	{
		for (const auto& [key, value] : m_instances)
		{
			if(m_instances[key].start != std::nullopt && m_instances[key].stop != std::nullopt)
			{ 
				auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(m_instances[key].stop.value() - m_instances[key].start.value()).count();
				outputReadable(key, timeDifference);
			}
		}
	}

	//Outputting via io until file logs are made
	inline void outputReadable(const std::string& lname, const double& time)
	{
		const long long total = static_cast<long long>(time);
		const double frac = time - static_cast<double>(total);

		const long long hours = total / 3'600'000;
		const long long minutes = (total / 60'000) % 60;
		const long long seconds = (total / 1'000) % 60;
		const double millis = static_cast<double>(total % 1'000) + frac;

		std::cout << "[LOG] " << lname << " | "; 
		if (hours > 0) std::cout << hours << "h, ";
		if (hours > 0 || minutes > 0) std::cout << minutes << "m, ";
		if (total >= 1'000) std::cout << seconds << "s, ";
		std::cout << millis << "ms";
		std::cout << " | " << std::setprecision(3) << std::fixed << time / 1'000 << "s" << std::endl;
	}
}