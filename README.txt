--------------------------------------------------------------------------
READMEFILE of the VRI_board_Example of Broentech Solutions A.S.
--------------------------------------------------------------------------
This is a general purpose Board developed and opensourced as example of IoT fog device. It can be used as starting point for your own device!

--------------------------------------------------------------------------
HARDWARE: 
The Vri Board is Based on STM32L151 and it consist of 2 different boards:
	1. A Main board
	2. An RF shield
The main board include the MCU and the power managment unit wich automatically recharge the single cell Li-Po Battery when is connected to usb power source.
The RF shield is connected by UART to the main shield. It also route some GPIO pins to be used for controlling various configuration signals. This design was done
in order to easily swap between different shields. The standar shield include the RadioCraft module with Tinymesh protocol inside. The choice of this module was based on 
the pin and API compatibility between the different families of the module. This means that you could swap shield changing the operating frequency without reflashing the MCU code!
It also include self configuring mesh protocol and AES128 bit encryption.
In the Schematic folder you will find the Schematic and Layouts of the board with some known issue (please read the README file inside that folder!)

--------------------------------------------------------------------------
SOFTWARE:
in the Code/SRC folder you will find example of code written in c. This code can be used as starting point for your project. Please notice that is relative large and many functions are not tested or optimized! Despite this you can use it for picking up the few libraries, functions or code lines that you need!