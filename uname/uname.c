#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc, char *argv[]) {

        //struct UNAME_STRUCT ubuffer;
		struct utsname ubuffer;
    // Check for proper usage
    if (argc != 1) {
        fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
        return (-1);
    }

    uname(&ubuffer);

    printf("System name: %s\n", ubuffer.sysname);
	printf("Host name: %s\n", ubuffer.nodename);
	printf("OS Release: %s\n", ubuffer.release);
	printf("OS Version: %s\n", ubuffer.version);
	printf("CPU Type: %s\n", ubuffer.machine);
    return 0;
}
