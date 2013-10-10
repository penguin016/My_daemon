#include <stdlib.h>
#include <pwd.h>
#include "parse.h"

static const char *parse_pid(char *str, sel_union *ret)
{
    char *endp;
    unsigned long num;
    static const char pidrange[] = "Process ID out of range.";
    static const char pidsyntax[] = "Process ID list syntax error.";
    num = strtoul(str, &endp, 0);
    if(*endp != '\0')        return pidsyntax;
    if(num < 1)              return pidrange;
    if(num > 0x7fffffffUL)   return pidrange;
    ret->pid = num;
    return 0;
}

static const char *parse_uid(char *str, sel_union *ret)
{
    struct passwd *passwd_data;
    char *endp;
    unsigned long num;
    static const char uidrange[] = "User ID out of range.";
    static const char uidexist[] = "User name does not exist.";
    num = strtoul(str, &endp, 0);
    if(*endp != '\0')
    {
        passwd_data = getpwnam(str);
        if(!passwd_data)  return uidexist;
        num = passwd_data->pw_uid;
    }
    if(num > 0xfffffffeUL)  return uidrange;
    ret->uid = num;
    return 0;
}

static const char *parse_cmd(char *str, sel_union *ret)
{
    strncpy(ret->cmd, str, sizeof ret->cmd);
    return 0;
}

