package org.DDAN.GDC;

import java.nio.file.Files;
import java.nio.file.Path;

public class GDC {
	public static void main(String[] args) {
		Localization.startLocalization();
		if (args.length == 0) {
			error(Localization.getLocalization("no_input_files"));
		}
		if (!Files.exists(Path.of(args[0]))) {
			error(Localization.getLocalization("file_no_exist"));
		}
	}

	public static void error(String msg) {
		System.err.println("gdc: " + ANSIColors.BRIGHT_RED + "error: " + ANSIColors.RESET + msg);
		System.exit(1);
	}
}
