document.addEventListener("DOMContentLoaded", appear);

let debounceTimer;
document.addEventListener("scroll", () => {
  clearTimeout(debounceTimer);
  debounceTimer = setTimeout(appear, 50);
});

function appear(){
  const contents = document.querySelectorAll(".fade-in");
  const screenPosition = window.innerHeight / 1.2;

  contents.forEach(content => {
    const contentPosition = content.getBoundingClientRect().top;
    const children = content.querySelectorAll(".fade-in");

    if (contentPosition < screenPosition) {
      content.classList.add("visible");
      children.forEach(child => {
        child.classList.add("visible");
      });
    }
  });
}

if (document.body.classList.contains("index")) {
  document.querySelector(".arrow").addEventListener("click", () => {
    const targetPosition = window.innerHeight;
  
    const scrollStep = () => {
      const currentScroll = window.scrollY;
      const distance = targetPosition - currentScroll;
  
      if (distance > 0) {
        window.scrollBy(0, Math.min(distance, 40));
        requestAnimationFrame(scrollStep);
      }
    };
    scrollStep();
  }); 
}

if (document.body.classList.contains("fingerstyle")){
  let player;
  let prev = document.getElementById("left_arrow");
  let next = document.getElementById("right_arrow");
  function onYouTubeIframeAPIReady() {
      player = new YT.Player("player", {
          height: "100%",
          width: "100%",
          videoId: "G2HhXQPLrbo",
          playerVars: {loop: 1, playlist: "G2HhXQPLrbo,VKEq8HFDKwU,RwURzReiiFw"},
          events: {onError: playerError, onReady: onPlayerReady}
      });
  }
  function onPlayerReady() {
      prev.addEventListener("click", () => {
          player.previousVideo();
      });

      next.addEventListener("click", () => {
          player.nextVideo();
      });
  }
  function playerError(){
    console.log("error");
  }
}
