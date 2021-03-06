# TachClock

Project used to convert 12,000 RPM Tachometer into a 12 hour clock.  Based on work completed by mrbigbusiness's project [tachometer-clock](https://github.com/mrbigbusiness/tachometer-clock).

<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/final.png?raw=true" width="320" height="240">

## Overview

The goal of the project was to convert a 12,000 RPM tachometer (found in a number of places, including [Amazon](https://www.amazon.com/gp/product/B0748C46FD/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)) into a working "clock". In this case, the hours are represented by the RPM dial, and the minutes are displayed as the speed.  The Neutral light indicates AM/PM (on for PM).  The fuel guage changes gradually over time.

### Tachometer Dial
After a bunch of trial and error with 0-5v and 0-12v logic levels, I finally figured out that the RPM guage needs an **AC** signal(!), with both negative and positive logic levels. The below diagrams show the creation of the negative rail, and the switching needed to produce the signal.

A [ICL7660S](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918) voltage converter was used to create the negative voltage rail:

 ![chargepump](https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/chargepump.png?raw=true")

an [LM358 OpAmp](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918) was used to create the square full swing square wave- design pulled on this [Quora](https://www.quora.com/How-can-you-create-an-AC-signal-from-DC-with-the-Arduino-Uno-Is-PWM-considered-an-AC-signal-since-it-produces-a-square-wave) article:

 ![chargepump](https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/opamp.png?raw=true")
 



### Speed Display
Speed on this tachometer is determined by the frequency of pulses being fed into the speed pin.  The shorter the duration between pulses, the faster the speed, or the faster the wheel is rotating.  A simple PWM or variable 0-5v pulse is good enough to set the speed.

### Fuel Dislpay
The fuel level on this tachometer corresponds to the amount of resistance between the fuel line and ground.  Apparently, very little (but at least some) resistance = full tank, and lot of resistance = empty tank.

R1 = 10, R2 = 22, R3 = 15, R4  = 22

### Neutral, Gear, Turn Signals
The other lights on the tachomter are just turned on by setting the corresponding line to ground.  Most of the lights, and the gear display works like this.


## Snapshots

<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/breadboard.png?raw=true" width="320" height="240">

## Hardware

Component | Price | Location
----------|-------|---------
Tachometer | $29.99 | [Amazon](https://www.amazon.com/gp/product/B0748C46FD/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
Push Button | $1.99 | [Adafruit](https://www.adafruit.com/product/1477)
RTC | $7.50 | [Adafruit](https://www.adafruit.com/product/3296)
12V Power Supply | $8.95 | [Adafruit](https://www.adafruit.com/product/798)
Barrel Jack | $2.95 | [Adafruit](https://www.adafruit.com/product/610)
Metro Mini | $12.50 | [Adafruit](https://www.adafruit.com/product/2590)
Voltage Converter | $1.74 | [DigiKey](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918)
LM358 OpAmp | $0.45 | [DigiKey](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918)

Resistors: 10 ohm, 22 ohm (x2), 15 ohm, 1K (x2), 10K

Capasitors: 10uf (x2)

Metro Mini was used because it can handle 12V in.

Also, to move the components off of the bread board and into the case (since I already had the through hole components), I created a 2 layer board to keep things cleaner.  


[OSH Park](https://oshpark.com/shared_projects/GJOlpiep) 


<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/board_front.png?raw=true" width="200" height="110">
<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/board_back.png?raw=true" width="200" height="110">
<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/completed.png?raw=true" width="200" height="110">
<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/schematic.png?raw=true" width="141" height="110">


## Case Model

The case model was built with Fusion 360, and exported to stl files.  See the first release for the attached files.  Updates needed to the model include: 1) the opening is a bit too big for the tachometer.  I ended up wrapping the tachometer with a few wraps of tape to get it to fit snugly.  2) The bottom, or base, needs a lot of work to fit right.  

<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/model.png?raw=true" width="200" height="130">

## Built With

Sloeber IDE, but could be built with the Arduino IDE.

## Contributing

Submit a pull request if interested in contributing.

## Versioning

[SemVer](http://semver.org/) for versioning.

## Authors

* **mrbigbusiness** - *Initial code* - [mrbigbusiness](https://github.com/mrbigbusiness)
* **Chris** - *Updates for specific hardware* - [c-devine](https://github.com/c-devine)


## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
Please use at your own risk since this is not a certified or even tested project!

## Acknowledgments

[tachometer-clock](https://github.com/mrbigbusiness/tachometer-clock).


