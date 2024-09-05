document.addEventListener("DOMContentLoaded", () => {
  const audio = document.querySelector("audio");
  const progressContainer = document.querySelector("#progress_container");
  const progressBar = document.querySelector("#progress_bar");
  const dragItem = document.querySelector("#drag_item");
  const playPauseButton = document.querySelector("#play span");

  let isDragging;

  function updateProgressBar() {
    const { currentTime, duration } = audio;
    const progressPercentage = (currentTime / duration) * 100;
    progressBar.style.width = `calc(${progressPercentage}% + 8px)`;
    dragItem.style.left = `${progressPercentage}%`;
  }

  audio.addEventListener("timeupdate", updateProgressBar);

  playPauseButton.addEventListener("click", () => {
    if (audio.paused) {
      audio.play();
      playPauseButton.innerText = " pause ";
    } else {
      audio.pause();
      playPauseButton.innerText = " play_arrow ";
    }
  });

  dragItem.addEventListener("mousedown", function (event) {
    isMouseDown = true;
    // 防止选中文本
    event.preventDefault();
  });

  function stopDragging() {
    isDragging = false;
    document.removeEventListener("mousemove", dragProgress);
    document.removeEventListener("mouseup", stopDragging);
    document.removeEventListener("touchmove", dragProgress);
    document.removeEventListener("touchend", stopDragging);
  }

  function startDragging(event) {
    isDragging = true;
    event.preventDefault();
    document.addEventListener("mousemove", dragProgress);
    document.addEventListener("mouseup", stopDragging);
    document.addEventListener("touchmove", dragProgress, { passive: false });
    document.addEventListener("touchend", stopDragging);
  }

  function dragProgress(event) {
    if (isDragging) {
      const containerRect = progressContainer.getBoundingClientRect();
      const mouseX =
        event.clientX || (event.touches && event.touches[0].clientX);

      let newLeft = mouseX - containerRect.left - dragItem.offsetWidth / 2;
      newLeft = Math.max(
        0,
        Math.min(newLeft, progressContainer.offsetWidth - dragItem.offsetWidth)
      );
      dragItem.style.left = newLeft + "px";
      let progress = newLeft / containerRect.width;
      progressBar.style.width = `calc(${progress * 100}% + 8px)`;
      audio.currentTime = progress * audio.duration;
    }
  }

  dragItem.addEventListener("mousedown", startDragging);
  dragItem.addEventListener("touchstart", startDragging, { passive: false });
});
