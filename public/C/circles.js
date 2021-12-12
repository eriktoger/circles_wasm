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
};

const render = (nrOfCircles, circleSize) => {
  const canvas = document.getElementById("canvas");
  const context = canvas.getContext("2d");

  const dataLength = nrOfCircles * circleSize;
  let circles = new Int32Array(
    wasmMemory.buffer,
    _getCircles(canvas.width, canvas.height),
    dataLength
  );
  context.clearRect(0, 0, canvas.width, canvas.height);

  for (let i = 0; i < dataLength; i += circleSize) {
    const [x, y, r, cr, cg, cb] = circles.slice(i, i + circleSize);
    context.beginPath();
    context.arc(x, y, r, 0, 2 * Math.PI, false);
    context.fillStyle = `rgba(${cr},${cg},${cb},0.75`;
    context.fill();
  }

  window.requestAnimationFrame(() => render(nrOfCircles, circleSize));
};
