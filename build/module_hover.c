#include "tauraro_types.h"

char* _error_code_at(char* line, long long character);
char* _error_code_doc(char* code);
char* _builtin_type_info(char* word);
char* _keyword_info(char* word);
char* _find_decl(TextDocument* doc, char* word, long long from_line);
char* _extract_ret(char* line);
char* _extract_params(char* line);

__attribute__((hot)) JsonVal provide_hover(TextDocument* doc, long long line, long long character) {
    /* pass */
    char* word = TextDocument_word_at(doc, line, character);
    /* pass */
    if ((_tr_strlen((char*)word) == 0LL)) {
        /* pass */
        return jnull();
    }
    /* pass */
    char* line_text = TextDocument_get_line(doc, line);
    /* pass */
    char* code_hover = _error_code_at(line_text, character);
    /* pass */
    if ((_tr_strlen((char*)code_hover) > 0LL)) {
        /* pass */
        return lsp_hover(code_hover, line, character, line, (character + _tr_strlen((char*)word)));
    }
    /* pass */
    char* type_info = _builtin_type_info(word);
    /* pass */
    if ((_tr_strlen((char*)type_info) > 0LL)) {
        /* pass */
        return lsp_hover(type_info, line, character, line, (character + _tr_strlen((char*)word)));
    }
    /* pass */
    char* kw_info = _keyword_info(word);
    /* pass */
    if ((_tr_strlen((char*)kw_info) > 0LL)) {
        /* pass */
        return lsp_hover(kw_info, line, character, line, (character + _tr_strlen((char*)word)));
    }
    /* pass */
    char* decl_info = _find_decl(doc, word, line);
    /* pass */
    if ((_tr_strlen((char*)decl_info) > 0LL)) {
        /* pass */
        return lsp_hover(decl_info, line, character, line, (character + _tr_strlen((char*)word)));
    }
    /* pass */
    return jnull();
}

