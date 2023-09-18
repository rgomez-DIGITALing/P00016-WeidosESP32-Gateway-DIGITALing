#pragma once

const char* energyMetersForm PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Energy Meters</title>
</head>
<body>
    <font face = "helvetica">
    <center>
        <div style = "background-color:#eb8c00; color:white; padding: 20px;">
            <h1 style="color:white; padding: 0; margin: 0;">Energy Meters Configuration</h1>
            <p><b>Energy Monitors:</b></p>
            Serial config: 9600 bps, no parity 1 stop bit.
                
            <form method="post" action="/energy-meters">
                <label for="EM1"><center>RTU address:1 Energy Monitor:</label>
                <select name="EM1" id="EM1" onchange="ShowCT(this, 'CT1')">
                    <option value="None">None</option>
                    <option value="EM110">EM110-RTU-2P</option>
                    <option value="EM111">EM111-RTU-2P</option>
                    <option value="EM120">EM120-RTU-2P</option>
                    <option value="EM122">EM122-RTU-2P</option>
                    <option value="EM220">EM220-RTU-4DI2DO</option>
                </select>
                <span id="CT1" hidden>
                    CT1 Primary: <input type="text" name="CT1Primary" style="width:30px;" maxlength="4" Value="5"> CT1 Secondary: <input type="text" name="CT1Secondary" style="width:30px;" maxlength="4" Value="5">
                </span></center>

                <label for="EM2"><center>RTU address:2 Energy Monitor:</label>
                    <select name="EM2" id="EM2" onchange="ShowCT(this, 'CT2')">
                        <option value="None">None</option>
                        <option value="EM110">EM110-RTU-2P</option>
                        <option value="EM111">EM111-RTU-2P</option>
                        <option value="EM120">EM120-RTU-2P</option>
                        <option value="EM122">EM122-RTU-2P</option>
                        <option value="EM220">EM220-RTU-4DI2DO</option>
                    </select>
                    <span id="CT2" hidden>
                        CT2 Primary: <input type="text" name="CT2Primary" style="width:30px;" maxlength="4" Value="5"> CT2 Secondary: <input type="text" name="CT2Secondary" style="width:30px;" maxlength="4" Value="5">
                    </span></center>

                    <label for="EM3"><center>RTU address:3 Energy Monitor:</label>
                        <select name="EM3" id="EM3" onchange="ShowCT(this, 'CT3')">
                            <option value="None">None</option>
                            <option value="EM110">EM110-RTU-2P</option>
                            <option value="EM111">EM111-RTU-2P</option>
                            <option value="EM120">EM120-RTU-2P</option>
                            <option value="EM122">EM122-RTU-2P</option>
                            <option value="EM220">EM220-RTU-4DI2DO</option>
                        </select>
                        <span id="CT3" hidden>
                            CT3 Primary: <input type="text" name="CT3Primary" style="width:30px;" maxlength="4" Value="5"> CT3 Secondary: <input type="text" name="CT3Secondary" style="width:30px;" maxlength="4" Value="5">
                        </span></center>

                        <label for="EM4"><center>RTU address:4 Energy Monitor:</label>
                            <select name="EM4" id="EM4" onchange="ShowCT(this, 'CT4')">
                                <option value="None">None</option>
                                <option value="EM110">EM110-RTU-2P</option>
                                <option value="EM111">EM111-RTU-2P</option>
                                <option value="EM120">EM120-RTU-2P</option>
                                <option value="EM122">EM122-RTU-2P</option>
                                <option value="EM220">EM220-RTU-4DI2DO</option>
                            </select>
                            <span id="CT4" hidden>
                                CT4 Primary: <input type="text" name="CT4Primary" style="width:30px;" maxlength="4" Value="5"> CT4 Secondary: <input type="text" name="CT4Secondary" style="width:30px;" maxlength="4" Value="5">
                            </span></center>

                            <label for="EM5"><center>RTU address:5 Energy Monitor:</label>
                                <select name="EM5" id="EM5" onchange="ShowCT(this, 'CT5')">
                                    <option value="None">None</option>
                                    <option value="EM110">EM110-RTU-2P</option>
                                    <option value="EM111">EM111-RTU-2P</option>
                                    <option value="EM120">EM120-RTU-2P</option>
                                    <option value="EM122">EM122-RTU-2P</option>
                                    <option value="EM220">EM220-RTU-4DI2DO</option>
                                </select>
                                <span id="CT5" hidden>
                                    CT5 Primary: <input type="text" name="CT5Primary" style="width:30px;" maxlength="4" Value="5"> CT5 Secondary: <input type="text" name="CT5Secondary" style="width:30px;" maxlength="4" Value="5">
                                </span></center>
                                <input type="submit" value="Submit" style = "margin-top:15px">

                <script type="text/javascript">
                    function ShowCT(EM, ctNum){
                        var selectedValue2=EM.value;
                        if ((selectedValue2=="EM120")||(selectedValue2=="EM220")||(selectedValue2=="EM110")){
                            document.getElementById(ctNum).hidden = false;
                        }
                        else{
                            document.getElementById(ctNum).hidden = true;
                        }
                    }
                </script>

                <script>
                    var sel = document.getElementById("EM1");
                    sel.value = '%EM1%';
                    ShowCT(sel, 'CT1');
                    sel = document.getElementById("EM2");
                    sel.value = '%EM2%';
                    ShowCT(sel, 'CT2');
                    sel = document.getElementById("EM3");
                    sel.value = '%EM3%';
                    ShowCT(sel, 'CT3');
                    sel = document.getElementById("EM4");
                    sel.value = '%EM4%';
                    ShowCT(sel, 'CT4');
                    sel = document.getElementById("EM5");
                    sel.value = '%EM5%';
                    ShowCT(sel, 'CT5');
                </script>
            </form>
        </div>
    </center>
    <footer>
        <center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center>
    </footer>
</body>
</html>
)rawliteral";