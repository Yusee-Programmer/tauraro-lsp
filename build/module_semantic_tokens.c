#include "tauraro_types.h"

List_str* _tauraro_keywords();
bool _is_kw(char* word, List_str* kws);
void _push_token(List_i64* data, long long line, long long start, long long length, long long tok_type, long long modifiers, long long prev_line, long long prev_start);
bool _is_type_name(char* word);
bool _is_upper_start(char* word);
bool _is_alpha_c(long long c);
bool _is_digit_c(long long c);

__attribute__((hot)) List_str* _tauraro_keywords() {
    /* pass */
    List_str* kw = (void*)List_str_new();
    /* pass */
    List_str_append(kw, "def");
    /* pass */
    List_str_append(kw, "pub");
    /* pass */
    List_str_append(kw, "mut");
    /* pass */
    List_str_append(kw, "class");
    /* pass */
    List_str_append(kw, "extend");
    /* pass */
    List_str_append(kw, "enum");
    /* pass */
    List_str_append(kw, "interface");
    /* pass */
    List_str_append(kw, "implements");
    /* pass */
    List_str_append(kw, "if");
    /* pass */
    List_str_append(kw, "elif");
    /* pass */
    List_str_append(kw, "else");
    /* pass */
    List_str_append(kw, "while");
    /* pass */
    List_str_append(kw, "for");
    /* pass */
    List_str_append(kw, "in");
    /* pass */
    List_str_append(kw, "return");
    /* pass */
    List_str_append(kw, "break");
    /* pass */
    List_str_append(kw, "continue");
    /* pass */
    List_str_append(kw, "match");
    /* pass */
    List_str_append(kw, "case");
    /* pass */
    List_str_append(kw, "pass");
    /* pass */
    List_str_append(kw, "true");
    /* pass */
    List_str_append(kw, "false");
    /* pass */
    List_str_append(kw, "none");
    /* pass */
    List_str_append(kw, "and");
    /* pass */
    List_str_append(kw, "or");
    /* pass */
    List_str_append(kw, "not");
    /* pass */
    List_str_append(kw, "from");
    /* pass */
    List_str_append(kw, "import");
    /* pass */
    List_str_append(kw, "unsafe");
    /* pass */
    List_str_append(kw, "extern");
    /* pass */
    List_str_append(kw, "spawn");
    /* pass */
    List_str_append(kw, "await");
    /* pass */
    List_str_append(kw, "async");
    /* pass */
    List_str_append(kw, "const");
    /* pass */
    List_str_append(kw, "shared");
    /* pass */
    List_str_append(kw, "raise");
    /* pass */
    List_str_append(kw, "try");
    /* pass */
    List_str_append(kw, "except");
    /* pass */
    List_str_append(kw, "finally");
    /* pass */
    List_str_append(kw, "with");
    /* pass */
    List_str_append(kw, "assert");
    /* pass */
    List_str_append(kw, "as");
    /* pass */
    List_str_append(kw, "taskgroup");
    /* pass */
    return kw;
}

