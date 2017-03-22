# arduino-libraries

C++ libraries for running on Arduino hardware.

## Install These Arduino Libraries on your Host Machine

### Linux or Mac OS X

Install Python and git on your system if necessary.

[Setup Python](https://github.com/janelia-pypi/python_setup)

[Setup Git](https://github.com/janelia-idf/git_setup.git)

Open terminal:

```shell
mkdir ~/git
cd ~/git
git clone https://github.com/janelia-arduino/arduino-libraries.git
cd arduino-libraries
git submodule init
git submodule update
python symlinks.py --install #Makes symbolic links to libraries in /home/<yourusername>/Arduino/
```

### Windows

[Setup Git](https://github.com/janelia-idf/git_setup.git)

Open Git Bash:

(Use "Insert" key to paste into Git Bash)

```shell
cd ~/My\ Documents/Arduino/
mv libraries/ libraries2/ #Make copy of old libraries
git clone https://github.com/janelia-arduino/arduino-libraries.git libraries
cd libraries
git submodule init
git submodule update
cd ..
cp -r libraries2/. libraries/ #Add old libraries to new libraries if desired
cd libraries
git checkout . #Delete any old library code that conflicts with new library code
```

## Install Arduino on your Host Machine

### Download the Arduino Software

<http://arduino.cc/en/main/software>

### Linux Install

```shell
sudo apt-get remove arduino #remove older version if necessary
mkdir ~/ArduinoIde
mv ~/Downloads/arduino-X.Y.Z-linuxXX.tar.xz ~/ArduinoIde/
cd ~/ArduinoIde/
tar -xf arduino-X.Y.Z-linuxXX.tar.xz
cd arduino-X.Y.Z-linuxXX
echo "alias arduino='$(pwd)/arduino'" >> ~/.bashrc
source ~/.bashrc
```

On linux, you may need to add yourself to the group 'dialout' in order
to have write permissions on the USB port:

```shell
sudo usermod -aG dialout $USER
sudo reboot
```

#### Running on Linux

```shell
arduino
```

### Mac OS X Install

<https://www.arduino.cc/en/Guide/MacOSX>

### Windows Install

<https://www.arduino.cc/en/Guide/Windows>

### Setup

```shell
# after Arduino starts, go to File : Preferences
# verify Sketchbook location:
# /home/<yourusername>/Arduino/
```

## Install Teensyduino

### Download Teensyduino Installer

<https://www.pjrc.com/teensy/td_download.html>

### Linux Install

```shell
mv ~/Downloads/TeensyduinoInstall.linux64 ~/ArduinoIde/
cd ~/ArduinoIde/
chmod 755 TeensyduinoInstall.linux64
./TeensyduinoInstall.linux64
#select folder ~/ArduinoIde/arduino-X.Y.Z/
#select 'None' additional libraries to install
```

#### Download Linux udev rules

<https://www.pjrc.com/teensy/td_download.html>

```shell
sudo cp ~/Downloads/49-teensy.rules /etc/udev/rules.d/
```

## chipKit

### Arduino IDE 1.6.7 or Greater

From within the Arduino IDE, go to File->Preferences dialog box. Look
at the text entry field called "Additional Boards Manager URLs:". If
that text entry field is blank, then you can just copy/paste the
following URL into that text field
<https://github.com/chipKIT32/chipKIT-core/raw/master/package_chipkit_index.json>
Then click OK to close the Preferences dialog box.

Now select the Tools->Board->Board Manager menu from the Arduino IDE,
and it will open up the Boards Manager window. From there, scroll down
until you see the chipKIT board. Click once on any of the text in the
chipKIT section, and you will see a button appear that says
"Install". It will take some time to download all of the chipKIT
components and install them, but when it's done, you can click the
Close button to close the Board Manager window.

Now choose a chipKIT board from the Tools->Board menu and program your
chipKIT board!

### Arduino IDE Before 1.6.7

#### Install MPIDE

Download MPIDE

<http://chipkit.net/started/install-chipkit-software/>

#### Linux Install

```shell
mkdir ~/mpide
mv ~/Downloads/
mv ~/Downloads/mpide* ~/mpide
sudo apt-get install librxtx-java
cd ~/mpide
tar -xvzf mpide*
cd mpide*
cd ~/mpide
echo "alias mpide='$(pwd)/mpide'" >> ~/.bashrc
source ~/.bashrc
```

##### Running on Linux

```shell
mpide
```

#### Mac OS X Install

<http://chipkit.net/started/install-chipkit-software/installing-mpide-mac-os/>

#### Windows Install

<http://chipkit.net/started/install-chipkit-software/install-mpide-windows/>

#### MPIDE Setup

```shell
# after MPIDE starts, go to File : Preferences
# verify Sketchbook location:
# /home/<yourusername>/Arduino
```
