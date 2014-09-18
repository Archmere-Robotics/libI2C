#include "libCom.h"
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
