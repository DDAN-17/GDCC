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
			System.exit(1); // Unreachable
		}

		CScanner fileScanner = null;
		StringBuilder fileString = new StringBuilder();
		while (fileScan.hasNextLine()) {
			fileString.append(fileScan.nextLine());
			if (fileScan.hasNextLine()) {
				fileString.append("\n");
			}
		}
		fileScanner = new CScanner(fileString.toString());

		Compiler compiler = new Compiler(fileScanner);
	}

	public static void error(String msg) {
		System.err.println("gdc: " + ANSIColors.BRIGHT_RED + "error: " + ANSIColors.RESET + msg);
		System.exit(1);
	}
}
