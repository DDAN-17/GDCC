#include "common.h"
#include "scanner.h"
#include "localization.h"

void error(char*);

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

static bool isAtEnd() {
  return *scanner.current == '\0';
}

static Token errorToken(char* message) {
	Token token;
	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = strlen(message);
	token.line = scanner.line;
	return token;
}

static Token makeToken(TokenType tokenType) {
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

char match(char c) {
	if (peek() == c) {
		advance();
		return true;
	}
	return false;
}

Token nextToken() {
	scanner.start = scanner.current;

  	if (isAtEnd()) return makeToken(TOKEN_EOF);

  	char c = advance();

  	switch (c) {
  		case '(': return makeToken(TOKEN_LEFT_PAREN);
    	case ')': return makeToken(TOKEN_RIGHT_PAREN);
    	case '{': return makeToken(TOKEN_LEFT_BRACE);
    	case '}': return makeToken(TOKEN_RIGHT_BRACE);
    	case ';': return makeToken(TOKEN_SEMICOLON);
    	case ',': return makeToken(TOKEN_COMMA);
    	case '.': return makeToken(TOKEN_DOT);
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
    	case '&':
    		if (match('&')) {
    			return makeToken(TOKEN_AND);
    		} else {
    			error(BITWISE_NOT_ALLOWED);
    		}
  	}

  	error(UNEXPECTED_CHAR);
  	return makeToken(TOKEN_EOF); // Unreachable
}

bool scannerHasNextToken() {
	return !isAtEnd();
}