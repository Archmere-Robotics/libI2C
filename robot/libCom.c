#include "libCom.h"
static const int clockSpeed=500;
static int clock=false;
static unsigned byte pins=0x00;
static const unsigned byte PIN_CLOCK=0x01;
static const unsigned byte PIN_DATA=0x02;
bool bLock=false;
byte* buffer;
unsigned int bLen=0;
static bool[8] bitBuffer;
static unsigned byte bitPos=8;
void setPin(unsigned byte pin, bool value) {
	if(value) {
		pins=pins|pin;
	} else {
		pins=pins&(~pin);
	}
}
bool readPin(int pin) {
  return false;
}
void toggleClock() {
	setPin(PIN_CLOCK,(clock=!clock));
}
void pushByes(byte* bytes, unsigned int number) {
	int startPos=reDim(number);
	for(int i=startPos;i<
}
int reDim(int delta) {
	while(bLock){sleep(1);}
	bLock=true;
	byte* tempBuffer = byte[bLen+delta];
	if(delta>0) {
		for(int i=0;i<bLen;i++) {
			tempBuffer[i]=buffer[i];
		}
	}else{
		for(int i=0;i<bLen+delta;i++) {
			tempBuffer[i]=buffer[i-delta];
		}
	}
	buffer=tempBuffer;
	bLen=bLen+delta;
	bLock=false;
	return bLen-delta;
}
unsigned byte nextByte() {
	unsigned byte b=buffer[0];
	reDim(-1);
	return b;
}
void mpt() {
	while(true) {
		if(bitPos>=8 && bLen>0) {
			unsigned byte b=nextByte();
			bitBuffer[0]=b&0x1==1;
			bitBuffer[0]=b&0x2==1;
			bitBuffer[0]=b&0x4==1;
			bitBuffer[0]=b&0x8==1;
		} else if(bLen==0){
			//do nothing
		} else {
			setPin(PIN_DATA,bitBuffer[bitPos++]);
		}
		//read byte
		toggleClock();
	}
}