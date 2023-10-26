# Commander X16 Hello World (for macOS)

This is a tutorial project to get started with programming for the [Commander X16](https://www.commanderx16.com/) 8-bit computer, made by [The 8-bit Guy](https://www.youtube.com/channel/UC8uT9cgJorJPWu7ITLGo9Ww).

The project is a simple test of output and input of text, using C and assembly simultaneously and simply making sure your toolchain is set-up correctly.

It's based on the Windows template from [nb-programmer](https://github.com/nb-programmer/x16-hello)

## Setup

You need to install a toolchain to compile / assemble the project, and an emulator (or a real X16 system!) to execute it.

### macOS

1. Install the CC65 toolchain by using brew `brew install cc65`
2. Download the emulator from [here](https://github.com/X16Community/x16-emulator/releases)
3. Set the PATH environment variable to the folder where you have installed the X16 emulator

### Windows

See [here](https://github.com/nb-programmer/x16-hello) on how to install and use it on Windows

## Building

Open a Console window to this folder, and type `make`. It will compile the project and output `hello.prg` inside the `build` directory. This is the binary file that you will run.

## Running

You can use `make run` to launch the emulator, load, and launch the ROM on startup.

If you want to run it manually, launch the emulator as so:
```
x16emu -prg build/hello.prg -run
```
Omit the `-run` argument to load it into memory and not execute.

# References

- [SlithyMatt](https://github.com/SlithyMatt)'s repositories for X16 tutorials (some of my code is based on this! Thank you!)
- [GameBlaBla](https://github.com/gameblabla)'s repositories for some VERA code
- [The Official Commander X16 documentation](https://github.com/commanderx16/x16-docs) Check this out if you're serious about learning everything about this amazing system
- [C64 Wiki page](https://www.c64-wiki.com/wiki/Commander_X16) on the Commander X16, a very comprehensive description on the system