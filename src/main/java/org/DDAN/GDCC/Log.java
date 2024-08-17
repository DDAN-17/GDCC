package org.DDAN.GDCC;

public class Log {
	static String program = "GDCC";

	public static void info(String message) {
		System.out.println(program + ": \033[90m" + Localization.getLocalization("info") + ":\033[0m " + message);
	}

	public static void error(String message) {
		System.out.println(program + ": \033[91m" + Localization.getLocalization("error") + ":\033[0m " + message);
	}

	public static void warn(String message) {
		System.out.println(program + ": \033[93m" + Localization.getLocalization("warn") + ":\033[0m " + message);
	}

	public static void setup(String program) {
		Log.program = program;
	}
}
