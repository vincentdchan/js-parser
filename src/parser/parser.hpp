//
// Created by Duzhong Chen on 2019/9/3.
//
#pragma once

#include <iostream>
#include "parser_common.h"
#include "error_message.h"

#define ASSERT_NOT_NULL(EXPR, MSG) if ((EXPR) == nullptr) { \
        LogError(std::string(#EXPR) + " should not be nullptr " + MSG); \
        return false; \
    }

namespace parser {

    class Parser final: public ParserCommon {
    public:

        Parser(
            shared_ptr<u16string> source,
            const Config& config
        ): ParserCommon(source, config) {

        }

        template<typename T, typename ...Args>
        Sp<T> Alloc(Args && ...args) {
            static_assert(std::is_base_of<SyntaxNode, T>::value, "T not derived from AstNode");

            return Sp<T>(new T);
        }

        template <typename T>
        Sp<T> IsolateCoverGrammar(std::function<Sp<T>()> cb) {
            auto previousIsBindingElement = context_.is_binding_element;
            auto previousIsAssignmentTarget = context_.is_assignment_target;
            auto previousFirstCoverInitializedNameError = context_.first_cover_initialized_name_error;

            context_.is_binding_element = true;
            context_.is_assignment_target = true;
            context_.first_cover_initialized_name_error.reset();

            Sp<T> result = cb();
            if (context_.first_cover_initialized_name_error) {
                ThrowUnexpectedToken(Token(), "firstCoverInitializedNameError");
                return nullptr;
            }

            context_.is_binding_element = previousIsBindingElement;
            context_.is_assignment_target = previousIsAssignmentTarget;
            context_.first_cover_initialized_name_error = previousFirstCoverInitializedNameError;

            return result;
        }

        template <typename T>
        Sp<T> InheritCoverGrammar(std::function<Sp<T>()> cb) {
            auto previousIsBindingElement = context_.is_binding_element;
            auto previousIsAssignmentTarget = context_.is_assignment_target;
            auto previousFirstCoverInitializedNameError = context_.first_cover_initialized_name_error;

            context_.is_binding_element = true;
            context_.is_assignment_target = true;
            context_.first_cover_initialized_name_error.reset();

            Sp<T> result = cb();

            context_.is_binding_element &= previousIsBindingElement;
            context_.is_assignment_target &= previousIsAssignmentTarget;
            context_.first_cover_initialized_name_error =
                previousFirstCoverInitializedNameError ?
                previousFirstCoverInitializedNameError : context_.first_cover_initialized_name_error;

            return result;
        }


        template<typename T>
        Sp<T> Finalize(const Marker& marker, const Sp<T>& from);

        Sp<Expression> ParsePrimaryExpression();

        Sp<SpreadElement> ParseSpreadElement();

        template <typename NodePtr>
        bool ParsePropertyMethodFunction(NodePtr& ptr);

        template <typename NodePtr>
        bool ParsePropertyMethodAsyncFunction(NodePtr& ptr);

        Sp<SyntaxNode> ParseObjectProperty(bool& has_proto);

        Sp<SyntaxNode> ParseObjectPropertyKey();

        Sp<Expression> ParseObjectInitializer();

        template <typename NodePtr>
        bool ParseTemplateHead(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseTemplateElement(NodePtr& ptr);

        Sp<TemplateLiteral> ParseTemplateLiteral();

        template <typename NodePtr>
        bool ReinterpretExpressionAsPattern(NodePtr& ptr);

        template <typename NodePtr>
        bool ReinterpretAsCoverFormalsList(NodePtr& ptr, FormalParameterOptions& list);

        Sp<Expression> ParseGroupExpression();

        std::vector<Sp<SyntaxNode>> ParseArguments();

        Sp<Identifier> ParseIdentifierName();

        Sp<Expression> ParseNewExpression();

        template <typename NodePtr>
        bool ParseAsyncArgument(NodePtr& ptr);

        std::vector<Sp<SyntaxNode>> ParseAsyncArguments();

        Sp<Import> ParseImportCall();

        Sp<Expression> ParseLeftHandSideExpressionAllowCall();

        Sp<Super> ParseSuper();

        Sp<Expression> ParseLeftHandSideExpression();

        template <typename NodePtr>
        bool ParseLeftHandSideExpression(NodePtr& ptr);

        Sp<Expression> ParseUpdateExpression();

        Sp<AwaitExpression> ParseAwaitExpression();

        Sp<Expression> ParseUnaryExpression();

        Sp<Expression> ParseExponentiationExpression();

        Sp<Expression> ParseBinaryExpression();

        Sp<Expression> ParseConditionalExpression();

        Sp<Expression>
        ParseAssignmentExpression();

        template <typename NodePtr>
        bool ParseStatementListItem(NodePtr& ptr);

        Sp<Statement> ParseStatementListItem();

        Sp<BlockStatement> ParseBlock();

        template <typename NodePtr>
        bool ParseLexicalBinding(NodePtr& ptr);

        std::vector<Sp<VariableDeclarator>> ParseBindingList(VarKind kind);

        bool IsLexicalDeclaration();
        void ExpectCommaSeparator();

        Sp<Declaration> ParseLexicalDeclaration(bool& in_for);

        template <typename NodePtr>
        bool ParseBindingRestElement(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseArrayPattern(NodePtr& ptr);

        template <typename NodePtr>
        bool ParsePropertyPattern(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseRestProperty(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseObjectPattern(NodePtr& ptr);

        Sp<Expression> ParseArrayInitializer();

        template <typename NodePtr>
        bool PeinterpretExpressionAsPattern(NodePtr& ptr);

        void ParseFormalParameters(optional<Token> first_restricted, FormalParameterOptions& option);
        bool ParseFormalParameter(FormalParameterOptions& option);
        bool IsStartOfExpression();

        Sp<RestElement> ParseRestElement(std::vector<Sp<SyntaxNode>>& params);

        Sp<Identifier> ParsePattern(std::vector<Sp<SyntaxNode>>& params, VarKind  kind);

        template <typename NodePtr>
        bool ParsePatternWithDefault(NodePtr& ptr);

        Sp<Identifier> ParseVariableIdentifier(VarKind kind);

        Sp<VariableDeclarator> ParseVariableDeclaration(bool in_for);

        std::vector<Sp<VariableDeclarator>> ParseVariableDeclarationList(bool in_for);

        Sp<VariableDeclaration> ParseVariableStatement();

        template <typename NodePtr>
        bool ParseEmptyStatement(NodePtr& ptr);

        Sp<EmptyStatement> ParseEmptyStatement();

        Sp<ExpressionStatement> ParseExpressionStatement();

        Sp<Expression> ParseExpression();

        Sp<Statement> ParseIfClause();

        Sp<IfStatement> ParseIfStatement();

        Sp<DoWhileStatement> ParseDoWhileStatement();

        Sp<WhileStatement> ParseWhileStatement();

        Sp<Statement> ParseForStatement();

        Sp<ContinueStatement> ParseContinueStatement();

        Sp<BreakStatement> ParseBreakStatement();

        Sp<ReturnStatement> ParseReturnStatement();

        Sp<WithStatement> ParseWithStatement();

        Sp<SwitchCase> ParseSwitchCase();

        Sp<SwitchStatement> ParseSwitchStatement();

        Sp<Statement> ParseLabelledStatement();

        template <typename NodePtr>
        bool ParseLabelledStatement(NodePtr& ptr);

        Sp<ThrowStatement> ParseThrowStatement();

        Sp<CatchClause> ParseCatchClause();

        template <typename NodePtr>
        bool ParseCatchClause(NodePtr& ptr);

        Sp<BlockStatement> ParseFinallyClause();

        Sp<TryStatement> ParseTryStatement();

        Sp<DebuggerStatement> ParseDebuggerStatement();

        template <typename NodePtr>
        bool ParseDebuggerStatement(NodePtr& ptr);

        Sp<Statement> ParseStatement();

        Sp<BlockStatement> ParseFunctionSourceElements();

        Sp<Declaration> ParseFunctionDeclaration(bool identifier_is_optional);

        Sp<FunctionExpression> ParseFunctionExpression();

        Sp<Statement> ParseDirective();

        std::vector<Sp<SyntaxNode>> ParseDirectivePrologues();

        template <typename NodePtr>
        bool ParseGetterMethod(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseSetterMethod(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseGeneratorMethod(NodePtr& ptr);

        Sp<YieldExpression> ParseYieldExpression();

        template <typename NodePtr>
        bool ParseClassElement(NodePtr& ptr);

        std::vector<Sp<Property>> ParseClassElementList();

        Sp<ClassBody> ParseClassBody();

        Sp<ClassDeclaration> ParseClassDeclaration(bool identifier_is_optional);

        Sp<ClassExpression> ParseClassExpression();

        Sp<Module> ParseModule();

        template <typename NodePtr>
        bool ParseScript(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseModuleSpecifier(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseImportSpecifier(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseNamedImports(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseImportDefaultSpecifier(NodePtr& ptr);

        template <typename NodePtr>
        bool ParseImportNamespaceSpecifier(NodePtr& ptr);

        Sp<ImportDeclaration> ParseImportDeclaration();

        template <typename NodePtr>
        bool ParseExportSpecifier(NodePtr& ptr);


        Sp<Declaration> ParseExportDeclaration();

        bool MatchImportCall();

        inline bool MatchAsyncFunction();


        ~Parser() = default;

    };


//    template<typename FromT, typename ToT>
//    bool Finalize(const Marker& marker, FromT from, ToT& to);
    template<typename T>
    Sp<T> Parser::Finalize(const Parser::Marker &marker, const Sp<T>& from) {

        if (config_.range) {
            from->range = std::make_pair(marker.index, LastMarker().index);
        }

        if (config_.loc) {
            from->location.start_ = Position {
                marker.line,
                marker.column,
            };
            from->location.end_ = Position {
                LastMarker().line,
                LastMarker().column,
            };
        }

        return from;
    }

    inline bool Parser::MatchAsyncFunction() {
        bool match = MatchContextualKeyword(u"async");
        if (match) {
            auto state = scanner_->SaveState();
            std::vector<Comment> comments;
            scanner_->ScanComments(comments);
            Token next = scanner_->Lex();
            scanner_->RestoreState(state);

            match = (state.line_number_ == next.line_number_) && (next.type_ == JsTokenType::Keyword) && (next.value_ == u"function");
        }

        return match;
    }

    template <typename NodePtr>
    bool Parser::ParsePropertyMethodFunction(NodePtr &ptr) {
        static_assert(std::is_convertible<FunctionExpression*, NodePtr>::value, "NodePtr can not accept FunctionExpression*");
        auto marker = CreateNode();
        auto node = Alloc<FunctionExpression>();

        bool isGenerator = false;

        FormalParameterOptions options;
        bool previous_allow_yield = context_.allow_yield;
        context_.allow_yield = true;
        ParseFormalParameters(nullopt, options);
//        const params = this.parseFormalParameters();
//        const method = this.parsePropertyMethod(params);
        context_.allow_yield = previous_allow_yield;

        return Finalize(marker, node, ptr);
    }

    template <typename NodePtr>
    bool Parser::ParsePropertyMethodAsyncFunction(NodePtr& ptr) {
        static_assert(std::is_convertible<AsyncFunctionExpression*, NodePtr>::value, "NodePtr can not accept FunctionExpression*");
        auto marker = CreateNode();
        auto node = Alloc<AsyncFunctionExpression>();

        bool isGenerator = false;

        FormalParameterOptions options;
        bool previous_allow_yield = context_.allow_yield;
        bool previous_await = context_.await;
        context_.allow_yield = true;
        ParseFormalParameters(nullopt, options);
//        const params = this.parseFormalParameters();
//        const method = this.parsePropertyMethod(params);
        context_.allow_yield = previous_allow_yield;
        context_.await = previous_await;

        return Finalize(marker, node, ptr);
    }

    template <typename NodePtr>
    bool Parser::ParseTemplateHead(NodePtr &ptr) {
        return false;
    }

    template <typename NodePtr>
    bool Parser::ReinterpretExpressionAsPattern(NodePtr& ptr) {
        // TODO
        return false;
    }

    template <typename NodePtr>
    bool Parser::ReinterpretAsCoverFormalsList(NodePtr& ptr, FormalParameterOptions& list) {
        // TODO
        return false;
    }

}
