#include "libCom.h"
<<<<<<< HEAD
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
=======
//You have no use for this library with an emulator
#ifndef ROBOT
	#error This library will only do stuff on REAL robots.
#endif
#if (_TARGET == "Emulator")
	#define SENSOR      SensorValue
#else 
	#define SENSOR      SensorValueSimulations
#endif

typedef PIN unsigned byte;
typedef struct {
	byte * data;
	size_t len;
} BUFFER;
PIN PIN_DATA=		0x01;
PIN PIN_CLK=		0x02;
static PIN pins = 	0x00;
static tsensor HTPB;
static bool valClk=false;
static BUFFER buffer;
static BUFFER dim(t_size size) {
	BUFFER tmp;
	tmp.data = (byte*)malloc(size);
	tmp.len=size;
	return tmp;
}
static BUFFER redim(BUFFER buffer, int delta) {
	BUFFER tmp;
	tmp.data=(byte*)malloc(buffer.len+delta);
	tmp.len=sizeof(tmp.data);
	for(int i=0;i<buffer.len;i++) {
		tmp.data[i]=buffer.data[i];
	}
	release(buffer);
	return tmp;
}
static void release(BUFFER buffer) {
	free(buffer.data);
	free(buffer.len);
	free(buffer);
}
static BUFFER bufcat(BUFFER A, BUFFER B) {
	BUFFER C = dim(A.len+B.len);
	for(int i=0;i<A.len;i++) {
		C.data[i]=A.data[i];
	}
	for(int i=0;i<B.len;i++) {
		C.data[i+A.len]=B.data[i];
	}
	return c;
}
void pushBytes(byte * bytes) {
	BUFFER tmp;
	tmp.data=bytes;
	tmp.len = sizeof(bytes);
	BUFFER out = bufcat(buffer, tmp);
	release(buffer);
	release(tmp);
	buffer=out;
	release(out);
}
//TODO: look into whether param type/should be a pointer/address
void com_init(tsensor* _HTPB) {
	HTPBsetupIO(_HTPB, PIN_DATA);
	HTPBsetupIO(_HTPB, PIN_CLK);
	HTPB=_HTPB;
	buffer.data={};
	buffer.len=0;
	StartTask(comMain);
}
void setPin(PIN pin, bool value) {
	pins = value?(pins|pin):(pins&(~pin));
	HTPBwriteIO(HTPB, pins);
>>>>>>> FETCH_HEAD
}
bool readPin(int pin) {
  return false;//TODO: finish
}
void _Sleep(int msec) {
	ClearTimer(T1);
	endTimeslice();
	Sleep(max(time1[T1]-msec,0));
}
task comMain() {
	//bits to send
	bool[8] bits;
	byte bitNum;//bit to send next
	while(true) {
  	
  	_Sleep(50);
  }
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
