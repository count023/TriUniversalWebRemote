# TriUniversalWebRemote

My personal IR-Remote-Control for 5 devices.

## Motivation

Many people nowadays have a lot of devices around, most of them using IR-Remote-Controls, so i do. I simply was fed up with carrying those controls around when moving from the desk to my sofa and vice versa. After purchasing another device - a LED-stripe with yet another control - i seriously thought about buying a universal remote control. But the fixed layout of the buttons of the usual products annoyed me. Thus i decided, to build my own universal IR remote control, providing kind of RESTful API, to control my devices. And to code a nice looking Web-Interface for it - only with the buttons i use and suiting perfectly my personal needs.

![interface.html](TriUniversalWebRemote-schematic.png "see interface.html in this repository")


## Implementation

The first litter i made was with a ESP8266 nodemcu v1 and one IR-LED. I am using the [IRremoteESP8266 library from markszabo](https://github.com/markszabo/IRremoteESP8266). I also built up a simple IR-Receiver (nodemcu v3, too) with a slightly modified receiver sketch based on an example provided by this library for two purposes: sniffing my 5 existing remotes and checking the sent IR-codes by my own implementation.

This way 5 files in here may of considerable interest:
- IR-codes for a Samsung UE46F6500 (and for sure also other Samsung TVs)
- IR-codes for a older Kenwood 5.1 Receiver (KRF-X9060D)
- IR-codes for a cheap SEG DVD-Player
- IR-codes for a Paulmann LED-stripe
- IR-codes for a GigaBlue receiver (HD 800 UE plus)

The first problem i ran into was the fact, that my devices aren't located at one place but two of those around four meters away from the other three. The most IR-LEDs - and exspecially the cheap ones - have a emitter angle of around 20°. So i need to use two emitter. While meditate on the wiring i found a very similar project: [WiFi IR Blaster](https://create.arduino.cc/projecthub/BuddyC/wifi-ir-blaster-af6bca).

Inspired by BuddyC's [simple schema](https://create.arduino.cc/projecthub/BuddyC/wifi-ir-blaster-af6bca#schematics) i made it. (i added a more described version of a fritzing here - i am not an expert in wiring, and it always takes me hours - i'm more in coding which is easy for me)

The quasi RESTful API follows he simple schema of GET /<device>/<command> and pointing directly to a simple server running on the ESP8266 nodemcu. So hitting http://<ip-of-the-node>/<device>/<command> will be translated into an infrared signal and sent by the the two IR-LEDs.

I also added a modularised implementation of HTTP-Update based on another project by me: [GpioneersHttpUpdate](https://github.com/count023/esp-http-update-server) to provide a simple way to update the device without plugging it via USB to the computer.


## Fritzing

### schematic view
![schematic view](TriUniversalWebRemote-schematic.png)

### breadboard view
![breadboard view](TriUniversalWebRemote-breadboard.png)


## How To Use

- adapt the passwords.h.example as described in the file
- adapt the GpioneersHttpUpdate.h to point to your update server
- adapt the methods like handleTv and create similar .h-files like samsung_remote_codes.h for the ir-remote-codes of your special devices


## ToDo

The implementation of the methods like handleTv are bloody simple by now. I simply didn’t manage it to get use of a two dimensional HashMap for the translation of the HTTP-request-path into an IR-command. (Some trials of this are in the code right now - but they do not work yet)
