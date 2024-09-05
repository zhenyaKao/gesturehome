const express = require("express");
const router = express.Router();
const controller = require("./controller");

router.get("/getAll", controller.getAll);
router.post("/update", controller.update);

module.exports = router;
