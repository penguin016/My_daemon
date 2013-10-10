#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include <sys/types.h>
#include <stdlib.h>

typedef union sel_union
{
    pid_t pid;
    pid_t ppid;
    uid_t uid;
    gid_t gid;
    dev_t tty;
    char cmd[16];
}sel_union;


#endif // PARSE_H_INCLUDED
