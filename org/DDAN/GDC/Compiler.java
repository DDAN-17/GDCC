package org.DDAN.GDC;

import static org.DDAN.GDC.TokenType.*;

public class Compiler {
	CScanner scanner;

	Token current;
	Token previous;

	public Compiler(CScanner scanner) {
		this.scanner = scanner;
		//if ()
	}

	boolean match(TokenType t) {
		if (peek().type() == t) {
			advance();
			return true;
		}
		return false;
	}

	Token advance() {
		previous = current;
		current = scanner.nextToken();
		return previous;
	}

	Token peek() {
		return current;
	}

	public Item expression() {
		return or();
	}

	Item buildOr(Item left, Item right) {

	}

	Item or() {
		Item expr = and();

		while (match(OR)) {
			Item right = and();
			expr = buildOr(expr, right);
		}
		return expr;
	}

	Item and() {
		return new Item(0, true);
	}

}
