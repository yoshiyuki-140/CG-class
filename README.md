# CG Class 

This repository contains sample code for a university computer graphics (CG) class.
To execute this code, you should install `freeglut3-dev` on Debian-based systems.

## Install dependencies
```bash
sudo apt-get install freeglut3-dev
```

## Install stb_image.h

To use `stb_image.h`, execute these commands.
```bash
git clone https://github.com/nothings/stb.git
sudo cp stb/stb_image.h /usr/local/include/
rm -rf stb
```
