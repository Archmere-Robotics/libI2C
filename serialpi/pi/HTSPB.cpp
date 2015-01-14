#include <wiringSerial.h>
#include "HTSPB.hpp"
HTSPB::HTSPB(SerialDevice * device) {
	this->device = device;
}
HTSPB::HTSPB(string devPath) {
	this->device = new SerialDevice(devPath);
}
HTSPB::-HTSPB() {
	delete this->device;
}
void HTSPB::set(unsigned int address, unsigned int value) {
	this->device->writeByte(0x01);
	this->device->writeInt(address);
	this->device->writeInt(value);
}
int HTSPB::get(unsigned int address) {
	this->device->writeByte(0x02);
	this->device->writeInt(address);
	return this->device->readInt();
}
