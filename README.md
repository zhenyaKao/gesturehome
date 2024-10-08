## 手勢操控系統
![專案架構](/structure.png)

運用adxl345三軸加速度模組，透過感測器取得的移動數值，判斷使用者進行的手勢動作，以進行對應的居家設備操控

1. 使用C語言開發 kernal模組，並傳送至使用者層
2. 於使用者層判斷手勢模式，並呼叫對應的網頁api
3. 使用Node.js開發網頁後端程式，用以接收以及設定對應指令
4. 透過WebSocket作為網頁前後端通訊的方式，以便隨時接收指令
---

### Linux Kernal & User Space
編寫Linux驅動程式來讀取感測值數據，再將資料傳到使用者層做處理。
而使用者層主要分為三大功能：
1. read.c: 讀取原始數據，並進行轉換
2. movement.c: 分析xyz軸資訊來判斷當前使用者的手勢
3. api.c: 進行api的呼叫，將資料透過curl傳送至網頁端
![](/linux_code.png)

---
### 手勢功能設定頁
透過網頁端使用戶能夠依照自身需求來定義不同手勢的功能。在用戶儲存設定後，將會以.json的形式保存設定檔，當接收到/event傳來的指令時，
便會依據設定檔的內容，呼叫對應的動作。

![](/manage_sys.png)
![](/manage_sys2.png)
