package org.DDAN;

import org.DDAN.GDCC.BadFormatException;
import org.DDAN.GDCC.GDobjReader;

import java.io.File;
import java.io.FileNotFoundException;

public class GDobjUtil {
	public static void main(String[] args) throws FileNotFoundException, BadFormatException {
		System.out.println(GDobjReader.read(new File("/Users/DDAN/Documents/GitHub/GDC/GDobjTest.o")));
	}
}
