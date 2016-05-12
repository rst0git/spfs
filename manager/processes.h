#ifndef __SPFS_MANAGER_PROCESSES_H
#define __SPFS_MANAGER_PROCESSES_H

struct spfs_info_s;

int get_pids_list(const char *tasks_file, char **list);
int collect_one_process(pid_t pid, struct spfs_info_s *info);

int iterate_pids_list_name(const char *pids_list, struct spfs_info_s *info,
			   int (*actor)(pid_t pid, struct spfs_info_s *info),
			   const char *actor_name);

#define __stringify(x...)     #x
#define stringify(x...)       __stringify(x)

#define iterate_pids_list(pids_list, info, actor)			\
	iterate_pids_list_name(pids_list, info, actor, stringify(actor))

int spfs_seize_processes(struct spfs_info_s *info);
int spfs_release_processes(struct spfs_info_s *info);

enum {
	NS_UTS,
	NS_MNT,
	NS_NET,
	NS_PID,
	NS_USER,
	NS_MAX
};

#define NS_UTS_MASK	(1 << NS_UTS)
#define NS_MNT_MASK	(1 << NS_MNT)
#define NS_NET_MASK	(1 << NS_NET)
#define NS_PID_MASK	(1 << NS_PID)
#define NS_USER_MASK	(1 << NS_USER)

#define NS_ALL_MASK	NS_UTS_MASK | NS_MNT_MASK | NS_NET_MASK |	\
			NS_PID_MASK | NS_USER_MASK

int open_ns(pid_t pid, const char *ns);
int set_namespaces(int *ns_fds, unsigned ns_mask);
int change_namespaces(pid_t pid, unsigned ns_mask, int *orig_ns_fds[]);
int close_namespaces(int *ns_fds);
int open_namespaces(pid_t pid, int *ns_fds);

struct replace_fd;

struct process_fd {
	struct list_head list;
	int spfs_fd;
	int real_fd;
};

struct process_map {
	struct list_head list;
	int map_fd;
	off_t start;
	off_t end;
};

struct process_info {
	struct list_head list;
	int pid;
	int fds_nr;
	int maps_nr;
	struct list_head fds;
	struct list_head maps;
	struct spfs_info_s *info;
};

#endif
