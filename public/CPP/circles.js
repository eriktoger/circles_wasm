const init = () => {
  const canvas = document.getElementById("canvas");
  const header = document.getElementById("header");
  const footer = document.getElementById("footer");

  canvas.width = window.innerWidth - 40;
  canvas.height =
    window.innerHeight - header.clientHeight - footer.clientHeight;
  window.onresize = () => {
    canvas.height =
      window.innerHeight - header.clientHeight - footer.clientHeight;
    canvas.width = window.innerWidth - 40;
  };

  canvas.addEventListener("mousedown", (event) => {
    const { left, top } = canvas.getBoundingClientRect();
    Module.changeColor(event.clientX - left, event.clientY - top);
  });
};

const render = () => {
  const canvas = document.getElementById("canvas");
  const context = canvas.getContext("2d");

  const circles = Module.getCircles(canvas.width, canvas.height);

  context.clearRect(0, 0, canvas.width, canvas.height);
  for (let i = 0; i < circles.size(); i++) {
    const { x, y, r, cr, cg, cb } = circles.get(i);
    context.beginPath();
    context.arc(x, y, r, 0, 2 * Math.PI, false);
    context.fillStyle = `rgba(${cr},${cg},${cb},0.75`;
    context.fill();
  }

  window.requestAnimationFrame(() => render());
};

const increaseCircles = () => Module.increaseCircles();

const decreaesCircles = () => Module.decreaseCircles();
