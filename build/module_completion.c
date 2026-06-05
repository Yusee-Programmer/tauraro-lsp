#include "tauraro_types.h"

void _add_keywords(List_JsonVal* items, char* prefix);
void _add_builtin_types(List_JsonVal* items, char* prefix);
void _add_method_completions(List_JsonVal* items, char* type_name, char* prefix);
void _add_str_methods(List_JsonVal* items, List_str* methods, char* prefix, char* detail);
void _add_doc_identifiers(TextDocument* doc, List_JsonVal* items, char* prefix);
void _collect_idents(char* line, List_str* seen, char* prefix);
char* _get_prefix(TextDocument* doc, long long line, long long character);
bool _is_after_dot(TextDocument* doc, long long line, long long character);
char* _infer_receiver_type(TextDocument* doc, long long line, long long character);
char* _extract_ident_from(char* s, long long start);
bool _is_keyword_prefix(char* s);
bool _is_in(List_str* v, char* s);
bool _is_keyword(char* s);
bool _is_alpha(long long c);
bool _is_digit(long long c);

__attribute__((hot)) JsonVal provide_completions(TextDocument* doc, long long line, long long character) {
    /* pass */
    List_JsonVal* items = (void*)List_JsonVal_new();
    /* pass */
    char* prefix = _get_prefix(doc, line, character);
    /* pass */
    bool after_dot = _is_after_dot(doc, line, character);
    /* pass */
    if (after_dot) {
        /* pass */
        char* receiver_type = _infer_receiver_type(doc, line, character);
        /* pass */
        _add_method_completions(items, receiver_type, prefix);
    } else {
        /* pass */
        if (((_tr_strlen((char*)prefix) <= 2LL) || _is_keyword_prefix(prefix))) {
            /* pass */
            _add_keywords(items, prefix);
        }
        /* pass */
        _add_builtin_types(items, prefix);
        /* pass */
        _add_doc_identifiers(doc, items, prefix);
    }
    /* pass */
    return lsp_completion_list(items, false);
}

__attribute__((hot)) void _add_keywords(List_JsonVal* items, char* prefix) {
    /* pass */
    List_str* keywords = (void*)List_str_new();
    /* pass */
    List_str_append(keywords, "def");
    /* pass */
    List_str_append(keywords, "pub");
    /* pass */
    List_str_append(keywords, "mut");
    /* pass */
    List_str_append(keywords, "class");
    /* pass */
    List_str_append(keywords, "extend");
    /* pass */
    List_str_append(keywords, "enum");
    /* pass */
    List_str_append(keywords, "interface");
    /* pass */
    List_str_append(keywords, "implements");
    /* pass */
    List_str_append(keywords, "if");
    /* pass */
    List_str_append(keywords, "elif");
    /* pass */
    List_str_append(keywords, "else");
    /* pass */
    List_str_append(keywords, "while");
    /* pass */
    List_str_append(keywords, "for");
    /* pass */
    List_str_append(keywords, "in");
    /* pass */
    List_str_append(keywords, "return");
    /* pass */
    List_str_append(keywords, "break");
    /* pass */
    List_str_append(keywords, "continue");
    /* pass */
    List_str_append(keywords, "match");
    /* pass */
    List_str_append(keywords, "case");
    /* pass */
    List_str_append(keywords, "pass");
    /* pass */
    List_str_append(keywords, "true");
    /* pass */
    List_str_append(keywords, "false");
    /* pass */
    List_str_append(keywords, "none");
    /* pass */
    List_str_append(keywords, "and");
    /* pass */
    List_str_append(keywords, "or");
    /* pass */
    List_str_append(keywords, "not");
    /* pass */
    List_str_append(keywords, "from");
    /* pass */
    List_str_append(keywords, "import");
    /* pass */
    List_str_append(keywords, "unsafe");
    /* pass */
    List_str_append(keywords, "extern");
    /* pass */
    List_str_append(keywords, "spawn");
    /* pass */
    List_str_append(keywords, "await");
    /* pass */
    List_str_append(keywords, "async");
    /* pass */
    List_str_append(keywords, "const");
    /* pass */
    List_str_append(keywords, "shared");
    /* pass */
    List_str_append(keywords, "raise");
    /* pass */
    List_str_append(keywords, "try");
    /* pass */
    List_str_append(keywords, "except");
    /* pass */
    List_str_append(keywords, "finally");
    /* pass */
    List_str_append(keywords, "with");
    /* pass */
    List_str_append(keywords, "assert");
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < keywords->len)) {
        /* pass */
        char* kw = List_str_get(keywords, i);
        /* pass */
        if (((_tr_strlen((char*)prefix) == 0LL) || _tr_str_starts_with(kw, prefix))) {
            /* pass */
            List_JsonVal_append(items, lsp_completion_item(kw, 14LL, "keyword", kw));
        }
        /* pass */
        i = (i + 1LL);
    }
}

