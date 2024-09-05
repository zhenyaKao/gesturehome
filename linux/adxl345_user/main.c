#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "common.h"
#include "movement.h"
#include "read.h"

#define DEVICE_BLTEST "/dev/adxl345"

int main(void) {
  int movementfd;
  int ret = 0;
  char buf[6];

  struct event event;
  event.timestamp = time(NULL);
  event.count = 0;
  event.dir = NONE;

  movementfd = open(DEVICE_BLTEST, O_RDONLY);
  if (movementfd < 0) {
    perror("Cannot open device");
    exit(EXIT_FAILURE);
  }

  while (1) {
    ret = read(movementfd, buf, sizeof(buf));
    if (ret < 0) {
      perror("Read error");
    } else if (ret == sizeof(buf)) { // 有資料
      struct posData currData;
      currData = readData(buf);
      moveEvent(currData, prevData, event);
      prevData = currData;

    } else {
      fprintf(stderr, "Unexpected number of bytes read: %d\n", ret);
    }

    usleep(500000); // 5毫秒執行一次
  }

  if (movementfd >= 0) {
    close(movementfd);
  }

  return 0;
};
