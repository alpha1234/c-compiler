#pragma once


Token *getNextToken();
void lex_initialize();
void lex_finalize();
void undoTokenGet();