const socket = new WebSocket("ws://192.168.1.106:8181");

socket.addEventListener("open", (event) => {
  console.log("WebSocket is open now.");
});

socket.addEventListener("message", (event) => {
  let data = JSON.parse(event.data);
  if (data.type === "data") {
    //console.log(data.posData);
    acceleration = data.posData;
  }
});

socket.addEventListener("error", (event) => {
  console.error("WebSocket error observed:", event);
});
