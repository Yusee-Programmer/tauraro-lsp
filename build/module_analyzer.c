#include "tauraro_types.h"

void _parse_output(char* output, AnalysisResult* result);
void _extract_symbols(TextDocument* doc, AnalysisResult* result);
char* _extract_ident(char* s, long long start);
char* _extract_return_type(char* line);
long long _find_block_end(TextDocument* doc, long long start);
List_str* _list_dirs(char* path);
char* _tmp_path(char* uri);
char* _str_hash(char* s);
char* _hex_nibble(long long n);
char* _capture(char* cmd);

__attribute__((malloc,returns_nonnull,hot)) Diagnostic* Diagnostic_init(long long line, long long col, long long severity, char* message, char* code) {
    /* pass */
    Diagnostic* d = ((Diagnostic*)_tr_checked_alloc(sizeof(Diagnostic)));
    /* pass */
    d->line = line;
    /* pass */
    d->col = col;
    /* pass */
    d->end_line = line;
    /* pass */
    d->end_col = 9999LL;
    /* pass */
    d->severity = severity;
    /* pass */
    d->message = message;
    /* pass */
    d->code = code;
    /* pass */
    return d;
}

__attribute__((malloc,returns_nonnull,hot)) AnalysisResult* AnalysisResult_init() {
    /* pass */
    AnalysisResult* r = ((AnalysisResult*)_tr_checked_alloc(sizeof(AnalysisResult)));
    /* pass */
    r->diagnostics = (void*)List_ptr_new();
    /* pass */
    r->symbols = (void*)List_ptr_new();
    /* pass */
    r->ok = true;
    /* pass */
    return r;
}

__attribute__((malloc,returns_nonnull,hot)) Analyzer* Analyzer_init(char* compiler_path) {
    /* pass */
    Analyzer* a = ((Analyzer*)_tr_checked_alloc(sizeof(Analyzer)));
    /* pass */
    a->compiler_path = compiler_path;
    /* pass */
    return a;
}

__attribute__((hot)) AnalysisResult* Analyzer_analyze(Analyzer* self, TextDocument* doc) {
    /* pass */
    AnalysisResult* result = AnalysisResult_init();
    /* pass */
    char* tmp_path = _tmp_path(doc->uri);
    /* pass */
    File_write_text(tmp_path, doc->text);
    /* pass */
    char* compiler = self->compiler_path;
    /* pass */
    if ((_tr_strlen((char*)compiler) == 0LL)) {
        /* pass */
        compiler = _find_compiler();
    }
    /* pass */
    if ((_tr_strlen((char*)compiler) == 0LL)) {
        /* pass */
        Diagnostic* d = Diagnostic_init(0LL, 0LL, 3LL, "tauraroc not found — install it or set TAURARO_PATH", "");
        /* pass */
        List_ptr_append(result->diagnostics, d);
        /* pass */
        result->ok = false;
        /* pass */
        return result;
    }
    /* pass */
    char* cmd = _tr_str_concat(_tr_str_concat(_tr_str_concat(_tr_str_concat("\"", compiler), "\" \""), tmp_path), "\" --check 2>&1");
    /* pass */
    char* output = _capture(cmd);
    /* pass */
    _parse_output(output, result);
    /* pass */
    _extract_symbols(doc, result);
    /* pass */
    if (_tr_is_windows()) {
        /* pass */
        _tr_system(_tr_str_concat(_tr_str_concat("del /Q \"", tmp_path), "\" 2>nul"));
    } else {
        /* pass */
        _tr_system(_tr_str_concat(_tr_str_concat("rm -f \"", tmp_path), "\""));
    }
    /* pass */
    return result;
}

