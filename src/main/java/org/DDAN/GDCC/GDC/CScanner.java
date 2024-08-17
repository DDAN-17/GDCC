package org.DDAN.GDCC.GDC;

import org.DDAN.GDCC.Localization;
import org.DDAN.GDCC.Log;

import java.util.HashMap;
import java.util.Map;

import static org.DDAN.GDCC.GDC.TokenType.*;

public class CScanner {
	String file;
	int line = 0;
	int current = 0;
	int start = 0;
	Map<String, TokenType> keywords = new HashMap<>();

	CScanner(String file) {
		this.file = file;
		keywords.put("const", CONST);
		keywords.put("continue",CONTINUE);
		keywords.put("default",DEFAULT);
		keywords.put("do",DO);
		keywords.put("else",ELSE);
		keywords.put("enum",ENUM);
		keywords.put("for",FOR);
		keywords.put("if",IF);
		keywords.put("int",INT);
		keywords.put("return",RETURN);
		keywords.put("sizeof",SIZEOF);
		keywords.put("struct",STRUCT);
		keywords.put("switch",SWITCH);
		keywords.put("typedef",TYPEDEF);
		keywords.put("union",UNION);
		keywords.put("void",VOID);
		keywords.put("while",WHILE);
		keywords.put("static",STATIC);
		keywords.put("bool",BOOL);
		keywords.put("true",TRUE);
		keywords.put("false",FALSE);
		keywords.put("break",BREAK);
		keywords.put("case",CASE);
	}

	char advance() {
		return file.charAt(current++);
	}

	boolean match(char c) {
		if (peek() == c) {
			advance();
			return true;
		}
		return false;
	}

	char peek() {
		if (!isAtEnd()) {
			return file.charAt(current);
		}
		return '\u0000';
	}

	Token makeToken(TokenType t) {
		Token token = new Token(file.substring(start, current), line, t);
		start = current;
		return token;
	}

	void skipWhitespace() {
		char c = peek();

		switch (c) {
			case ' ':
			case '\r':
			case '\t':
				advance();
				start = current;
				skipWhitespace();
				break;
			case '\n':
				advance();
				start = current;
				line++;
				skipWhitespace();
				break;
		}
	}

	Token nextToken() {
		if (isAtEnd()) return makeToken(EOF);
		skipWhitespace();
		char c = advance();

		switch (c) {
			case '(': return makeToken(LEFT_PAREN);
			case ')': return makeToken(RIGHT_PAREN);
			case '{': return makeToken(LEFT_BRACE);
			case '}': return makeToken(RIGHT_BRACE);
			case ';': return makeToken(SEMICOLON);
			case ',': return makeToken(COMMA);
			case '.': return makeToken(DOT);
			case '=': return makeToken(EQUAL);
			case '#': return makeToken(HASH);
			case '+':
				if (match('+')) {
					return makeToken(PLUS_PLUS);
				} else if (match('=')) {
					return makeToken(PLUS_EQUAL);
				} else {
					return makeToken(PLUS);
				}
			case '-':
				if (match('-')) {
					return makeToken(MINUS_MINUS);
				} else if (match('=')) {
					return makeToken(MINUS_EQUAL);
				} else {
					return makeToken(MINUS);
				}
			case '*':
				if (match('=')) {
					return makeToken(STAR_EQUAL);
				} else {
					return makeToken(STAR);
				}
			case '/':
				if (match('=')) {
					return makeToken(SLASH_EQUAL);
				} else {
					return makeToken(SLASH);
				}
			case '>':
				if (match('=')) {
					return makeToken(GREATER_EQUAL);
				} else if (match('>')) {
					targetedError(Localization.getLocalization("no_bitwise"), ">>");
				} else {
					return makeToken(GREATER);
				}
			case '<':
				if (match('=')) {
					return makeToken(LESS_EQUAL);
				} else if (match('<')) {
					targetedError(Localization.getLocalization("no_bitwise"), "<<");
				} else {
					return makeToken(LESS);
				}
			case '|':
				if (match('|')) {
					return makeToken(OR);
				} else {
					targetedError(Localization.getLocalization("no_bitwise"), c);
				}
			case '!':
				if (match('=')) {
					return makeToken(BANG_EQUAL);
				} else {
					return makeToken(BANG);
				}
			case '&':
				if (match('&')) {
					return makeToken(AND);
				} else {
					targetedError(Localization.getLocalization("no_bitwise"), c);
				}
			default:
				if (isAlpha(c)) {
					return identifier();
				}
				return null;
		}
	}

	boolean isAlpha(char c) {
		return c >= 'a' && c <= 'z' ||
				c >= 'A' && c <= 'Z';
	}

	Token identifier() {
		while (isAlpha(peek())) {
			advance();
		}

		if (keywords.containsKey(file.substring(start, current))) {
			return makeToken(keywords.get(file.substring(start, current)));
		}

		return makeToken(IDENTIFIER);
	}

	boolean isAtEnd() {
		return current == file.length();
	}

	void targetedError(String msg, char c) {
		Log.error(msg + ": at \"" + c + "\"");
	}
	void targetedError(String msg, String c) {
		Log.error(msg + ": at \"" + c + "\"");
	}
}
