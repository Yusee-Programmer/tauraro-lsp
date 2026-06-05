#include "tauraro_types.h"

long long DocumentStore__find(DocumentStore* self, char* uri);
bool _has_drive_letter(char* s);
List_str* _split_lines(char* text);
bool _is_ident_char(long long c);

__attribute__((malloc,returns_nonnull,hot)) TextDocument* TextDocument_init(char* uri, char* language, long long version, char* text) {
    /* pass */
    TextDocument* d = ((TextDocument*)_tr_checked_alloc(sizeof(TextDocument)));
    /* pass */
    d->uri = uri;
    /* pass */
    d->language = language;
    /* pass */
    d->version = version;
    /* pass */
    d->text = text;
    /* pass */
    d->lines = _split_lines(text);
    /* pass */
    return d;
}

__attribute__((hot)) void TextDocument_update(TextDocument* self, long long version, char* new_text) {
    /* pass */
    self->version = version;
    /* pass */
    self->text = new_text;
    /* pass */
    self->lines = _split_lines(new_text);
}

__attribute__((hot)) long long TextDocument_line_count(TextDocument* self) {
    /* pass */
    return self->lines->len;
}

__attribute__((hot)) char* TextDocument_get_line(TextDocument* self, long long n) {
    /* pass */
    if (((n >= 0LL) && (n < self->lines->len))) {
        /* pass */
        return List_str_get(self->lines, n);
    }
    /* pass */
    return "";
}

