# Orient
c program to automatically change screen orientation based on accelerometer data
* Requires xrandr ````sudo apt-get install xrandr````
* Tested on Ubuntu 14.04
* Tested on Antegros and Arch
* Should work on any linux distro running Xorg

## Compatibility
* HP Envy x360 - 15-u010dx
* HP Envy - 15t slim quad
* Other HP devices?
* If your device has an accelerometer and does not work, please send me the details and I will try to add compatilbility

## Download, Build & Run
Download from this repo or the upstream repo
````bash
git clone https://github.com/insanengineer/orient.git
````
Upstream repo
````bash
git clone https://github.com/leszakk/orient.git

````
Building
````bash
cd ~/
gcc ~/orient/orient.c -o ~/orient/orient
~/orient/orient
````

## Future
* Read from config file
* Seperate laptop, tablet, and convertible modes
* More precision using all accelerometers to minimize accidental rotations
