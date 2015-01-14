#include <wiringSerial.h>
#include "SerialDevice.hpp"
class HTSPB {
	SerialDevice * device;
	public:
		HTSPB(string location);
		HTSPB(SerialDevice * device);
		-HTSPB();
		void set(unsigned int address, unsigned int value);
		int get(unsigned int address);
}
