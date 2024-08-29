/*
 * POSIX does not request sleep(1) to support float argument,
 * thus "sleep 0.1" is not guaranteed to be portable.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int main(int argc, char** argv)
{
  double        dsec = 0;
  long int      lsec = 0;
  useconds_t    usec = 0;
  char*         endp = NULL;

  if (argc < 2) {
    fprintf(stderr, "%s requires one argument\n", argv[0]);
    exit(-1);
  }

  dsec = strtod(argv[1], &endp);
  if (endp == NULL || endp[0]) {
    fprintf(stderr, "Failed to parse %s as a floating number\n", argv[1]);
    exit(-2);
  }

  if (dsec < 0) {
    fprintf(stderr, "Negative value %f is unacceptable\n", dsec);
    exit(-3);
  }

  if (UINT_MAX < dsec) {
    fprintf(stderr, "Too big value %f is unacceptable\n", dsec);
    exit(-4);
  }

  lsec = lrint(floor(dsec));
  usec = (useconds_t)(int)((dsec - lsec) * 1000000);

  sleep((unsigned int)lsec);
  usleep(usec);

  exit(0);
}
