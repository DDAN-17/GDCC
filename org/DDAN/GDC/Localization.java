package org.DDAN.GDC;

import java.util.*;

public class Localization {
	public static HashMap<String, String> localizedStrings = new HashMap<>();

	public static void startLocalization() {
		ResourceBundle localization = ResourceBundle.getBundle("resources/localization", Locale.getDefault());
		Iterator<String> keys = localization.getKeys().asIterator();
		while (keys.hasNext()) {
			String curKey = keys.next();
			localizedStrings.put(curKey, localization.getString(curKey));
		}
	}

	public static String getLocalization(String key) {
		return localizedStrings.get(key);
	}
}
