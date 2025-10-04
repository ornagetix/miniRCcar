// connect to websocket
const ws = new WebSocket(`ws://${window.location.hostname}/ws`);

// joystick elements
const joystick = document.getElementById("joystick");
const stick = document.getElementById("stick");
const joystickRadius = 125; // joystick radius
const stickRadius = 90; // stick movement limit

const throttleDisplay = document.getElementById("throttle");
const steerAngleDisplay = document.getElementById("steerAngle");

// center position
let rect = joystick.getBoundingClientRect();
let centerX = rect.width / 2;
let centerY = rect.height / 2;

// convert joystick x,y into throttle + steering
function sendCommand(x, y) {
    // calculate raw throttle value

    const maxZone = 0.8; // when stick is 80% out, consider it max throttle
    let throttlePercent = y / stickRadius; // -1 to +1
    let throttle;
    
    // if in max zone, set to max value, otherwise scale more aggressively
    if (Math.abs(throttlePercent) > maxZone) {
        throttle = Math.sign(throttlePercent) * 255;
    } else {
        // scale remaining range (0 to maxZone) to full throttle range
        throttle = Math.round((throttlePercent / maxZone) * 255);
    }

    let steerAngle = Math.round(90 + (x / stickRadius) * 35);   // 50 to 120

    // force joystick center at 90 degrees (car is straight)
    // 3px tolerance from center (stick jitter still counts as center)
    const centerTolerance = 3; // pixels
    if (Math.abs(x) <= centerTolerance && Math.abs(y) <= centerTolerance) {
        steerAngle = 90;
    }

    // send values to car via websocket as json
    ws.send(JSON.stringify({ throttle, steerAngle }));

    throttleDisplay.textContent = `Throttle: ${throttle}`;
    steerAngleDisplay.textContent = `Steering Angle: ${steerAngle}`;
}

// reset stick to center
function resetStick() {
    stick.style.left = `${centerX - stick.offsetWidth / 2}px`;
    stick.style.top  = `${centerY - stick.offsetHeight / 2}px`;
    sendCommand(0,0);
}

// handles movement
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