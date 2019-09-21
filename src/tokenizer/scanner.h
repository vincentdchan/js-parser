//
// Created by Duzhong Chen on 2019/9/3.
//
#pragma once

#include <memory>
#include <vector>
#include <stack>
#include "../parser/parse_error_handler.h"
#include "../utils.h"
#include "token.h"

struct Comment {
    bool multi_line_;
    std::pair<std::uint32_t, std::uint32_t> slice_;
    std::pair<std::uint32_t, std::uint32_t> range_;
    SourceLocation loc_;
};

class Scanner final {
public:
    Scanner(std::shared_ptr<std::u16string> source, std::shared_ptr<parser::ParseErrorHandler> error_handler);
    Scanner(const Scanner&) = delete;
    Scanner(Scanner&&) = delete;

    Scanner& operator=(const Scanner&) = delete;
    Scanner& operator=(Scanner&&) = delete;

    struct ScannerState {
        std::uint32_t index_ = 0;
        std::uint32_t line_number_ = 0;
        std::uint32_t line_start_ = 0;
    };

    inline std::int32_t Length() const {
        return source_->size();
    }

    inline void SetTrackComment(bool tc) {
        track_comment_ = tc;
    }

    ScannerState SaveState();
    void RestoreState(const ScannerState& state);

    void ThrowUnexpectedToken();
    void ThrowUnexpectedToken(const std::string& message);

    void TolerateUnexpectedToken();
    void TolerateUnexpectedToken(const std::string& message);

    inline bool IsEnd() const {
        return index_ >= Length();
    }

    inline std::uint32_t LineNumber() const {
        return line_number_;
    }

    inline std::uint32_t Index() const {
        return index_;
    }

    inline void SetIndex(std::uint32_t index) {
        index_ = index;
    }

    inline std::uint32_t Column() const {
        return index_ - line_start_;
    }

    inline std::uint32_t LineStart() const {
        return line_start_;
    }

    void SkipSingleLineComment(std::uint32_t offset, std::vector<Comment>& result);
    void SkipMultiLineComment(std::vector<Comment>& result);
    void ScanComments(std::vector<Comment>& result);
    static bool IsFutureReservedWord(const UString& str_);
    static bool IsStrictModeReservedWord(const UString& str_);
    static bool IsRestrictedWord(const UString& str_);
    static bool IsKeyword(const UString& str_);
    bool ScanHexEscape(char16_t ch, char32_t& result);
    char32_t ScanUnicodeCodePointEscape();
    UString GetIdentifier();
    UString GetComplexIdentifier();
    bool OctalToDecimal(char16_t ch, std::uint32_t& result);

    Token ScanIdentifier();
    Token ScanPunctuator();
    Token ScanHexLiteral(std::uint32_t index);
    Token ScanBinaryLiteral(std::uint32_t index);
    Token ScanOctalLiteral(char16_t prefix, std::uint32_t index);
    bool IsImplicitOctalLiteral();
    Token ScanNumericLiteral();
    Token ScanStringLiteral();
    Token ScanTemplate();
    bool TestRegExp(const UString& pattern, const UString& flags, UString& regex);
    bool ScanRegExpBody(UString& result);
    bool ScanRegExpFlags(UString& result);
    bool ScanRegExp(Token& tok);
    Token Lex();

    char32_t CodePointAt(std::uint32_t index, std::uint32_t* size_ = nullptr) const;

private:
    std::stack<UString> curly_stack_;

    std::uint32_t index_ = 0u;
    std::uint32_t line_number_ = 0u;
    std::uint32_t line_start_ = 0u;

    std::shared_ptr<parser::ParseErrorHandler> error_handler_;
    std::shared_ptr<std::u16string> source_;
    bool track_comment_ = false;
    bool is_module_ = false;

};
