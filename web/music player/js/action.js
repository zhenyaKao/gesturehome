function run(data) {
  console.log(data);
  switch (data.action) {
    case "vol_up":
      adjustVol(+0.2);
      break;
    case "vol_down":
      adjustVol(-0.2);
      break;
    case "play_pause":
      playAndPause();
      break;
    default:
      break;
  }
}

function adjustVol(val) {
  let audio = document.querySelector("audio");
  audio.volume += val;
  let idx = (10 * audio.volume) / 2;
  let volElems = document.querySelectorAll(".vol_group span");
  console.log(audio.volume);
  volElems.forEach((elem, i) => {
    if (i > idx) {
      elem.classList.add("inactive");
    } else {
      elem.classList.remove("inactive");
    }
  });
}

function playAndPause() {
  let audio = document.querySelector("audio");
  let playBtn = document.querySelector("#play span");
  console.log(playBtn);
  if (audio.paused) {
    audio.play();
    playBtn.innerHTML = " pause ";
  } else {
    playBtn.innerHTML = " play_arrow ";
    audio.pause();
  }
}
