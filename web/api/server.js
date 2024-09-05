const WebSocket = require("ws");
const http = require("http");
const express = require("express");
const cors = require("cors");
const session = require("express-session");
const eventRouter = require("./event/router");
const manageRouter = require("./manage/router");

const { initializeWebSocketServer } = require("./ws/ws_server"); // 引入 WebSocket 模塊

const app = express();

app.use(
  session({
    secret: "login",
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false },
  })
);

app.use(
  cors({
    origin: "*", // 允許所有來源，你可以根據需要限制來源
    methods: ["GET", "POST", "PUT", "DELETE", "OPTIONS"], // 允許的方法
    allowedHeaders: ["Content-Type", "Authorization"], // 允許的標頭
    credentials: true, // 如果需要跨域傳送 Cookies
  })
);

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// 設置路由
app.use("/event", eventRouter);
app.use("/manage", manageRouter);

// 建立 HTTP 伺服器
const server = http.createServer(app);

// 初始化 WebSocket 伺服器
initializeWebSocketServer(server);

server.listen(8181, () => {
  console.log("Server running on port 8181");
});