__attribute__((hot)) char* TextDocument_word_at(TextDocument* self, long long line, long long character) {
    /* pass */
    char* l = TextDocument_get_line(self, line);
    /* pass */
    if ((_tr_strlen((char*)l) == 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    long long n = _tr_strlen((char*)l);
    /* pass */
    if ((character >= n)) {
        /* pass */
        return "";
    }
    /* pass */
    long long start = character;
    /* pass */
    while (((start > 0LL) && _is_ident_char(_tr_str_char_at_code(l, (start - 1LL))))) {
        /* pass */
        start = (start - 1LL);
    }
    /* pass */
    long long end = character;
    /* pass */
    while (((end < n) && _is_ident_char(_tr_str_char_at_code(l, end)))) {
        /* pass */
        end = (end + 1LL);
    }
    /* pass */
    if ((start >= end)) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(l, start, end);
}

__attribute__((hot)) long long TextDocument_offset_of(TextDocument* self, long long line, long long character) {
    /* pass */
    long long total = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while (((i < line) && (i < self->lines->len))) {
        /* pass */
        total = ((total + _tr_strlen((char*)List_str_get(self->lines, i))) + 1LL);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return (total + character);
}

__attribute__((malloc,returns_nonnull,hot)) DocumentStore* DocumentStore_init() {
    /* pass */
    DocumentStore* s = ((DocumentStore*)_tr_checked_alloc(sizeof(DocumentStore)));
    /* pass */
    s->docs = (void*)List_ptr_new();
    /* pass */
    s->uris = (void*)List_str_new();
    /* pass */
    return s;
}

__attribute__((hot)) void DocumentStore__tr_fn_open(DocumentStore* self, char* uri, char* language, long long version, char* text) {
    /* pass */
    long long i = DocumentStore__find(self, uri);
    /* pass */
    if ((i >= 0LL)) {
        /* pass */
        TextDocument_update(((TextDocument*)List_ptr_get(self->docs, i)), version, text);
    } else {
        /* pass */
        List_ptr_append(self->docs, TextDocument_init(uri, language, version, text));
        /* pass */
        List_str_append(self->uris, uri);
    }
}

__attribute__((hot)) void DocumentStore_change(DocumentStore* self, char* uri, long long version, char* new_text) {
    /* pass */
    long long i = DocumentStore__find(self, uri);
    /* pass */
    if ((i >= 0LL)) {
        /* pass */
        TextDocument_update(((TextDocument*)List_ptr_get(self->docs, i)), version, new_text);
    }
}

__attribute__((hot)) void DocumentStore__tr_fn_close(DocumentStore* self, char* uri) {
    /* pass */
    long long i = DocumentStore__find(self, uri);
    /* pass */
    if ((i >= 0LL)) {
        /* pass */
        ((TextDocument*)List_ptr_get(self->docs, i))->version = (-1LL);
    }
}

__attribute__((hot)) TextDocument* DocumentStore_get(DocumentStore* self, char* uri) {
    /* pass */
    long long i = DocumentStore__find(self, uri);
    /* pass */
    if ((i >= 0LL)) {
        /* pass */
        return ((TextDocument*)List_ptr_get(self->docs, i));
    }
    /* pass */
    return TextDocument_init(uri, "tauraro", 0LL, "");
}

__attribute__((hot)) bool DocumentStore_has(DocumentStore* self, char* uri) {
    /* pass */
    return (DocumentStore__find(self, uri) >= 0LL);
}

__attribute__((hot)) long long DocumentStore__find(DocumentStore* self, char* uri) {
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < self->uris->len)) {
        /* pass */
        if ((strcmp((char*)List_str_get(self->uris, i), (char*)uri) == 0)) {
            /* pass */
            return i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return (-1LL);
}

__attribute__((hot)) char* uri_to_path(char* uri) {
    /* pass */
    char* s = uri;
    /* pass */
    if (_tr_str_starts_with(s, "file:///")) {
        /* pass */
        s = _tr_str_slice(s, 8LL, _tr_strlen((char*)s));
        /* pass */
        if (((!_tr_str_starts_with(s, "/")) && (!_has_drive_letter(s)))) {
            /* pass */
            s = _tr_str_concat("/", s);
        }
    } else if (_tr_str_starts_with(s, "file://")) {
        /* pass */
        s = _tr_str_slice(s, 7LL, _tr_strlen((char*)s));
    }
    /* pass */
    s = _tr_str_replace(s, "%20", " ");
    /* pass */
    s = _tr_str_replace(s, "%3A", ":");
    /* pass */
    s = _tr_str_replace(s, "%2F", "/");
    /* pass */
    return s;
}

__attribute__((hot)) char* path_to_uri(char* path) {
    /* pass */
    char* s = _tr_str_replace(path, "\\", "/");
    /* pass */
    if (_has_drive_letter(s)) {
        /* pass */
        return _tr_str_concat("file:///", s);
    }
    /* pass */
    if ((!_tr_str_starts_with(s, "/"))) {
        /* pass */
        s = _tr_str_concat("/", s);
    }
    /* pass */
    return _tr_str_concat("file://", s);
}

__attribute__((hot)) bool _has_drive_letter(char* s) {
    /* pass */
    if ((_tr_strlen((char*)s) < 2LL)) {
        /* pass */
        return false;
    }
    /* pass */
    long long c = _tr_str_char_at_code(s, 0LL);
    /* pass */
    long long colon = _tr_str_char_at_code(s, 1LL);
    /* pass */
    return ((((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))) && (colon == 58LL));
}

__attribute__((hot)) List_str* _split_lines(char* text) {
    /* pass */
    List_str* lines = (void*)List_str_new();
    /* pass */
    long long i = 0LL;
    /* pass */
    long long n = _tr_strlen((char*)text);
    /* pass */
    long long start = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = _tr_str_char_at_code(text, i);
        /* pass */
        if ((c == 10LL)) {
            /* pass */
            long long line_end = i;
            /* pass */
            if (((line_end > start) && (_tr_str_char_at_code(text, (line_end - 1LL)) == 13LL))) {
                /* pass */
                line_end = (line_end - 1LL);
            }
            /* pass */
            List_str_append(lines, _tr_str_slice(text, start, line_end));
            /* pass */
            start = (i + 1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((start <= n)) {
        /* pass */
        List_str_append(lines, _tr_str_slice(text, start, n));
    }
    /* pass */
    return lines;
}

__attribute__((hot)) bool _is_ident_char(long long c) {
    /* pass */
    return (((((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))) || ((c >= 48LL) && (c <= 57LL))) || (c == 95LL));
}

