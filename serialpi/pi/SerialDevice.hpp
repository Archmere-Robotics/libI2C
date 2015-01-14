#include <string>
class SerialDevice {
	int fd;
	public:
		SerialDevice(std::string device);
		SerialDevice(int device);
		SerialDevice(std::string device, int baud);
		-SerialDevice();
		void writeByte(byte b);
		void writeShort(unsigned short b);
		void writeInt(unsigned int b);
		byte readByte();
		short readShort();
		int readInt();
}
