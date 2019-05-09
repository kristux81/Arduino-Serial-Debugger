# Arduino-Serial-Debugger
The serial shell(console) provided with Arduino IDE has limited debug capabilities especially when your project is based on lot of I/O and dependency / interaction among them. When there are too many events (changes in data values) logged at a higher rate (say a couple of seconds), it’s hard to follow the changes from a debugging perspective. We faced this challenge while building a greenhouse using Arduino Mega at its core (Yes, replacing the trusted PLC). The initial version of code we developed was written from scratch and had no state machines. The logging was added at each stage to assist with debugging at different stages of development and testing. Soon it was hard to debug things as the code grew. Since the IDE does not provide standard debug UI (and we did not want to spend extra bucks on specialized hardware) we chose to write a Serial debugger for Arduino. It’s basically in two parts:

# The Firmware

A debugger function that reads PIN registers at an interval, formats them to a message (String/word) and then writes it to Serial Port. It is provided inside c header file which must be include in your Arduino project and the debugger called inside the loop function.

Code : https://github.com/kristux81/Arduino-Serial-Debugger/tree/master/Arduino

# The Software

It is basically a flow running on the Node-Red Server. The debugger can be installed on any OS of your choice that supports Node-Red. Since Node-Red is available on Windows, Linux, Mac and platforms like Raspberry Pi, the debugger can be deployed on any of these machines the only requirement is that it should have USB to Serial drivers installed. Since actual Serial ports are a thing of the past, Arduino uses Virtual COM port (USB to Serial).

# The Program

The flow uses Serial and Dashboard Nodes. These must be pre-installed on Node-Red. The flow builds an Angular style reactive UI which has mappings for I/O ports and a display area for additional console messages.

Code : https://github.com/kristux81/Arduino-Serial-Debugger/tree/master/Node-Red

![Debugger Node Red Flow](https://github.com/kristux81/Arduino-Serial-Debugger/blob/master/Debugger%20flow.jpg)

# The Execution

Arduino must be connected to Computer via USB, with Debugger program running on the computer. The debugger firmware inside the Arduino periodically sends a data string (usually less than 256 bytes) over the USB Serial. These data messages have a frame closing which helps the receiving node identify end-of-message. The Node-red flow grabs these messages and parses them to populate inside a mapped html element on the dashboard. Since the dashboard is based on Angular, no external refresh is required on the UI. It makes easier for the programmers to see the states of each I/O ports without having to painfully watch the running console.

![Debugger UI](https://github.com/kristux81/Arduino-Serial-Debugger/blob/master/Debugger%20UI.jpg)
