/* Generated by Ruby Script! */


#pragma once

#include "base_nodes.h"
#include <optional>
#include <vector>
#include <variant>


class ArrayExpression: public Expression {
public:
    ArrayExpression();

    std::vector<Sp<SyntaxNode>> elements;

};

class ArrayPattern: public Pattern {
public:
    ArrayPattern();

    std::vector<std::optional<Sp<SyntaxNode>>> elements;

};

class ArrowFunctionExpression: public Expression {
public:
    ArrowFunctionExpression();

    std::optional<Sp<Identifier>> id;
    std::vector<Sp<SyntaxNode>> params;
    Sp<SyntaxNode> body;
    bool generator = false;
    bool expression = false;
    bool async = false;

};

class AssignmentExpression: public Expression {
public:
    AssignmentExpression();

    UString operator_;
    Sp<Pattern> left;
    Sp<Expression> right;

};

class AssignmentPattern: public Pattern {
public:
    AssignmentPattern();

    Sp<SyntaxNode> left;
    Sp<Expression> right;

};

class AwaitExpression: public Expression {
public:
    AwaitExpression();

    Sp<Expression> argument;

};

class BinaryExpression: public Expression {
public:
    BinaryExpression();

    UString operator_;
    Sp<Expression> left;
    Sp<Expression> right;

};

class BlockStatement: public Statement {
public:
    BlockStatement();

    std::vector<Sp<SyntaxNode>> body;

};

class BreakStatement: public Statement {
public:
    BreakStatement();

    std::optional<Sp<Identifier>> label;

};

class CallExpression: public Expression {
public:
    CallExpression();

    Sp<Expression> callee;
    std::vector<Sp<SyntaxNode>> arguments;

};

class CatchClause: public SyntaxNode {
public:
    CatchClause();

    Sp<SyntaxNode> param;
    Sp<BlockStatement> body;

};

class ClassBody: public SyntaxNode {
public:
    ClassBody();

    std::vector<Sp<MethodDefinition>> body;

};

class ClassDeclaration: public Declaration {
public:
    ClassDeclaration();

    std::optional<Sp<Identifier>> id;
    std::optional<Sp<Identifier>> super_class;
    Sp<ClassBody> body;

};

class ClassExpression: public Expression {
public:
    ClassExpression();

    std::optional<Sp<Identifier>> id;
    std::optional<Sp<Identifier>> super_class;
    std::optional<Sp<ClassBody>> body;

};

class ComputedMemberExpression: public Expression, public Pattern {
public:
    ComputedMemberExpression();

    bool computed = false;
    Sp<Expression> object;
    Sp<Expression> property;

};

class ConditionalExpression: public Expression {
public:
    ConditionalExpression();

    Sp<Expression> test;
    Sp<Expression> consequent;
    Sp<Expression> alternate;

};

class ContinueStatement: public Statement {
public:
    ContinueStatement();

    std::optional<Sp<Identifier>> label;

};

class DebuggerStatement: public Statement {
public:
    DebuggerStatement();


};

class Directive: public Statement {
public:
    Directive();

    Sp<Expression> expression;
    UString directive;

};

class DoWhileStatement: public Statement {
public:
    DoWhileStatement();

    Sp<Statement> body;
    Sp<Expression> test;

};

class EmptyStatement: public Statement {
public:
    EmptyStatement();


};

class ExportAllDeclaration: public Declaration {
public:
    ExportAllDeclaration();

    Sp<Literal> source;

};

class ExportDefaultDeclaration: public Declaration {
public:
    ExportDefaultDeclaration();

    Sp<SyntaxNode> declaration;

};

class ExportNamedDeclaration: public Declaration {
public:
    ExportNamedDeclaration();

    std::optional<Sp<SyntaxNode>> declaration;
    std::vector<Sp<ExportSpecifier>> specifiers;
    std::optional<Sp<Literal>> source;

};

class ExportSpecifier: public SyntaxNode {
public:
    ExportSpecifier();

    Sp<Identifier> exported;
    Sp<Identifier> local;

};

class ExpressionStatement: public Statement {
public:
    ExpressionStatement();

    Sp<Expression> expression;

};

class ForInStatement: public Statement {
public:
    ForInStatement();

    Sp<SyntaxNode> left;
    Sp<SyntaxNode> right;
    Sp<Statement> body;
    bool each = false;

};

class ForOfStatement: public Statement {
public:
    ForOfStatement();

    Sp<SyntaxNode> left;
    Sp<SyntaxNode> right;
    Sp<Statement> body;

};

class ForStatement: public Statement {
public:
    ForStatement();

    std::optional<Sp<SyntaxNode>> init;
    std::optional<Sp<SyntaxNode>> test;
    std::optional<Sp<SyntaxNode>> update;
    Sp<Statement> body;

};

class FunctionDeclaration: public Declaration {
public:
    FunctionDeclaration();

    std::optional<Sp<Identifier>> id;
    std::vector<Sp<SyntaxNode>> params;
    Sp<BlockStatement> body;
    bool generator = false;
    bool expression = false;
    bool async = false;

};

class FunctionExpression: public Expression {
public:
    FunctionExpression();

    std::optional<Sp<Identifier>> id;
    std::vector<Sp<SyntaxNode>> params;
    Sp<BlockStatement> body;
    bool generator = false;
    bool expression = false;
    bool async = false;

};

class Identifier: public Expression, public Pattern {
public:
    Identifier();

    UString name;

};

class IfStatement: public Statement {
public:
    IfStatement();

    Sp<Expression> test;
    Sp<Statement> consequent;
    std::optional<Sp<Statement>> alternate;

};

