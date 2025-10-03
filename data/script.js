// connect to websocket
const ws = new WebSocket(`ws://${window.location.hostname}/ws`);

// joystick elements
const joystick = document.getElementById("joystick");
const stick = document.getElementById("stick");
const joystickRadius = 125; // joystick radius
const stickRadius = 90;     // stick movement limit

const throttleDisplay = document.getElementById("throttle");
const angleDisplay = document.getElementById("angle");

// center position
let rect = joystick.getBoundingClientRect();
let centerX = rect.width / 2;
let centerY = rect.height / 2;

// Convert x,y into throttle + steering
function sendCommand(x, y) {
    let steering = Math.round(85 + (x / stickRadius) * 35);   // -90 to +90
    let throttle = Math.round((y / stickRadius) * 255);  // -255 to +255
    ws.send(JSON.stringify({ throttle, steering }));
    throttleDisplay.textContent = `Throttle: ${throttle}`;
    angleDisplay.textContent = `Steering Angle: ${steering}`;
}

// Reset stick to center
function resetStick() {
    stick.style.left = `${centerX - stick.offsetWidth / 2}px`;
    stick.style.top  = `${centerY - stick.offsetHeight / 2}px`;
    sendCommand(0,0);
}

// Handle movement
// clientX, clientY are the mouse/touch coordinates
function handleMove(clientX, clientY) {
    const rect = joystick.getBoundingClientRect();
    let x = clientX - rect.left - centerX;
    let y = clientY - rect.top - centerY;

    const dist = Math.sqrt(x*x + y*y);
    if (dist > stickRadius) {
        const angle = Math.atan2(y, x);
        x = stickRadius * Math.cos(angle);
        y = stickRadius * Math.sin(angle);
    }
    
    stick.style.left = `${centerX + x - stick.offsetWidth/2}px`;
    stick.style.top  = `${centerY + y - stick.offsetHeight/2}px`;
    
    sendCommand(x, -y); // invert y so up=forward
}

joystick.addEventListener("mousedown", e => {
    handleMove(e.clientX, e.clientY);
    joystick.addEventListener("mousemove", moveHandler);
});

document.addEventListener("mouseup", () => {
    joystick.removeEventListener("mousemove", moveHandler);
    resetStick();
});

joystick.addEventListener("touchstart", e => {
    handleMove(e.touches[0].clientX, e.touches[0].clientY);
});

joystick.addEventListener("touchmove", e => {
    handleMove(e.touches[0].clientX, e.touches[0].clientY);
});
joystick.addEventListener("touchend", resetStick);

function moveHandler(e) {
    handleMove(e.clientX, e.clientY);
}