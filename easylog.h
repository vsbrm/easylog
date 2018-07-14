#ifndef EASYLOG_H
#define EASYLOG_H

#include <fstream>
#include <ctime>
#include <string>
#include <cstdint>
/*
	log structure
	[timestamp] <Level>  place: "message";
*/

namespace easylog
{
const uint8_t Lcritical = 1;
const uint8_t Lerror = 2;
const uint8_t Lwarning = 4;
const uint8_t Linfo = 8;
const uint8_t Ltrace = 16;
const uint8_t Lall = Lcritical | Lerror | Lwarning | Linfo | Ltrace;

class logger
{
protected:
	uint8_t log_level;
	std::fstream log_file;
	virtual void write_log (const char *a_message, const char *a_level = nullptr,
								const char *a_place = nullptr);
	std::string default_place;
public:
	logger();
	logger(const char *a_file_name, const char *a_default_place = nullptr);
	virtual ~logger();

	void set_log_level (uint8_t a_log_level = Lall);
	uint8_t get_log_level () const;

	void log_critical (const char *a_message, const char *a_place = nullptr);
	void log_error (const char *a_message, const char *a_place = nullptr);
	void log_warning (const char *a_message, const char *a_place = nullptr);
	void log_info (const char *a_message, const char *a_place = nullptr);
	void log_trace (const char *a_message, const char *a_place = nullptr);
};

class daily_logger : public logger
{
private:
	std::time_t tomorrow;
	std::string dir_name;
	void write_log (const char *a_message, const char *a_level = nullptr,
		 						const char *a_place = nullptr);
public:
	daily_logger(const char *a_dir_name = nullptr, const char *a_default_place = nullptr);
	~daily_logger();
};

class one_run_logger : public logger
{
public:
	one_run_logger(const char *a_file_name, const char *a_default_place = nullptr);
	~one_run_logger();
};

}


#endif //EASYLOG_H
