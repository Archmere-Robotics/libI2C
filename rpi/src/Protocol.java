public class Protocol {
  public static final short pin_DATA=0x01;
  public static final short pin_CLK= 0x02;
  public static final short pin_REQ= 0x03;
  public static final short pin_ACK= 0x04;
  public static final short mspb= 50;
  static boolean isSending=false;
  public static boolean clk_pos=false;
  public static final byte intToByte(int i) {
    return (byte)(i & 0x00FF);
  }
  public static final boolean sleep(int millis) {
	  try {
		  Thread.sleep(millis);
		  return true;
	  } catch(InterruptedException e) {
		  return false;
	  }
  }
  public static void setPin(short pin, boolean value) {
    System.out.println("PIN"+pin+"|"+value);
  }
  public static boolean getPin(short pin) {
    return false;
  }
  public static void beginTransmit() {
      //send REQ
      setPin(pin_REQ,true);
      //wait for ACK
      while(!getPin(pin_ACK)) {
        sleep(5);
      }
  }
  public static void endTransmit() {
      //send REQ
      setPin(pin_REQ,false);
      //wait for ACK
      while(getPin(pin_ACK)) {
        sleep(5);
      }
  }
  public static void sendBit(boolean b) {
    setPin(pin_DATA, b);
    setPin(pin_CLK,(clk_pos=!clk_pos));
  }
  public static void sendByte(byte x) {
    boolean bs[] = new boolean[4];
    /*bs[0] = ((x & 0x01) != 0);
    bs[1] = ((x & 0x02) != 0);
    bs[2] = ((x & 0x04) != 0);
    bs[3] = ((x & 0x08) != 0);*/
    for(byte i=0;i<8;i++) {
    	bs[i]=(x & (byte)(1<<i))!=0;
    }
    beginTransmit();
    for(byte i=0;i<4;i++) {
      sendBit(bs[i]);
    }
  }
  public static byte[] write(byte[] src, byte[] data, int begin, int end) {
    for(int i=begin;i<end;i++)src[i]=data[i-begin];
    return src;
  }
  public static byte[] write(byte[] src, byte data, int index) {
    src[index]=data;
    return src;
  }
  public static void sendBytes(byte[] bs) {
    //make header
    byte[] header = new byte[2];
    //first is length
    header[0]=intToByte(bs.length);
    //seccond
  }
  public static void send() {
    
  }
}
