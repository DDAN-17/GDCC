#include "scanner.h"
#include "common.h"
#include "localization.h"

void error(char*);
void warning(char*);

typedef struct {
	const char* start;
	const char* current;
	int line;
} Scanner ;

Scanner scanner;

void initScanner(char* source) {
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

Token makeToken(TokenType tokenType) {
	Token token;
	token.type = tokenType;
	token.start = scanner.start;
	token.length = (int)(scanner.current - scanner.start);
	token.line = scanner.line;
	return token;
}

char advance() {
	scanner.current++;
	return scanner.current[-1];
}

char peek() {
	return *scanner.current;
}

char peek2() {
	return *(scanner.current + 1);
}

char match(char c) {
	if (peek() == c) {
		advance();
		return true;
	}
	return false;
}

bool isAtEnd() {
  return *scanner.start == '\0';
}

void targetedError(char* msgIn, char loc) {
	char* msg;
    asprintf(&msg, "%s, line %d, at %c", msgIn, scanner.line, loc);
    error(msg);
}

void targetedErrorL(char* msgIn, char* loc) {
	char* msg;
    asprintf(&msg, "%s, line %d, at %s", msgIn, scanner.line, loc);
    error(msg);
}

bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

Token identifier() {
	while (isAlpha(peek()) || isDigit(peek())) advance();
	return makeToken(TOKEN_IDENTIFIER);
}

void skipWhitespace() {
	char c = peek();
	begin:

	switch (c) {
		case ' ':
		case '\t':
		case '\r':
			advance();
			c = peek();
			goto begin;
		case '\n':
			scanner.line++;
			advance();
			c = peek();
			goto begin;
		case '/':
			if (peek2() == '/') {
				advance();
				advance();
				while (!(peek() == '\n')) advance();
				c = peek();
				goto begin;
			} else if (peek2() == '*') {
				advance();
				advance();

				multiLine:
				while (!(peek() == '*')) advance();
				if (!(peek2() == '/')) { advance(); goto multiLine; }
				advance();
				advance();
				c = peek();
				goto begin;
			}
			return;
			

	}
}

Token nextTokenWrap() {
	if (isAtEnd()) return makeToken(TOKEN_EOF);

	skipWhitespace();

	if (isAtEnd()) return makeToken(TOKEN_EOF);

	scanner.start = scanner.current;

  	char c = advance();

  	switch (c) {
  		case '(': return makeToken(TOKEN_LEFT_PAREN);
    	case ')': return makeToken(TOKEN_RIGHT_PAREN);
    	case '{': return makeToken(TOKEN_LEFT_BRACE);
    	case '}': return makeToken(TOKEN_RIGHT_BRACE);
    	case ';': return makeToken(TOKEN_SEMICOLON);
    	case ',': return makeToken(TOKEN_COMMA);
    	case '.': return makeToken(TOKEN_DOT);
    	case '=': return makeToken(TOKEN_EQUAL);
    	case '#': return makeToken(TOKEN_HASH);
    	case '+': 
    		if (match('+')) {
    			return makeToken(TOKEN_PLUS_PLUS);
    		} else if (match('=')) {
    			return makeToken(TOKEN_PLUS_EQUAL);
    		} else {
    			return makeToken(TOKEN_PLUS);
    		}
    	case '-': 
    		if (match('-')) {
    			return makeToken(TOKEN_MINUS_MINUS);
    		} else if (match('=')) {
    			return makeToken(TOKEN_MINUS_EQUAL);
    		} else {
    			return makeToken(TOKEN_MINUS);
    		}
    	case '*': 
    		if (match('=')) {
    			return makeToken(TOKEN_STAR_EQUAL);
    		} else {
    			return makeToken(TOKEN_STAR);
    		}
    	case '/': 
    		if (match('=')) {
    			return makeToken(TOKEN_SLASH_EQUAL);
    		} else {
    			return makeToken(TOKEN_SLASH);
    		}
    	case '>':
    		if (match('=')) {
    			return makeToken(TOKEN_GREATER_EQUAL);
    		} else if (match('>')) {
    			targetedErrorL(BITWISE_NOT_ALLOWED_MSG, ">>");
    		} else {
    			return makeToken(TOKEN_GREATER);
    		}
    	case '<':
    		if (match('=')) {
    			return makeToken(TOKEN_LESS_EQUAL);
    		} else if (match('<')) {
    			targetedErrorL(BITWISE_NOT_ALLOWED_MSG, "<<");
    		} else {
    			return makeToken(TOKEN_LESS);
    		}
    	case '|':
    		if (match('|')) {
    			return makeToken(TOKEN_OR);
    		} else {
    			targetedError(BITWISE_NOT_ALLOWED_MSG, c);
    		}
    	case '!':
    		if (match('=')) {
    			return makeToken(TOKEN_BANG_EQUAL);
    		} else {
    			return makeToken(TOKEN_BANG);
    		}
    	case '&':
    		if (match('&')) {
    			return makeToken(TOKEN_AND);
    		} else {
    			targetedError(BITWISE_NOT_ALLOWED_MSG, c);
    		}
    	default:
    		return identifier();
  	}

  	targetedError(UNEXPECTED_CHAR_MSG, c);
  	return makeToken(TOKEN_EOF); // Unreachable
}

Token nextToken() {
	scanner.start = scanner.current;
	if (isAtEnd()) return makeToken(TOKEN_EOF);
	Token t = nextTokenWrap();
	if (isAtEnd()) return makeToken(TOKEN_EOF);
	return t;
}

bool scannerHasNextToken() {
	return !isAtEnd();
}