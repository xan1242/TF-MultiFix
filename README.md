# Tag Force MultiFix

This is a multi-purpose fix and enhancement kit for Yu-Gi-Oh! Tag Force games.

The goal is to mainly fix the JP releases of the games to run with non-JP assets, while also providing other goodies.

## Features

- Fixes all UI bugs for the JP release

- Allows swapping of X (cross) and O (circle) buttons as confirm and back buttons respectively

- Matrix font on cards regardless of region/language

- See partner's cards like in the older Tag Force games

- Disable the "Help" icon in the lower right corner during duels

- Disable the "Installation" feature

- Allow for using UTF-8 encoded story script files

- Enable/disable all of these features, and more, via a configuration window

- Cheats that actually work

## Compatibility

Currently only compatible with Tag Force 6 (ULJM05940).

It will be ported to all other games in the near future.

### PSP note

Tag Force 6 currently runs out of memory with 32MB RAM when loading up the Story Mode. 

You need at least 64MB to run the script as it is now.

This could be remedied by splitting the mod into separate modules.

## Usage

### IMPORTANT NOTES

- It is highly recommended to use a stock EBOOT file (and stock gmodule prx files) and then use [TF-EhpLoader](https://github.com/xan1242/TFEhpLoader) to load modified files. This is due to old translations doing a bad job at fixing the game, so the results might not be as expected!

- Disable all cheats! They will NOT work and may break the game!

### PPSSPP

First, download the PPSSPP release file.

Extract the TFx-MultiFix folder to: `memstick/PSP/PLUGINS` (where x is the game number)

You can open the memstick folder in PPSSPP by opening the following: `File -> Open Memory Stick`.

### PSP hardware

1. Extract the plugins `TF-MultiFixBoot.prx` and `TF-MultiFix.prx` to the seplugins folder

2. Enable `TF-MultiFixBoot.prx` as a plugin in your CFW

3. (TF6 only) Enable 64MB memory extension. NOTE: This is only available for newer PSP models (PSP Go and Street).

Once you have the files installed, run the game. You shouldn't notice anything obvious immediately.

## Configuration window

To open the MultiFix Configuration window, press R + Triangle while the WLAN switch is ON.

On PPSSPP you can usually find the WLAN switch in the button mapping configuration menu. Simply map "WLAN" to any button (I recommend one of the thumbsticks).

On a real PSP, it's a toggle switch you have to engage physically, usually located at the top of the unit.

The configuration is saved inside the game save directory as a file `TF-Multifix.cfg`

## Cheats

Cheats are disabled by default. 

Now, I won't tell you how to enable them, but since this is a Konami game, I think it should be pretty obvious 😉
