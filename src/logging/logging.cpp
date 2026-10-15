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

	}

	//Outputting via io until file logs are made
	inline void outputReadable(const double& time)
	{
		const long long total = static_cast<long long>(time);
		const double frac = time - static_cast<double>(total);

		const long long hours = total / 3'600'000;
		const long long minutes = (total / 60'000) % 60;
		const long long seconds = (total / 1'000) % 60;
		const double millis = static_cast<double>(total % 1'000) + frac;

		std::cout << "Time: ";
		if (hours > 0) std::cout << hours << "h, ";
		if (hours > 0 || minutes > 0) std::cout << minutes << "m, ";
		if (total >= 1'000) std::cout << seconds << "s, ";
		std::cout << millis << "ms\n";
	}
}