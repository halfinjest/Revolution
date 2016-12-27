# Revolution

Programs for the Nintendo Wii (Revolution) through the Homebrew Channel.

These programs can be executed through the Homebrew Channel. Homebrew must be installed on the Wii, and an application SD card must also be created. A guide to installing Homebrew and creating an application SD card can be found on their [web site](http://wiibrew.org/wiki/Homebrew_setup).

## Usage

Before being able to compile, devkitPro must be installed. Instructions for installing devkitPro can be found on their [web site](http://devkitpro.org/wiki/Getting_Started).

Navigate to the directory of the desired program, then compile it:

`make`

A directory for this program is made under the `apps` directory on the SD card.

The `.dol` file is copied to this new directory as `boot.dol`.

Optionally, the `icon.png` and `meta.xml` files can also be copied to this directory. This information shows up on the Homebrew menu, but it is not necessary when executing an application.
