#include <string>
class SerialDevice {
	int fd;
	public:
		SerialDevice(std::string device);
		SerialDevice(int device);
		SerialDevice(std::string device, int baud);
		-SerialDevice();
		void writeByte(unsigned char b);
		void writeInt(unsigned int b);
		char nextByte();
		unsigned int nextInt();
		void flush();
		int available();
}