class Import: public Expression {
public:
    Import();


};

class ImportDeclaration: public Declaration {
public:
    ImportDeclaration();

    std::vector<Sp<SyntaxNode>> specifiers;
    Sp<Literal> source;

};

class ImportDefaultSpecifier: public SyntaxNode {
public:
    ImportDefaultSpecifier();

    Sp<Identifier> local;

};

class ImportNamespaceSpecifier: public SyntaxNode {
public:
    ImportNamespaceSpecifier();

    Sp<Identifier> local;

};

class ImportSpecifier: public SyntaxNode {
public:
    ImportSpecifier();

    Sp<Identifier> local;
    Sp<Identifier> imported;

};

class LabeledStatement: public Statement {
public:
    LabeledStatement();

    Sp<Identifier> label;
    Sp<Statement> body;

};

class Literal: public Expression {
public:
    Literal();

    std::variant<bool, double, UString> value;
    UString raw;

};

class MetaProperty: public Expression {
public:
    MetaProperty();

    Sp<Identifier> meta;
    Sp<Identifier> property;

};

class MethodDefinition: public SyntaxNode {
public:
    MethodDefinition();

    std::optional<Sp<SyntaxNode>> key;
    bool computed = false;
    std::optional<Sp<Expression>> value;
    VarKind kind;
    bool static_ = false;

};

class Module: public SyntaxNode {
public:
    Module();

    std::vector<Sp<SyntaxNode>> body;
    UString source_type;

};

class NewExpression: public Expression {
public:
    NewExpression();

    Sp<Expression> callee;
    std::vector<Sp<SyntaxNode>> arguments;

};

class ObjectExpression: public Expression {
public:
    ObjectExpression();

    std::vector<Sp<SyntaxNode>> properties;

};

class ObjectPattern: public Pattern {
public:
    ObjectPattern();

    std::vector<Sp<SyntaxNode>> properties;

};

class Property: public SyntaxNode {
public:
    Property();

    Sp<SyntaxNode> key;
    bool computed = false;
    std::optional<Sp<SyntaxNode>> value;
    VarKind kind;
    bool method = false;
    bool shorthand = false;

};

class RegexLiteral: public SyntaxNode {
public:
    RegexLiteral();

    UString value;
    UString raw;

};

class RestElement: public Pattern, public Expression {
public:
    RestElement();

    Sp<SyntaxNode> argument;

};

class ReturnStatement: public Statement {
public:
    ReturnStatement();

    std::optional<Sp<Expression>> argument;

};

class Script: public SyntaxNode {
public:
    Script();

    std::vector<Sp<SyntaxNode>> body;
    UString source_type;

};

class SequenceExpression: public Expression {
public:
    SequenceExpression();

    std::vector<Sp<Expression>> expressions;

};

class SpreadElement: public SyntaxNode {
public:
    SpreadElement();

    Sp<Expression> argument;

};

class StaticMemberExpression: public Expression, public Pattern {
public:
    StaticMemberExpression();

    bool computed = false;
    Sp<Expression> object;
    Sp<Expression> property;

};

class Super: public Expression {
public:
    Super();


};

class SwitchCase: public SyntaxNode {
public:
    SwitchCase();

    std::optional<Sp<Expression>> test;
    std::vector<Sp<Statement>> consequent;

};

class SwitchStatement: public Statement {
public:
    SwitchStatement();

    Sp<Expression> discrimiant;
    std::vector<Sp<SwitchCase>> cases;

};

class TaggedTemplateExpression: public Expression {
public:
    TaggedTemplateExpression();

    Sp<Expression> tag;
    Sp<TemplateLiteral> quasi;

};

class TemplateElement: public SyntaxNode {
public:
    TemplateElement();

    UString cooked;
    UString raw;
    bool tail = false;

};

class TemplateLiteral: public Expression {
public:
    TemplateLiteral();

    std::vector<Sp<TemplateElement>> quasis;
    std::vector<Sp<Expression>> expressions;

};

class ThisExpression: public Expression {
public:
    ThisExpression();


};

class ThrowStatement: public Statement {
public:
    ThrowStatement();

    Sp<Expression> argument;

};

class TryStatement: public Statement {
public:
    TryStatement();

    Sp<BlockStatement> block;
    std::optional<Sp<CatchClause>> handler;
    std::optional<Sp<BlockStatement>> finalizer;

};

class UnaryExpression: public Expression {
public:
    UnaryExpression();

    UString operator_;
    Sp<Expression> argument;
    bool prefix = false;

};

class UpdateExpression: public Expression {
public:
    UpdateExpression();

    UString operator_;
    Sp<Expression> argument;
    bool prefix = false;

};

class VariableDeclaration: public Declaration {
public:
    VariableDeclaration();

    std::vector<Sp<VariableDeclarator>> declarations;
    VarKind kind;

};

class VariableDeclarator: public SyntaxNode {
public:
    VariableDeclarator();

    Sp<SyntaxNode> id;
    std::optional<Sp<Expression>> init;

};

class WhileStatement: public Statement {
public:
    WhileStatement();

    Sp<Expression> test;
    Sp<Statement> body;

};

class WithStatement: public Statement {
public:
    WithStatement();

    Sp<Expression> object;
    Sp<Statement> body;

};

class YieldExpression: public Expression {
public:
    YieldExpression();

    std::optional<Sp<Expression>> argument;
    bool delegate = false;

};

class ArrowParameterPlaceHolder: public Expression {
public:
    ArrowParameterPlaceHolder();

    std::vector<Sp<SyntaxNode>> params;
    bool async = false;

};
