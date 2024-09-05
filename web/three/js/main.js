import * as THREE from "three";

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(
  30,
  window.innerWidth / window.innerHeight,
  1,
  3000
);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

const geometry = new THREE.BoxGeometry(35, 2, 50);
var textureLoader = new THREE.TextureLoader();
var materials = [
  new THREE.MeshBasicMaterial({ color: 0xdddddd }), // 紅色
  new THREE.MeshBasicMaterial({ color: 0xdddddd }), // 綠色
  new THREE.MeshBasicMaterial({
    map: textureLoader.load("image/adxl345_material.jpg"), // 替換為你的 JPG 圖片路徑
  }),
  new THREE.MeshBasicMaterial({ color: 0xdddddd }), // 黃色
  new THREE.MeshBasicMaterial({ color: 0xdddddd }), // 紫色
  new THREE.MeshBasicMaterial({ color: 0xdddddd }), // 青色
];
const cube = new THREE.Mesh(geometry, materials);
scene.add(cube);

// const axesHelper = new THREE.AxesHelper(150);
// scene.add(axesHelper);

camera.position.set(200, 200, 200);
camera.lookAt(0, 0, 0);

function calculateRotation(data) {
  var pitch = Math.atan2(data.x, Math.sqrt(data.y * data.y + data.z * data.z));
  var roll = Math.atan2(data.y, data.z);

  return {
    pitch: pitch,
    roll: roll,
  };
}

function animate() {
  let data = calculateRotation(acceleration);
  // 更新立方體的旋轉
  cube.rotation.x = -data.pitch; // 俯仰角對應到 x 軸
  cube.rotation.z = data.roll; // 翻滾角對應到 y 軸

  // 假設感測器數據以 milli-g 為單位，這裡將其轉換成更合適的比例
  var scale = 0.01; // 調整比例以適應視覺效果

  renderer.render(scene, camera);
}
