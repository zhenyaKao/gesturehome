
#include "read.h"
#include "common.h"
#include <sys/types.h>

struct posData readData(char *buf) {
  struct posData currData;
  int16_t dis_data;
  // 解析x,y,z資料
  dis_data = (buf[1] << 8) | buf[0]; // X 軸資料
  currData.x_axis = (double)dis_data * 3.9;

  dis_data = (buf[3] << 8) | buf[2]; // Y 軸資料
  currData.y_axis = (double)dis_data * 3.9;

  dis_data = (buf[5] << 8) | buf[4]; // Z 軸資料
  currData.z_axis = (double)dis_data * 3.9;

  return currData;
}
