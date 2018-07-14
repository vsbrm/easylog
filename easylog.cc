#include "easylog.h"

const char* default_file_name = "logfile.log";

namespace easylog
{

logger::logger()
{
	log_level = Lall;
}

logger::logger(const char *a_file_name, const char *a_default_place)
{
	log_level = Lall;
	default_place = (a_default_place != nullptr) ? a_default_place : "";
	log_file.open (a_file_name, std::fstream::out | std::fstream::app);
	if (!log_file.is_open()) {
		log_file.open (default_file_name, std::fstream::out | std::fstream::app);
		if (log_file.is_open()) {
			log_file << "can not open file: " << default_file_name << std::endl;
		} else {
			//throw "exception: can not open log file";
		}
	}
}

logger::~logger()
{
	if (log_file.is_open())
		log_file.close();
}

void logger::set_log_level (uint8_t a_log_level)
{
	log_level = a_log_level;
}

uint8_t logger::get_log_level () const
{
	return log_level;
}

void logger::write_log(const char *a_message, const char *a_level, const char *a_place)
{
	log_file << '<' << std::to_string(std::time(nullptr)) << "> ";
	if (a_level != nullptr)
		log_file << "[" << a_level << "]: ";
	log_file << ((a_place != nullptr) ? a_place : default_place)  << " - ";
	log_file << a_message;
	log_file << std::endl;
}

void logger::log_critical (const char *a_message, const char *a_place)
{
	if (a_message == nullptr)
		return;
	if (log_level | Lcritical)
		write_log(a_message, "crit", a_place);
}


void logger::log_error (const char *a_message, const char *a_place)
{
	if (a_message == nullptr)
		return;
	if (log_level | Lerror)
		write_log(a_message, "_err", a_place);
}

void logger::log_warning (const char *a_message, const char *a_place)
{
	if (a_message == nullptr)
		return;
	if (log_level | Lwarning)
		write_log(a_message, "warn", a_place);
}

void logger::log_info (const char *a_message, const char *a_place)
{
	if (a_message == nullptr)
		return;
	if (log_level | Linfo)
		write_log(a_message, "info", a_place);
}

void logger::log_trace (const char *a_message, const char *a_place)
{
	if (a_message == nullptr)
		return;
	if (log_level | Ltrace)
		write_log(a_message, "trce", a_place);
}

daily_logger::daily_logger(const char *a_dir_name, const char *a_default_place)
{
	default_place = (a_default_place != nullptr) ? a_default_place : "";
	dir_name = (a_dir_name != nullptr) ? a_dir_name : "./";
	std::string filename = dir_name + '/';
	std::time_t t = std::time(nullptr);
	std::tm tm_t = *localtime(&t);
	filename += std::to_string(tm_t.tm_year + 1900);
	filename += "-" + std::to_string(tm_t.tm_mon + 1);
	filename += "-" + std::to_string(tm_t.tm_mday) + ".log";
	log_file.open (filename, std::fstream::out | std::fstream::app);
	tm_t.tm_mday++;
	tm_t.tm_hour = 0;
	tm_t.tm_min = 0;
	tm_t.tm_sec = 0;
	tomorrow = mktime(&tm_t);
	// if (!log_file.is_open()) {
	// 	//throw "exception: can not open log file";
	// }

}

daily_logger::~daily_logger()
{

}


void daily_logger::write_log(const char *a_message, const char *a_level, const char *a_place)
{
	std::time_t t = std::time(nullptr);
	if (t >= tomorrow) {
		log_file.close();
		std::string filename = dir_name + '/';
		std::time_t t = std::time(nullptr);
		std::tm tm_t = *localtime(&t);
		filename += std::to_string(tm_t.tm_year + 1900);
		filename += "-" + std::to_string(tm_t.tm_mon + 1);
		filename += "-" + std::to_string(tm_t.tm_mday) + ".log";
		log_file.open (filename, std::fstream::out | std::fstream::app);
		tm_t.tm_mday++;
		tm_t.tm_hour = 0;
		tm_t.tm_min = 0;
		tm_t.tm_sec = 0;
		tomorrow = mktime(&tm_t);
	}
	log_file << '<' << std::to_string(t) << "> ";
	if (a_level != nullptr) {
		log_file << "[" << a_level << "]: ";
	}
	log_file << ((a_place != nullptr) ? a_place : default_place)  << " - ";
	log_file << a_message;
	log_file << std::endl;
}


one_run_logger::one_run_logger(const char *a_file_name, const char *a_default_place)
{
	default_place = (a_default_place != nullptr) ? a_default_place : "";
	log_file.open (a_file_name, std::fstream::out);
	if (!log_file.is_open()) {
		log_file.open (default_file_name, std::fstream::out);
		if (log_file.is_open()) {
			log_file << "can not open file: " << default_file_name << std::endl;
		} else {
			//throw "exception: can not open log file";
		}
	}
}

one_run_logger::~one_run_logger()
{

}

}
