package org.DDAN.GDC;

import static org.DDAN.GDC.TokenType.*;

public class CScanner {
	String file;
	int line = 0;
	int current = 0;
	int start = 0;

	CScanner(String file) {
		this.file = file;
	}

	char advance() {
		return file.charAt(current++);
	}

	boolean match(char t) {
		if (peek() == t) {
			advance();
			return true;
		}
		return false;
	}

	char peek() {
		return file.charAt(current + 1);
	}

	Token makeToken(TokenType t) {
		Token token = new Token(file.substring(start, current), line, t);
		start = current;
		return token;
	}

	Token nextToken() {
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
				return makeToken(IDENTIFIER);
		}
	}

	boolean isAtEnd() {
		return file.charAt(current) == '\0';
	}

	void targetedError(String msg, char c) {
		GDC.error(msg + " at character \"" + c + "\"");
	}
	void targetedError(String msg, String c) {
		GDC.error(msg + " at character \"" + c + "\"");
	}
}
