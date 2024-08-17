package org.DDAN.GDCC;

import java.util.*;

public class Localization {
	static ResourceBundle localization = ResourceBundle.getBundle("l10n", Locale.getDefault());

	public static String getLocalization(String key) {
		try {
			return localization.getString(key);
		} catch (MissingResourceException e) {
			Log.error("Internal Error. Error Code 0001, Data: " + key);
			return "__MISSINGERR__";
		}
	}
}
