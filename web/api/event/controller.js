const fs = require("fs");
const path = require("path");

const { sendMessageToAllClients } = require("../ws/ws_server");

const event_data = path.join(__dirname, "../../events.json");

exports.data = (req, res) => {
  const x = req.body.x;
  const y = req.body.y;
  const z = req.body.z;

  sendPosData({ x: x, y: y, z: z });
  res.send("Data received");
};

exports.shakeUpDown = (req, res) => {
  callEvent("shake_up_down");
  res.send("up-down\n");
};
exports.shakeLeftRight = (req, res) => {
  callEvent("shake_left_right");
  res.send("left-right\n");
};
exports.flip = (req, res) => {
  callEvent("flip");
  res.send("flip\n");
};

function callEvent(sensorMovement) {
  let parsedData;
  fs.readFile(event_data, "utf8", (err, data) => {
    if (err) {
      console.error("檔案讀取失敗:", err);
    } else {
      if (data) {
        parsedData = JSON.parse(data);
        parsedData.forEach((event) => {
          let { sensor, action } = event;
          if (sensor.id == sensorMovement) {
            actionFunction[action.id]();
          }
        });
      }
    }
  });
}

const actionFunction = {
  vol_up: function () {
    console.log("vol_up");
    sendMessageToAllClients({ type: "event", event: { action: "vol_up" } });
  },
  vol_down: function () {
    console.log("vol_down");
    sendMessageToAllClients({ type: "event", event: { action: "vol_down" } });
  },
  play_pause: function () {
    console.log("play_pause");
    sendMessageToAllClients({ type: "event", event: { action: "play_pause" } });
  },
};

const sendPosData = (posData) => {
  sendMessageToAllClients({ type: "data", posData: posData });
};