__attribute__((hot)) void _parse_output(char* output, AnalysisResult* result) {
    /* pass */
    List_str* lines = _tr_str_split(output, "\n");
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < lines->len)) {
        /* pass */
        char* line = _tr_str_strip(List_str_get(lines, i));
        /* pass */
        if ((_tr_strlen((char*)line) == 0LL)) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            continue;
        }
        /* pass */
        long long severity = 0LL;
        /* pass */
        char* rest = "";
        /* pass */
        if (_tr_str_starts_with(line, "error: ")) {
            /* pass */
            severity = 1LL;
            /* pass */
            rest = _tr_str_slice(line, 7LL, _tr_strlen((char*)line));
        } else if (_tr_str_starts_with(line, "warning: ")) {
            /* pass */
            severity = 2LL;
            /* pass */
            rest = _tr_str_slice(line, 9LL, _tr_strlen((char*)line));
        } else if (_tr_str_starts_with(line, "Parser error:")) {
            /* pass */
            severity = 1LL;
            /* pass */
            rest = _tr_str_strip(_tr_str_slice(line, 13LL, _tr_strlen((char*)line)));
            /* pass */
            Diagnostic* d = Diagnostic_init(0LL, 0LL, severity, _tr_str_concat("Parser error: ", rest), "parse");
            /* pass */
            List_ptr_append(result->diagnostics, d);
            /* pass */
            result->ok = false;
            /* pass */
            i = (i + 1LL);
            /* pass */
            continue;
        }
        /* pass */
        if ((severity == 0LL)) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            continue;
        }
        /* pass */
        long long lnum = 0LL;
        /* pass */
        char* msg = rest;
        /* pass */
        if (_tr_str_starts_with(rest, "line ")) {
            /* pass */
            char* after_line = _tr_str_slice(rest, 5LL, _tr_strlen((char*)rest));
            /* pass */
            long long colon = _tr_str_index_of(after_line, ":");
            /* pass */
            if ((colon > 0LL)) {
                /* pass */
                lnum = _tr_str_to_int(_tr_str_strip(_tr_str_slice(after_line, 0LL, colon)));
                /* pass */
                if ((lnum > 0LL)) {
                    /* pass */
                    lnum = (lnum - 1LL);
                }
                /* pass */
                msg = _tr_str_strip(_tr_str_slice(after_line, (colon + 1LL), _tr_strlen((char*)after_line)));
            }
        }
        /* pass */
        char* code = "";
        /* pass */
        if (_tr_str_starts_with(msg, "[")) {
            /* pass */
            long long _tr_v_close = _tr_str_index_of(msg, "]");
            /* pass */
            if ((_tr_v_close > 0LL)) {
                /* pass */
                code = _tr_str_slice(msg, 1LL, _tr_v_close);
                /* pass */
                msg = _tr_str_strip(_tr_str_slice(msg, (_tr_v_close + 1LL), _tr_strlen((char*)msg)));
            }
        }
        /* pass */
        if (((severity > 0LL) && (_tr_strlen((char*)msg) > 0LL))) {
            /* pass */
            Diagnostic* d = Diagnostic_init(lnum, 0LL, severity, msg, code);
            /* pass */
            List_ptr_append(result->diagnostics, d);
            /* pass */
            if ((severity == 1LL)) {
                /* pass */
                result->ok = false;
            }
        }
        /* pass */
        i = (i + 1LL);
    }
}

__attribute__((hot)) void _extract_symbols(TextDocument* doc, AnalysisResult* result) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < TextDocument_line_count(doc))) {
        /* pass */
        char* line = _tr_str_strip(TextDocument_get_line(doc, i));
        /* pass */
        if ((_tr_str_starts_with(line, "pub def ") || _tr_str_starts_with(line, "def "))) {
            /* pass */
            long long offset = 4LL;
            /* pass */
            if (_tr_str_starts_with(line, "pub ")) {
                /* pass */
                offset = 8LL;
            }
            /* pass */
            char* name = _extract_ident(line, offset);
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                SymbolInfo* sym = ((SymbolInfo*)_tr_checked_alloc(sizeof(SymbolInfo)));
                /* pass */
                sym->name = name;
                /* pass */
                sym->kind = 12LL;
                /* pass */
                sym->line = i;
                /* pass */
                sym->end_line = _find_block_end(doc, i);
                /* pass */
                sym->detail = _extract_return_type(line);
                /* pass */
                List_ptr_append(result->symbols, sym);
            }
        } else if ((_tr_str_starts_with(line, "pub class ") || _tr_str_starts_with(line, "class "))) {
            /* pass */
            long long offset = 6LL;
            /* pass */
            if (_tr_str_starts_with(line, "pub ")) {
                /* pass */
                offset = 10LL;
            }
            /* pass */
            char* name = _extract_ident(line, offset);
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                SymbolInfo* sym = ((SymbolInfo*)_tr_checked_alloc(sizeof(SymbolInfo)));
                /* pass */
                sym->name = name;
                /* pass */
                sym->kind = 5LL;
                /* pass */
                sym->line = i;
                /* pass */
                sym->end_line = _find_block_end(doc, i);
                /* pass */
                sym->detail = "";
                /* pass */
                List_ptr_append(result->symbols, sym);
            }
        } else if ((_tr_str_starts_with(line, "pub enum ") || _tr_str_starts_with(line, "enum "))) {
            /* pass */
            long long offset = 5LL;
            /* pass */
            if (_tr_str_starts_with(line, "pub ")) {
                /* pass */
                offset = 9LL;
            }
            /* pass */
            char* name = _extract_ident(line, offset);
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                SymbolInfo* sym = ((SymbolInfo*)_tr_checked_alloc(sizeof(SymbolInfo)));
                /* pass */
                sym->name = name;
                /* pass */
                sym->kind = 10LL;
                /* pass */
                sym->line = i;
                /* pass */
                sym->end_line = _find_block_end(doc, i);
                /* pass */
                sym->detail = "";
                /* pass */
                List_ptr_append(result->symbols, sym);
            }
        } else if (_tr_str_starts_with(line, "extend ")) {
            /* pass */
            char* name = _extract_ident(line, 7LL);
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                SymbolInfo* sym = ((SymbolInfo*)_tr_checked_alloc(sizeof(SymbolInfo)));
                /* pass */
                sym->name = _tr_str_concat(name, " (extend)");
                /* pass */
                sym->kind = 5LL;
                /* pass */
                sym->line = i;
                /* pass */
                sym->end_line = _find_block_end(doc, i);
                /* pass */
                sym->detail = "extend";
                /* pass */
                List_ptr_append(result->symbols, sym);
            }
        } else if ((_tr_str_starts_with(line, "pub interface ") || _tr_str_starts_with(line, "interface "))) {
            /* pass */
            long long offset = 10LL;
            /* pass */
            if (_tr_str_starts_with(line, "pub ")) {
                /* pass */
                offset = 14LL;
            }
            /* pass */
            char* name = _extract_ident(line, offset);
            /* pass */
            if ((_tr_strlen((char*)name) > 0LL)) {
                /* pass */
                SymbolInfo* sym = ((SymbolInfo*)_tr_checked_alloc(sizeof(SymbolInfo)));
                /* pass */
                sym->name = name;
                /* pass */
                sym->kind = 11LL;
                /* pass */
                sym->line = i;
                /* pass */
                sym->end_line = _find_block_end(doc, i);
                /* pass */
                sym->detail = "";
                /* pass */
                List_ptr_append(result->symbols, sym);
            }
        }
        /* pass */
        i = (i + 1LL);
    }
}

