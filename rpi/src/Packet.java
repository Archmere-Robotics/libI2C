import java.nio.ByteBuffer;

public class Packet {
	public static final boolean debug = false;
	public static long packetNum = 1;

	public static final int lrot(int src, byte times) {
		int out = src;
		for (; times > 0; times--)
			out = lrot(out);
		return out;
	}

	public static final int rrot(int src, byte times) {
		int out = src;
		for (; times > 0; times--)
			out = rrot(out);
		return out;
	}

	public static final int lrot(int src) {
		return src << 2 + ((src & 0xFF000000) >> 6);
	}

	public static final int rrot(int src) {
		return src >> 2 + ((src & 0xFF) << 6);
	}

	public static final int rrot(byte src, byte times) {
		byte out = src;
		for (; times > 0; times--)
			out = rrot(out);
		return out;
	}

	public static final byte rrot(byte src) {
		return (byte) (src >> 1 + ((src & 0x8) << 7));
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
			chk_1 += (tmp & 0x1) + ((tmp & 0x2) >> 2) + ((tmp & 0x4) >> 4)
					+ ((tmp & 0x8) >> 6);
			chk_2 += (tmp & 0x3) + ((tmp & 0xC) >> 2) + ((tmp & 0x6) << 3)
					+ ((tmp & 0x9) << 6);
			chk_3 += (rrot(tmp, (byte) 1) & 0x3) << 0 + (rrot(tmp, (byte) 2) & 0x3) << 2 + (rrot(
					tmp, (byte) 3) & 0x3) << 4 + (rrot(tmp, (byte) 4) & 0x3) << 6;
			chk_4 += rrot(tmp) << 0 + (rrot(tmp, (byte) 2)) << 2 + (rrot(tmp,
					(byte) 3)) << 4 + tmp << 6;
			int tmp_4 = chk_4;
			chk_4 = rrot(chk_3);
			chk_3 = lrot(chk_2);
			chk_2 = rrot(chk_1);
			chk_1 = lrot(tmp_4, (byte) 2);
		}
		if (debug) {
			System.out.println("Checksum data:");
			System.out.println("1\t2\t3\t4");
			System.out.println(Integer.toHexString(chk_1) + "\t"
					+ Integer.toHexString(chk_2) + "\t"
					+ Integer.toHexString(chk_3) + "\t"
					+ Integer.toHexString(chk_4));
		}
		return ByteBuffer.allocate(Integer.BYTES)
				.putInt((chk_1 + chk_2) | (chk_3 + chk_4)).array();
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
