## 手勢操控系統
![專案架構](/structure.png)

運用adxl345三軸加速度模組，透過感測器取得的移動數值，判斷使用者進行的手勢動作，以進行對應的居家設備操控

1. 使用C語言開發 kernal模組，並傳送至使用者層
2. 於使用者層判斷手勢模式，並呼叫對應的網頁api
3. 使用Node.js開發網頁後端程式，用以接收以及設定對應指令
4. 透過WebSocket作為網頁前後端通訊的方式，以便隨時接收指令
---

### Linux Kernal & User Space
![](/linux_code.png)


### 手勢功能設定頁
![](/manage_sys.png)
![](/manage_sys2.png)
