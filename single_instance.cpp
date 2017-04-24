#include "single_instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

static int Lockfile(int fd) {
  struct flock fl;

  fl.l_type = F_WRLCK;
  fl.l_start = 0;
  fl.l_whence = SEEK_SET;
  fl.l_len = 0;

  return (fcntl(fd, F_SETLK, &fl));
}

int AlreadyRunning(const char *filename) {
  int fd;
  char buf[24];

  fd = open(filename, O_RDWR | O_CREAT, LOCKMODE);
  if (fd < 0) {
    fprintf(stderr, "can't open %s, error: %s\n", filename, strerror(errno));
    exit(1);
  }
  if (Lockfile(fd) == -1) {
    if (errno == EACCES || errno == EAGAIN) {
      fprintf(stderr, "file: %s already locked\n", filename);
      close(fd);
      return 1;
    }
    fprintf(stderr, "can't lock %s, error: %s\n", filename, strerror(errno));
    exit(1);
  }
  ftruncate(fd, 0);
  snprintf(buf, sizeof(buf) - 1, "%ld", (long)getpid());
  write(fd, buf, strlen(buf) + 1);
  return 0;
}
