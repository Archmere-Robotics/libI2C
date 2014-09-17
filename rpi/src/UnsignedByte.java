
public class UnsignedByte {
	public static UnsignedByte[] makeUnsigned(byte[] bytes) {
		UnsignedByte[] out = new UnsignedByte[bytes.length];
		for(int i=0;i<bytes.length;i++)
			out[i] = new UnsignedByte(bytes[i]);
		return out;
	}
	public static UnsignedByte[] makeUnsigned(int[] bytes) {
		UnsignedByte[] out = new UnsignedByte[bytes.length];
		for(int i=0;i<bytes.length;i++)
			out[i] = new UnsignedByte(bytes[i]);
		return out;
	}
	public static byte[] makeSigned(UnsignedByte[] bytes) {
		byte[] out = new byte[bytes.length];
		for(int i=0;i<bytes.length;i++)
			out[i] = bytes[i].toByte();
		return out;
	}
	protected byte data;
	public UnsignedByte(int data) {
		this.data = (byte) (data&0xFF);
	}
	public UnsignedByte(byte data) {
		this.data = data;
	}
	public byte toByte() {
		return data;
	}
}
