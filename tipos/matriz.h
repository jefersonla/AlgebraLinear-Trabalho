#ifndef MATRIZ_H
#define MATRIZ_H

/* ------------------------------------------------------------- */
/*                       Constantes Matriz                       */
/* ------------------------------------------------------------- */


/* ------------------------------------------------ */
/*                Prototype definitions             */
/* ------------------------------------------------ */

/* Token Node */
typedef struct strToken TokenNode;

/* TokenList */
typedef struct strTokenList TokenList;

/* Symbol Node */
typedef struct strSymbolNode SymbolNode;

/* Symbol Table */
typedef struct strSymbolTable SymbolTable;

/* Instruction Node */
typedef struct strInstructionNode InstructionNode;

/* Instruction Queue */
typedef struct strInstructionQueue InstructionQueue;

/* ------------------------------------------------ */
/*                 Token Node Structure             */
/* ------------------------------------------------ */

typedef struct strToken{
    /* Root token of the given node */
    TokenNode *root_token;

    /* Token String */
    /* Store token string node */
    char *token_str;

    /* Lexical String */
    /* Store value read by lexical */
    char *lex_str;

    /* TokenType */
    int token_type;

    /* Child Nodes */
    TokenList *child_list;
} TokenNode, *ptrTokenNode;

/*------------ Token Structure Methods ------------ */

/* Creates a new token node */
TokenNode* newTokenNode(int token_type);

/* Free a token */
bool deleteTokenNode(ptrTokenNode *token_node, bool deleteChilds);

/* Add Token String */
bool nodeAddTokenStr(TokenNode *token_node, char *token_str);

/* Add Lexical String */
bool nodeAddLexStr(TokenNode *token_node, char *lex_str);

/* Add Root Token */
bool nodeAddRootToken(TokenNode *token_node, TokenNode *root_token);

/* ------------------------------------------------------------- */

#endif
