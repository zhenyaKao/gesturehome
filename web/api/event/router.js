const express = require("express");
const router = express.Router();
const controller = require("./controller");

router.post("/data", controller.data);
router.get("/shakeUpDown", controller.shakeUpDown);
router.get("/shakeLeftRight", controller.shakeLeftRight);
router.get("/flip", controller.flip);

module.exports = router;
