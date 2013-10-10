#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void init_daemon(); // 守护进程初始化

//字符串匹配
//src:源字符串
//dst：目标字符串
//len:源字符串被比较的长度
int match(char *src,char *dst,int len)
{
    int i = 0;
    int j = 0;
    int size_dst = 0;

    //获得目标字符串的长度
    size_dst = strlen(dst);
    //如果目标字符串的长度大于len，返回失败
    if (size_dst > len)
    {
        return 0;
    }
    //开始比较
    for (i = 0;i < len;i++)
    {
        for (j = 0;j < size_dst;j++)
        {
            if (src[i + j] != dst[j])
            {
                break;
            }
        }
        if (j == size_dst)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    //FILE *fp;
    /*int fd;
    time_t t;
    struct data list;
    char buf[1000];
    int pid;
    //init_daemon();

    //while(1)
   // {
        sleep(1);
        //creat("test.log", 0644);
       // if((creat("test.log", 0644)) < 0)
        //{
            //文件创建失败
        //    exit(1);
        //}
       // else
       // {
       //     printf("文件创建成功！\n");
        //}

        //system("ps aux | grep mpirun >> test.log");

        if((fd = open("test.log", O_RDWR)) < 0)
        {
           //打开文件失败
           printf("打开文件失败");
           exit(1);
        }
        read(fd, buf, 1000);
        if(match(buf, "mpirun", 1000))
        {
            memset(buf,0,1000);
            printf("匹配成功\n");
            lseek(fd, 0, 0);//文件描述符放在文件开始
            while(read(fd, &list, sizeof(list)) > 0)
            {
                printf("zhengzaizhao\n");
                //printf("%s\n", list.pid);
                printf("%s\n", list.usr);
                if(match(list.command, "blcr", 100))
                {
                    printf("找到了\n");
                    //pid = atoi(list.pid);
                    //printf("%d\n", pid);
                }
            }
        }
        else
        {
            printf("匹配失败\n");
        }
        //memset(buf,0,100);
        //write(fd, buf, 1000);
        close(fd);


        //printf("%d\n", i);
    //}
    */
    return 0;
}
