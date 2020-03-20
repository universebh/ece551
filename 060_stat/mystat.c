#include <assert.h>
#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 256

typedef struct stat stat_t;

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

int printFirstLine(const char * pathName, const stat_t * sb) {
  //Step 7:
  //check if the file is a symbolic link, and if so,
  //get the target of the link and print it
  if (S_ISLNK(sb->st_mode)) {
    char linktarget[BUFFER_SIZE];
    ssize_t len = readlink(pathName, linktarget, BUFFER_SIZE);
    if (len == -1) {
      fprintf(stderr, "error in printFirstLine\n");
      perror("readlink");
      return -1;
    }
    strcat(linktarget, "");
    printf("  File: ‘%s’ -> ‘%s’\n", pathName, linktarget);
  }
  else {
    printf("  File: ‘%s’\n", pathName);
  }
  return 0;
}

int printSecondLine(const stat_t * sb) {
  char desc[BUFFER_SIZE];
  switch (sb->st_mode & S_IFMT) {
    case S_IFBLK: {
      strcpy(desc, "block special file");
    } break;
    case S_IFCHR: {
      strcpy(desc, "character special file");
    } break;
    case S_IFDIR: {
      strcpy(desc, "directory");
    } break;
    case S_IFIFO: {
      strcpy(desc, "fifo");
    } break;
    case S_IFLNK: {
      strcpy(desc, "symbolic link");
    } break;
    case S_IFREG: {
      strcpy(desc, "regular file");
    } break;
    case S_IFSOCK: {
      strcpy(desc, "socket");
    } break;
    default: {
      fprintf(stderr, "unkown file/directory type in printSecondLine\n");
      return -1;
    }
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         (long)sb->st_size,
         (long)sb->st_blocks,
         (long)sb->st_blksize,
         desc);
  return 0;
}

int printThirdLine(const stat_t * sb) {
  //Step 6:
  //check if the file is a device
  if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           (long)sb->st_dev,
           (long)sb->st_dev,
           (long)sb->st_ino,
           (long)sb->st_nlink,
           major(sb->st_rdev),
           minor(sb->st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           (long)sb->st_dev,
           (long)sb->st_dev,
           (long)sb->st_ino,
           (long)sb->st_nlink);
  }
  return 0;
}

const char * parseFirstLetter(char modeDesc[], mode_t mode) {
  assert(strlen(modeDesc) == 0);
  switch (mode) {
    case S_IFBLK: {
      strcat(modeDesc, "b");
    } break;
    case S_IFCHR: {
      strcpy(modeDesc, "c");
    } break;
    case S_IFDIR: {
      strcpy(modeDesc, "d");
    } break;
    case S_IFIFO: {
      strcpy(modeDesc, "p");
    } break;
    case S_IFLNK: {
      strcpy(modeDesc, "l");
    } break;
    case S_IFREG: {
      strcpy(modeDesc, "-");
    } break;
    case S_IFSOCK: {
      strcpy(modeDesc, "s");
    } break;
    default: {
      fprintf(stderr, "unknown accessing type in parseFirstLetter\n");
      return NULL;
    }
  }
  return modeDesc;
}

void catASign(char modeDesc[], mode_t mode, const char * sign) {
  if (mode != 0) {
    strcat(modeDesc, sign);
  }
  else {
    strcat(modeDesc, "-");
  }
}

const char * parseLetters(size_t order, char modeDesc[], mode_t mode) {
  assert(order >= 2);
  assert(strlen(modeDesc) == order - 1);
  switch (order) {
    case 2: {
      catASign(modeDesc, mode, "r");
    } break;
    case 3: {
      catASign(modeDesc, mode, "w");
    } break;
    case 4: {
      catASign(modeDesc, mode, "x");
    } break;
    case 5: {
      catASign(modeDesc, mode, "r");
    } break;
    case 6: {
      catASign(modeDesc, mode, "w");
    } break;
    case 7: {
      catASign(modeDesc, mode, "x");
    } break;
    case 8: {
      catASign(modeDesc, mode, "r");
    } break;
    case 9: {
      catASign(modeDesc, mode, "w");
    } break;
    case 10: {
      catASign(modeDesc, mode, "x");
    } break;
    default: {
      fprintf(stderr, "unknown accessing type in parseLetters\n");
      return NULL;
    }
  }
  return modeDesc;
}

