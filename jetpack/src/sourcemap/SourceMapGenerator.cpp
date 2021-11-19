//
// Created by Duzhong Chen on 2020/7/13.
//

#include <cstring>
#include <fmt/format.h>
#include "utils/JetJSON.h"
#include "utils/io/FileIO.h"
#include "Benchmark.h"
#include "SourceMapGenerator.h"
#include "ModuleResolver.h"

#define IntToVLQBufferSize 8

namespace jetpack {
    using std::memset;

    static char Base64EncodingTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                         'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                         'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                         'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                         'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                         '4', '5', '6', '7', '8', '9', '+', '/'};

    static std::once_flag back_encoding_init_;

    static int Base64BackEncodingTable[127];

    inline char IntToBase64(int code) {
        J_ASSERT(code >= 0 && code <= 0b111111);
        return Base64EncodingTable[code];
    }

    void SourceMapGenerator::IntToVLQ(std::string& ss, int code) {
        int buffer[IntToVLQBufferSize];

        int s1 = code < 0 ? (-code << 1) | 1 : code << 1;
        int counter = 0;
        if (s1 > 0b11111) {
            memset(buffer, 0, IntToVLQBufferSize * sizeof(int));
            while (s1 > 0b11111) {
                buffer[counter++] = s1 & 0b11111;
                s1 >>= 5;
            }
            buffer[counter++] = s1;

            for (int i = 0; i < counter; i++) {
                if (i != counter - 1) {
                    buffer[i] |= 0b100000;
                }
                char ch = IntToBase64(buffer[i]);
                ss.push_back(ch);
            }
        } else {
            char ch = IntToBase64(s1);
            ss.push_back(ch);
        }
    }

    int SourceMapGenerator::VLQToInt(const char* str, const char*& next) {
        std::call_once(back_encoding_init_, [] {
            memset(Base64BackEncodingTable, 0, sizeof(Base64BackEncodingTable));
            static constexpr size_t tableSize = sizeof(Base64EncodingTable) / sizeof(char);

            for (int i = 0; i < tableSize; i++) {
                char ch = Base64EncodingTable[i];
                Base64BackEncodingTable[ch] = i;
            }
        });

        uint32_t len = 0;
        int result = 0;

        std::vector<int> buffer;

        int factor = (str[0] & 1) ? 1 : -1;

        while (str[len] != '\0') {
            char ch = str[len++];
            J_ASSERT(ch < 127);
            int intValue = Base64BackEncodingTable[ch];
            if ((intValue & 0b100000) == 0) {  // has no next
                buffer.push_back(intValue & 0b11111);
                break;
            }
            buffer.push_back(intValue & 0b11111);
        }

        for (int32_t i = buffer.size() - 1; i >= 0; i--) {
            result = result << 5 | buffer[i];
        }

        next = str + len;

        return (result >> 1) * factor;
    }

    void SourceMapGenerator::GenerateVLQStr(std::string& ss, int transformed_column,
                                            int file_index, int before_line, int before_column, int var_index) {
        IntToVLQ(ss, transformed_column);
        IntToVLQ(ss, file_index);
        IntToVLQ(ss, before_line);
        IntToVLQ(ss, before_column);
        if (var_index >= 0) {
            IntToVLQ(ss, var_index);
        }
    }