__attribute__((hot)) char* _extract_ident(char* s, long long start) {
    /* pass */
    long long i = start;
    /* pass */
    long long n = _tr_strlen((char*)s);
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = _tr_str_char_at_code(s, i);
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
    return _tr_str_slice(s, start, i);
}

__attribute__((hot)) char* _extract_return_type(char* line) {
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

__attribute__((hot)) long long _find_block_end(TextDocument* doc, long long start) {
    /* pass */
    long long i = (start + 1LL);
    /* pass */
    long long n = TextDocument_line_count(doc);
    /* pass */
    while ((i < n)) {
        /* pass */
        char* line = TextDocument_get_line(doc, i);
        /* pass */
        if ((((_tr_strlen((char*)line) > 0LL) && (_tr_str_char_at_code(line, 0LL) != 32LL)) && (_tr_str_char_at_code(line, 0LL) != 9LL))) {
            /* pass */
            return (i - 1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return (n - 1LL);
}

__attribute__((hot)) char* _find_compiler() {
    /* pass */
    char* env_path = _tr_getenv("TAURARO");
    /* pass */
    if (((_tr_strlen((char*)env_path) > 0LL) && File_file_exists(env_path))) {
        /* pass */
        return env_path;
    }
    /* pass */
    char* tp = _tr_getenv("TAURARO_PATH");
    /* pass */
    if ((_tr_strlen((char*)tp) > 0LL)) {
        /* pass */
        List_str* parts = _tr_str_split(tp, ":");
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < parts->len)) {
            /* pass */
            char* candidate = _tr_str_concat(_tr_str_strip(List_str_get(parts, i)), "/tauraroc");
            /* pass */
            if (_tr_is_windows()) {
                /* pass */
                candidate = _tr_str_concat(candidate, ".exe");
            }
            /* pass */
            if (File_file_exists(candidate)) {
                /* pass */
                return candidate;
            }
            /* pass */
            i = (i + 1LL);
        }
    }
    /* pass */
    char* home = "";
    /* pass */
    if (_tr_is_windows()) {
        /* pass */
        home = _tr_getenv("USERPROFILE");
    } else {
        /* pass */
        home = _tr_getenv("HOME");
    }
    /* pass */
    if ((_tr_strlen((char*)home) > 0LL)) {
        /* pass */
        char* bin_root = _tr_str_concat(home, "/.taupkg/bin");
        /* pass */
        List_str* dirs = _list_dirs(bin_root);
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < dirs->len)) {
            /* pass */
            char* d = List_str_get(dirs, i);
            /* pass */
            if (_tr_str_starts_with(d, "tauraroc-")) {
                /* pass */
                char* candidate = _tr_str_concat(_tr_str_concat(_tr_str_concat(bin_root, "/"), d), "/tauraroc");
                /* pass */
                if (_tr_is_windows()) {
                    /* pass */
                    candidate = _tr_str_concat(candidate, ".exe");
                }
                /* pass */
                if (File_file_exists(candidate)) {
                    /* pass */
                    return candidate;
                }
            }
            /* pass */
            i = (i + 1LL);
        }
    }
    /* pass */
    if (_tr_is_windows()) {
        /* pass */
        char* out = _capture("where tauraroc.exe 2>nul");
        /* pass */
        char* line = _tr_str_strip(List_str_get(_tr_str_split(out, "\n"), 0LL));
        /* pass */
        if ((_tr_strlen((char*)line) > 0LL)) {
            /* pass */
            return line;
        }
    } else {
        /* pass */
        char* out = _capture("command -v tauraroc 2>/dev/null");
        /* pass */
        char* line = _tr_str_strip(out);
        /* pass */
        if ((_tr_strlen((char*)line) > 0LL)) {
            /* pass */
            return line;
        }
    }
    /* pass */
    return "";
}

