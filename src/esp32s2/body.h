#ifndef BODY_H
#define BODY_H

const char body[] PROGMEM = R"===(
<!-- 
  ### Don't forget to update the body.h file every time this file is modified! ###

  The website for this project need to do the following jobs:
  1. Mannually select the car mode: fully-automatic (competition), wall-following, police car pushing, fully-manual
  2. Manuually control the car when fully manual mode is selected (front, back, left, right, stop)
  3. Manually control the gripping jaw (open, close)
  4. (Optional) Display car position and battery voltage 
  
-->

<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8" />
  <title>ESP32S2 Web Server</title>
  <style>
    body {
      margin-top: 0px;
      margin-bottom: 0px;
      margin-left: 10%;
      margin-right: 10%;
    }

    .button {
      padding: 4% 5%;
      font-size: 100%;
      text-align: center;
      cursor: pointer;
      outline: none;
      color: #ffffff;
      background-color: #3168cf;
      border: none;
      border-radius: 5px;
      box-shadow: 0 3px #999;
      margin-left: 5px;
      margin-right: 5px;
      margin-top: 5px;
      margin-bottom: 5px;
    }

    /* .button:hover {
        background-color: #b60000;
      } */

    .active {
      background-color: #009f05;
      box-shadow: 0 2px #666;
      transform: translateY(4px);
    }

    .slider {
      width: 50%;
      height: 15px;
      border-radius: 5px;
      outline: none;
      opacity: 0.7;
      -webkit-transition: 0.2s;
      transition: opacity 0.2s;
    }
  </style>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
</head>

