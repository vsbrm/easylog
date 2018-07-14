#include "easylog.h"
#include <string>

int main(int argc, char const *argv[])
{
	easylog::logger log("test.log", "testplace default");
	easylog::one_run_logger r1_log("test_1r.log", "testplace default");
	easylog::daily_logger d_log("log", "testplace default");

	for (auto i = 0; i < 100; ++i) {
		log.log_critical((std::string("test critical") + std::to_string(i)).c_str());
		log.log_error("test error");
		log.log_warning("test warning");
		log.log_trace("test trace");
		log.log_info("info");

		log.log_critical("test critical", "testplace c");
		log.log_error("test error", "testplace e");
		log.log_warning("test warning", "testplace w");
		log.log_trace("test trace", "testplace t");
		log.log_info("info", "info place");

		r1_log.log_critical((std::string("test critical") + std::to_string(i)).c_str());
		r1_log.log_error("test error");
		r1_log.log_warning("test warning");
		r1_log.log_trace("test trace");
		r1_log.log_info("info");

		r1_log.log_critical("test critical", "testplace c");
		r1_log.log_error("test error", "testplace e");
		r1_log.log_warning("test warning", "testplace w");
		r1_log.log_trace("test trace", "testplace t");
		r1_log.log_info("info", "info place");

		d_log.log_critical((std::string("test critical") + std::to_string(i)).c_str());
		d_log.log_error("test error");
		d_log.log_warning("test warning");
		d_log.log_trace("test trace");
		d_log.log_info("info");

		d_log.log_critical("test critical", "testplace c");
		d_log.log_error("test error", "testplace e");
		d_log.log_warning("test warning", "testplace w");
		d_log.log_trace("test trace", "testplace t");
		d_log.log_info("info", "info place");
	}
	return 0;
}