__attribute__((hot)) void _add_builtin_types(List_JsonVal* items, char* prefix) {
    /* pass */
    List_str* types = (void*)List_str_new();
    /* pass */
    List_str_append(types, "int");
    /* pass */
    List_str_append(types, "float");
    /* pass */
    List_str_append(types, "str");
    /* pass */
    List_str_append(types, "bool");
    /* pass */
    List_str_append(types, "char");
    /* pass */
    List_str_append(types, "void");
    /* pass */
    List_str_append(types, "u64");
    /* pass */
    List_str_append(types, "u32");
    /* pass */
    List_str_append(types, "i32");
    /* pass */
    List_str_append(types, "i8");
    /* pass */
    List_str_append(types, "Vec");
    /* pass */
    List_str_append(types, "Map");
    /* pass */
    List_str_append(types, "Pointer");
    /* pass */
    List_str_append(types, "Option");
    /* pass */
    List_str_append(types, "Result");
    /* pass */
    List_str_append(types, "Shared");
    /* pass */
    List_str_append(types, "Atomic");
    /* pass */
    List_str_append(types, "Mutex");
    /* pass */
    List_str_append(types, "Chan");
    /* pass */
    List_str_append(types, "StringBuilder");
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < types->len)) {
        /* pass */
        char* t = List_str_get(types, i);
        /* pass */
        if (((_tr_strlen((char*)prefix) == 0LL) || _tr_str_starts_with(t, prefix))) {
            /* pass */
            List_JsonVal_append(items, lsp_completion_item(t, 7LL, "type", t));
        }
        /* pass */
        i = (i + 1LL);
    }
}

__attribute__((hot)) void _add_method_completions(List_JsonVal* items, char* type_name, char* prefix) {
    /* pass */
    if (((strcmp((char*)type_name, (char*)"str") == 0) || (strcmp((char*)type_name, (char*)"") == 0))) {
        /* pass */
        List_str* methods = (void*)List_str_new();
        /* pass */
        List_str_append(methods, "len()");
        /* pass */
        List_str_append(methods, "split(sep)");
        /* pass */
        List_str_append(methods, "trim()");
        /* pass */
        List_str_append(methods, "strip()");
        /* pass */
        List_str_append(methods, "to_upper()");
        /* pass */
        List_str_append(methods, "to_lower()");
        /* pass */
        List_str_append(methods, "starts_with(prefix)");
        /* pass */
        List_str_append(methods, "ends_with(suffix)");
        /* pass */
        List_str_append(methods, "contains(s)");
        /* pass */
        List_str_append(methods, "index_of(s)");
        /* pass */
        List_str_append(methods, "slice(start, end)");
        /* pass */
        List_str_append(methods, "replace(from, to)");
        /* pass */
        List_str_append(methods, "char_at(i)");
        /* pass */
        List_str_append(methods, "parse_int()");
        /* pass */
        List_str_append(methods, "parse_float()");
        /* pass */
        List_str_append(methods, "parse_bool()");
        /* pass */
        List_str_append(methods, "to_str()");
        /* pass */
        List_str_append(methods, "capitalize()");
        /* pass */
        List_str_append(methods, "reverse()");
        /* pass */
        List_str_append(methods, "repeat(n)");
        /* pass */
        _add_str_methods(items, methods, prefix, "str");
    }
    /* pass */
    if ((((strcmp((char*)type_name, (char*)"Vec") == 0) || (strcmp((char*)type_name, (char*)"List") == 0)) || (strcmp((char*)type_name, (char*)"") == 0))) {
        /* pass */
        List_str* methods = (void*)List_str_new();
        /* pass */
        List_str_append(methods, "push(item)");
        /* pass */
        List_str_append(methods, "pop()");
        /* pass */
        List_str_append(methods, "get(i)");
        /* pass */
        List_str_append(methods, "set(i, item)");
        /* pass */
        List_str_append(methods, "len");
        /* pass */
        List_str_append(methods, "contains(item)");
        /* pass */
        List_str_append(methods, "remove(i)");
        /* pass */
        List_str_append(methods, "clear()");
        /* pass */
        List_str_append(methods, "is_empty()");
        /* pass */
        _add_str_methods(items, methods, prefix, "Vec");
    }
    /* pass */
    if (((strcmp((char*)type_name, (char*)"Map") == 0) || (strcmp((char*)type_name, (char*)"") == 0))) {
        /* pass */
        List_str* methods = (void*)List_str_new();
        /* pass */
        List_str_append(methods, "insert(key, val)");
        /* pass */
        List_str_append(methods, "get(key)");
        /* pass */
        List_str_append(methods, "contains(key)");
        /* pass */
        List_str_append(methods, "remove(key)");
        /* pass */
        _add_str_methods(items, methods, prefix, "Map");
    }
    /* pass */
    if ((((strcmp((char*)type_name, (char*)"int") == 0) || (strcmp((char*)type_name, (char*)"float") == 0)) || (strcmp((char*)type_name, (char*)"") == 0))) {
        /* pass */
        List_str* methods = (void*)List_str_new();
        /* pass */
        List_str_append(methods, "to_str()");
        /* pass */
        List_str_append(methods, "to_float()");
        /* pass */
        List_str_append(methods, "to_int()");
        /* pass */
        _add_str_methods(items, methods, prefix, "int");
    }
}

