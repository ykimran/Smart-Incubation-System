# Hardware and wiring

Source: the supplied project report and `images/circuit.png`.

| Component | Connection / setting |
| --- | --- |
| Controller | Arduino Uno |
| DHT11 data | D2 |
| Buzzer | D4 |
| Heating relay input | D8, active LOW |
| Fan relay input | D9, active LOW |
| 16x2 I2C LCD | Address 0x27; Uno SDA A4, SCL A5 |
| Relay module | Two channels, shown as a 5 V module |
| Cooling fan | Shown as 12 V |
| Bulb | Shown as 220 V in the supplied schematic |

Use the schematic as historical documentation, not a certified wiring plan. Verify module ratings, grounds, supply arrangements, isolation and contact wiring against the actual components. The ZIP does not provide a full bill of materials, load ratings, or a verified protection design.

The LCD library name is shared by multiple implementations. Choose one with the constructor and methods used by the sketch, and confirm the address with the actual module. No exact historical software dependency versions are available.
