package org.DDAN.GDC;

public record Token(String lexeme, int line, TokenType type) {}