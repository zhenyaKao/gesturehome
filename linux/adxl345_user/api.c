#include "api.h"
#include "common.h"
#include <curl/curl.h>
#include <stdio.h>

// 寫入回調函數，這裡只是簡單地將響應數據打印到標準輸出
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t total_size = size * nmemb;
  printf("%.*s", (int)total_size, (char *)contents);
  return total_size;
}

int get(char *event_type) {
  CURL *curl;
  CURLcode res;
  char url[256];

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    snprintf(url, sizeof(url), "http://192.168.1.106:8181/event/%s",
             event_type);
    // 設置 URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // 設置回調函數
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // 執行請求
    res = curl_easy_perform(curl);

    // 錯誤處理
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // 清理
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}

int post(struct posData d) {
  CURL *curl;
  CURLcode res;
  char url[256] = "http://192.168.1.106:8181/event/data";
  char postData[200];

  snprintf(postData, sizeof(postData), "x=%.6f&y=%.6f&z=%.6f", d.x_axis,
           d.y_axis, d.z_axis);

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {

    // 設置 URL
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // 設置傳遞參數
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

    // 設置回調函數
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // 執行請求
    res = curl_easy_perform(curl);
    // 錯誤處理
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // 清理
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}
