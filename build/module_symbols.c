#include "tauraro_types.h"

bool _is_top_decl(char* line, char* keyword, char* query);
char* _ident_after(char* line, char* keyword);

__attribute__((hot)) JsonVal provide_document_symbols(List_ptr* symbols) {
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < symbols->len)) {
        /* pass */
        SymbolInfo* s = ((SymbolInfo*)List_ptr_get(symbols, i));
        /* pass */
        JArrBuilder_add(arr, lsp_document_symbol(s->name, s->kind, s->line, s->end_line, s->detail));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return JArrBuilder_build(arr);
}

__attribute__((hot)) JsonVal provide_workspace_symbols(DocumentStore* store, char* query) {
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < store->docs->len)) {
        /* pass */
        TextDocument* doc = ((TextDocument*)List_ptr_get(store->docs, i));
        /* pass */
        if ((doc->version < 0LL)) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            continue;
        }
        /* pass */
        long long j = 0LL;
        /* pass */
        while ((j < TextDocument_line_count(doc))) {
            /* pass */
            char* line = _tr_str_strip(TextDocument_get_line(doc, j));
            /* pass */
            char* name = "";
            /* pass */
            long long kind = 12LL;
            /* pass */
            if ((_is_top_decl(line, "def", query) || _is_top_decl(line, "pub def", query))) {
                /* pass */
                name = _ident_after(line, "def");
                /* pass */
                kind = 12LL;
            } else if ((_is_top_decl(line, "class", query) || _is_top_decl(line, "pub class", query))) {
                /* pass */
                name = _ident_after(line, "class");
                /* pass */
                kind = 5LL;
            } else if ((_is_top_decl(line, "enum", query) || _is_top_decl(line, "pub enum", query))) {
                /* pass */
                name = _ident_after(line, "enum");
                /* pass */
                kind = 10LL;
            } else if ((_is_top_decl(line, "interface", query) || _is_top_decl(line, "pub interface", query))) {
                /* pass */
                name = _ident_after(line, "interface");
                /* pass */
                kind = 11LL;
            }
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                /* pass */
                /* pass */
                /* pass */
                /* pass */
                JsonVal loc = lsp_location(doc->uri, j, 0LL, j, _tr_strlen((char*)line));
                /* pass */
                JsonVal sym = JObjBuilder_build(JObjBuilder_add(JObjBuilder_add(JObjBuilder_add(JObjBuilder_init(), "name", jstr(name)), "kind", jint(kind)), "location", loc));
                /* pass */
                JArrBuilder_add(arr, sym);
            }
            /* pass */
            j = (j + 1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return JArrBuilder_build(arr);
}

__attribute__((hot)) bool _is_top_decl(char* line, char* keyword, char* query) {
    /* pass */
    char* prefix = _tr_str_concat(keyword, " ");
    /* pass */
    if ((!_tr_str_starts_with(line, prefix))) {
        /* pass */
        return false;
    }
    /* pass */
    char* name = _ident_after(line, keyword);
    /* pass */
    if ((_tr_strlen((char*)query) == 0LL)) {
        /* pass */
        return (_tr_strlen((char*)name) > 0LL);
    }
    /* pass */
    return _tr_str_starts_with(name, query);
}

__attribute__((hot)) char* _ident_after(char* line, char* keyword) {
    /* pass */
    long long start = (_tr_strlen((char*)keyword) + 1LL);
    /* pass */
    if (_tr_str_starts_with(line, _tr_str_concat("pub ", keyword))) {
        /* pass */
        start = ((4LL + _tr_strlen((char*)keyword)) + 1LL);
    }
    /* pass */
    if ((start >= _tr_strlen((char*)line))) {
        /* pass */
        return "";
    }
    /* pass */
    long long i = start;
    /* pass */
    while ((i < _tr_strlen((char*)line))) {
        /* pass */
        long long c = _tr_str_char_at_code(line, i);
        /* pass */
        if ((((((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))) || ((c >= 48LL) && (c <= 57LL))) || (c == 95LL))) {
            /* pass */
            i = (i + 1LL);
        } else {
            /* pass */
            break;
        }
    }
    /* pass */
    if ((i == start)) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(line, start, i);
}

