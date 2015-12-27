# Orient
This application will automatically change screen orientation and disable/enable
the touchpad based on accelerometer data.

###Compatibility
* HP Envy x360 - 15-u010dx

###Package Requirements
* X11 for xinput and xrandr
* gio for gsettings

###Building
Run make in the cloned directory
````bash
make

````

###Manual Building
To manually build the application using gcc.
````bash
gcc `pkg-config --cflags gtk+-3.0` -o bin/orient src/orient.c src/touchpad.c `pkg-config --libs gtk+-3.0`

````

###Building the Schema for GSettings
Make sure to do this step or the application will not start
````bash
sudo cp schemas/apps.orient.gschema.xml /usr/share/glib-2.0/schemas/
sudo glib-compile-schemas /usr/share/glib-2.0/schemas/

````

###Installing the application
Use the provided install.sh or to manually install run the commands below
````bash
sudo mkdir /opt/orient
sudo cp bin/orient
sudo cp orient.desktop /usr/share/applications/
cp orient.desktop $HOME/.config/autostart/

````

###Autostarting with the user interface
Copy the orient.desktop to $HOME/.config/autostart
````bash
cp orient.desktop $HOME/.config/autostart/

````

###Disabling Auto Rotation
To disable orient auto rotation run the commando below.
````bash
gsettings set apps.orient enable-autorotate false

````

To disable orient auto rotation run the command below.
````bash
gsettings set apps.orient enable-autorotate true

````

###Todo
* Seperate laptop, tablet, and convertible mode
* More precision using all accelerometers to minimize accidental rotations
* Gnome shell extention that exposes the gsettings and indicates if the
  application is running.
* Create a AUR package
* Create a ubuntu and debian package
* Wayland support
