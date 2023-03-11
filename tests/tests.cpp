#include "../src/headers.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

bool lexer_throws_exception_on_input(string input) {
  try {
    Lexer l(input);
    while (true) {
      Token current = l.next_token();
      if (current.get_type() == END)
        break;
    }
  } catch (...) {
    return true;
  }

  return false;
}

bool lexer_matches_expected_types(string input, vector<Token_type> expected) {
  Lexer l(input);
  vector<Token_type> received;

  while (true) {
    Token t = l.next_token();
    received.push_back(t.get_type());

    if (t.get_type() == END)
      break;
  }

  return received == expected;
}

void test_lexer() {
  assert(lexer_throws_exception_on_input("="));
  assert(lexer_throws_exception_on_input("13.1"));

  assert(!lexer_throws_exception_on_input("(13)"));
  assert(!lexer_throws_exception_on_input("john"));
  assert(!lexer_throws_exception_on_input(""));
  assert(!lexer_throws_exception_on_input("1 + 1"));
  assert(!lexer_throws_exception_on_input("1 - 1"));
  assert(!lexer_throws_exception_on_input("1 * 1"));
  assert(!lexer_throws_exception_on_input("1 / 1"));
  assert(!lexer_throws_exception_on_input("\r\n\t "));

  assert(lexer_matches_expected_types("", {END}));
  assert(lexer_matches_expected_types("13", {NUMBER, END}));
  assert(lexer_matches_expected_types("13+2", {NUMBER, PLUS, NUMBER, END}));
  assert(lexer_matches_expected_types("print;", {PRINT, SEMICOLON, END}));
  assert(lexer_matches_expected_types("print pi uit;",
                                      {PRINT, NAME, UIT, SEMICOLON, END}));
  assert(lexer_matches_expected_types(
      "laat x 15 zijn;", {LAAT, NAME, NUMBER, ZIJN, SEMICOLON, END}));
  assert(lexer_matches_expected_types(
      "laat pi 3 zijn en print het uit;",
      {LAAT, NAME, NUMBER, ZIJN, EN, PRINT, HET, UIT, SEMICOLON, END}));
}

bool parser_throws_exception_on_input(std::string input) {
	Parser p(input);
	
	try {
		p.parse();
	} catch (...) {
		return true;
	}

	return false;
}

void test_parser() {
	// Invalid input
	assert(parser_throws_exception_on_input(""));
	assert(parser_throws_exception_on_input(";"));
	assert(parser_throws_exception_on_input("2;"));
	assert(parser_throws_exception_on_input("2+2;"));
	assert(parser_throws_exception_on_input("print 2 uit"));
	assert(parser_throws_exception_on_input("print 2 uit en"));

	// Valid input
	assert(!parser_throws_exception_on_input("print 2 uit;"));
	assert(!parser_throws_exception_on_input("laat pi 3 zijn;"));
	assert(!parser_throws_exception_on_input("laat pi 3 zijn en print het uit;"));
	assert(!parser_throws_exception_on_input("print 2 * 2 uit;"));
	assert(!parser_throws_exception_on_input("print 2 * (2) uit;"));
	assert(!parser_throws_exception_on_input("print (2) uit;"));
	assert(!parser_throws_exception_on_input("print (3 + 3) / 7 uit;"));
	assert(!parser_throws_exception_on_input("laat pi (3 + 3) zijn;"));
	assert(!parser_throws_exception_on_input("laat pi 22/7 zijn en laat tau pi*2 zijn en print het uit;"));
	assert(!parser_throws_exception_on_input("print 7/(200-11) uit;"));
}

void test_all() {
	test_lexer();
	test_parser();
}

int main() {
  test_all();
  cout << "all tests passed :) (LESGOOOO!!!)" << endl;
  return 0;
}
