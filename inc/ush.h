#ifndef _USH_H_
#define _USH_H_

#include "../libmx/inc/libmx.h"

#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <termios.h>
#include <signal.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/param.h>

#define _GNU_SOURCE
#define _SVID_SOURCE
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500 
#define TILDA "~\0"

struct s_global
{
    char* PWD;
    char* OLDPWD;
    char* HOME;
    int exit_status;
    char* PATH;
}      t_global;

typedef struct s_jobs
{
    int pid;
    int job_id;
    char* cmd;
    struct s_jobs* next;
    struct s_jobs* prev;
}      t_jobs;

typedef struct s_flags_cd
{
    int flag_s;
    int flag_P;
}              t_flags_cd;

typedef struct s_flags_echo
{
    int flag_N;
    int flag_e;
    int flag_E;
}              t_flags_echo;

typedef struct s_flags_env
{
    int flag_I;
    int flag_U;
    int flag_P;
}              t_flags_env;

typedef struct s_flags_pwd
{
    int flag_L;
    int flag_P;
}              t_flags_pwd;

typedef struct s_flags_which
{
    int flag_A;
    int flag_S;
}              t_flags_which;

extern char **environ;
void init_global_own(void);
void free_global_own(void);
void replace_tilda_own(char **str);
int cmd_substitution_own(char **str);
void escape_sequences(char ***arr);
void create_process_own(char *command, char **parameters, char *cmd);

t_jobs *jobs;
t_jobs * jobs_create(int pid, char *cmd);
void jobs_clear(t_jobs **head);
void jobs_push_back(t_jobs **list, t_jobs **data);
int jobs_remove(t_jobs **head, int pid);

int get_input(char **arr, int len);
void read_command(char **l);
int execute_commands(char *command, char **params, char ***commands_arr, int i);

int cd_own(char **parameters, t_flags_cd *flags);
void init_cd_flags(t_flags_cd *data);
int cd_flags_setter(t_flags_cd *data, char **flags);

int echo_own(t_flags_echo *flags, char **str);
void init_echo_flags(t_flags_echo *data_own);
int echo_flags_setter(t_flags_echo *data_own, char **flags);

int env_own(t_flags_env *flags, char **data_own);
void init_env_flags(t_flags_env *data_own);
int env_flags_setter(t_flags_env *data_own, char **parameters);

int pwd_own(t_flags_pwd *flags);
void init_pwd_flags(t_flags_pwd *data_own);
int pwd_flags_setter(t_flags_pwd *data_own, char **flags);

int which_own(t_flags_which *flags, char **data_own);
void init_which_flags(t_flags_which *data_own);
int which_flags_setter(t_flags_which *data, char **flags);

int unset_own(const char *arr);
int unset_check_parameters_own(char **data_own);

#endif 
