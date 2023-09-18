#pragma once

const char* azureForm PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Azure IoT Central</title>
    <style>
        input {
            width:150px;
        }
    </style>
</head>
<body>
    <font face = "helvetica">
    <center>
        <div style = "background-color:#eb8c00; color:white; padding:20px">
            
            <h1 style="color:white; padding:0; margin:0;">Azure IoT Central configuration</h1>
            <form method="post" action="/azure">
                <label for="deviceId">Device ID:</label>
                <input type="text" id="deviceId" name="deviceId" value="%deviceId%" maxlength="100" required><br><br>

                <label for="scopeId">Scope ID:</label>
                <input type="text" id="scopeId" name="scopeId" value="%scopeId%" maxlength="100" required><br><br>

                <label for="groupPrimaryKey">Group Primary Key:</label>
                <input type="text" id="groupPrimaryKey" name="groupPrimaryKey" value="%groupPrimaryKey%" style="width:400px;" maxlength="250" required><br><br>

                <label for="weidosModelId">WeidOS-ESP32-Wifi Model ID:</label>
                <input type="text" id="weidosModelId" name="weidosModelId" value="%weidosModelId%" maxlength="100" required><br><br>

                <label for="em3BasicLineId">EM3Ph Basic Line Serial Model ID:</label>
                <input type="text" id="em3BasicLineId" name="em3BasicLineId" value="%em3BasicLineId%" maxlength="100" required><br><br>

                <label for="em1BasicLineId">EM1Ph Basic Line Serial Model ID:</label>
                <input type="text" id="em1BasicLineId" name="em1BasicLineId" value="%em1BasicLineId%" maxlength="100" required><br><br>

                <input type="submit" value="Submit" style = "width: auto;">
            </form>
        </div>
    </center>

    <footer>
        <center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center>
    </footer>
    </font>
</body>
</html>
)rawliteral";