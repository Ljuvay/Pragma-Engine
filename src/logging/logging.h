#ifndef LOGGING_H
#define LOGGING_H

#include <sstream>
#include <ostream>
#include <chrono>
#include <string>
#include <iostream>
#include <cstdint>
#include <optional>
#include <unordered_map>

namespace LOGGING
{
	struct logInstance
	{
		std::string name = "";
		std::optional<std::chrono::steady_clock::time_point> start = std::nullopt;
		std::optional<std::chrono::steady_clock::time_point> stop = std::nullopt;
	};

	class Logger
	{
	public:
		void createInstance(const std::string& lname);
		void stopInstance(const std::string& lname);
		void writeInstance(const std::string & lname);
		void writeAll();
	private:
		std::unordered_map<std::string, logInstance> m_instances;
	};

	inline double mstos(const double& ms) { return ms / 1000.0; }
	inline double stom(const double& s) { return s / 60.0; }
	inline double mtoh(const double& m) { return m / 60.0; }

	inline double timeDifference(const double& msBegin, const double& msEnd) { return msEnd - msBegin; }
	inline void outputReadable(const std::string& lname, const double& time);
}

#endif // !LOGGING_H
