package org.DDAN;

import org.DDAN.GDL.LevelData;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class LevelDataUtil {
	public static void main(String[] args) {
		Document test;
		try {
			test = LevelData.decode();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}

		NodeList tags = test.getElementsByTagName("s");

		String levelData = "";
		Node levelDataTag = null;
		for (int i = 0; i < tags.getLength(); i++) {
			if (!Objects.equals(tags.item(i).getTextContent(), "Trigger Testing")) {
				continue;
			}
			try {
				levelDataTag = tags.item(i + 1);
				String levelData2 = levelDataTag.getTextContent();
				levelData = new String(LevelData.b64Decode(levelData2));
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
			break;
		}

		System.out.println(levelData.substring(levelData.indexOf(";") + 1));

		if (Integer.decode(args[0]) == 0) {
			return;
		}

		levelData = levelData.concat(new Scanner(System.in).nextLine());

		try {
			levelData = LevelData.b64Encode(levelData.getBytes());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		if (levelDataTag != null) {
			levelDataTag.setTextContent(levelData);
		}

		try {
			LevelData.encode(test);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
