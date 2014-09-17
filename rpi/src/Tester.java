import java.util.Random;

public class Tester {
	final protected static char[] hexArray = "0123456789ABCDEF".toCharArray();

	public static String bytesToHex(byte[] bytes) {
		char[] hexChars = new char[bytes.length * 2];
		for (int j = 0; j < bytes.length; j++) {
			int v = bytes[j] & 0xFF;
			hexChars[j * 2] = hexArray[v >>> 4];
			hexChars[j * 2 + 1] = hexArray[v & 0x0F];
		}
		return new String(hexChars);
	}

	public static String strSplit(String src) {
		String t = "";
		for (int i = 0; i < src.length(); i += 2) {
			t += src.substring(i, i + 2) + " ";
		}
		return t;
	}

	public static void main(String[] args) {
		{
			byte[] testInt = UnsignedByte.makeSigned(UnsignedByte.makeUnsigned(new int[] {0x00, 0x00, 0x00, 0x00}));
			int out = (testInt[0]<<6)+testInt[1]<<4+testInt[2]<<2+testInt[3];
			
			System.out.println(out);
		}
		System.exit(0);
		Packet packet = new Packet(UnsignedByte.makeSigned(UnsignedByte
				.makeUnsigned(new int[] { 0xFF, 0xFF, 0x00, 0x32, 0x00 })));
		String s = bytesToHex(packet.getBytes());
		System.out
				.println(strSplit("HLHLHLHLDLDLDLDLCCCCCCCCNNNNNNNNNNNNNNNNDDDDDDDDDD"));
		System.out.println(strSplit(s));
		Random r = new Random(System.currentTimeMillis());
		while (true) {
			byte[] bytes = new byte[5];
			r.nextBytes(bytes);
			packet = new Packet(bytes);
			System.out.println(strSplit(bytesToHex(packet.getBytes())));
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
// 00 1E 03 7F
// 00 1C 0B 17