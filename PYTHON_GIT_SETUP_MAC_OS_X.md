Python Git Setup Mac OS X
=========================

##Install XCode

<https://developer.apple.com/xcode/>

##Install Homebrew

```shell
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Insert Homebrew directory at the top of the PATH by adding the
following line to the bottom of your ~/.profile file (create it if it
does not exist):

```shell
export PATH=/usr/local/bin:/usr/local/sbin:$PATH
```

Open a new terminal to complete the PATH modification or run:

```shell
source ~/.profile
```


##Install Python

```shell
brew install python
```

##Install Git

```shell
brew install git
```
