InputCapture
============

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

Use InputCapture to execute a function once per period of a square
wave applied to the input capture pin. The duration of the period (in
units of microseconds) and the on_duration (in units of microseconds)
are automatically sent to the user function as parameters. 

[Usage Examples](./examples)

##Execute Interrupt Service Routine (ISR) Function Once Per Period

```cpp
void userFunc(unsigned int period_us, unsigned int on_duration_us)
{
  //your code here
}
void setup()
{
  input_capture.init();
  input_capture.addCycleTask(userFunc);
}
```
