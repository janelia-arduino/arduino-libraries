AD57X4R
=======

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

Provides an SPI based interface to the AD57X4R Complete, Quad,
12-/14-/16-Bit, Serial Input, Unipolar/Bipolar Voltage Output DACs.

[Usage Examples](./examples)

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
