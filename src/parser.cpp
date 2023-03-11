#include "headers.h"
#include <exception>
#include <stdexcept>

Parser::Parser(Lexer input) {
  this->input = input;
  consume();
}

Parser::Parser(std::string input) {
  this->input = Lexer(input);
  consume();
}

Parser::Parser() = default;

void Parser::consume() { lookahead = input.next_token(); }

Token Parser::expect(Token_type expected) {
  Token got = lookahead;

  if (got.get_type() != expected)
    throw std::runtime_error("Expected: " + Token::type_to_string(expected) +
                             "; got: " + Token::type_to_string(got.get_type()));

  consume();
  return got;
}

AST Parser::parse() {
	AST result = program();
	expect(END);

	return result;
}

AST Parser::program() {
	AST result(AST_type::PROGRAM);

	if (lookahead.get_type() == END)
		throw std::runtime_error("Empty parser input");

	while (lookahead.get_type() != END)
		result.add_child(statement());

	return result;
}

AST Parser::statement() {
  AST result;
  if (lookahead.get_type() == LAAT)
    result = assignment();
  else if (lookahead.get_type() == PRINT)
    result = print();
  else
    throw std::runtime_error("Expected assignment or print, got: " +
                             lookahead.to_string());

	if (lookahead.get_type() == EN) {
		consume();
		if (lookahead.get_type() == END)
			throw std::runtime_error("Expected end of file after 'en'");
	} else if (lookahead.get_type() == SEMICOLON) {
		consume();
	} else {
    throw std::runtime_error("Expected semicolon or 'en', got: " +
				lookahead.to_string());
	}

	return result;
}
AST Parser::assignment() {
  expect(LAAT);
  std::string what_to_assign_to = expect(NAME).get_value();
  AST value = expression();
  expect(ZIJN);

  AST result(AST_type::ASSIGNMENT);
  result.add_child({AST_type::NAME, what_to_assign_to});
  result.add_child(value);

  return result;
}

AST Parser::print() {
  expect(PRINT);
  AST expression_to_print = expression();
  expect(UIT);

  AST result(AST_type::PRINT);
  result.add_child(expression_to_print);

  return result;
}

AST Parser::expression() {
  AST result = mul();

  while (true) {
    Token_type t = lookahead.get_type();
    AST new_parent;

    if (t == PLUS) {
      new_parent = {AST_type::PLUS};
		} else if (t == MINUS) {
      new_parent = {AST_type::MINUS};
		} else {
      break;
		} 
			
		consume();

    new_parent.add_child(result);
    new_parent.add_child(mul());

    result = new_parent;
  }

  return result;
}

AST Parser::mul() {
  AST result = value();

  while (true) {
    Token_type t = lookahead.get_type();
    AST new_parent;

    if (t == TIMES)
      new_parent = {AST_type::TIMES};
    else if (t == DIVIDE)
      new_parent = {AST_type::DIVIDE};
    else
      break;

		consume();

    new_parent.add_child(result);
    new_parent.add_child(value());

    result = new_parent;
  }

  return result;
}

AST Parser::value() {
  AST result;

  switch (lookahead.get_type()) {
  case NUMBER:
    result = {AST_type::NUMBER, lookahead.get_value()};
		consume();
		break;
  case NAME:
    result = {AST_type::NAME, lookahead.get_value()};
		consume();
		break;
	case HET:
		result = {AST_type::HET};
		consume();
		break;
  case LPAREN:
		consume();
    result = expression();
    expect(RPAREN);
		break;
  default:
    throw std::runtime_error("Invalid token: " + lookahead.to_string());
  }

  return result;
}
