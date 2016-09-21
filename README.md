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
with the unit. Eventually there will be a wiring diagram for prototyping with
a parts list and then an eagle schematic and parts list so the board can be
ordered and then put together and reflowed. After that, separate STL files for 
parts that will need to be 3d printed will be added based on common
configurations.

## Proposed Configurations

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
to hear it when at highway speeds.
