package org.DDAN.GDC;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class GDC {
	public static void main(String[] args) {
		Localization.startLocalization();
		if (args.length == 0) {
			error(Localization.getLocalization("no_input_files"));
		}

		File file = new File(args[0]);
		Scanner fileScan = null;
		try {
			fileScan = new Scanner(file);
		} catch (FileNotFoundException e) {
			error(Localization.getLocalization("file_no_exist"));
		}

		if (fileScan != null) {
			CScanner fileScanner = new CScanner(fileScan.toString());
		}
	}

	public static void error(String msg) {
		System.err.println("gdc: " + ANSIColors.BRIGHT_RED + "error: " + ANSIColors.RESET + msg);
		System.exit(1);
	}
}
