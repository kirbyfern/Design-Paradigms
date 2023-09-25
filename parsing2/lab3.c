#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // Added for exit()

/* Global declarations */

/* Variables */
int charClass;      // Character class (LETTER, DIGIT, UNKNOWN)
char lexeme[100];   // Current lexeme being built
char nextChar;      // Next character from input
int lexLen;         // Length of the current lexeme
int token;          // Current token
int nextToken;      // Next token
FILE *in_fp, *fopen();

/* Function declarations */
void addChar(); // Declaration added here
void getChar();
void getNonBlank();
int lex();

// Function declarations for the parser
void factor();
void term();
void expr();
void error();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/*****************************************************/

/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
  switch (ch) {
    case '(':
      addChar();
      nextToken = LEFT_PAREN;
      break;
    case ')':
      addChar();
      nextToken = RIGHT_PAREN;
      break;
    case '+':
      addChar();
      nextToken = ADD_OP;
      break;
    case '-':
      addChar();
      nextToken = SUB_OP;
      break;
    case '*':
      addChar();
      nextToken = MULT_OP;
      break;
    case '/':
      addChar();
      nextToken = DIV_OP;
      break;
    case '=':
      addChar();
      nextToken = ASSIGN_OP;
      break;
    default:
      if (isalpha(ch)) {
        addChar();
        nextToken = IDENT;
      } else if (isdigit(ch)) {
        addChar();
        nextToken = INT_LIT;
      } else {
        nextToken = UNKNOWN;
      }
      break;
  }
  return nextToken;
}

/*****************************************************/

/* addChar - a function to add nextChar to lexeme */
void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar; // Add the next character to the lexeme
    lexeme[lexLen] = '\0';       // Null-terminate the lexeme for a valid string
  } else {
    printf("Error - lexeme is too long \n");
  }
}

/*****************************************************/

/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else
      charClass = UNKNOWN;
  } else
    charClass = EOF;
}

/*****************************************************/

/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/******************************************************/

/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
  lexLen = 0;
  getNonBlank();

  switch (charClass) {
    /* Parse identifiers */
    case LETTER:
      addChar();
      getChar();
      while (charClass == LETTER || charClass == DIGIT) {
        addChar();
        getChar();
      }
      nextToken = IDENT;
      break;

    /* Parse integer literals */
    case DIGIT:
      addChar();
      getChar();
      while (charClass == DIGIT) {
        addChar();
        getChar();
      }
      nextToken = INT_LIT;
      break;

    /* Parentheses and operators */
    case UNKNOWN:
      lookup(nextChar); // Lookup and set the next token
      getChar();        // Get the next character
      break;

    /* EOF */
    case EOF:
      nextToken = EOF;
      lexeme[0] = 'E';
      lexeme[1] = 'O';
      lexeme[2] = 'F';
      lexeme[3] = 0; // Null-terminate the EOF lexeme
      break;
  } /* End of switch */

  printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
  return nextToken;
} /* End of function lex */

/*****************************************************/

/* Error handling function */
void error() {
  printf("Syntax error at lexeme: %s\n", lexeme);
  exit(1);
}

/*****************************************************/

/* Parser functions */

/* factor - parses a factor in the grammar */
void factor() {
  printf("Enter <factor>\n");

  // Determine which RHS: variable, constant, or ( <expr> )
  if (nextToken == IDENT || nextToken == INT_LIT) {
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    nextToken = lex();
  } else if (nextToken == LEFT_PAREN) {
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    nextToken = lex();
    expr();
    if (nextToken == RIGHT_PAREN) {
      printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
      nextToken = lex();
    } else {
      error();
    }
  } else {
    error();
  }

  printf("Exit <factor>\n");
}

/* term - parses a term in the grammar */
void term() {
  printf("Enter <term>\n");

  // Parse the first factor
  factor();

  // As long as the next token is * or /, get the next token and parse the next factor
  while (nextToken == MULT_OP || nextToken == DIV_OP) {
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    nextToken = lex();
    factor();
  }

  printf("Exit <term>\n");
}

/* expr - parses an expression in the grammar */
void expr() {
  printf("Enter <expr>\n");

  // Parse the first term
  term();

  // As long as the next token is + or -, get the next token and parse the next term
  while (nextToken == ADD_OP || nextToken == SUB_OP) {
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    nextToken = lex();
    term();
  }

  printf("Exit <expr>\n");
}

/*****************************************************/

/* main driver */
int main() {
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("test1.txt", "r")) == NULL) {
    printf("ERROR - cannot open front.in\n");
    return 1;
  }

  getChar(); // Initialize the character buffer

  do {
    lex(); // Call the lexical analyzer function
    expr(); // Start parsing an expression
  } while (nextToken != EOF);

  fclose(in_fp);

  return 0;
}
