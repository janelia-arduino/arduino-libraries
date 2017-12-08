# arduino-libraries

C++ libraries for running on Arduino hardware.

## Install These Arduino Libraries on your Host Machine

### Linux or Mac OS X

Install Python and git on your system if necessary.

[Setup Python](https://github.com/janelia-pypi/python_setup)

[Setup Git](https://github.com/janelia-experimental-technology/git_setup.git)

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

[Setup Git](https://github.com/janelia-experimental-technology/git_setup.git)

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

## Install and Setup Arduino on your Host Machine

[Setup Arduino](https://github.com/janelia-arduino/arduino_setup.git)
