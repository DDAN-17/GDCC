package org.DDAN.GDCC.GDL;

import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorOutputStream;
import org.bouncycastle.crypto.paddings.PKCS7Padding;
import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.w3c.dom.Document;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.zip.DataFormatException;

public class LevelData {
	public static byte[] key = {
			0x69, 0x70, 0x75, 0x39, 0x54, 0x55, 0x76, 0x35,
			0x34, 0x79, 0x76, 0x5D, 0x69, 0x73, 0x46, 0x4D,
			0x68, 0x35, 0x40, 0x3B, 0x74, 0x2E, 0x35, 0x77,
			0x33, 0x34, 0x45, 0x32, 0x52, 0x79, 0x40, 0x7B
	};

	public static Document decode() throws Exception {
		String OSName = System.getProperty("os.name");
		if (OSName.contains("Mac")) {
			return macosDecode();
		} else if (OSName.contains("Windows")) {
			return windowsDecode();
		} else {
			throw new Exception("OS not supported.");
		}
	}

	public static void encode(Document doc) throws Exception {
		String OSName = System.getProperty("os.name");
		if (OSName.contains("Mac")) {
			macosEncode(doc);
		} else if (OSName.contains("Windows")) {
			windowsEncode(doc);
		} else {
			throw new Exception("OS not supported.");
		}
	}