__attribute__((hot)) bool _is_kw(char* word, List_str* kws) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < kws->len)) {
        /* pass */
        if ((strcmp((char*)List_str_get(kws, i), (char*)word) == 0)) {
            /* pass */
            return true;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return false;
}

__attribute__((hot)) JsonVal provide_semantic_tokens(TextDocument* doc) {
    /* pass */
    List_i64* data = (void*)List_i64_new();
    /* pass */
    long long prev_line = 0LL;
    /* pass */
    long long prev_start = 0LL;
    /* pass */
    List_str* keywords = _tauraro_keywords();
    /* pass */
    long long line_idx = 0LL;
    /* pass */
    while ((line_idx < TextDocument_line_count(doc))) {
        /* pass */
        char* line = TextDocument_get_line(doc, line_idx);
        /* pass */
        long long n = _tr_strlen((char*)line);
        /* pass */
        long long col = 0LL;
        /* pass */
        while ((col < n)) {
            /* pass */
            long long c = _tr_str_char_at_code(line, col);
            /* pass */
            if ((c == 35LL)) {
                /* pass */
                long long length = (n - col);
                /* pass */
                _push_token(data, line_idx, col, length, STT_COMMENT(), 0LL, prev_line, prev_start);
                /* pass */
                prev_line = line_idx;
                /* pass */
                prev_start = col;
                /* pass */
                break;
            }
            /* pass */
            if (((c == 34LL) || (c == 39LL))) {
                /* pass */
                long long quote = c;
                /* pass */
                long long start = col;
                /* pass */
                col = (col + 1LL);
                /* pass */
                while (((col < n) && (_tr_str_char_at_code(line, col) != quote))) {
                    /* pass */
                    if ((_tr_str_char_at_code(line, col) == 92LL)) {
                        /* pass */
                        col = (col + 1LL);
                    }
                    /* pass */
                    col = (col + 1LL);
                }
                /* pass */
                if ((col < n)) {
                    /* pass */
                    col = (col + 1LL);
                }
                /* pass */
                long long length = (col - start);
                /* pass */
                _push_token(data, line_idx, start, length, STT_STRING(), 0LL, prev_line, prev_start);
                /* pass */
                prev_line = line_idx;
                /* pass */
                prev_start = start;
                /* pass */
                continue;
            }
            /* pass */
            if (((c >= 48LL) && (c <= 57LL))) {
                /* pass */
                long long start = col;
                /* pass */
                bool is_float = false;
                /* pass */
                while ((col < n)) {
                    /* pass */
                    long long nc = _tr_str_char_at_code(line, col);
                    /* pass */
                    if (((nc >= 48LL) && (nc <= 57LL))) {
                        /* pass */
                        col = (col + 1LL);
                    } else if (((((nc == 46LL) || (nc == 120LL)) || (nc == 98LL)) || (nc == 111LL))) {
                        /* pass */
                        is_float = true;
                        /* pass */
                        col = (col + 1LL);
                    } else if ((nc == 95LL)) {
                        /* pass */
                        col = (col + 1LL);
                    } else {
                        /* pass */
                        break;
                    }
                }
                /* pass */
                _push_token(data, line_idx, start, (col - start), STT_NUMBER(), 0LL, prev_line, prev_start);
                /* pass */
                prev_line = line_idx;
                /* pass */
                prev_start = start;
                /* pass */
                continue;
            }
            /* pass */
            if (_is_alpha_c(c)) {
                /* pass */
                long long start = col;
                /* pass */
                while (((col < n) && (_is_alpha_c(_tr_str_char_at_code(line, col)) || _is_digit_c(_tr_str_char_at_code(line, col))))) {
                    /* pass */
                    col = (col + 1LL);
                }
                /* pass */
                char* word = _tr_str_slice(line, start, col);
                /* pass */
                long long tok_type = (-1LL);
                /* pass */
                if (_is_kw(word, keywords)) {
                    /* pass */
                    tok_type = STT_KEYWORD();
                } else if (_is_type_name(word)) {
                    /* pass */
                    tok_type = STT_TYPE();
                } else if (((col < n) && (_tr_str_char_at_code(line, col) == 40LL))) {
                    /* pass */
                    tok_type = STT_FUNCTION();
                } else if (_is_upper_start(word)) {
                    /* pass */
                    tok_type = STT_CLASS();
                }
                /* pass */
                if ((tok_type >= 0LL)) {
                    /* pass */
                    _push_token(data, line_idx, start, (col - start), tok_type, 0LL, prev_line, prev_start);
                    /* pass */
                    prev_line = line_idx;
                    /* pass */
                    prev_start = start;
                }
                /* pass */
                continue;
            }
            /* pass */
            col = (col + 1LL);
        }
        /* pass */
        line_idx = (line_idx + 1LL);
    }
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < data->len)) {
        /* pass */
        JArrBuilder_add(arr, jint(List_i64_get(data, i)));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return JObjBuilder_build(JObjBuilder_add(JObjBuilder_init(), "data", JArrBuilder_build(arr)));
}

__attribute__((hot)) void _push_token(List_i64* data, long long line, long long start, long long length, long long tok_type, long long modifiers, long long prev_line, long long prev_start) {
    /* pass */
    long long delta_line = (line - prev_line);
    /* pass */
    long long delta_start = start;
    /* pass */
    if ((delta_line == 0LL)) {
        /* pass */
        delta_start = (start - prev_start);
    }
    /* pass */
    List_i64_append(data, delta_line);
    /* pass */
    List_i64_append(data, delta_start);
    /* pass */
    List_i64_append(data, length);
    /* pass */
    List_i64_append(data, tok_type);
    /* pass */
    List_i64_append(data, modifiers);
}

__attribute__((hot)) bool _is_type_name(char* word) {
    /* pass */
    if (((((strcmp((char*)word, (char*)"int") == 0) || (strcmp((char*)word, (char*)"float") == 0)) || (strcmp((char*)word, (char*)"str") == 0)) || (strcmp((char*)word, (char*)"bool") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"char") == 0) || (strcmp((char*)word, (char*)"void") == 0)) || (strcmp((char*)word, (char*)"u64") == 0)) || (strcmp((char*)word, (char*)"u32") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"i32") == 0) || (strcmp((char*)word, (char*)"i8") == 0)) || (strcmp((char*)word, (char*)"Vec") == 0)) || (strcmp((char*)word, (char*)"Map") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if ((((strcmp((char*)word, (char*)"Pointer") == 0) || (strcmp((char*)word, (char*)"Option") == 0)) || (strcmp((char*)word, (char*)"Result") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"Shared") == 0) || (strcmp((char*)word, (char*)"Mutex") == 0)) || (strcmp((char*)word, (char*)"Chan") == 0)) || (strcmp((char*)word, (char*)"Atomic") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if ((strcmp((char*)word, (char*)"StringBuilder") == 0)) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool _is_upper_start(char* word) {
    /* pass */
    if ((_tr_strlen((char*)word) == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    long long c = _tr_str_char_at_code(word, 0LL);
    /* pass */
    return ((c >= 65LL) && (c <= 90LL));
}

__attribute__((hot)) bool _is_alpha_c(long long c) {
    /* pass */
    return ((((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))) || (c == 95LL));
}

__attribute__((hot)) bool _is_digit_c(long long c) {
    /* pass */
    return ((c >= 48LL) && (c <= 57LL));
}

