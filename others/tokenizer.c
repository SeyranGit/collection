/* clang main.c list/list.c -o main.exe -Weverything -Wno-unsafe-buffer-usage */

#include <stdio.h>
#include <malloc.h>
#include "../data-structures/list/list/list.h"


#define end_buffer(buf, i) buf[i] = '\0'; i = 0
#define true  1
#define false 0


typedef char bool;
typedef char *string;
typedef enum {
  NAME,
  NUMBER,
  TYPE,
  OP,
  LPAR,
  RPAR,
  SEMI,
  KEYWORD,
  FBRACEO,
  FBRACEC,
  QM,
  LETTER,
  SPACE,
  SINGLE_NUMBER
} TokenName;


struct Token {
  TokenName token;
  string value;
};


static unsigned int length(string str) {
  unsigned int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return ++len;
}


static bool cmp(string s1, string s2) {
  unsigned int len = length(s1);
  if (len != length(s2)) {
    return false;
  }
  for (unsigned int i = 0; i < len; i++) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}


static string heap_string(string str) {
  string heap_str = malloc(length(str));
  for (unsigned int i = 0; i < length(str); i++) {
    heap_str[i] = str[i];
  }
  return heap_str;
}


static TokenName get_symbolic_token(char symbol) {
  switch (symbol) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return SINGLE_NUMBER;
    case '*':
    case '/':
    case '+':
    case '-':
    case '=':
      return OP;
    case '(':
      return LPAR;
    case ')':
      return RPAR;
    case '{':
      return FBRACEO;
    case '}':
      return FBRACEC;
    case '"':
      return QM;
    case ';':
      return SEMI;
    case ' ':
    case '\n':
      return SPACE;
    default:
      return LETTER;
  }
}


static TokenName get_token(string id) {
  if (cmp(id, "int") || cmp(id, "void")) {
    return KEYWORD;
  } else {
    return NAME;
  }
}


static List tokenize(string code) {
  List tokens = new_list();
  struct Token *token = NULL;
  char buffer[100];
  for (unsigned int i = 0, bi = 0; i < length(code); i++) {
    TokenName token_name = get_symbolic_token(code[i]);
    if (token_name == LETTER) {
      buffer[bi++] = code[i];
    } else {
      if (bi) {
        end_buffer(buffer, bi);
        token = malloc(sizeof(struct Token));
        token->token = get_token(buffer);
        token->value = heap_string(buffer);
        tokens.append(&tokens, token);
      }
      if (token_name != SPACE) {
        token = malloc(sizeof(struct Token));
        char buff[2] = { code[i], '\0' };
        token->token = token_name;
        token->value = heap_string(buff);
        tokens.append(&tokens, token);
      }
    }
  }
  return tokens;
}


static void parse(string code) {
  List tokens = tokenize(code);
  for (unsigned int i = 0; i < tokens.len; i++) {
    struct Token *token = tokens.get(&tokens, i);
    printf("%d %s\n", token->token, token->value);
  }
}


int main(void) {
  string code = "int main(void) { int a = 0; print(\"Hello\"); }";
  parse(code);
  return 0;
}
