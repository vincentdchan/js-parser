/* Generated by Racket Script! */

#include "node_types.h"

const char* SyntaxNodeTypeToString(SyntaxNodeType type_) {
    switch (type_) {
        case SyntaxNodeType::ArrayExpression:
            return "ArrayExpression";

        case SyntaxNodeType::ArrayPattern:
            return "ArrayPattern";

        case SyntaxNodeType::ArrowFunctionExpression:
            return "ArrowFunctionExpression";

        case SyntaxNodeType::AssignmentExpression:
            return "AssignmentExpression";

        case SyntaxNodeType::AssignmentPattern:
            return "AssignmentPattern";

        case SyntaxNodeType::AsyncArrowFunctionExpression:
            return "AsyncArrowFunctionExpression";

        case SyntaxNodeType::AsyncFunctionDeclaration:
            return "AsyncFunctionDeclaration";

        case SyntaxNodeType::AsyncFunctionExpression:
            return "AsyncFunctionExpression";

        case SyntaxNodeType::AwaitExpression:
            return "AwaitExpression";

        case SyntaxNodeType::BinaryExpression:
            return "BinaryExpression";

        case SyntaxNodeType::BlockStatement:
            return "BlockStatement";

        case SyntaxNodeType::BreakStatement:
            return "BreakStatement";

        case SyntaxNodeType::CallExpression:
            return "CallExpression";

        case SyntaxNodeType::CatchClause:
            return "CatchClause";

        case SyntaxNodeType::ClassBody:
            return "ClassBody";

        case SyntaxNodeType::ClassDeclaration:
            return "ClassDeclaration";

        case SyntaxNodeType::ClassExpression:
            return "ClassExpression";

        case SyntaxNodeType::ComputedMemberExpression:
            return "ComputedMemberExpression";

        case SyntaxNodeType::ConditionalExpression:
            return "ConditionalExpression";

        case SyntaxNodeType::ContinueStatement:
            return "ContinueStatement";

        case SyntaxNodeType::DebuggerStatement:
            return "DebuggerStatement";

        case SyntaxNodeType::Directive:
            return "Directive";

        case SyntaxNodeType::DoWhileStatement:
            return "DoWhileStatement";

        case SyntaxNodeType::EmptyStatement:
            return "EmptyStatement";

        case SyntaxNodeType::ExportAllDeclaration:
            return "ExportAllDeclaration";

        case SyntaxNodeType::ExportDefaultDeclaration:
            return "ExportDefaultDeclaration";

        case SyntaxNodeType::ExportNamedDeclaration:
            return "ExportNamedDeclaration";

        case SyntaxNodeType::ExportSpecifier:
            return "ExportSpecifier";

        case SyntaxNodeType::ExpressionStatement:
            return "ExpressionStatement";

        case SyntaxNodeType::ForInStatement:
            return "ForInStatement";

        case SyntaxNodeType::ForOfStatement:
            return "ForOfStatement";

        case SyntaxNodeType::ForStatement:
            return "ForStatement";

        case SyntaxNodeType::FunctionDeclaration:
            return "FunctionDeclaration";

        case SyntaxNodeType::FunctionExpression:
            return "FunctionExpression";

        case SyntaxNodeType::Identifier:
            return "Identifier";

        case SyntaxNodeType::IfStatement:
            return "IfStatement";

        case SyntaxNodeType::Import:
            return "Import";

        case SyntaxNodeType::ImportDeclaration:
            return "ImportDeclaration";

        case SyntaxNodeType::ImportDefaultSpecifier:
            return "ImportDefaultSpecifier";

        case SyntaxNodeType::ImportNamespaceSpecifier:
            return "ImportNamespaceSpecifier";

        case SyntaxNodeType::ImportSpecifier:
            return "ImportSpecifier";

        case SyntaxNodeType::LabeledStatement:
            return "LabeledStatement";

        case SyntaxNodeType::Literal:
            return "Literal";

        case SyntaxNodeType::MetaProperty:
            return "MetaProperty";

        case SyntaxNodeType::MethodDefinition:
            return "MethodDefinition";

        case SyntaxNodeType::Module:
            return "Module";

        case SyntaxNodeType::NewExpression:
            return "NewExpression";

        case SyntaxNodeType::ObjectExpression:
            return "ObjectExpression";

        case SyntaxNodeType::ObjectPattern:
            return "ObjectPattern";

        case SyntaxNodeType::Property:
            return "Property";

        case SyntaxNodeType::RegexLiteral:
            return "RegexLiteral";

        case SyntaxNodeType::RestElement:
            return "RestElement";

        case SyntaxNodeType::ReturnStatement:
            return "ReturnStatement";

        case SyntaxNodeType::Script:
            return "Script";

        case SyntaxNodeType::SequenceExpression:
            return "SequenceExpression";

        case SyntaxNodeType::SpreadElement:
            return "SpreadElement";

        case SyntaxNodeType::StaticMemberExpression:
            return "StaticMemberExpression";

        case SyntaxNodeType::Super:
            return "Super";

        case SyntaxNodeType::SwitchCase:
            return "SwitchCase";

        case SyntaxNodeType::SwitchStatement:
            return "SwitchStatement";

        case SyntaxNodeType::TaggedTemplateExpression:
            return "TaggedTemplateExpression";

        case SyntaxNodeType::TemplateElement:
            return "TemplateElement";

        case SyntaxNodeType::ThisExpression:
            return "ThisExpression";

        case SyntaxNodeType::ThrowStatement:
            return "ThrowStatement";

        case SyntaxNodeType::TryStatement:
            return "TryStatement";

        case SyntaxNodeType::UnaryExpression:
            return "UnaryExpression";

        case SyntaxNodeType::UpdateExpression:
            return "UpdateExpression";

        case SyntaxNodeType::VariableDeclaration:
            return "VariableDeclaration";

        case SyntaxNodeType::VariableDeclarator:
            return "VariableDeclarator";

        case SyntaxNodeType::WhileStatement:
            return "WhileStatement";

        case SyntaxNodeType::WithStatement:
            return "WithStatement";

        case SyntaxNodeType::YieldExpression:
            return "YieldExpression";

        default:
            return "<Invalid>";

    }
}