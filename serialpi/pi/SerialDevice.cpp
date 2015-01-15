#include "SerialDevice.hpp"
#include <vector>
#define STD_BAUD 115200
SerialDevice::SerialDevice(std::string name, int baud) {
	this->fd=serialOpen(str.c_str(),baud);
}
SerialDevice::SerialDevice(std::string name) {
	this->fd=serialOpen(str.c_str(),STD_BAUD);
}
SerialDevice::SerialDevice(int fd) {
	this->fd=fd;
}
SerialDevice::-SerialDevice() {
	serialClose(this->fd);
}
void SerialDevice::sendChar(unsigned char b) {
	serialPuts(this->fd,b);
}
void SerialDevice::sendBytes(int num, unsigned char* b) {
	for(int i=0;i<num;i++) {
		sendChar(b[i]);
	}
}
void SerialDevice::sendString(std::string b) {
	serialPrintf(this->fd,b);
}
void SerialDevice::sendInt(unsigned int b) {
	char* bytes = intToBytes(b);
	sendBytes(bytes);
	delete bytes;
}
void SerialDevice::flush() {
	serialFlush(this->fd);
}
int SerialDevice::available() {
	return serialDataAvail(this->fd);
}
char SerialDevice::nextByte() {
	return serialGetchar(this->fd) & 0xFF;
}
int SerialDevice::nextInt() {
	int result=0;
	char c;
	for(int i=0;i<4;i++,result<<8) {
		result+=(c = this->nextByte());
		if(c==-1)
			return -1;
	}
	return result;
}
static char* intToBytes(int paramInt) {
	char* result=new char[4];
	for (int i = 0; i < 4; i++)
		result[3 - i] = (paramInt >> (i * 8));
	return result;
}