__attribute__((hot)) List_str* _list_dirs(char* path) {
    /* pass */
    List_str* dirs = (void*)List_str_new();
    /* pass */
    char* out = "";
    /* pass */
    if (_tr_is_windows()) {
        /* pass */
        out = _capture(_tr_str_concat(_tr_str_concat("dir /AD /B \"", path), "\" 2>nul"));
    } else {
        /* pass */
        out = _capture(_tr_str_concat(_tr_str_concat("ls \"", path), "\" 2>/dev/null"));
    }
    /* pass */
    List_str* lines = _tr_str_split(out, "\n");
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < lines->len)) {
        /* pass */
        char* l = _tr_str_strip(List_str_get(lines, i));
        /* pass */
        if ((_tr_strlen((char*)l) > 0LL)) {
            /* pass */
            List_str_append(dirs, l);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return dirs;
}

__attribute__((hot)) char* _tmp_path(char* uri) {
    /* pass */
    char* base = "";
    /* pass */
    if (_tr_is_windows()) {
        /* pass */
        base = _tr_getenv("TEMP");
        /* pass */
        if ((_tr_strlen((char*)base) == 0LL)) {
            /* pass */
            base = _tr_getenv("TMP");
        }
        /* pass */
        if ((_tr_strlen((char*)base) == 0LL)) {
            /* pass */
            base = "C:/Windows/Temp";
        }
    } else {
        /* pass */
        base = "/tmp";
    }
    /* pass */
    char* hash = _str_hash(uri);
    /* pass */
    char* suffix = _tr_str_concat(_tr_str_concat("_lsp_", hash), ".tr");
    /* pass */
    return _tr_str_concat(_tr_str_concat(base, "/"), suffix);
}

__attribute__((hot)) char* _str_hash(char* s) {
    /* pass */
    unsigned long long h = ((unsigned long long)(-3750763034362895579LL));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < _tr_strlen((char*)s))) {
        /* pass */
        unsigned long long c = ((unsigned long long)(_tr_str_char_at_code(s, i)));
        /* pass */
        h = ((h ^ c) * ((unsigned long long)(1099511628211LL)));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    char* result = "";
    /* pass */
    long long shift = 28LL;
    /* pass */
    while ((shift >= 0LL)) {
        /* pass */
        long long nibble = ((((long long)(h)) >> shift) & 15LL);
        /* pass */
        result = _tr_str_concat(result, _hex_nibble(nibble));
        /* pass */
        shift = (shift - 4LL);
    }
    /* pass */
    return result;
}

__attribute__((hot)) char* _hex_nibble(long long n) {
    /* pass */
    if ((n < 10LL)) {
        /* pass */
        return _tr_int_to_str((long long)(n));
    }
    /* pass */
    if ((n == 10LL)) {
        /* pass */
        return "a";
    }
    /* pass */
    if ((n == 11LL)) {
        /* pass */
        return "b";
    }
    /* pass */
    if ((n == 12LL)) {
        /* pass */
        return "c";
    }
    /* pass */
    if ((n == 13LL)) {
        /* pass */
        return "d";
    }
    /* pass */
    if ((n == 14LL)) {
        /* pass */
        return "e";
    }
    /* pass */
    return "f";
}

__attribute__((hot)) char* _capture(char* cmd) {
    /* pass */
    /* pass */
    /* pass */
    return _tr_popen_read(cmd);
}

