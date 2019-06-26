# This is an example for IoT_NODE
## Component:
   2 * Raspberry Pi 3 model B+
   2 * IoT-Node(A) Development Board
   1 * 4 Channel Relay Board
## Sender
  iotnode_sender: it will send data to receiver in a loop.
## Receiver
  iotnode_receiver: it will receive data from sender and do statement judge, and then turn on or turn off the relay by using "i2cset -y 1 0x10 0x01 0xff" 
## More information 
   please visit: wiki.52pi.com 