const char * printAccess(const stat_t * sb, char modeDesc[]) {
  mode_t modeArray[10] = {sb->st_mode & S_IFMT,
                          sb->st_mode & S_IRUSR,
                          sb->st_mode & S_IWUSR,
                          sb->st_mode & S_IXUSR,
                          sb->st_mode & S_IRGRP,
                          sb->st_mode & S_IWGRP,
                          sb->st_mode & S_IXGRP,
                          sb->st_mode & S_IROTH,
                          sb->st_mode & S_IWOTH,
                          sb->st_mode & S_IXOTH};
  if (parseFirstLetter(modeDesc, modeArray[0]) == NULL) {
    return NULL;
  }
  for (size_t i = 1; i < 10; i++) {
    if (parseLetters(i + 1, modeDesc, modeArray[i]) == NULL) {
      return NULL;
    }
  }
  return modeDesc;
}

int printFourthLine(const stat_t * sb) {
  mode_t accessMode = sb->st_mode & ~S_IFMT;
  char modeDesc[BUFFER_SIZE];
  strcpy(modeDesc, "");
  if (printAccess(sb, modeDesc) == NULL) {
    fprintf(stderr, "printAcess error in printFourthLine\n");
    return -1;
  }
  const char * pwName = getpwuid(sb->st_uid)->pw_name;
  if (pwName == NULL) {
    fprintf(stderr, "could not get password name in printFourthLine\n");
    perror("getpwuid");
    return -1;
  }
  const char * grName = getgrgid(sb->st_gid)->gr_name;
  if (grName == NULL) {
    fprintf(stderr, "could not get group name in printFourthLine\n");
    perror("getgrgid");
    return -1;
  }
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         accessMode,
         modeDesc,
         sb->st_uid,
         pwName,
         sb->st_gid,
         grName);
  return 0;
}

int printLastFourLines(const stat_t * sb) {
  char * atimestr = time2str(&sb->st_atime, sb->st_atim.tv_nsec);
  char * mtimestr = time2str(&sb->st_mtime, sb->st_mtim.tv_nsec);
  char * ctimestr = time2str(&sb->st_ctime, sb->st_ctim.tv_nsec);
  printf("Access: %s\n", atimestr);
  printf("Modify: %s\n", mtimestr);
  printf("Change: %s\n", ctimestr);
  printf(" Birth: -\n");
  if (atimestr != NULL) {
    free(atimestr);
    atimestr = NULL;
  }
  if (mtimestr != NULL) {
    free(mtimestr);
    mtimestr = NULL;
  }
  if (ctimestr != NULL) {
    free(ctimestr);
    ctimestr = NULL;
  }
  return 0;
}

int printInfo(const char * dirName, stat_t * sb) {
  if (lstat(dirName, sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  if (printFirstLine(dirName, sb) == -1) {
    exit(EXIT_FAILURE);
  }
  if (printSecondLine(sb) == -1) {
    exit(EXIT_FAILURE);
  }
  printThirdLine(sb);
  //Step 2:
  //add part of the fourth line of output from stat
  //Step 3:
  //finish this fourth line
  if (printFourthLine(sb) == -1) {
    exit(EXIT_FAILURE);
  }
  //Step 4:
  //add the last four line of output
  printLastFourLines(sb);
  return 0;
}

int main(int argc, char ** argv) {
  //Step 1:
  //take exactly one file name as a command line argument
  //and print out the first three lines of the output that
  //"stat" would print for that file
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }
  //Step 5:
  //change the program so that it accept any number of
  //arguments on the command line, and print info for
  //each of them
  for (int i = 1; i < argc; i++) {
    stat_t sb;
    printInfo(argv[i], &sb);
  }
  return EXIT_SUCCESS;
}
