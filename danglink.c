#define _XOPEN_SOURCE 600
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usageError(const char *progName, const char *msg) {
  if (msg != NULL) {
    fprintf(stderr, "%s\n", msg);
  }

  fprintf(stderr, "Usage: %s [directory-path]\n", progName);
  fprintf(stderr, "\t -r Remove(unlink) dangling symbolic links\n");
  fprintf(stderr, "\t -m Mute, don't show output of dangling links\n");
  exit(EXIT_FAILURE);
}

static int removeLinks = 0;
static int muteOutput = 0;
static int dirTree(const char *pathname, const struct stat *sbuf, int type,
                   struct FTW *ftwb) {
  if ((sbuf->st_mode & S_IFMT) == S_IFLNK && type == FTW_SLN) {
    if (!muteOutput) {
      printf("%s\n", pathname);
    }

    if (removeLinks) {
      unlink(pathname);
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int opt;

  if (argc > 1 && strcmp(argv[1], "--help") == 0) {
    usageError(argv[0], NULL);
  }

  while ((opt = getopt(argc, argv, "rm")) != -1) {
    switch (opt) {
    case 'r':
      removeLinks = 1;
      break;
    case 'm':
      muteOutput = 1;
      break;
    }
  }

  if (argc > optind + 1) {
    usageError(argv[0], NULL);
  }

  if (nftw((argc > optind) ? argv[optind] : ".", dirTree, 20, 0)) {
    perror("nftw");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
