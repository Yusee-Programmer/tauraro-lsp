#include "tauraro_types.h"

JsonVal _search_doc(TextDocument* doc, char* word, long long skip_line);
bool _is_decl_of(char* line, char* keyword, char* name);
List_str* _collect_imports(TextDocument* doc);
char* _extract_import_path(char* line);
bool _is_builtin(char* word);
bool jv_is_null_def(JsonVal v);

__attribute__((hot)) JsonVal provide_definition(DocumentStore* store, TextDocument* doc, long long line, long long character) {
    /* pass */
    char* word = TextDocument_word_at(doc, line, character);
    /* pass */
    if ((_tr_strlen((char*)word) == 0LL)) {
        /* pass */
        return jnull();
    }
    /* pass */
    if (_is_builtin(word)) {
        /* pass */
        return jnull();
    }
    /* pass */
    JsonVal result = _search_doc(doc, word, line);
    /* pass */
    if ((!jv_is_null_def(result))) {
        /* pass */
        return result;
    }
    /* pass */
    List_str* imports = _collect_imports(doc);
    /* pass */
    long long ii = 0LL;
    /* pass */
    while ((ii < imports->len)) {
        /* pass */
        char* imp_uri = List_str_get(imports, ii);
        /* pass */
        if (DocumentStore_has(store, imp_uri)) {
            /* pass */
            TextDocument* imp_doc = DocumentStore_get(store, imp_uri);
            /* pass */
            JsonVal r2 = _search_doc(imp_doc, word, (-1LL));
            /* pass */
            if ((!jv_is_null_def(r2))) {
                /* pass */
                return r2;
            }
        }
        /* pass */
        ii = (ii + 1LL);
    }
    /* pass */
    return jnull();
}

__attribute__((hot)) JsonVal _search_doc(TextDocument* doc, char* word, long long skip_line) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < TextDocument_line_count(doc))) {
        /* pass */
        if ((i == skip_line)) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            continue;
        }
        /* pass */
        char* line = _tr_str_strip(TextDocument_get_line(doc, i));
        /* pass */
        if ((_is_decl_of(line, "def", word) || _is_decl_of(line, "pub def", word))) {
            /* pass */
            return lsp_location(doc->uri, i, 0LL, i, _tr_strlen((char*)line));
        }
        /* pass */
        if ((_is_decl_of(line, "class", word) || _is_decl_of(line, "pub class", word))) {
            /* pass */
            return lsp_location(doc->uri, i, 0LL, i, _tr_strlen((char*)line));
        }
        /* pass */
        if ((_is_decl_of(line, "enum", word) || _is_decl_of(line, "pub enum", word))) {
            /* pass */
            return lsp_location(doc->uri, i, 0LL, i, _tr_strlen((char*)line));
        }
        /* pass */
        if ((_is_decl_of(line, "interface", word) || _is_decl_of(line, "pub interface", word))) {
            /* pass */
            return lsp_location(doc->uri, i, 0LL, i, _tr_strlen((char*)line));
        }
        /* pass */
        if (((_tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("mut ", word), " ")) || _tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("mut ", word), ":"))) || _tr_str_starts_with(line, _tr_str_concat(_tr_str_concat("mut ", word), "=")))) {
            /* pass */
            return lsp_location(doc->uri, i, 0LL, i, _tr_strlen((char*)line));
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return jnull();
}

__attribute__((hot)) bool _is_decl_of(char* line, char* keyword, char* name) {
    /* pass */
    char* prefix = _tr_str_concat(_tr_str_concat(keyword, " "), name);
    /* pass */
    if ((!_tr_str_starts_with(line, prefix))) {
        /* pass */
        return false;
    }
    /* pass */
    if ((_tr_strlen((char*)line) <= _tr_strlen((char*)prefix))) {
        /* pass */
        return true;
    }
    /* pass */
    long long next = _tr_str_char_at_code(line, _tr_strlen((char*)prefix));
    /* pass */
    return (((((next == 40LL) || (next == 58LL)) || (next == 32LL)) || (next == 60LL)) || (next == 91LL));
}

__attribute__((hot)) List_str* _collect_imports(TextDocument* doc) {
    /* pass */
    List_str* uris = (void*)List_str_new();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < TextDocument_line_count(doc))) {
        /* pass */
        char* line = _tr_str_strip(TextDocument_get_line(doc, i));
        /* pass */
        if (_tr_str_starts_with(line, "from ")) {
            /* pass */
            char* module_path = _extract_import_path(line);
            /* pass */
            if ((_tr_strlen((char*)module_path) > 0LL)) {
                /* pass */
                char* file_path = _tr_str_concat(_tr_str_replace(module_path, ".", "/"), ".tr");
                /* pass */
                List_str_append(uris, path_to_uri(_tr_str_concat("src/", file_path)));
            }
            /* pass */
            i = (i + 1LL);
        } else if (((_tr_strlen((char*)line) > 0LL) && (!_tr_str_starts_with(line, "#")))) {
            /* pass */
            if (((!_tr_str_starts_with(line, "from ")) && (!_tr_str_starts_with(line, "import ")))) {
                /* pass */
                if ((i > 0LL)) {
                    /* pass */
                    break;
                }
            }
        } else {
            /* pass */
            i = (i + 1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return uris;
}

__attribute__((hot)) char* _extract_import_path(char* line) {
    /* pass */
    if ((!_tr_str_starts_with(line, "from "))) {
        /* pass */
        return "";
    }
    /* pass */
    char* rest = _tr_str_strip(_tr_str_slice(line, 5LL, _tr_strlen((char*)line)));
    /* pass */
    long long space = _tr_str_index_of(rest, " ");
    /* pass */
    if ((space < 0LL)) {
        /* pass */
        return rest;
    }
    /* pass */
    return _tr_str_slice(rest, 0LL, space);
}

__attribute__((hot)) bool _is_builtin(char* word) {
    /* pass */
    if (((((strcmp((char*)word, (char*)"int") == 0) || (strcmp((char*)word, (char*)"float") == 0)) || (strcmp((char*)word, (char*)"str") == 0)) || (strcmp((char*)word, (char*)"bool") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"char") == 0) || (strcmp((char*)word, (char*)"void") == 0)) || (strcmp((char*)word, (char*)"true") == 0)) || (strcmp((char*)word, (char*)"false") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"none") == 0) || (strcmp((char*)word, (char*)"Vec") == 0)) || (strcmp((char*)word, (char*)"Map") == 0)) || (strcmp((char*)word, (char*)"Pointer") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    if (((((strcmp((char*)word, (char*)"Option") == 0) || (strcmp((char*)word, (char*)"Result") == 0)) || (strcmp((char*)word, (char*)"print") == 0)) || (strcmp((char*)word, (char*)"len") == 0))) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool jv_is_null_def(JsonVal v) {
    /* pass */
    /* pass */
    /* pass */
    return jv_is_null(v);
}