	public static Document windowsDecode() {
		String path = System.getProperty("user.home") + "/AppData/Roaming/GeometryDash/CCLocalLevels.dat";
		byte[] bytes;
		try {
			bytes = Files.readAllBytes(Paths.get(path));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		String xml;
		try {
			xml = new String(xorDecode(bytes));
		} catch (IOException | DataFormatException e) {
			throw new RuntimeException(e);
		}


		File file = new File(System.getProperty("user.home") + "AppData/Roaming/GeometryDash/CCLocalLevels.xml");
		FileWriter fileWriter;
		try {
			fileWriter = new FileWriter(file);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		try {
			fileWriter.write(xml);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		try {
			fileWriter.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder;
		try {
			builder = factory.newDocumentBuilder();
		} catch (ParserConfigurationException e) {
			throw new RuntimeException(e);
		}
		Document document;
		try {
			document = builder.parse(file);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}

		return document;
	}

	public static void windowsEncode(Document xmlDoc) throws IOException {
		DOMSource domSource = new DOMSource(xmlDoc);
		Transformer transformer;
		try {
			transformer = TransformerFactory.newDefaultInstance().newTransformer();
		} catch (TransformerConfigurationException e) {
			throw new RuntimeException(e);
		}
		ByteArrayOutputStream os = new ByteArrayOutputStream();
		StreamResult result = new StreamResult(os);
		try {
			transformer.transform(domSource, result);
		} catch (TransformerException e) {
			throw new RuntimeException(e);
		}
		String xml = os.toString();

		byte[] encoded = xorEncode(xml.getBytes());
		String path = System.getProperty("user.home") + "/AppData/Roaming/GeometryDash/CCLocalLevels.dat";

		FileOutputStream fileWriter;
		try {
			fileWriter = new FileOutputStream(path);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			fileWriter.write(encoded);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		fileWriter.close();
	}

	public static byte[] xorEncode(byte[] bytes) {
		byte[] bytes1 = b64Decode(new String(bytes));

		for (int i = 0; i < bytes1.length; i++) {
			bytes1[i] ^= 11;
		}

		return bytes1;
	}

	public static byte[] xorDecode(String in) throws IOException, DataFormatException {
		Base64.Decoder decoder = Base64.getUrlDecoder();
		return xorDecode(decoder.decode(in));
	}

	public static byte[] xorDecode(byte[] bytes) throws IOException, DataFormatException {
		for (int i = 0; i < bytes.length; i++) {
			bytes[i] ^= 11;
		}

		return b64Decode(new String(bytes));
	}

	public static byte[] b64Decode(String bytes) {
		Base64.Decoder decoder = Base64.getUrlDecoder();
		byte[] bytes1 = decoder.decode(bytes);

		ByteArrayOutputStream out;
		try {
			InputStream fin = new ByteArrayInputStream(bytes1);
			BufferedInputStream in = new BufferedInputStream(fin);
			out = new ByteArrayOutputStream();
			GzipCompressorInputStream gzIn = new GzipCompressorInputStream(in);
			final byte[] buffer = new byte[512];
			int n;
			while (-1 != (n = gzIn.read(buffer))) {
				out.write(buffer, 0, n);
			}
			out.close();
			gzIn.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			return out.toByteArray();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public static String b64Encode(byte[] bytes) throws IOException {
		InputStream in = new ByteArrayInputStream(bytes);
		ByteArrayOutputStream fout = new ByteArrayOutputStream();
		BufferedOutputStream out = new BufferedOutputStream(fout);
		GzipCompressorOutputStream gzOut = new GzipCompressorOutputStream(out);
		final byte[] buffer = new byte[512];
		int n;
		while (-1 != (n = in.read(buffer))) {
			gzOut.write(buffer, 0, n);
		}
		gzOut.close();
		in.close();

		Base64.Encoder encoder = Base64.getUrlEncoder();
		return new String(encoder.encode(fout.toByteArray()));
	}

	public static byte[] b64String(String b64) {
		Base64.Decoder decoder = Base64.getUrlDecoder();
		return decoder.decode(b64);
	}

	public static Document macosDecode() {

		String path = System.getProperty("user.home") + "/Library/Application Support/GeometryDash/CCLocalLevels.dat";
		byte[] bytes;
		try {
			bytes = Files.readAllBytes(Paths.get(path));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		File file = new File(System.getProperty("user.home") + "/Library/Application Support/GeometryDash/CCLocalLevels.xml");
		FileWriter fileWriter;
		try {
			fileWriter = new FileWriter(file);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		byte[] decoded = aesDecode(bytes);

		try {
			fileWriter.write(new String(decoded));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			fileWriter.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder;
		try {
			builder = factory.newDocumentBuilder();
		} catch (ParserConfigurationException e) {
			throw new RuntimeException(e);
		}

		Document document;
		try {
			document = builder.parse(file);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}

		return document;
	}

	public static void macosEncode(Document xmlDoc) throws IOException {
		DOMSource domSource = new DOMSource(xmlDoc);
		Transformer transformer;
		try {
			transformer = TransformerFactory.newDefaultInstance().newTransformer();
		} catch (TransformerConfigurationException e) {
			throw new RuntimeException(e);
		}
		ByteArrayOutputStream os = new ByteArrayOutputStream();
		StreamResult result = new StreamResult(os);
		try {
			transformer.transform(domSource, result);
		} catch (TransformerException e) {
			throw new RuntimeException(e);
		}
		String xml = os.toString();
		byte[] encoded = aesEncode(xml.getBytes());
		String path = System.getProperty("user.home") + "/Library/Application Support/GeometryDash/CCLocalLevels.dat";
		FileOutputStream fileWriter;
		try {
			fileWriter = new FileOutputStream(path);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			fileWriter.write(encoded);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		fileWriter.close();

	}

	public static byte[] aesDecode(String in) {
		Base64.Decoder decoder = Base64.getUrlDecoder();
		return aesDecode(decoder.decode(in));
	}

	public static byte[] aesDecode(byte[] in) {
		Cipher aes;
		try {
			aes = Cipher.getInstance("AES/ECB/PKCS7Padding", new BouncyCastleProvider());
		} catch (NoSuchPaddingException | NoSuchAlgorithmException e) {
			throw new RuntimeException(e);
		}

		try {
			aes.init(Cipher.DECRYPT_MODE, new SecretKeySpec(key, "AES"));
		} catch (InvalidKeyException e) {
			throw new RuntimeException(e);
		}

		PKCS7Padding padding = new PKCS7Padding();
		padding.addPadding(in, in.length);

		byte[] out;
		try {
			out = aes.doFinal(in);
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			throw new RuntimeException(e);
		}

		return out;
	}

	public static byte[] aesEncode(String in) {
		Base64.Decoder decoder = Base64.getUrlDecoder();
		return aesEncode(decoder.decode(in));
	}

	public static byte[] aesEncode(byte[] in) {
		Cipher aes;
		try {
			aes = Cipher.getInstance("AES/ECB/PKCS7Padding", new BouncyCastleProvider());
		} catch (NoSuchPaddingException | NoSuchAlgorithmException e) {
			throw new RuntimeException(e);
		}

		try {
			aes.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key, "AES"));
		} catch (InvalidKeyException e) {
			throw new RuntimeException(e);
		}

		PKCS7Padding padding = new PKCS7Padding();
		padding.addPadding(in, in.length);

		byte[] out;
		try {
			out = aes.doFinal(in);
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			throw new RuntimeException(e);
		}

		return out;
	}
}
