#pragma once

#include "Token.h"

Token getNextToken();
void lex_initialize(const char *);
void lex_finalize();
void undoTokenGet();