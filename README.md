# TachClock

Project used to convert 12,000 RPM Tachometer into a 12 hour clock.  Based on work completed by mrbigbusiness's project [tachometer-clock](https://github.com/mrbigbusiness/tachometer-clock).

## Overview

The goal of the project was to convert a 12,000 RPM tachometer (found in a number of places, including [Amazon](https://www.amazon.com/gp/product/B0748C46FD/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)) into a working "clock". In this case, the hours are represented by the RPM dial, and the minutes are displayed as the speed.  The Neutral light indicates AM/PM (on for PM).  The fuel guage changes gradually over time.

### Tachometer Dial
After a bunch of trial and error with 0-5v logic level, I finally figured out that the RPM guage needs an **AC** signal, with both negative and positive logic levels. The below diagrams show the creation of the negative rail, and the switching needed to produce the signal.

*ToDo* add negative rail and op amp diagrams


### Speed Display
Speed on this tachometer is determined by the frequency of pulses being fed into the speed pin.  The shorter the duration between pulses, the faster the speed, or the faster the wheel is rotating.  A simple PWM or variable 0-5v pulse is good enough to set the speed.

### Fuel Dislpay
The fuel level on this tachometer corresponds to the amount of resistance between the fuel line and gound.  Apparently, very little (but at least some) resistance = full tank, and lot of resistance = empty tank.

### Neutral, Gear, Turn Signals
The other lights on the tachomter are just turned on by setting the corresponding line to ground.  Most of the lights, and the gear display works like this.


## Snapshots

<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/breadboard.png?raw=true" width="320" height="240">
<img src="https://raw.githubusercontent.com/c-devine/TachClock/snapshots/assets/img/final.png?raw=true" width="320" height="240">

*add final result*
*add case model*

## Hardware

Component | Price | Location
----------|-------|---------
Tachometer | $29.99 | [Amazon](https://www.amazon.com/gp/product/B0748C46FD/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1))
Push Button | $1.99 | [Adafruit](https://www.adafruit.com/product/1477)
RTC | $7.50 | [Adafruit](https://www.adafruit.com/product/3296)
12V Power Supply | $8.95 | [Adafruit](https://www.adafruit.com/product/798)
Barrel Jack | $2.95 | [Adafruit](https://www.adafruit.com/product/610)
Metro Mini | $12.50 | [Adafruit](https://www.adafruit.com/product/2590)
Charge Pump | $1.74 | [DigiKey](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918)
OpAmp | $0.45 | [DigiKey](https://www.digikey.com/product-detail/en/renesas-electronics-america-inc/ICL7660ACPAZ/ICL7660ACPAZ-ND/1034918)

Metro Mini was used because it can handle 12V in.

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

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

## Acknowledgments

[tachometer-clock](https://github.com/mrbigbusiness/tachometer-clock).


