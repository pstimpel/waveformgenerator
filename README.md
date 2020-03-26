# Waveform Generator

 
[![Video on Youtube](https://img.youtube.com/vi/MJ1rr9S12Lc/0.jpg)](https://www.youtube.com/watch?v=MJ1rr9S12Lc)

Click to play video

First of all, the credit for creating the basic circuit goes to Scullcom Hobby Electronics Youtube channel, who is inactive meanwhile - sadly.

https://www.youtube.com/channel/UCDqryeq1kMDSEQwltWqASrA

Project page at Thingiverse: https://www.thingiverse.com/thing:4243526

Project page at Prusaprinters: https://www.prusaprinters.org/prints/27172-xr2206-waveform-generator


## Why?

Someone said: when starting the hobby electronics, you will need to build 2 things, a power supply and a waveform generator.

## Again, why?

I was keen to dive into electronics again, after 20 years of ignoring this hobby. To get some practice again, I thought building such a generator would be fun. It was fun. 

## What did you change on the original circuit?

Based on Scullcoms circuit I started creating an Arduino controlled waveform gegenerator. My goal was to control as much as possible by the Arduino. So I removed the following parts from the original circuit:

* switch for changing from sine to triangle wave
* switch for changing from sine/triangle to square wave
* switch for enabling pulse width modulation
* switch for changing the frequency range

I replaced them with a relay and some opto isolators.

## Was there any challenge?

Uh, plenty of challenges. 

Figuring out how to replace mechanical switches by opto isolators and relay was kind of a long way for me. First of, I tried to do it by simple transistors, and failed. So opto isolators were the next try, and I was able to replace 3 of 4 switches by these ICs. One left. So I tried a micro relay, and this worked out great.

Another issue I had was to balance out the whole circuit, so I would be able to select halfway decent frequency ranges. Finally, a big enough coarse frequency potentiometer combined with a trim poti did the trick. My goal was to have kind of smooth waveforms, not to hunt Megahertzes for the marketing paper. 

I built the whole circuit at least 4 times on breadboards. And what to tell: those breadboards can be a pain in the ass, at least the cheapos. 

## What can you expect?

You will get a waveform generator able to generate sine, triangle and square waves. The frequency range is from about 1 Hz up to 100 kHz, split into 5 ranges you can switch between (1-10, 10-100, 100 to 1,000, 1,000 to 10,000 and 10,000 to 100,000 Hz, roughly). You can adjust the frequency within these ranges by two potis. The amplitude is about +5 to -5 V (adjustable) at the 50 Ohms output, and from 0 to 5V at the TTL output. There is a basic Pulse width modulation available as well. You can adjust the pulse width. By combining sine or triangle waves and PWM you recieve kind of a ramp modulation. The waveform is quite solid, but with 100kHz you will see some distortion and spikes. It seems this is kind of a typical behavior of the XR2206 chipset. There is a frequency counter used to display the set frequency. However, this is kind of an estimation, especially in very low Hz ranges.

## What you will find in this repository

### Folder enclosure

This folder contains the stl files to 3D print the enclosure. I was using PLA and my Prusa I3 Mk3 printer. On top, there are 2 PDFs containing labels. You could just print them, cut them out of the sheet of paper, use an exacto knife to cut the holes, and mount it to the front of your enclosure

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/wvg.jpg "Enclosure in Fusion 360")


### Folder circuits

There are 2 circuits. One keeps all the control stuff and the Arduino, and the other creates the waveform and gets controlled by the control board. There are gerber files, the KICAD board file, and PDFs with the circuit scheme itself. In each subfolder you wil find a list of parts. 

## What to buy (BOM)

Beside the stuff from the parts lists in the circuit folders, you will need

* potentiometer 10k linear, 6mm axle (gain control)
* potentiometer 1M linear, 6mm axle (frequency control, coarse)
* potentiometer 10k linear, 6mm axle (frequency control, fine)
* potentiometer 1ook linear, 6mm axle (PWM control)
* 3 push buttons, closing type, like in https://www.amazon.de/gp/product/B07MY2WVQ3
* 1 switch, like in https://www.amazon.de/gp/product/B07MY2WVQ3
* 1 smaller heatsink for TO220, LM7812
* 1 midsze heatsink for TO220, LM7805
* 15 V power supply with 5.5x2.1 connector
* matching 5.5x2.1 socket for your power supply
* 25 cylinderhead screws, M3x12
* 16x2 I2C LED for Arduino
* 2 BNC sockets
* wires
* Pinheaders 2.54mm
* matching IC sockets if you dislike soldering the ICs to the PCB directly (2x 8pin, 1x 14pin, 3x 16pin)
* 3 screw terminals, 2 poles, 5mm 
* dupont style wires or similar to connect to pinheaders

## Howto

### Fast lane

Order PCBs and parts, solder all the stuff together, patch the Arduino using the sketch provided, 3d Print the enclosure, put PCBs inside enclosure, mount LCD, potis and switches to the front, solder dupont style wires to them, connect with the PCBs, mount BNC sockets to the front, use some cable to connect them to the PCB, insert 5.5x2.1 soocket in its pocket, lock it using the lock, connect it to the PCB. Lock the PCBs using the pcblock, secure it using one of the screws. Close the enclosure. Connect power, switch the device on, and have fun.

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200320_211039.jpg "Etching one of the PCBs")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200320_211827.jpg "Final PCB")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200321_164054.jpg "Does it work?")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200325_190900.jpg "Put the stuff into the enclosure")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200325_191428.jpg "Still working?")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200325_191501.jpg "Some mayhem")

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200326_204721.jpg "Done!")

## Remarks, hints

### Arduino

To run the display you will need to add library LiquidCrystal_I2C by Frank de Brabander.

To have frequence counting, you will need to add library FreqCounter by Martin Nawrath.

### Breadboarding

I highly recommend testing the circuit on a breadboard before you go for the soldering stuff. You will learn much more that way than by just following this rough guide. 

![alt text](https://github.com/pstimpel/waveformgenerator/raw/master/media/IMG_20200220_083028.jpg "Half of the circuit")


### Pricing vs functionality vs fun

If you look for a decent waveform generator delivering Megahertz samples, buy one. 

If you look for the cheapest of all solutions, by such a chinese XR2206 kit for less than 10 USD.

If you want to enjoy DIY, start buying parts and follow the guide I provided. Good luck, wish you well.

## CORONA

This project was finished during the spare time provided by Corona. If someone reads this in the future, I reall hope Corona is no issue anymore. Until then: stay safe, wash your hands, and take care of your family.