<body>
  <h1>ESP32C3 Web Server</h1>
  <p style="text-align: center">Group 30</p>
  <p style="text-align: center">Zhanqian Wu, Bowen Jiang, Enlin Gu, Yurui Wang</p>

  <!-- <h2>Connection Info</h2>
    <p>Delay: <span id="BatteryVoltage">?</span> ms</p>
    <p>Battery Voltage: <span id="BatteryVoltage">?.?</span> V</p> -->

  <h2>Mode</h2>
  <div style="text-align: center">
    <button id="trophy_moving_mode_button" class="button" onclick="activateModeButtons('trophy_moving_mode_button')">
      Trophy Moving
    </button>
    <button id="fully_manual_mode_button" class="button" onclick="activateModeButtons('fully_manual_mode_button')">
      Fully Manual
    </button>
  </div>
  <div style="text-align: center">
    <button id="wall_following_mode_button" class="button" onclick="activateModeButtons('wall_following_mode_button')">
      Wall Following
    </button>
    <button id="car_pushing_mode_button" class="button" onclick="activateModeButtons('car_pushing_mode_button')">
      Car Pushing
    </button>

  </div>

  <h2>Direction</h2>
  <div style="text-align: center">
    <button id="forward_button" class="button" onclick="activateDirectionButtons('forward_button')">
      F
    </button>
  </div>
  <div style="text-align: center">
    <button id="left_button" class="button" onclick="activateDirectionButtons('left_button')">
      L
    </button>
    <button id="stop_button" class="button" onclick="activateDirectionButtons('stop_button')">
      O
    </button>
    <button id="right_button" class="button" onclick="activateDirectionButtons('right_button')">
      R
    </button>
  </div>
  <div style="text-align: center">
    <button id="backward_button" class="button" onclick="activateDirectionButtons('backward_button')">
      B
    </button>
  </div>

  <h2>Gripping Jaw</h2>
  <div style="text-align: center">
    <button id="open_button" class="button" onclick="activateJawButtons('open_button')">
      Open
    </button>
    <button id="close_button" class="button" onclick="activateJawButtons('close_button')">
      Close
    </button>
  </div>

  <h2>Turn Rate Control</h2>
  <div style="text-align: center">
    <input type="range" min="0" max="100" value="20" class="slider" id="turn_rate_slider" oninput="displayTurnRate()" />
  </div>
  <p>Turn rate: <span id="turn_rate_val"></span>%</p>

  <h2>Speed Control</h2>
  <div style="text-align: center">
    <input type="range" min="1600" max="4095" value="4000" class="slider" id="speed_slider" oninput="displaySpeed()" />
  </div>
  <p>Speed: <span id="speed_val"></span></p>

  <script>
    speed_slider.onchange = function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("value").innerHTML = this.responseText;
        }
      };
      var str = "speed_slider=";
      var res = str.concat(this.value);
      xhttp.open("GET", res, true);
      xhttp.send();
    };

    turn_rate_slider.onchange = function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("value").innerHTML = this.responseText;
        }
      };
      var str = "turn_rate_slider=";
      var res = str.concat(this.value);
      xhttp.open("GET", res, true);
      xhttp.send();
    };

    function activateDirectionButtons(buttonId) {
      // get the button element by id
      var forward_button = document.getElementById("forward_button");
      var backward_button = document.getElementById("backward_button");
      var left_button = document.getElementById("left_button");
      var right_button = document.getElementById("right_button");
      var stop_button = document.getElementById("stop_button");

      removeAllActiveDirectionButtons(); // remove all active class from the buttons

      if (buttonId == "forward_button") {
        forward_button.classList.add("active"); // add active class to the button
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "F", true);
        xhttp.send();
      }

      if (buttonId == "left_button") {
        left_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "L", true);
        xhttp.send();
      }

      if (buttonId == "stop_button") {
        stop_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "O", true);
        xhttp.send();
      }

      if (buttonId == "right_button") {
        right_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "R", true);
        xhttp.send();
      }

      if (buttonId == "backward_button") {
        backward_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "B", true);
        xhttp.send();
      }
    }

    function activateModeButtons(buttonId) {
      // get the button element by id
      var trophy_moving_mode_button = document.getElementById("trophy_moving_mode_button");
      var fully_manual_mode_button = document.getElementById("fully_manual_mode_button");
      var wall_following_mode_button = document.getElementById("wall_following_mode_button");
      var car_pushing_mode_button = document.getElementById("car_pushing_mode_button");

      removeAllActiveModeButtons(); // remove all active class from the buttons

      if (buttonId == "trophy_moving_mode_button") {
        trophy_moving_mode_button.classList.add("active"); // add active class to the button
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "tro", true);
        xhttp.send();
      }

      if (buttonId == "fully_manual_mode_button") {
        fully_manual_mode_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "man", true);
        xhttp.send();
      }

      if (buttonId == "wall_following_mode_button") {
        wall_following_mode_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "wall", true);
        xhttp.send();
      }

      if (buttonId == "car_pushing_mode_button") {
        car_pushing_mode_button.classList.add("active");
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "car", true);
        xhttp.send();
      }
    }

    function activateJawButtons(buttonId) {
      var open_button = document.getElementById("open_button");
      var close_button = document.getElementById("close_button");

      removeAllActiveJawButtons(); // remove all active class from the buttons

      if (buttonId == "open_button") {
        forward_button.classList.add("active"); // add active class to the button
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "open", true);
        xhttp.send();
      }

      if (buttonId == "close_button") {
        forward_button.classList.add("active"); // add active class to the button
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "close", true);
        xhttp.send();
      }
    }

    function removeAllActiveDirectionButtons() {
      var forward_button = document.getElementById("forward_button");
      var backward_button = document.getElementById("backward_button");
      var left_button = document.getElementById("left_button");
      var right_button = document.getElementById("right_button");
      var stop_button = document.getElementById("stop_button");

      forward_button.classList.remove("active");
      backward_button.classList.remove("active");
      left_button.classList.remove("active");
      right_button.classList.remove("active");
      stop_button.classList.remove("active");
    }

    function removeAllActiveModeButtons() {
      var trophy_moving_mode_button = document.getElementById("trophy_moving_mode_button");
      var fully_manual_mode_button = document.getElementById("fully_manual_mode_button");
      var wall_following_mode_button = document.getElementById("wall_following_mode_button");
      var car_pushing_mode_button = document.getElementById("car_pushing_mode_button");

      trophy_moving_mode_button.classList.remove("active");
      fully_manual_mode_button.classList.remove("active");
      wall_following_mode_button.classList.remove("active");
      car_pushing_mode_button.classList.remove("active");
    }

    function removeAllActiveJawButtons()
    {
      var open_button = document.getElementById("open_button");
      var close_button = document.getElementById("close_button");

      open_button.classList.remove("active");
      close_button.classList.remove("active");
    }

    function speedup() {
      if (prev_state != "+") {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "+", true);
        xhttp.send();
      }
    }

    function slowdown() {
      if (prev_state != "-") {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "-", true);
        xhttp.send();
      }
    }

    var prev_state = null;
    document.addEventListener("keypress", function (event) {
      if (event.key == prev_state) {
        return;
      }
      if (event.key == "w") {
        activateDirectionButtons("forward_button");
      }
      if (event.key == "s") {
        activateDirectionButtons("backward_button");
      }
      if (event.key == "a") {
        activateDirectionButtons("left_button");
      }
      if (event.key == "d") {
        activateDirectionButtons("right_button");
      }
      if (event.key == "x") {
        activateDirectionButtons("stop_button");
      }
      if (event.key == "+" && prev_state != "+") {
        speedup();
      }
      if (event.key == "-" && prev_state != "-") {
        slowdown();
      }
      prev_state = event.key;
    });

    // release WASD keys
    document.addEventListener("keyup", function (event) {
      if (
        prev_state == "w" ||
        prev_state == "s" ||
        prev_state == "a" ||
        prev_state == "d"
      ) {
        activateDirectionButtons("stop_button");
        prev_state = null;
      }
      if (
        prev_state == "+" ||
        prev_state == "-"
      ) {
        prev_state = null;
      }
    });

    var speed = document.getElementById("speed_slider");
    var turn_Rate = document.getElementById("turn_rate_slider");

    function displaySpeed() {
      var output_speed = document.getElementById("speed_val");
      output_speed.innerHTML = speed_slider.value;
    }

    function displayTurnRate() {
      var output_turn_rate = document.getElementById("turn_rate_val");
      output_turn_rate.innerHTML = turn_rate_slider.value;
    }

    function display() {
      displaySpeed();
      displayTurnRate();
    }

    function send_speed_onload() {
      // send speed value on load
      var speed_slider_value = document.getElementById("speed_val");
      var xhttp = new XMLHttpRequest();
      var str = "speed_slider=";
      var res = str.concat(speed_slider_value);
      xhttp.open("GET", res, true);
      xhttp.send();
    }

    function send_turn_rate_onload() {
      var speed_slider_value = document.getElementById("turn_rate_val");
      var xhttp = new XMLHttpRequest();
      var str = "turn_rate_slider=";
      var res = str.concat(speed_slider_value);
      xhttp.open("GET", res, true);
      xhttp.send();
    }

    window.onload = function () {
      display();
      activateDirectionButtons("stop_button");
      send_speed_onload();
      send_turn_rate_onload();
    };
  </script>
</body>

</html>
)===";

#endif