//
// Created by Duzhong Chen on 2020/3/22.
//

#pragma once

#include <vector>
#include <Utils.h>
#include <robin_hood.h>
#include "../parser/NodeTypes.h"

namespace rocket_bundle {

    class SyntaxNode;

    class ExternalVariable {
    public:
        bool is_export_all;
        UString source_name;

        std::vector<UString> export_names;

    };

    struct ExternalInfo {
    public:
        UString path;
        bool is_export_all = false;
        std::vector<UString> names;

    };

    /**
     * Ref: https://github.com/vincentdchan/webpack-deep-scope-analysis-plugin/blob/master/packages/deep-scope-analyser/src/exportManager.ts
     */
    class ExportManager {
    public:
        enum EC {
            Ok = 0,

            UnknownSpecifier = -1,

        };

        ExportManager() = default;
        ExportManager(const ExportManager&) = delete;

        ExportManager& operator=(const ExportManager) = delete;

        EC ResolveAllDecl(const std::shared_ptr<ExportAllDeclaration>&);
        EC ResolveDefaultDecl(const std::shared_ptr<ExportDefaultDeclaration>&);
        EC ResolveNamedDecl(const std::shared_ptr<ExportNamedDeclaration>&);

        std::vector<UString> local_export_name;
//        robin_hood::unordered_map<UString, ExternalVariable> external_export_vars;

        std::vector<std::weak_ptr<SyntaxNode>> external_asts;

        std::vector<ExternalInfo> CollectExternalInfos();

    };

}