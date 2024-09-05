// websocketServer.js
const WebSocket = require("ws");

let wss; // 用於儲存 WebSocket 伺服器實例

/**
 * 初始化 WebSocket 伺服器
 * @param {http.Server} server - 已經創建的 HTTP 伺服器
 */
function initializeWebSocketServer(server) {
  if (wss) {
    throw new Error("WebSocket server is already initialized");
  }

  wss = new WebSocket.Server({ server });

  wss.on("connection", (ws) => {
    console.log("A new client connected");

    ws.on("message", (message) => {
      console.log("Received message:", message);
    });

    ws.on("close", () => {
      console.log("Client disconnected");
    });
  });

  return wss;
}

/**
 * 發送消息到所有已連接的 WebSocket 客戶端
 * @param {string} message - 要發送的消息
 */
function sendMessageToAllClients(data) {
  if (!wss) {
    throw new Error("WebSocket server is not initialized");
  }

  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });
}

module.exports = {
  initializeWebSocketServer,
  sendMessageToAllClients,
};
