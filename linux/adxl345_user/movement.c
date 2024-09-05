#include "movement.h"
#include "api.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

// Function to convert radians to degrees
struct event events[TRIGGER_TIMES] = {0};

void moveEvent(struct posData prevData, struct posData currData,
               struct event myEvent) {
  // 判斷動作類型
  // 上下及左右移動距離
  double z_distance = fabs(currData.z_axis - prevData.z_axis);
  double x_distance = fabs(currData.x_axis - prevData.x_axis);

  printf("X: %f, Y: %f, Z: %f \n", currData.x_axis, currData.y_axis,
         currData.z_axis);
  post(currData);

  // 根據z軸判斷是否翻轉，反面時z軸為負值
  if (fabs(prevData.z_axis + currData.z_axis) <= 200) {
    printf("翻轉了\n");
    // call api
    // 翻轉事件只需一次即觸發，不需再執行後面紀錄與判斷
    get("flip");
    // 清空事件
    memset(events, 0, sizeof(events));
    sleep(3); // 冷卻時間3秒
    return;
  } else if ((currData.z_axis - prevData.z_axis) > 100 &&
             (z_distance > x_distance)) {
    printf("上下搖動了 \n");
    myEvent.dir = UP_DOWN;
    z_movement++;
  } else if ((currData.x_axis - prevData.x_axis) > 100 &&
             (x_distance > z_distance)) {
    printf("左右搖動了 \n");

    myEvent.dir = LEFT_RIGHT;
    x_movement++;
  } else {
    return;
  }

  myEvent.timestamp = time(NULL);

  // 紀錄事件，移動元素並更新事件
  for (int i = TRIGGER_TIMES - 1; i > 0; i--) {
    events[i] = events[i - 1];
  }
  events[0] = myEvent;

  // 檢查最後一個事件的時間戳
  if (events[TRIGGER_TIMES - 1].timestamp != 0) {

    // 檢查是否都是同一個方向
    int flag = 1;
    for (int i = 1; i < TRIGGER_TIMES; i++) {
      if (events[i].dir != myEvent.dir) {
        flag = 0;
      }
    }

    // 20秒內連續發生三次才視為呼叫用的手勢
    if (flag) {
      // 計算時間差（秒數）
      double differenceInSeconds =
          difftime(events[0].timestamp, events[TRIGGER_TIMES - 1].timestamp);

      if (differenceInSeconds <= 20.0) {
        // callapi
        if (myEvent.dir == UP_DOWN) {

          get("shakeUpDown");
        } else if (myEvent.dir == LEFT_RIGHT) {
          get("shakeLeftRight");

        } else if (myEvent.dir == FLIP) {
          get("flip");
        }
        printf("api called!\n");
        // 清空事件
        memset(events, 0, sizeof(events));

        sleep(2); // 冷卻時間2秒
      }
    }
  }
}