__attribute__((hot)) char* _error_code_at(char* line, long long character) {
    /* pass */
    char* search = line;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < _tr_strlen((char*)search))) {
        /* pass */
        if ((_tr_str_char_at_code(search, i) == 91LL)) {
            /* pass */
            long long j = (i + 1LL);
            /* pass */
            while ((((j < _tr_strlen((char*)search)) && (_tr_str_char_at_code(search, j) != 93LL)) && ((j - i) < 8LL))) {
                /* pass */
                j = (j + 1LL);
            }
            /* pass */
            if (((j < _tr_strlen((char*)search)) && (_tr_str_char_at_code(search, j) == 93LL))) {
                /* pass */
                if (((character >= i) && (character <= j))) {
                    /* pass */
                    char* code = _tr_str_slice(search, (i + 1LL), j);
                    /* pass */
                    return _error_code_doc(code);
                }
            }
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* _error_code_doc(char* code) {
    /* pass */
    if ((strcmp((char*)code, (char*)"M-1") == 0)) {
        /* pass */
        return "**[M-1] Use after move**\n\nA value was used after it was moved. Moves transfer ownership; the original variable is no longer valid.\n\n**Fix:** Copy the value before moving, or don't move it.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"M-2") == 0)) {
        /* pass */
        return "**[M-2] Double move**\n\nA value was moved more than once.\n\n**Fix:** Clone or restructure the code to avoid the second move.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"M-4") == 0)) {
        /* pass */
        return "**[M-4] Mutation while borrowed**\n\nA container was mutated while a borrow into it was live.\n\n**Fix:** Finish using the borrowed value before mutating the container.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"F-3") == 0)) {
        /* pass */
        return "**[F-3] Missing return**\n\nNot all code paths in a non-void function return a value.\n\n**Fix:** Add a `return` at the end, or ensure every branch returns.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"N-1") == 0)) {
        /* pass */
        return "**[N-1] Reserved name**\n\nA built-in name was used as a variable/function name.\n\n**Fix:** Rename the identifier.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"T-1") == 0)) {
        /* pass */
        return "**[T-1] Non-Sendable type in spawn**\n\nA type crossing a thread boundary does not implement `Sendable`.\n\n**Fix:** Wrap in `Mutex[T]` or add `implements Sendable`.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"L-1") == 0)) {
        /* pass */
        return "**[L-1] Escaping local pointer**\n\nA local `Pointer[T]` is being returned without a lifetime annotation.\n\n**Fix:** Annotate the return type with `from <param>`, or use `unsafe:` if heap-allocated.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"E-1") == 0)) {
        /* pass */
        return "**[E-1] Explicit main() call**\n\nCalling `main()` explicitly is forbidden; the compiler invokes it automatically.";
    }
    /* pass */
    if ((strcmp((char*)code, (char*)"U-1") == 0)) {
        /* pass */
        return "**[U-1] Unsafe in strict mode**\n\n`unsafe:` blocks are not allowed when compiling with `--strict`.";
    }
    /* pass */
    return _tr_str_concat(_tr_str_concat("**[", code), "]** Tauraro compiler diagnostic");
}

__attribute__((hot)) char* _builtin_type_info(char* word) {
    /* pass */
    if ((strcmp((char*)word, (char*)"int") == 0)) {
        /* pass */
        return "**int** — 64-bit signed integer (`long long` in C)";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"float") == 0)) {
        /* pass */
        return "**float** — 64-bit floating point (`double` in C)";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"str") == 0)) {
        /* pass */
        return "**str** — Immutable C string (`char*`). Use `StringBuilder` for building strings.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"bool") == 0)) {
        /* pass */
        return "**bool** — Boolean value: `true` or `false`";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"char") == 0)) {
        /* pass */
        return "**char** — Single ASCII character (8-bit)";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"u64") == 0)) {
        /* pass */
        return "**u64** — 64-bit unsigned integer";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"u32") == 0)) {
        /* pass */
        return "**u32** — 32-bit unsigned integer";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"i32") == 0)) {
        /* pass */
        return "**i32** — 32-bit signed integer";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"i8") == 0)) {
        /* pass */
        return "**i8** — 8-bit signed integer";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"void") == 0)) {
        /* pass */
        return "**void** — No value (unit type)";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Vec") == 0)) {
        /* pass */
        return "**Vec[T]** — Growable array.\n\n```tauraro\nmut v = Vec[int].init(8)\nv.push(42)\nprint(v.get(0))\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Map") == 0)) {
        /* pass */
        return "**Map[K, V]** — Hash map.\n\n```tauraro\nmut m = Map[str, int].init(16)\nm.insert(\"a\", 1)\nprint(m.get(\"a\"))\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Pointer") == 0)) {
        /* pass */
        return "**Pointer[T]** — Raw pointer to T. Use in `unsafe:` blocks for low-level operations.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Option") == 0)) {
        /* pass */
        return "**Option[T]** — Optional value: `Option.some(val)` or `Option.none()`";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Result") == 0)) {
        /* pass */
        return "**Result[T, E]** — Error-handling type: `Result.ok(val)` or `Result.err(err)`";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Shared") == 0)) {
        /* pass */
        return "**Shared[T]** — Reference-counted shared ownership. Cloned via `clone()`, freed automatically.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Mutex") == 0)) {
        /* pass */
        return "**Mutex[T]** — Thread-safe value container. Use `.lock()` / `.get()` to access.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Chan") == 0)) {
        /* pass */
        return "**Chan[T]** — Synchronous channel for goroutine-style communication.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"Atomic") == 0)) {
        /* pass */
        return "**Atomic[T]** — Lock-free atomic integer operations.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"StringBuilder") == 0)) {
        /* pass */
        return "**StringBuilder** — Efficient string building.\n\n```tauraro\nmut sb = StringBuilder.init(64)\nsb.append(\"Hello \")\nsb.append(\"World\")\nmut s = sb.to_string()\n```";
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* _keyword_info(char* word) {
    /* pass */
    if ((strcmp((char*)word, (char*)"def") == 0)) {
        /* pass */
        return "**def** — Define a function.\n\n```tauraro\ndef add(a: int, b: int) -> int:\n    return a + b\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"pub") == 0)) {
        /* pass */
        return "**pub** — Mark a function, class, or field as public (visible outside the module).";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"mut") == 0)) {
        /* pass */
        return "**mut** — Declare a mutable variable or function parameter.\n\n```tauraro\nmut x = 5\nx = x + 1\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"class") == 0)) {
        /* pass */
        return "**class** — Define a class (reference type, heap-allocated).\n\n```tauraro\nclass Point:\n    pub x: float\n    pub y: float\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"extend") == 0)) {
        /* pass */
        return "**extend** — Add methods to a class or enum outside its definition.\n\n```tauraro\nextend Point:\n    pub def dist(self) -> float:\n        return (self.x * self.x + self.y * self.y).sqrt()\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"enum") == 0)) {
        /* pass */
        return "**enum** — Define a sum type (tagged union).\n\n```tauraro\nenum Shape:\n    Circle(radius: float)\n    Rect(w: float, h: float)\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"match") == 0)) {
        /* pass */
        return "**match** — Pattern matching on an enum value.\n\n```tauraro\nmatch shape:\n    case Shape.Circle(r): print(r)\n    case Shape.Rect(w, h): print(w * h)\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"unsafe") == 0)) {
        /* pass */
        return "**unsafe:** — Opt-in to unsafe operations (raw pointer arithmetic, etc.).\n\n```tauraro\nunsafe:\n    mut p = value as Pointer[char]\n    p.offset(0).write(65 as char)\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"spawn") == 0)) {
        /* pass */
        return "**spawn** — Launch a concurrent task.\n\n```tauraro\nspawn my_function(arg)\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"await") == 0)) {
        /* pass */
        return "**await** — Wait for an async task to complete.";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"from") == 0)) {
        /* pass */
        return "**from** — Import specific symbols from a module.\n\n```tauraro\nfrom std.io import File\nfrom mymod import MyClass, my_fn\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"extern") == 0)) {
        /* pass */
        return "**extern \"C\"** — Declare an external C function.\n\n```tauraro\nextern \"C\":\n    def my_c_fn(x: int) -> int\n```";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"true") == 0)) {
        /* pass */
        return "**true** — Boolean literal `true`";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"false") == 0)) {
        /* pass */
        return "**false** — Boolean literal `false`";
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"none") == 0)) {
        /* pass */
        return "**none** — Null literal for `Option[T]` types";
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* _find_decl(TextDocument* doc, char* word, long long from_line) {
    /* pass */
    long long i = from_line;
    /* pass */
    while (((i >= 0LL) && (i > (from_line - 50LL)))) {
        /* pass */
        char* line = _tr_str_strip(TextDocument_get_line(doc, i));
        /* pass */
        if ((_tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("def ", word), "(")) || _tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("pub def ", word), "(")))) {
            /* pass */
            char* ret = _extract_ret(line);
            /* pass */
            char* params = _extract_params(line);
            /* pass */
            char* header = _tr_str_concat("```tauraro\n", _tr_str_replace(line, "pub ", ""));
            /* pass */
            if ((_tr_strlen((char*)ret) > 0LL)) {
                /* pass */
                return _tr_str_concat(_tr_str_concat(_tr_str_concat(_tr_str_concat("**function** `", word), "`\n\n"), header), "\n```");
            }
            /* pass */
            return _tr_str_concat(_tr_str_concat(_tr_str_concat(_tr_str_concat("**function** `", word), "`\n\n```tauraro\n"), line), "\n```");
        }
        /* pass */
        if ((_tr_str_starts_with(line, _tr_str_concat("class ", word)) || _tr_str_starts_with(line, _tr_str_concat("pub class ", word)))) {
            /* pass */
            return _tr_str_concat(_tr_str_concat("**class** `", word), "`\n\nUser-defined class (heap-allocated reference type).");
        }
        /* pass */
        if ((_tr_str_starts_with(line, _tr_str_concat("enum ", word)) || _tr_str_starts_with(line, _tr_str_concat("pub enum ", word)))) {
            /* pass */
            return _tr_str_concat(_tr_str_concat("**enum** `", word), "`\n\nUser-defined enum (tagged union / sum type).");
        }
        /* pass */
        if ((_tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("mut ", word), ":")) || _tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("mut ", word), " =")))) {
            /* pass */
            char* after = _tr_str_strip(_tr_str_slice(line, (4LL + _tr_strlen((char*)word)), _tr_strlen((char*)line)));
            /* pass */
            if (_tr_str_starts_with(after, ":")) {
                /* pass */
                char* type_str = _tr_str_strip(_tr_str_slice(after, 1LL, _tr_strlen((char*)after)));
                /* pass */
                long long eq = _tr_str_index_of(type_str, "=");
                /* pass */
                if ((eq >= 0LL)) {
                    /* pass */
                    type_str = _tr_str_strip(_tr_str_slice(type_str, 0LL, eq));
                }
                /* pass */
                return _tr_str_concat(_tr_str_concat(_tr_str_concat(_tr_str_concat("**variable** `", word), ": "), type_str), "`");
            }
            /* pass */
            return _tr_str_concat(_tr_str_concat("**variable** `", word), "`");
        }
        /* pass */
        i = (i - 1LL);
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* _extract_ret(char* line) {
    /* pass */
    long long arrow = _tr_str_index_of(line, "->");
    /* pass */
    if ((arrow < 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    char* rest = _tr_str_strip(_tr_str_slice(line, (arrow + 2LL), _tr_strlen((char*)line)));
    /* pass */
    long long colon = _tr_str_index_of(rest, ":");
    /* pass */
    if ((colon >= 0LL)) {
        /* pass */
        rest = _tr_str_strip(_tr_str_slice(rest, 0LL, colon));
    }
    /* pass */
    return rest;
}

__attribute__((hot)) char* _extract_params(char* line) {
    /* pass */
    long long _tr_v_open = _tr_str_index_of(line, "(");
    /* pass */
    long long _tr_v_close = _tr_str_index_of(line, ")");
    /* pass */
    if (((_tr_v_open < 0LL) || (_tr_v_close < 0LL))) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(line, (_tr_v_open + 1LL), _tr_v_close);
}

