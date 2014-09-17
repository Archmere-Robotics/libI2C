import java.nio.ByteBuffer;

public class Packet {
	public static final boolean debug = false;
	public static long packetNum = 1;

	public static final int lrot(int src, int bits) {
		return return (src >>> bits) | (src << (Integer.SIZE - bits));
	}

	public static final int rrot(int src, int bits) {
		return (src << bits) | (src >>> (Integer.SIZE - bits));
	}
	public static byte rotateRight(byte bits, int shift) {
		return (byte)(((bits & 0xff)  >>> shift) | ((bits & 0xff) << (8 - shift)));
	}
	public static byte rotateLeft(byte bits, int shift) {
		return (byte)(((bits & 0xff) << shift) | ((bits & 0xff) >>> (8 - shift)));
	}

	public synchronized static byte[] bCat(byte[]... bytes) {
		int size = 0;
		for (int i = 0; i < bytes.length; i++)
			size += bytes[i].length;
		ByteBuffer b = ByteBuffer.allocate(size);
		for (int i = 0; i < bytes.length; i++) {
			b.put(bytes[i]);
		}
		return b.array();
	}

	protected byte[] data;
	protected long num;
	protected long ACK = 0;

	public Packet(byte[] data) {
		this.data = data;
		this.num = packetNum++;
	}

	public Packet(byte[] data, long ACK) {
		this(data);
		this.ACK = ACK;
	}

	/**
	 * 
	 * @return byte[4]
	 */
	protected byte[] getChecksum() {
		int chk_1 = 0, chk_2 = 0, chk_3 = 0, chk_4 = 0;
		for (int i = 0; i < data.length; i++) {
			byte tmp = data[i];
			chk_1 += tmp&0x01 + ((tmp&0xFF)>>2)&0x01 + ((tmp&0xFF)>>4)&0x01 + ((tmp&0xFF)>>6)&0x01;//sum of the bits
			chk_2 += (tmp&0xFF)&0x03 + ((tmp&0xFF)>>2)&0x03 + ((tmp&0xFF)>>4)&0x03 + ((tmp>>6)&0x03;//sum of pairs of bits
			chk_3 += tmp&0x07 + rotateRight(tmp,0x2)&0x07 + rotateRight(tmp,0x4)&0x07 + rotateRight(tmp,0x6)&0x07;//sum of tripplets
			chk_4 += tmp&0xFF + rotateRight(tmp,0x2)&0xFF + rotateRight(tmp,0x4)&0xFF + rotateRight(tmp,0x6)&0xFF;//sum of rotated bytes
			//rotate the checksums (assures that a byte of 0x00 has an effect on the checksum)
			int tmp_4 = chk_4;
			chk_4 = rrot(chk_3,1);
			chk_3 = rrot(chk_2,1);
			chk_2 = rrot(chk_1,1);
			chk_1 = rrot(tmp_4,1);
		}
		byte[] chk = ByteBuffer.allocate(Integer.BYTES).putInt((chk_1 + chk_2) ^ (chk_3 + chk_4)).array();
		if (debug) {
			System.out.println("Checksum data:");
			System.out.println("1\t2\t3\t4");
			System.out.println(Integer.toHexString(chk_1) + "\t"
					+ Integer.toHexString(chk_2) + "\t"
					+ Integer.toHexString(chk_3) + "\t"
					+ Integer.toHexString(chk_4));
			System.out.println("Checksum\n"+Tester.bytesToHex(chk));
		}
		return chk;
	}

	public byte[] getHeader() {
		byte[] chk = getChecksum();
		boolean hasAck = (ACK != 0);
		if(debug)System.out.println("CHK Size: " + Integer.toHexString(chk.length));
		ByteBuffer hBuffer = ByteBuffer.allocate(Integer.BYTES * 2 + chk.length
				+ (Long.BYTES*(hasAck ? 2 : 1)));
		if(debug)System.out.println("HEAD Size: "
				+ Integer.toHexString(Integer.BYTES * 2 + chk.length));
		hBuffer.putInt(Integer.BYTES * 2 + chk.length);// header length
														// (includes checksum)
		if(debug)System.out.println("DATA Size: " + Integer.toHexString(data.length));
		hBuffer.putInt(data.length);// length of data
		if(debug)System.out.println("CHECKSUM:" + Tester.bytesToHex(chk));
		hBuffer.put(chk);
		if(debug)System.out.println("NUM:"+num);
		hBuffer.putLong(num);
		if (hasAck) {
			if(debug)System.out.println("ACK: " + ACK);
			hBuffer.putLong(ACK);
		}
		return hBuffer.array();
	}

	public byte[] getBytes() {
		byte[] header = getHeader();
		return bCat(header, data);
	}
}
