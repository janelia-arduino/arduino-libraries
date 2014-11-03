LinearSensorArray
-----------------

AMS-TAOS linear sensor array driver for TSL family e.g. TSL1406RS

Notes:

Author: Peter Polidoro


#Example Wiring of One TSL1406RS

##Serial Connection

pixel\_per\_sensor\_count = 768

sensor\_count = 1

Connect SO1 to SI2.

SO2 not connected.

| TSL1406RS | Description | Arduino | Description |
|----------:|:------|--------:|:------|
|         1 | Vpp   | GND     | GND   |
|         2 | SI1   | 2       | SI    |
|         3 | HOLD1 | 2       | SI    |
|         4 | CLK1  | 3       | CLK   |
|         5 | GND   | GND     | GND   |
|         6 | AO1   | A0      | A0    |
|         7 | SO1   |         |       |
|         8 | SI2   |         |       |
|         9 | HOLD2 | 2       | SI    |
|        10 | CLK2  | 3       | CLK   |
|        11 | SO2   |         |       |
|        12 | AO2   | A0      | A0    |
|        13 | Vdd   | 5V      | +5VDC |

##Parallel Connection

pixel\_per\_sensor\_count = 384

sensor\_count = 2

SO1 not connected.

SO2 not connected.

| TSL1406RS | Description | Arduino | Description |
|----------:|:------|--------:|:------|
|         1 | Vpp   |     GND | GND   |
|         2 | SI1   |       2 | SI    |
|         3 | HOLD1 |       2 | SI    |
|         4 | CLK1  |       3 | CLK   |
|         5 | GND   |     GND | GND   |
|         6 | AO1   |      A0 | A0    |
|         7 | SO1   |         |       |
|         8 | SI2   |       2 | SI    |
|         9 | HOLD2 |       2 | SI    |
|        10 | CLK2  |       3 | CLK   |
|        11 | SO2   |         |       |
|        12 | AO2   |      A1 | A1    |
|        13 | Vdd   |      5V | +5VDC |

