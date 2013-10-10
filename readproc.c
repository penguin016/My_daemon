#include "readproc.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void stat2proc(const char* S, proc_t *P)
{
    unsigned num;
    char* tmp;

ENTER(0x160);

    P->processor = 0;
    P->rtprio = -1;
    P->sched = -1;
    P->nlwp = 0;

    S = strchr(S, '(') + 1;
    tmp = strrchr(S, ')');
    num = tmp - S;
    if(unlikely(num >= sizeof P->cmd)) num = sizeof P->cmd - 1;
    memcpy(P->cmd, S, num);
    P->cmd[num] = '\0';
    S = tmp + 2;

    num = sscanf(S,
       "%c "
       "%d %d %d %d %d "
       "%lu %lu %lu %lu %lu "
       "%Lu %Lu %Lu %Lu "  /* utime stime cutime cstime */
       "%ld %ld "
       "%d "
       "%ld "
       "%Lu "  /* start_time */
       "%lu "
       "%ld "
       "%lu %"KLF"u %"KLF"u %"KLF"u %"KLF"u %"KLF"u "
       "%*s %*s %*s %*s " /* discard, no RT signals & Linux 2.1 used hex */
       "%"KLF"u %*lu %*lu "
       "%d %d "
       "%lu %lu",
       &P->state,
       &P->ppid, &P->pgrp, &P->session, &P->tty, &P->tpgid,
       &P->flags, &P->min_flt, &P->cmin_flt, &P->maj_flt, &P->cmaj_flt,
       &P->utime, &P->stime, &P->cutime, &P->cstime,
       &P->priority, &P->nice,
       &P->nlwp,
       &P->alarm,
       &P->start_time,
       &P->vsize,
       &P->rss,
       &P->rss_rlim, &P->start_code, &P->end_code, &P->start_stack, &P->kstk_esp, &P->kstk_eip,
       &P->wchan,
       &P->exit_signal, &P->processor,
       &P->rtprio, &P->sched
    );

    if(!P->nlwp){
      P->nlwp = 1;
    }

LEAVE(0x160);
}

static int file2str(const char *directory, const char *what, char *ret, int cap) {
    static char filename[80];
    int fd, num_read;

    sprintf(filename, "%s/%s", directory, what);
    fd = open(filename, O_RDONLY, 0);
    if(unlikely(fd==-1)) return -1;
    num_read = read(fd, ret, cap - 1);
    close(fd);
    if(unlikely(num_read<=0)) return -1;
    ret[num_read] = '\0';
    return num_read;
}

static proc_t* simple_readproc(proc_t *const p)
{
    static char sbuf[1024];
    char *const path = p->path;
    unsigned flags = p->flags;

}