__attribute__((hot)) void _add_str_methods(List_JsonVal* items, List_str* methods, char* prefix, char* detail) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < methods->len)) {
        /* pass */
        char* m = List_str_get(methods, i);
        /* pass */
        char* name = m;
        /* pass */
        long long paren = _tr_str_index_of(m, "(");
        /* pass */
        if ((paren >= 0LL)) {
            /* pass */
            name = _tr_str_slice(m, 0LL, paren);
        }
        /* pass */
        if (((_tr_strlen((char*)prefix) == 0LL) || _tr_str_starts_with(name, prefix))) {
            /* pass */
            List_JsonVal_append(items, lsp_completion_item(name, 2LL, _tr_str_concat(_tr_str_concat(detail, "."), m), name));
        }
        /* pass */
        i = (i + 1LL);
    }
}

__attribute__((hot)) void _add_doc_identifiers(TextDocument* doc, List_JsonVal* items, char* prefix) {
    /* pass */
    List_str* seen = (void*)List_str_new();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < TextDocument_line_count(doc))) {
        /* pass */
        char* line = TextDocument_get_line(doc, i);
        /* pass */
        _collect_idents(line, seen, prefix);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    long long si = 0LL;
    /* pass */
    while ((si < seen->len)) {
        /* pass */
        List_JsonVal_append(items, lsp_completion_item(List_str_get(seen, si), 6LL, "variable", List_str_get(seen, si)));
        /* pass */
        si = (si + 1LL);
    }
}

__attribute__((hot)) void _collect_idents(char* line, List_str* seen, char* prefix) {
    /* pass */
    long long i = 0LL;
    /* pass */
    long long n = _tr_strlen((char*)line);
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = _tr_str_char_at_code(line, i);
        /* pass */
        if (_is_alpha(c)) {
            /* pass */
            long long start = i;
            /* pass */
            while (((i < n) && (_is_alpha(_tr_str_char_at_code(line, i)) || _is_digit(_tr_str_char_at_code(line, i))))) {
                /* pass */
                i = (i + 1LL);
            }
            /* pass */
            char* ident = _tr_str_slice(line, start, i);
            /* pass */
            if (((_tr_strlen((char*)ident) > 2LL) && ((_tr_strlen((char*)prefix) == 0LL) || _tr_str_starts_with(ident, prefix)))) {
                /* pass */
                if (((!_is_in(seen, ident)) && (!_is_keyword(ident)))) {
                    /* pass */
                    List_str_append(seen, ident);
                }
            }
        } else {
            /* pass */
            i = (i + 1LL);
        }
    }
}

