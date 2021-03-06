#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "arccc.h"

// 新しいトークンを作成してcurに繋げる
Token* new_token(TokenKind kind, Token* cur, char* str, int len) {
  Token* tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

bool is_alnum(char c){
  return isalnum(c) || c == '_';
}

bool startswith(char* p, char* q) {
  return memcmp(p, q, strlen(q)) == 0;
}

int get_ident_len(char* p) {
  int len = 0;
  if (isalpha(*p) || *p == '_') {
    len = 1;
    p++;
    while (is_alnum(*p)) {
      len++;
      p++;
    }
  }
  return len;
}

// 入力文字列pをトークナイズしてそれを返す
Token* tokenize(void) {
  Token head;
  head.next = NULL;
  Token* cur = &head;
  char* p = user_input;

  while (*p) {
    // 空白文字をスキップ
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (startswith(p, "return") && !is_alnum(p[6])) {
      cur = new_token(TK_RETURN, cur, p, 6);
      p += 6;
      continue;
    }
    if (startswith(p, "if") && !is_alnum(p[2])) {
      cur = new_token(TK_IF, cur, p, 2);
      p += 2;
      continue;
    }
    if (startswith(p, "else") && !is_alnum(p[4])) {
      cur = new_token(TK_ELSE, cur, p, 2);
      p += 6;
      continue;
    }

    if (startswith(p, "==") || startswith(p, "!=") || startswith(p, "<=") ||
        startswith(p, ">=")) {
      cur = new_token(TK_RESERVED, cur, p, 2);
      p += 2;
      continue;
    }
    if (strchr("+-*/()<>=;", *p)) {
      cur = new_token(TK_RESERVED, cur, p++, 1);
      continue;
    }
    if (get_ident_len(p)) {
      int len = get_ident_len(p);
      cur = new_token(TK_IDENT, cur, p, len);
      p += len;
      continue;
    }

    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, 0);
      char* q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }
    error_at(p, "トークナイズできません");
  }

  new_token(TK_EOF, cur, p, 0);
  return head.next;
}
