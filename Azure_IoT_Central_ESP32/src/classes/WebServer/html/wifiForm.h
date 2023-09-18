#pragma once

const char* wifiForm PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>WiFi Configuration</title>
</head>
<body>
    <font face = "helvetica">
    <center>
        <div style = "background-color:#eb8c00; color:white; padding: 20px">
            <font face = "helvetica"></font>
            <h1 style="color:white; padding:0; margin:0;">WiFi Configuration</h1>
            <form method="post" action="/wifi">
                <label for="ssid">WiFi SSID:</label>
                <input type="text" id="ssid" name="ssid" value= "%SSID%" style="width:120px;" maxlength="25" required><br><br>

                <label for="password">WiFi Password:</label>
                <input type="password" id="password" name="password" value="%password%" style="width:120px;" maxlength="25" required><br><br>

                <input type="submit" value="Submit">
            </form>
        </div>
    </center>

    <footer>
        <center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center>
    </footer>
</body>
</html>
)rawliteral";