# Easylog 0.1.0

Library provides classes which helps to write log files in text format.
Each log entrance has log level. Each log level can be turned on or off to make
log files look more clear.

## Log levels

* citical;
* error;
* warning;
* trace;
* info.

## Logger classes

* logger - simple log format;
* one run logger- rewrites old log file;
* daily logger - creates new log file every day in specified directory.

## Usage

Set up logger class to log into specified file and set default place.
If no default place specified default log place will be empty.

### Setup logger class

```c++
easylog::logger log("path/to/log/file", "default place");
easylog::one_run_logger r1_log("path/to/onerunlog/file");
easylog::daily_logger d_log("path/to/dir/with/log/files");
```
By default all messeasylog::one_run_logger r1_log("test_1r.log", "testplace default");
	easylog::daily_logger d_log("log", "testplace default");
ages would be written to file.
To mask some log messages ```set_log_level()``` method is used. Log levels can be or\`ed.
To get current log level ```get_log_level()``` is used.

```c++
log.set_log_level(log.get_log_level() | logger::Lcritical | logger::Ltrace);
```

### Constants specifying logging levels:

* Lall
* Lcritical
* Lerror
* Lwarning
* Linfo
* Ltrace

### Writing log messages

```c++
log.log_critical("critical message", "some info about place");
log.log_error("error");
log.log_warning("warning");
log.log_trace("trace");
log.log_info("info");
```

## Log file example

```
<timestamp>  [_lvl]: place - message
<1531655153> [crit]: some info about place - critical message
<1531655153> [_err]: default place - error
<1531655153> [warn]: - warning
<1531655153> [trce]: - trace
<1531655153> [info]: - info
```