__attribute__((hot)) char* _get_prefix(TextDocument* doc, long long line, long long character) {
    /* pass */
    char* l = TextDocument_get_line(doc, line);
    /* pass */
    if ((_tr_strlen((char*)l) == 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    long long end = character;
    /* pass */
    if ((end > _tr_strlen((char*)l))) {
        /* pass */
        end = _tr_strlen((char*)l);
    }
    /* pass */
    long long start = end;
    /* pass */
    while (((start > 0LL) && (_is_alpha(_tr_str_char_at_code(l, (start - 1LL))) || _is_digit(_tr_str_char_at_code(l, (start - 1LL)))))) {
        /* pass */
        start = (start - 1LL);
    }
    /* pass */
    if ((start >= end)) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(l, start, end);
}

__attribute__((hot)) bool _is_after_dot(TextDocument* doc, long long line, long long character) {
    /* pass */
    char* l = TextDocument_get_line(doc, line);
    /* pass */
    long long pos = (character - 1LL);
    /* pass */
    while (((pos > 0LL) && (_is_alpha(_tr_str_char_at_code(l, pos)) || _is_digit(_tr_str_char_at_code(l, pos))))) {
        /* pass */
        pos = (pos - 1LL);
    }
    /* pass */
    if (((pos > 0LL) && (_tr_str_char_at_code(l, pos) == 46LL))) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) char* _infer_receiver_type(TextDocument* doc, long long line, long long character) {
    /* pass */
    char* l = TextDocument_get_line(doc, line);
    /* pass */
    long long pos = (character - 1LL);
    /* pass */
    while (((pos > 0LL) && (_is_alpha(_tr_str_char_at_code(l, pos)) || _is_digit(_tr_str_char_at_code(l, pos))))) {
        /* pass */
        pos = (pos - 1LL);
    }
    /* pass */
    if (((pos <= 0LL) || (_tr_str_char_at_code(l, pos) != 46LL))) {
        /* pass */
        return "";
    }
    /* pass */
    pos = (pos - 1LL);
    /* pass */
    while (((pos > 0LL) && (_tr_str_char_at_code(l, pos) == 32LL))) {
        /* pass */
        pos = (pos - 1LL);
    }
    /* pass */
    long long end = (pos + 1LL);
    /* pass */
    long long start = pos;
    /* pass */
    while (((start > 0LL) && (_is_alpha(_tr_str_char_at_code(l, (start - 1LL))) || _is_digit(_tr_str_char_at_code(l, (start - 1LL)))))) {
        /* pass */
        start = (start - 1LL);
    }
    /* pass */
    if ((start >= end)) {
        /* pass */
        return "";
    }
    /* pass */
    char* var_name = _tr_str_slice(l, start, end);
    /* pass */
    long long search_line = line;
    /* pass */
    while (((search_line >= 0LL) && (search_line > (line - 20LL)))) {
        /* pass */
        char* sl = _tr_str_strip(TextDocument_get_line(doc, search_line));
        /* pass */
        if (_tr_str_contains(sl, _tr_str_concat(var_name, ":"))) {
            /* pass */
            long long colon = _tr_str_index_of(sl, _tr_str_concat(var_name, ":"));
            /* pass */
            if ((colon >= 0LL)) {
                /* pass */
                char* after = _tr_str_strip(_tr_str_slice(sl, ((colon + _tr_strlen((char*)var_name)) + 1LL), _tr_strlen((char*)sl)));
                /* pass */
                return _extract_ident_from(after, 0LL);
            }
        }
        /* pass */
        search_line = (search_line - 1LL);
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* _extract_ident_from(char* s, long long start) {
    /* pass */
    long long i = start;
    /* pass */
    while (((i < _tr_strlen((char*)s)) && (_tr_str_char_at_code(s, i) == 32LL))) {
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    long long begin = i;
    /* pass */
    while (((i < _tr_strlen((char*)s)) && (_is_alpha(_tr_str_char_at_code(s, i)) || _is_digit(_tr_str_char_at_code(s, i))))) {
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((begin >= i)) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(s, begin, i);
}

__attribute__((hot)) bool _is_keyword_prefix(char* s) {
    /* pass */
    return (_tr_strlen((char*)s) <= 3LL);
}

__attribute__((hot)) bool _is_in(List_str* v, char* s) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < v->len)) {
        /* pass */
        if ((strcmp((char*)List_str_get(v, i), (char*)s) == 0)) {
            /* pass */
            return true;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool _is_keyword(char* s) {
    /* pass */
    if (((((strcmp((char*)s, (char*)"def") == 0) || (strcmp((char*)s, (char*)"pub") == 0)) || (strcmp((char*)s, (char*)"mut") == 0)) || (strcmp((char*)s, (char*)"class") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)s, (char*)"if") == 0) || (strcmp((char*)s, (char*)"else") == 0)) || (strcmp((char*)s, (char*)"elif") == 0)) || (strcmp((char*)s, (char*)"while") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)s, (char*)"for") == 0) || (strcmp((char*)s, (char*)"in") == 0)) || (strcmp((char*)s, (char*)"return") == 0)) || (strcmp((char*)s, (char*)"true") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)s, (char*)"false") == 0) || (strcmp((char*)s, (char*)"none") == 0)) || (strcmp((char*)s, (char*)"and") == 0)) || (strcmp((char*)s, (char*)"or") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)s, (char*)"not") == 0) || (strcmp((char*)s, (char*)"from") == 0)) || (strcmp((char*)s, (char*)"import") == 0)) || (strcmp((char*)s, (char*)"match") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)s, (char*)"case") == 0) || (strcmp((char*)s, (char*)"pass") == 0)) || (strcmp((char*)s, (char*)"break") == 0)) || (strcmp((char*)s, (char*)"continue") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool _is_alpha(long long c) {
    /* pass */
    return ((((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))) || (c == 95LL));
}

__attribute__((hot)) bool _is_digit(long long c) {
    /* pass */
    return ((c >= 48LL) && (c <= 57LL));
}

