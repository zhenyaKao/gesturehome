const fs = require("fs");
const path = require("path");

const event_data = path.join(__dirname, "../../events.json");

exports.getAll = (req, res) => {
  let parsedData = {};
  // 從文件讀取 JSON 數據
  fs.readFile(event_data, "utf8", (err, data) => {
    if (err) {
      console.error("檔案讀取失敗:", err);
    } else {
      if (data) {
        parsedData = JSON.parse(data);
        res.status(200).json(parsedData);
      }
    }
  });
};

exports.update = (req, res) => {
  let { content } = req.body;
  console.log(content);
  //將 JSON 數據寫入文件
  fs.writeFile(
    event_data,
    JSON.stringify(JSON.parse(content), null, 2),
    (err) => {
      if (err) {
        console.error("寫入檔案失敗:", err);
      }
    }
  );

  res.status(200).send({ message: "成功獲得資料" });
};
