--------------------------------------------------------------------------
READMEFILE of the VRI_board_Example of Broentech Solutions A.S.
--------------------------------------------------------------------------
--------------------------------------------------------------------------
HARDWARE INSTRUCTIONS
--------------------------------------------------------------------------

The Vri Board is Based on STM32L151 and it consist of 2 different boards stacked one onto the other:
	1. A Main board
		The main board include the MCU and the power managment unit wich automatically recharge the single cell Li-Po Battery when is connected to usb power source.
		It has 3 connectors: one for flashing code, the second for i2c and other digital inputs and the third for analog i/o. please check the STM32 datasheed for complete functionalities!
	2. An RF shield
		The RF shield is connected by UART to the main shield. It also route some GPIO pins to be used for controlling various configuration signals. This design was done
		in order to easily swap between different shields. The standar shield include the RadioCraft/Tinymesh module. The choice of this module was based on 
		the pin and API compatibility between the different families of the module. This means that you could swap shield changing the operating frequency without reflashing the MCU code!
		The protocol is a self configuring mesh with AES128 bit encryption.

--------------------------------------------------------------------------
KNOWN ISSUE: 
 1. PLEASE notice that there is a mistake on the LAYOUT. In Particular the transistor Q2 that controls the system shoutdown has been connected with Source-Gate swapped. 
	This error does not affect the main functionalities of the board, however it prevents it to shoutdown by the on/off button... basically the board stays always ON... 
	
----------------------------------------------------------------------------
DISCLAIMER:
THE MATERIAL IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIAL OR THE USE OR OTHER DEALINGS IN THE MATERIAL.