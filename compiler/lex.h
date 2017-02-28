#pragma once


Token *getNextToken();
void lex_initialize(char *);
void lex_finalize();
void undoTokenGet();