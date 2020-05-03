#include <stdio.h>

// トークンの種類
typedef enum {
  TK_RESERVED,  // 記号
  TK_RETURN,    // return
  TK_IF,        // if
  TK_ELSE,      // else
  TK_IDENT,     // 識別子
  TK_NUM,       // 整数トークン
  TK_EOF,       // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind;  // トークンの型
  Token* next;     // 次の入力トークン
  int val;         // kindがTK_NUMの場合、その数値
  char* str;       // トークン文字列
  int len;         // トークンの長さ
};

// 抽象構文木のノードの種類
typedef enum {
  ND_RETURN,  // reteurn
  ND_IF,      // if
  ND_ELSE,    // else
  ND_ADD,     // +
  ND_SUB,     // -
  ND_MUL,     // *
  ND_DIV,     // /
  ND_EQ,      // ==
  ND_NE,      // !=
  ND_LT,      // <
  ND_LE,      // <=
  ND_ASSIGN,  // =
  ND_LVAR,    // ローカル変数
  ND_NUM,     // 整数
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
  NodeKind kind;  // ノードの型
  Node* lhs;      // 左辺
  Node* rhs;      // 右辺
  int val;        // kindがND_NUMの場合のみ使う
  int offset;     // kindがND_LVAR
  int len;        // kindがND_LVAR
  Node* cond;     // kindがND_IF
  Node* then;     // kindがND_IF
  Node* els;      // kindがND_IF
};

typedef struct LVar LVar;

// ローカル変数の型
struct LVar {
  LVar* next;  // 次の変数かNULL
  char* name;  // 変数の名前
  int len;     // 名前の長さ
  int offset;  // RBPからのオフセット
};

// 現在着目しているトークン
extern Token* token;
// 入力プログラム
extern char* user_input;

extern Node* code[100];

// ローカル変数
extern LVar* locals;

void program();

void codegen(void);

Token* tokenize(void);

void error(char* fmt, ...);
void error_at(char* loc, char* fmt, ...);