#ifndef __SPFS_LOG_H_
#define __SPFS_LOG_H_

#include <stdio.h>
#include <sys/syslog.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <syscall.h>

static inline pid_t gettid(void)
{
	return syscall(SYS_gettid);

}

#define pr_emerg(fmt, ...)			\
	print_on_level(LOG_EMERG,		\
			"EMERG : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_alert(fmt, ...)			\
	print_on_level(LOG_ALERT,		\
			"ALERT : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_crit(fmt, ...)			\
	print_on_level(LOG_CRIT,		\
			"CRIT  : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_err(fmt, ...)			\
	print_on_level(LOG_ERR,			\
			"ERROR : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_warn(fmt, ...)			\
	print_on_level(LOG_WARNING,		\
			"WARN  : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_notice(fmt, ...)			\
	print_on_level(LOG_NOTICE,		\
			"NOTICE: %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_info(fmt, ...)			\
	print_on_level(LOG_INFO,		\
			"INFO  : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_debug(fmt, ...)			\
	print_on_level(LOG_DEBUG,		\
			"DEBUG : %d: "fmt, gettid(), ##__VA_ARGS__)

#define pr_perror(fmt, ...)			\
({						\
	int _errno = errno;			\
        print_on_level(LOG_ERR,			\
                       "ERROR : %d: "fmt": %d\n", gettid(),	\
		       ##__VA_ARGS__, errno);	\
	errno = _errno;				\
})

int print_on_level_va(unsigned int level, const char *format, va_list args);
int print_on_level(unsigned int level, const char *format, ...);

void set_log_level(FILE *log, int level);
int setup_log(const char *log_file, int verbosity);

#endif
