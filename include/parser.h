#pragma once

enum class Kind{
    IDENTIFIER,
    TYPE
};

enum class Declarators {
    IDENTIFIER,
    ARRAY,
    FUNCTION,

};

void parser_initialize();
