#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(void)
{
	struct stat sb;
	stat("stat.c", &sb);
	printf("I-node number: %ld\n", (long) sb.st_ino);
	printf("Mode: %lo (octal)\n", (unsigned long) sb.st_mode);
	printf("Link count: %ld\n", (long) sb.st_nlink);
	printf("Ownership: UID=%ld GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
	printf("File size: %lld bytes\n", (long long) sb.st_size);
	printf("Blocks allocated: %lld\n", (long long) sb.st_blocks);
	printf("Last status change: %s", ctime(&sb.st_ctime));
	printf("Last file access: %s", ctime(&sb.st_atime));
	printf("Last file modification: %s", ctime(&sb.st_mtime));

}
