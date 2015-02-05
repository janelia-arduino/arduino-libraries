Watchdog
========

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

Use Watchdog to execute a function and/or reset the microcontroller
after a set amount of time passes, unless the timer is reset.

[Useage Examples](./examples)

##Execute Interrupt Service Routine (ISR) Function on Timeout

```cpp
void userFunc()
{
  //your code here
}
void setup()
{
  watchdog.enableIsr(userFunc);
}
```

##Reset Microcontroller on Timeout

```cpp
void setup()
{
  watchdog.enableSystemReset();
}
```

##Specify Timeout

```cpp
void setup()
{
  watchdog.begin(Watchdog::TIMEOUT_1000MS);
}
```

##Timeout Values

* TIMEOUT_16MS
* TIMEOUT_32MS
* TIMEOUT_64MS
* TIMEOUT_125MS
* TIMEOUT_250MS
* TIMEOUT_500MS
* TIMEOUT_1000MS
* TIMEOUT_2000MS
* TIMEOUT_4000MS
* TIMEOUT_8000MS

##Prevent Timeout

```cpp
// Call resetTimer before timeout duration expires. Repeat.
watchdog.resetTimer();
```
