InputCapture
============

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

Use InputCapture to execute a function once per period of a square
wave applied to the input capture pin. The duration of the period (in
units of microseconds) and the on_duration (in units of microseconds)
are automatically sent to the user function as
parameters. InputCapture is capable of measuring frequencies from less
than 1Hz up to approximately 7kHz. For now, InputCapture is hard coded
to use Timer5, so it works with the Arduino Mega.

[Usage Examples](./examples)

##Execute Interrupt Service Routine (ISR) Function Once Per Period

```cpp
void userFunc(unsigned long period_us, unsigned long on_duration_us)
{
  //your code here
}
void setup()
{
  input_capture.init();
  input_capture.addCycleTask(userFunc);
}
```