//    static constexpr size_t TableSize = sizeof Base64EncodingTable / sizeof(char);
//

    SourceMapGenerator::SourceMapGenerator(
            const std::shared_ptr<ModuleResolver>& resolver,
            io::Writer& writer,
            const std::string& filename
    ): writer_(writer), module_resolver_(resolver) {
        writer_.Write("{\n");
        writer_.Write("  \"version\": 3,\n");
        writer_.WriteS(fmt::format("  \"file\": \"{}\",\n", EscapeJSONString(filename)));
        writer_.Write("  \"sourceRoot\": \"\",\n");
        writer_.Write("  \"names\": [],\n");
        mappings_.reserve(8 * 1024);
    }

    void SourceMapGenerator::AddSource(const Sp<ModuleFile>& moduleFile) {
        sources_.push_back(moduleFile);
//        result["sources"].push_back(moduleFile.Path());
//        result["sourcesContent"].push_back(moduleFile.src_content.toStdString());
    }

    int32_t SourceMapGenerator::GetFilenameIndexByModuleId(int32_t module_id) {
        auto iter = module_id_to_index_.find(module_id);
        if (iter != module_id_to_index_.end()) {
            // found;
            return iter->second;
        }
        auto mod = module_resolver_->findModuleById(module_id);
        if (unlikely(mod == nullptr)) {
            // error;
            std::cerr << fmt::format("sourcemap: get module by id failed: {}", module_id) << std::endl;
            return -1;
        }

        AddSource(mod);

        int32_t index = src_counter_++;
        module_id_to_index_[mod->id()] = index;
        return index;
    }

    void SourceMapGenerator::Finalize(Slice<const MappingItem> mapping_items) {
        benchmark::BenchMarker mapping_barker(benchmark::BENCH_FINALIZE_SOURCEMAP_2);
        FinalizeMapping(mapping_items);
        mapping_barker.Submit();

        FinalizeSources();
        FinalizeSourcesContent();

        writer_.Write("  \"mappings\": \"");
        writer_.WriteS(mappings_);
        writer_.Write("\"\n");
        writer_.Write("}");
    }

    void SourceMapGenerator::FinalizeSources() {
        if (sources_.empty()) {
            writer_.Write("  \"sources\": [],\n");
            return;
        }

        writer_.Write("  \"sources\": [\n");
        uint32_t counter = 0;
        for (auto& module : sources_) {
            writer_.Write("    \"");
            writer_.WriteS(EscapeJSONString(module->Path()));
            writer_.Write("\"");
            if (counter++ < sources_.size() - 1) {
                writer_.Write(",");
            }
            writer_.Write("\n");
        }
        writer_.Write("  ],\n");
    }

    void SourceMapGenerator::FinalizeSourcesContent() {
        if (sources_.empty()) {
            writer_.Write("  \"sourcesContent\": [],\n");
            return;
        }
        writer_.Write("  \"sourcesContent\": [\n");

        uint32_t counter = 0;
        for (auto& module : sources_) {
            writer_.Write("    \"");
            writer_.WriteS(module->escaped_content);
            writer_.Write("\"");
            if (counter++ < sources_.size() - 1) {
                writer_.Write(",");
            }
            writer_.Write("\n");
        }

        writer_.Write("  ],\n");
    }

    void SourceMapGenerator::FinalizeMapping(Slice<const MappingItem> items) {
        for (const auto& item : items) {
            AddEnoughLines(item.dist_line);
            bool ec = AddLocation(item.name, item.dist_column,
                                  item.origin.fileId, item.origin.start.line, item.origin.start.column
                                  );
            J_ASSERT(ec);
        }
    }

    void SourceMapGenerator::AddEnoughLines(int32_t target_line) {
        while (line_counter_ < target_line) {
            l_after_col_ = 0;
//            l_file_index_ = 0;
            line_counter_++;
            EndLine();
        }
    }

#define SW(NEW, OLD) ((NEW) - (OLD))

    bool SourceMapGenerator::AddLocation(const std::string& name, int after_col, int file_id, int before_line, int before_col) {
        if (unlikely(file_id < 0)) {
//            J_ASSERT(fileId != -1);
            return true;
        }
        if (mappings_.length() > 0 && mappings_[mappings_.length() - 1] != ';' && mappings_[mappings_.length() - 1] != ',') {
            mappings_.push_back(',');
        }
//        int32_t var_index = GetIdOfName(name);
        int32_t filename_index = GetFilenameIndexByModuleId(file_id);
        if (unlikely(filename_index < 0)) {
            return false;
        }
        GenerateVLQStr(mappings_,
                       SW(after_col, l_after_col_),
                       SW(filename_index, l_file_index_),
                       SW(before_line, l_before_line_),
                       SW(before_col, l_before_col_),
                       -1);
        l_after_col_ = after_col;
        l_file_index_ = filename_index;
        l_before_line_ = before_line;
        l_before_col_ = before_col;
        return true;
    }

}
