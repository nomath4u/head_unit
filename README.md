# Custom Bluetooth Headunit

## Summary

The idea behind this project is to get a lightweight bluetooth stereo
into any car. The amount of exposed unit will be customizable (If you want a
screen on it you will want to be able to see it). But should be able to function
with only the microphone showing, allowing the rest of the DIN area to be used 
for other things

##Included in this repository

As I work on this project I will be adding additional thing. For now there is
only the INO file in order to program the microcontroller that will be used 
with the unit. As well as a tool to help send commands to the rn-52. Eventually there will be a wiring diagram for prototyping with
a parts list and then an eagle schematic and parts list so the board can be
ordered and then put together and reflowed. After that, separate STL files for 
parts that will need to be 3d printed will be added based on common
configurations.

## Bugs in V1.0
CMD enable is wired to GPIO10 instead of 9
USBD- is not wired at all
Power input is not exposed

## Bugs in V1.1
Still yet to be discovered

## Proposed Configurations

## Schematic
![schematic](./schematic.png)

### Minimal

In the minimal configuration only the microphone will be exposed. The board 
will be mounted on the back of any 3d printed part with only a hole for the
microphone and no buttons will be broken out. In this configuration everything
will need to be controlled from the phone

### Standard

In this configuration we have the same setup as the Minimal except with buttons
broken out for play/pause, next/previous track, and a few other buttons.

### Large

In this configuration a screen is involved. On this creen the Title, artist,
and album name of the song will displayed as well as a customizable background.
This is implemented with a SPI TFT screen. There are many different sizes
available from adafruit so as requests are made different STL files and code
defines will have to be made in order to accomodate the different screens

##NOTE

* You will want an amplifier for this to be in normal volume range. There is a 
preamplifier on the bluetooth part but without an amplifier you won't be able
to hear it when at highway speeds. As of V1.1 There are spaces for 2 LM386s which help. It may be loud enough on its own for you if you use those connections.

## Useful setup tips
Update to version 1.16 first. Many settings don't work as expected without doing that
Use the added uart_via_arduino code in order to relay commands through an arduino
to the RN-52. Make sure your arduino is @ 3.3V.

Commands I liked
S%,86 // Enableds reconnect on power-on, discoverable on startup, and disables system tones
SN,<name_here> //Name your device.
SS,0F //Turn up the internal amplifier to the max (may want to use something different depending on your amp

