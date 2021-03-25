//
// Created by Duzhong Chen on 2021/3/25.
//

#ifndef ROCKET_BUNDLE_UCHAR_H
#define ROCKET_BUNDLE_UCHAR_H

namespace UChar {

    inline bool IsDecimalDigit(char32_t cp) {
        return (cp >= 0x30 && cp <= 0x39);      // 0..9
    }

    inline bool IsLineTerminator(char32_t cp) {
        return (cp == 0x0A) || (cp == 0x0D) || (cp == 0x2028) || (cp == 0x2029);
    }

    static char32_t WHITE_SPACE[] = {0x1680, 0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007, 0x2008, 0x2009, 0x200A, 0x202F, 0x205F, 0x3000, 0xFEFF};

    inline bool IsWhiteSpace(char32_t cp) {
        if (cp >= 0x1680) {
            std::size_t count = sizeof(WHITE_SPACE) / sizeof(char32_t);
            for (std::size_t i = 0; i < count; i++) {
                if (WHITE_SPACE[i] == cp) return true;
            }
        }
        return (cp == 0x20) || (cp == 0x09) || (cp == 0x0B) || (cp == 0x0C) || (cp == 0xA0);
    }

    inline bool IsIdentifierStart(char32_t cp) {
        return (cp == 0x24) || (cp == 0x5F) ||  // $ (dollar) and _ (underscore)
               (cp >= 0x41 && cp <= 0x5A) ||         // A..Z
               (cp >= 0x61 && cp <= 0x7A) ||         // a..z
               (cp == 0x5C) ||                      // \ (backslash)
               ((cp >= 0x80)); // && Regex.NonAsciiIdentifierStart.test(Character.fromCodePoint(cp)));
    }

    inline bool IsIdentifierPart(char32_t cp) {
        return (cp == 0x24) || (cp == 0x5F) ||  // $ (dollar) and _ (underscore)
               (cp >= 0x41 && cp <= 0x5A) ||         // A..Z
               (cp >= 0x61 && cp <= 0x7A) ||         // a..z
               (cp >= 0x30 && cp <= 0x39) ||         // 0..9
               (cp == 0x5C) ||                      // \ (backslash)
               ((cp >= 0x80)); //&& Regex.NonAsciiIdentifierPart.test(Character.fromCodePoint(cp)));
    }

    inline bool IsHexDigit(char32_t cp) {
        return (cp >= 0x30 && cp <= 0x39) ||    // 0..9
               (cp >= 0x41 && cp <= 0x46) ||       // A..F
               (cp >= 0x61 && cp <= 0x66);         // a..f
    }

    inline bool IsOctalDigit(char32_t cp) {
        return (cp >= 0x30 && cp <= 0x37);      // 0..7
    }

}


#endif //ROCKET_BUNDLE_UCHAR_H
