#!/usr/bin/sh

sudo mkdir /opt/orient
sudo cp bin/orient /opt/orient/

sudo cp schemas/apps.orient.gschema.xml /usr/share/glib-2.0/schemas/
sudo glib-compile-schemas /usr/share/glib-2.0/schemas/

cp orient.desktop $HOME/.config/autostart/
sudo cp orient.desktop /usr/share/applications/
