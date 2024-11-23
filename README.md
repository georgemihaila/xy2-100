# An Arduino implementation of the XY2-100 laser scanner protocol

### Protocol overview

The XY2-100 protocol uses 4 (at minimum) pairs of wires in order to send data packets in a differential manner.

This is what a standard 16-bit data packet looks like. 

![Packet overview](resources/packet.png)

#### Setup

```cpp
XY2_100 *galvo = new XY2_100(...);
```

#### Usage

-  Drawing rectangles
  
```cpp
galvo->rect(1000, 1000, 100, 400); // x, y, w, h
```

-  Drawing circles
  
```cpp
//x, y, r, n points
galvo->circleCW(1000, 1000, 500, 360 * 4);
galvo->circleCCW(1000, 1000, i, 360 * 4);
```

- Drawing lines

```cpp
galvo->setXY(0, 0);
galvo->tickingDelay(100000);
galvo->setXY(1000, 1000);
```

### Demo

![shape demo](resources/Galvo%20demo.gif)
### FAQ:

- Any easier way of using this library? Preferably with laser control and G code support?
  - Yes, check out [SerialGCodeParser](https://github.com/georgemihaila/galvo-controller), based on this library

- Is 18-bit extended mode supported?
  - No, not as of now.

- Does this work at the standard rate of 2MHz? 
  - Most likely not, but an Arduino Nano seems to be able to drive a galvo just fine. 
  
[References](docs/)
