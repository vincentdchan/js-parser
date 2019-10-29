//
// Created by Duzhong Chen on 2019/10/30.
//
#pragma once

#include "parser.hpp"

namespace parser {

    class TypeScriptParser {
    public:
        TypeScriptParser(Parser* parser);

        TypeScriptParser(const TypeScriptParser& tsParser) = delete;
        TypeScriptParser(TypeScriptParser&& tsParser) = delete;

        TypeScriptParser& operator=(const TypeScriptParser& tsParser) = delete;
        TypeScriptParser& operator=(TypeScriptParser&&) = delete;

        Sp<TSTypeAliasDeclaration> ParseTypeAliasDeclaration();

        Sp<TSTypeParameterDeclaration> ParseTypeParameterDeclaration();

        Sp<TSType> ParseType();

        Sp<TSType> ParseNonConditionalType();

        Sp<TSThisType> ParseThisType();

        Sp<TSFunctionType> ParseFunctionType();

        Sp<TSConstructorType> ParseConstructorType();

        Sp<TSType> ParseUnionTypeOrHigher();

        Sp<TSLiteralType> ParseLiteralTypeNode();

    private:
        bool IsStartOfFunctionType();

        Parser& parser_;

    };

}
