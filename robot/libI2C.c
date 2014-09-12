#include libI2C.h
void setupI2C(short port) {
  // The data to be written: 0x10 = 010000 binary,
  // makes B4 digital port an output.
	HTPBsetupIO(HTPB, port);
}
task readi2c() {
  while(true) {
    if(HTPBreadIO(HTPB, 0xF3) == 0) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Magnet present");
      HTPBwriteIO(HTPB, 0x10);
    } else {
      eraseDisplay();
      nxtDisplayTextLine(1, "Magnet absent");
      HTPBwriteIO(HTPB, 0x00);
    }
    wait1Msec(50);
  }
}
