#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
       int f=0,n;
       char l[80];
       struct stat s;
       if(argc!=2)
       {
         write(1, "Mismatch argument. ", 19);
         return -1;
       }
       if(access(argv[1],F_OK))
       {
         write(1, "File Doesn't Exist. ", 20);
         return -1;
       }
       if(stat(argv[1],&s)<0)
       {
         write(1, "Stat ERROR. ", 12);
         return -1;
       }
       if(S_ISREG(s.st_mode)<0)
       {
         write(1, "Not a Regular FILE. ", 20);
         return -1;
       }
       if(geteuid()==s.st_uid) {
               if(s.st_mode & S_IRUSR)
                       f=1;
       }
       else if(getegid()==s.st_gid) {
               if(s.st_mode & S_IRGRP)
                       f=1;
       }
       else if(s.st_mode & S_IROTH) {
               f=1;
       }


       f=open(argv[1],O_RDONLY);
       while((n=read(f,l,80))>0) {
               write(1,l,n);
             }
       if(!f)
       {
         write(1, "Permission denied. ", 19);
         return -1;
       }

  return 0;
}
