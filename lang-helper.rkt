#lang racket

(require "js-syntax.rkt")

(define symbol-tbl (make-hash))

(for-each
  (lambda (node)
    (let (
      [node-id (syntax-node-id node)]
      [node-base (syntax-node-base node)]
      [node-props (syntax-node-props node)]
    )
      (match node-id
        [(cons 'Virtual name) (hash-set! symbol-tbl node-id node)]
        [_ (hash-set! symbol-tbl node-id node)]
      )
    )
  )
  syntax-list
)

(define (type->string type) (match type
  ['String "UString"]
  ['Boolean "bool"]
  ['Number "double"]
  [(cons type-prefix pair-value) (match type-prefix
    ['Vec (string-append "std::vector<" (type->string pair-value) ">")]
    ['Option (string-append "std::optional<" (type->string pair-value) ">")]
    ['Variant (string-append
      "std::variant<"
      (substring
        (foldl
          (lambda (a b) (string-append b ", " (type->string a)))
          ""
          pair-value
        )
        2
      )
      ">")
    ]
  )]
  [_ (string-append "Sp<" (symbol->string type) ">")]
))

(define resersved-prop-name 
  (list
    "operator"
    "static"
  )
)

(define (normalize-prop-name name)
  (list->string
    (flatten
      (map
        (lambda (ch)
          (if (char-upper-case? ch)
            (list #\_ (char-downcase ch))
            ch
          )
        )
        (string->list name)
      )
    )
  )
)

(define (prop->string prop) (letrec (
  [prop-type (car prop)]
  [prop-name (normalize-prop-name (cdr prop))]
  [type-name (type->string prop-type)]
  [default-value (match prop-type
    ['Boolean " = false"]
    [_ ""]
  )]
)
  (if (memf (lambda (item) (equal? prop-name item)) resersved-prop-name)
    (string-append type-name " " prop-name "_" default-value)
    (string-append type-name " " prop-name default-value)
  )
))

(with-output-to-file "src/parser/node_types.h"
	#:exists 'replace
  (lambda()
    (printf "/* Generated by Racket Script! */~n")
    (newline)
    (printf "#pragma once~n")
    (newline)
    (printf "enum class SyntaxNodeType {~n")
    (printf "    Invalid = 0,~n")
    (newline)
    (for-each
      (lambda (node)
        (let (
          [node-id (syntax-node-id node)]
          [node-base (syntax-node-base node)]
        )
          (when (symbol? node-id)
            (printf "    ~s,~n" node-id)
          )
        )
      )
      syntax-list
    )
    (newline)
    (printf "};~n")
    (newline)

    (printf "static const char* SyntaxNodeTypeToString(SyntaxNodeType type_);~n")
    (newline)

    (for-each
      (lambda (node)
        (letrec (
          [node-id (syntax-node-id node)]
          [node-base (syntax-node-base node)]
          [class-name (match node-id
            [(cons 'Virtual symbol) (symbol->string symbol)]
            [_ (symbol->string node-id)]
          )]
        )
          (printf "class ~a;~n" class-name)
        )
      )
      syntax-list
    )
    (newline)
  )
)

(with-output-to-file "src/parser/syntax_nodes.h"
	#:exists 'replace
  (lambda ()
    (printf "/* Generated by Racket Script! */~n")
    (newline)
    (printf "#pragma once~n")
    (newline)
    (printf "#include \"base_nodes.h\"~n")
    (printf "#include <optional>~n")
    (printf "#include <vector>~n")
    (printf "#include <variant>~n")
    (newline)

    (for-each
      (lambda (node)
        (let (
          [node-id (syntax-node-id node)]
          [node-base (syntax-node-base node)]
        )
          (when (symbol? node-id)
            (let (
              [base-str (symbol->string node-base)]
            )
              (printf "class ~s: public ~a {~n" node-id base-str)
              (printf "public:~n")
              (printf "    ~s();~n" node-id)
              (newline)
              (for-each (lambda (prop)
                (printf "    ~a;~n" (prop->string prop))
              ) (syntax-node-props node))
              (newline)
              (printf "};~n")
              (newline)
            )
          )
        )
      )
      syntax-list
    )
  )
)

(with-output-to-file "src/parser/syntax_nodes.cpp"
	#:exists 'replace
  (lambda ()
    (printf "/* Generated by Racket Script! */~n")
    (newline)
    (printf "#include \"syntax_nodes.h\"~n")
    (newline)

    (for-each
      (lambda (node)
        (let (
          [node-id (syntax-node-id node)]
          [node-base (syntax-node-base node)]
        )
          (when (symbol? node-id)
            (let (
              [base-str (symbol->string node-base)]
            )
              (printf "~s::~s(): ~a() {~n" node-id node-id base-str)
              (printf "    type = SyntaxNodeType::~s;\n" node-id)
              (printf "}\n")
              (newline)
            )
          )
        )
      )
      syntax-list
    )
  )
)

(with-output-to-file "src/parser/node_types.cpp"
	#:exists 'replace
  (lambda ()
    (printf "/* Generated by Racket Script! */~n")
    (newline)
    (printf "#include \"node_types.h\"~n")
    (newline)

    (printf "const char* SyntaxNodeTypeToString(SyntaxNodeType type_) {~n")
    (printf "    switch (type_) {~n")
    (for-each
      (lambda (node)
        (let (
          [node-id (syntax-node-id node)]
          [node-base (syntax-node-base node)]
        )
          (when (symbol? node-id)
            (let (
              [base-str (symbol->string node-base)]
            )
              (printf "        case SyntaxNodeType::~s:~n" node-id)
              (printf "            return \"~s\";~n" node-id)
              (newline)
            )
          )
        )
      )
      syntax-list
    )
    (printf "        default:~n")
    (printf "            return \"<Invalid>\";~n")
    (newline)
    (printf "    }~n")
    (printf "}~n")
  )
)