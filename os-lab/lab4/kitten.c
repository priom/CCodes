//Nrimoni Chowdhury - A00371596

#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
   int file = 0;
   int x;
   char buff [2084];
   //struct stat s;

//Throw error if there aren't 2 arguments
   if(argc != 2) {
      write(1, "Sorry, it has to be 2 arguments.\n ", 33);
      return -1;
   }

//Throw error if file not found
   if(access(argv[1],F_OK)) {
      write(1, "File Doesn't Exist.\n ", 20);
      return -1;
   }

//Open file in read mode
   file = open(argv[1], O_RDONLY);

//Read the file and write it
   while((x = read(file, buff, 80)) > 0) {
         write(1, buff, x);
   }

  return 0;
}

