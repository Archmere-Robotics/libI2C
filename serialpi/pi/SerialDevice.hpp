#include <string.h>
class SerialDevice {
	int fd;
	public:
		SerialDevice(string device);
		SerialDevice(int device);
		SerialDevice(string device, int baud);
		void writeByte(byte b);
		void writeShort(unsigned short b);
		void writeInt(unsigned int b);
		byte readByte();
		short readShort();
		int readInt();
}
