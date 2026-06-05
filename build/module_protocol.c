#include "tauraro_types.h"


__attribute__((hot)) JsonVal lsp_position(long long line, long long character) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "line", jint(line));
    /* pass */
    JObjBuilder_add(b, "character", jint(character));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_range(long long start_line, long long start_char, long long end_line, long long end_char) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "start", lsp_position(start_line, start_char));
    /* pass */
    JObjBuilder_add(b, "end", lsp_position(end_line, end_char));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_range_line(long long line) {
    /* pass */
    return lsp_range(line, 0LL, line, 9999LL);
}

__attribute__((hot)) JsonVal lsp_location(char* uri, long long start_line, long long start_char, long long end_line, long long end_char) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "uri", jstr(uri));
    /* pass */
    JObjBuilder_add(b, "range", lsp_range(start_line, start_char, end_line, end_char));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_diagnostic(long long start_line, long long start_char, long long end_line, long long end_char, long long severity, char* message, char* code) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "range", lsp_range(start_line, start_char, end_line, end_char));
    /* pass */
    JObjBuilder_add(b, "severity", jint(severity));
    /* pass */
    JObjBuilder_add(b, "message", jstr(message));
    /* pass */
    JObjBuilder_add(b, "source", jstr("tauraroc"));
    /* pass */
    if ((_tr_strlen((char*)code) > 0LL)) {
        /* pass */
        JObjBuilder_add(b, "code", jstr(code));
    }
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_publish_diagnostics(char* uri, List_JsonVal* diagnostics) {
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < diagnostics->len)) {
        /* pass */
        JArrBuilder_add(arr, List_JsonVal_get(diagnostics, i));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "uri", jstr(uri));
    /* pass */
    JObjBuilder_add(b, "diagnostics", JArrBuilder_build(arr));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_completion_item(char* label, long long kind, char* detail, char* insert_text) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "label", jstr(label));
    /* pass */
    JObjBuilder_add(b, "kind", jint(kind));
    /* pass */
    if ((_tr_strlen((char*)detail) > 0LL)) {
        /* pass */
        JObjBuilder_add(b, "detail", jstr(detail));
    }
    /* pass */
    if (((_tr_strlen((char*)insert_text) > 0LL) && (strcmp((char*)insert_text, (char*)label) != 0))) {
        /* pass */
        JObjBuilder_add(b, "insertText", jstr(insert_text));
    }
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_completion_list(List_JsonVal* items, bool is_incomplete) {
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < items->len)) {
        /* pass */
        JArrBuilder_add(arr, List_JsonVal_get(items, i));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "isIncomplete", jbool(is_incomplete));
    /* pass */
    JObjBuilder_add(b, "items", JArrBuilder_build(arr));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_hover(char* contents, long long start_line, long long start_char, long long end_line, long long end_char) {
    /* pass */
    JObjBuilder* mk = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(mk, "kind", jstr("markdown"));
    /* pass */
    JObjBuilder_add(mk, "value", jstr(contents));
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "contents", JObjBuilder_build(mk));
    /* pass */
    JObjBuilder_add(b, "range", lsp_range(start_line, start_char, end_line, end_char));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_document_symbol(char* name, long long kind, long long line, long long end_line, char* detail) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "name", jstr(name));
    /* pass */
    JObjBuilder_add(b, "kind", jint(kind));
    /* pass */
    JObjBuilder_add(b, "range", lsp_range(line, 0LL, end_line, 9999LL));
    /* pass */
    JObjBuilder_add(b, "selectionRange", lsp_range(line, 0LL, line, _tr_strlen((char*)name)));
    /* pass */
    if ((_tr_strlen((char*)detail) > 0LL)) {
        /* pass */
        JObjBuilder_add(b, "detail", jstr(detail));
    }
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal lsp_text_edit(long long start_line, long long start_char, long long end_line, long long end_char, char* new_text) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "range", lsp_range(start_line, start_char, end_line, end_char));
    /* pass */
    JObjBuilder_add(b, "newText", jstr(new_text));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) long long STT_NAMESPACE() {
    /* pass */
    return 0LL;
}

__attribute__((hot)) long long STT_TYPE() {
    /* pass */
    return 1LL;
}

__attribute__((hot)) long long STT_CLASS() {
    /* pass */
    return 2LL;
}

__attribute__((hot)) long long STT_ENUM() {
    /* pass */
    return 3LL;
}

__attribute__((hot)) long long STT_INTERFACE() {
    /* pass */
    return 4LL;
}

__attribute__((hot)) long long STT_STRUCT() {
    /* pass */
    return 5LL;
}

__attribute__((hot)) long long STT_FUNCTION() {
    /* pass */
    return 6LL;
}

__attribute__((hot)) long long STT_METHOD() {
    /* pass */
    return 7LL;
}

__attribute__((hot)) long long STT_PROPERTY() {
    /* pass */
    return 8LL;
}

__attribute__((hot)) long long STT_VARIABLE() {
    /* pass */
    return 9LL;
}

__attribute__((hot)) long long STT_PARAMETER() {
    /* pass */
    return 10LL;
}

__attribute__((hot)) long long STT_KEYWORD() {
    /* pass */
    return 11LL;
}

__attribute__((hot)) long long STT_COMMENT() {
    /* pass */
    return 12LL;
}

__attribute__((hot)) long long STT_STRING() {
    /* pass */
    return 13LL;
}

__attribute__((hot)) long long STT_NUMBER() {
    /* pass */
    return 14LL;
}

__attribute__((hot)) long long STT_OPERATOR() {
    /* pass */
    return 15LL;
}

__attribute__((hot)) long long pos_line(JsonVal p) {
    /* pass */
    return jv_int(jv_get(p, "line"));
}

__attribute__((hot)) long long pos_char(JsonVal p) {
    /* pass */
    return jv_int(jv_get(p, "character"));
}

