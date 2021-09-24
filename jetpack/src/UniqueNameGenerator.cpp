//
// Created by Duzhong Chen on 2020/3/24.
//

#include <cstdlib>
#include <string>
#include <vector>
#include "UniqueNameGenerator.h"
#include "utils/Common.h"

namespace jetpack {

    static const char FirstCharCandidates[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_$";
    static const char CharCandidates[] = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_$";

    static constexpr std::size_t FirstCharCandidatesSize = sizeof(FirstCharCandidates) - 1;
    static constexpr std::size_t CharCandidatesSize = sizeof(CharCandidates) - 1;

    static auto TwoCharsJsKeywords = {
        "do", "if", "in",
    };

    static auto ThreeCharsJSKeywords = {
        "try", "new", "var", "for",
    };

    static auto LongJsKeywords = {
        "await", "break", "case", "catch", "class", "const", "continue", "debugger",
        "default", "delete", "else", "enum", "export", "extends", "false", "finally",
        "function", "import", "instanceof", "null", "return", "super",
        "switch", "this", "throw", "true", "typeof", "void", "while", "with",
        "yield"
    };

    UniqueNameGeneratorWithUsedName::UniqueNameGeneratorWithUsedName() {
        std::call_once(init_once_, [] {
            for (auto& keyword : LongJsKeywords) {
                long_keywords_set.insert(keyword);
            }
        });
    }

    bool UniqueNameGeneratorWithUsedName::IsJsKeyword(const std::string& name) {
        if (name.size() == 1) {
            return false;
        } else if (name.size() == 2) {
            switch (name.at(0)) {
                case 'd':
                    return name.at(1) == 'o';

                case 'i':
                    return name.at(1) == 'f' || name.at(1) == 'n';

                default:
                    return false;

            }
        } else if (name.size() == 3) {
            switch (name.at(0)) {
                case 't':
                    return name == "try";

                case 'n':
                    return name == "new";

                case 'v':
                    return name == "var";

                case 'f':
                    return name == "for";

                default:
                    return false;

            }
        } else {
            return long_keywords_set.find(name) != long_keywords_set.end();
        }
    }

    std::once_flag UniqueNameGeneratorWithUsedName::init_once_;
    HashSet<std::string> UniqueNameGeneratorWithUsedName::long_keywords_set;

    std::shared_ptr<ReadableNameGenerator> ReadableNameGenerator::Make() {
        std::shared_ptr<ReadableNameGenerator> result(new ReadableNameGenerator);
        result->weak_self = result;
        return result;
    }

    std::optional<std::string>
    ReadableNameGenerator::Next(const std::string &original_name) {
        if (!IsNameUsed(original_name)) {  // not exist
            used_name.insert(original_name);
            return std::nullopt;
        }

        std::string tmp = std::to_string(counter++);
        std::string new_name = original_name + "_" + tmp;
        used_name.insert(new_name);
        return { new_name };
    }

    bool ReadableNameGenerator::IsNameUsed(const std::string &name) {
        if (IsJsKeyword(name)) {
            return true;
        }

        std::shared_ptr<ReadableNameGenerator> self = weak_self.lock();

        while (self != nullptr) {
            if (self->used_name.find(name) != self->used_name.end()) {  // found
                return true;
            }
            self = self->prev;
        }

        return false;
    }

    std::shared_ptr<MinifyNameGenerator> MinifyNameGenerator::Make() {
        std::shared_ptr<MinifyNameGenerator> result(new MinifyNameGenerator);
        result->weak_self = result;
        return result;
    }

    std::shared_ptr<MinifyNameGenerator>
    MinifyNameGenerator::Merge(std::vector<std::shared_ptr<MinifyNameGenerator>> &vec) {
        auto result = Make();

        for (auto& ptr : vec) {
            if (ptr->counter > result->counter) {
                result->counter = ptr->counter;
            }
            result->used_name.insert(std::begin(ptr->used_name),
                                     std::end(ptr->used_name));
        }

        return result;
    }

    std::shared_ptr<MinifyNameGenerator>
    MinifyNameGenerator::Merge(std::vector<std::shared_ptr<MinifyNameGenerator>>& vec,
                               const std::shared_ptr<UniqueNameGenerator>& prev) {
        auto result = Merge(vec);

        result->prev = prev;

        return result;
    }

    std::optional<std::string>
    MinifyNameGenerator::Next(const std::string& original) {
        std::string result;

        do {
            result = GenAName();
        } while(IsNameUsed(result));

        return { result };
    }

    bool MinifyNameGenerator::IsNameUsed(const std::string &name) {
        if (IsJsKeyword(name)) {
            return true;
        }

        if (used_name.find(name) != used_name.end()) {  // found
            return true;
        }

        return prev != nullptr && prev->IsNameUsed(name);
    }

    std::string MinifyNameGenerator::GenAName() {
        std::string result;

        std::int32_t buffer[BUFFER_SIZE];
        std::memset(buffer, 0, BUFFER_SIZE * sizeof(std::int32_t));

        int i = 0;
        std::int32_t x = counter;
        if (x == 0) {
            result.push_back(FirstCharCandidates[0]);
        } else {
            bool is_first = true;

            while(x) {

                if (is_first) {
                    buffer[i] = x % FirstCharCandidatesSize;
                    x /= FirstCharCandidatesSize;
                    is_first = false;
                } else {
                    buffer[i] = x % CharCandidatesSize;
                    x /= CharCandidatesSize;
                }

                i++;
            }

            for (std::int32_t j = 0; j < i; j++) {
                if (j == 0) {
                    result.push_back(FirstCharCandidates[buffer[j]]);
                } else {
                    result.push_back(CharCandidates[buffer[j]]);
                }
            }
        }

        counter++;

        return result;
    }

    void UnresolvedNameCollector::InsertByList(std::vector<Identifier*> list) {
        std::lock_guard<std::mutex> lk(logger_mutex);
        for (auto& id : list){
            used_name.insert(id->name);
        }
    }

    bool UnresolvedNameCollector::IsNameUsed(const std::string& name) {
        return used_name.find(name) != used_name.end();
    }

}
