#pragma once

const char* homePage PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Home</title>
    <style>


        .button {
            display: inline-block;
            padding: 10px 20px;
            font-size: 18px;
            text-decoration: none;
            background-color: white;
            color: black;
            border-radius: 5px;
            margin: 10px;
        }
    </style>
</head>
<body>
    <font face = "helvetica">
    <div style="text-align:center; color:white; background-color:#eb8c00; padding:20px">
        <h1 style="padding:0 0 30px; margin:0;" >Weidmuller Energy Monitoring. Wifi Version.</h1>
        <a class="button" href="/wifi">WiFi Configuration</a>
        <a class="button" href="/azure">Azure IoT Central</a>
        <a class="button" href="/energy-meters">Energy Meters</a>
        <a class="button" href="/flow-meters">Flow Meters</a>
        <a class="button" href="/pulse-meters">Pulse Meters</a>
    </div>

    <footer>
        <center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center>
    </footer>
</body>
</html>
)rawliteral";