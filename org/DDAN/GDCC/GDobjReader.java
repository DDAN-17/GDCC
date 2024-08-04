package org.DDAN.GDCC;

import java.io.*;

public class GDobjReader {
	public static GDobj read(File path) throws BadFormatException, FileNotFoundException {
		try {
			FileInputStream stream = new FileInputStream(path);
			byte[] sig = new byte[5];
			sig[0] = (byte) stream.read();
			sig[1] = (byte) stream.read();
			sig[2] = (byte) stream.read();
			sig[3] = (byte) stream.read();
			sig[4] = (byte) stream.read();
			if (!new String(sig).equals("GDobj")) {
				throw new BadFormatException(path.getName() + " is not in GDobj format or is corrupted.");
			}
			int version = stream.read();
			byte[] idBytes = new byte[10];
			idBytes[0] = (byte) stream.read();
			idBytes[1] = (byte) stream.read();
			idBytes[2] = (byte) stream.read();
			idBytes[3] = (byte) stream.read();
			idBytes[4] = (byte) stream.read();
			idBytes[5] = (byte) stream.read();
			idBytes[6] = (byte) stream.read();
			idBytes[7] = (byte) stream.read();
			idBytes[8] = (byte) stream.read();
			idBytes[9] = (byte) stream.read();
			String id = new String(idBytes);
			byte itemSizeLo = (byte) stream.read();
			byte itemSizeHi = (byte) stream.read();
			int itemSize = ((int) itemSizeHi) * 256 + ((int) itemSizeLo);
			String[] items = new String[itemSize];
			for (int i = 0; i < itemSize; i++) {
				byte next = (byte) stream.read();
				if (next == 0x00) {
					continue;
				}
				String finalString = Character.toString(next);
				next = (byte) stream.read();
				while (next != 0x00) {
					finalString = finalString.concat(Character.toString(next));
					next = (byte) stream.read();
				}
				items[i] = finalString;
			}
			byte groupSizeLo = (byte) stream.read();
			byte groupSizeHi = (byte) stream.read();
			int groupSize = ((int) groupSizeHi) * 256 + ((int) groupSizeLo);
			String[] groups = new String[groupSize];
			for (int i = 0; i < groupSize; i++) {
				byte next = (byte) stream.read();
				if (next == 0x00) {
					continue;
				}
				String finalString = Character.toString(next);
				next = (byte) stream.read();
				while (next != 0x00) {
					finalString = finalString.concat(Character.toString(next));
					next = (byte) stream.read();
				}
				groups[i] = finalString;
			}
			String code = "";
			while (stream.available() != 1) {
				code = code.concat(Character.toString(stream.read()));
			}
			return new GDobj(version, id, groups, items, code);
		} catch (FileNotFoundException e) {
			throw e;
		} catch (IOException e) {
			throw new BadFormatException(path.getName() + " is not in GDobj format or is corrupted.");
		}
	}
}