
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
main(int argc, char *argv[])
{
	int i;
	uid_t uid;
	gid_t gid;
	struct passwd *pw;
	struct group *gr;

	printf("This program shows your information.\n");

	uid = getuid();
	if ((pw = getpwuid(uid)) == NULL) {
		perror("getpwuid()");
		exit(1);
	}
	printf("User name : %s, UID: %d, GID: %d, HOME: %s\n", 
		pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir);
	
	gid = getgid();
	if ((gr = getgrgid(gid)) == NULL) {
		perror("getgrgid()");
		exit(1);
	}
	printf("Group name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);

	do {
		if ((gr = getgrent()) != NULL) {
			for (i = 0; gr->gr_mem[i] != NULL; i++) {
				if (!strcmp(pw->pw_name, gr->gr_mem[i])) {
					printf("%d(%s) ", gr->gr_gid, gr->gr_name);
				}
			}
		}
	} while (gr != NULL);
	printf("\n");

	exit(0);
}

