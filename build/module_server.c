#include "tauraro_types.h"

bool LspServer_on_initialize(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_did_open(LspServer* self, JsonVal params);
bool LspServer_on_did_change(LspServer* self, JsonVal params);
bool LspServer_on_did_close(LspServer* self, JsonVal params);
bool LspServer_on_did_save(LspServer* self, JsonVal params);
void LspServer_analyze_and_publish(LspServer* self, char* uri);
bool LspServer_on_hover(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_completion(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_definition(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_document_symbols(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_workspace_symbols(LspServer* self, JsonVal id, JsonVal params);
bool LspServer_on_semantic_tokens(LspServer* self, JsonVal id, JsonVal params);
void LspServer_log(LspServer* self, char* msg);
JsonVal _str_arr_v(List_str* v);
JsonVal _semantic_tokens_legend();

__attribute__((malloc,returns_nonnull,hot)) LspServer* LspServer_init() {
    /* pass */
    LspServer* s = ((LspServer*)_tr_checked_alloc(sizeof(LspServer)));
    /* pass */
    s->store = DocumentStore_init();
    /* pass */
    s->analyzer = Analyzer_init(_find_compiler());
    /* pass */
    s->initialized = false;
    /* pass */
    s->shutdown = false;
    /* pass */
    s->log_file = "";
    /* pass */
    return s;
}

__attribute__((hot)) bool LspServer_handle(LspServer* self, JsonVal msg) {
    /* pass */
    if (jv_is_null(msg)) {
        /* pass */
        return false;
    }
    /* pass */
    char* method = jv_str(jv_get(msg, "method"));
    /* pass */
    JsonVal id = jv_get(msg, "id");
    /* pass */
    JsonVal params = jv_get(msg, "params");
    /* pass */
    LspServer_log(self, _tr_str_concat("-> ", method));
    /* pass */
    if ((strcmp((char*)method, (char*)"initialize") == 0)) {
        /* pass */
        return LspServer_on_initialize(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"initialized") == 0)) {
        /* pass */
        self->initialized = true;
        /* pass */
        return true;
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"shutdown") == 0)) {
        /* pass */
        self->shutdown = true;
        /* pass */
        rpc_write(rpc_response(id, jnull()));
        /* pass */
        return true;
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"exit") == 0)) {
        /* pass */
        return false;
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"$/cancelRequest") == 0)) {
        /* pass */
        return true;
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"$/setTrace") == 0)) {
        /* pass */
        return true;
    }
    /* pass */
    if ((!self->initialized)) {
        /* pass */
        rpc_write(rpc_error(id, LSP_ERR_SERVER_NOT_INIT(), "Server not initialized"));
        /* pass */
        return true;
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/didOpen") == 0)) {
        /* pass */
        return LspServer_on_did_open(self, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/didChange") == 0)) {
        /* pass */
        return LspServer_on_did_change(self, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/didClose") == 0)) {
        /* pass */
        return LspServer_on_did_close(self, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/didSave") == 0)) {
        /* pass */
        return LspServer_on_did_save(self, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/hover") == 0)) {
        /* pass */
        return LspServer_on_hover(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/completion") == 0)) {
        /* pass */
        return LspServer_on_completion(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/definition") == 0)) {
        /* pass */
        return LspServer_on_definition(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/documentSymbol") == 0)) {
        /* pass */
        return LspServer_on_document_symbols(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"workspace/symbol") == 0)) {
        /* pass */
        return LspServer_on_workspace_symbols(self, id, params);
    }
    /* pass */
    if ((strcmp((char*)method, (char*)"textDocument/semanticTokens/full") == 0)) {
        /* pass */
        return LspServer_on_semantic_tokens(self, id, params);
    }
    /* pass */
    if ((!jv_is_null(id))) {
        /* pass */
        rpc_write(rpc_error(id, LSP_ERR_METHOD_NOT_FOUND(), _tr_str_concat("Method not found: ", method)));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_initialize(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    JArrBuilder* trigger_chars = JArrBuilder_init();
    /* pass */
    JArrBuilder_add(trigger_chars, jstr("."));
    /* pass */
    JArrBuilder_add(trigger_chars, jstr("("));
    /* pass */
    JObjBuilder* completion_provider = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(completion_provider, "triggerCharacters", JArrBuilder_build(trigger_chars));
    /* pass */
    JObjBuilder_add(completion_provider, "resolveProvider", jbool(false));
    /* pass */
    JsonVal sem_legend = _semantic_tokens_legend();
    /* pass */
    JObjBuilder* sem_provider = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(sem_provider, "legend", sem_legend);
    /* pass */
    JObjBuilder_add(sem_provider, "full", jbool(true));
    /* pass */
    JObjBuilder* capabilities = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(capabilities, "textDocumentSync", jint(1LL));
    /* pass */
    JObjBuilder_add(capabilities, "hoverProvider", jbool(true));
    /* pass */
    JObjBuilder_add(capabilities, "completionProvider", JObjBuilder_build(completion_provider));
    /* pass */
    JObjBuilder_add(capabilities, "definitionProvider", jbool(true));
    /* pass */
    JObjBuilder_add(capabilities, "documentSymbolProvider", jbool(true));
    /* pass */
    JObjBuilder_add(capabilities, "workspaceSymbolProvider", jbool(true));
    /* pass */
    JObjBuilder_add(capabilities, "semanticTokensProvider", JObjBuilder_build(sem_provider));
    /* pass */
    JObjBuilder* server_info = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(server_info, "name", jstr("tauraro-lsp"));
    /* pass */
    JObjBuilder_add(server_info, "version", jstr("0.1.0"));
    /* pass */
    JObjBuilder* result = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(result, "capabilities", JObjBuilder_build(capabilities));
    /* pass */
    JObjBuilder_add(result, "serverInfo", JObjBuilder_build(server_info));
    /* pass */
    rpc_write(rpc_response(id, JObjBuilder_build(result)));
    /* pass */
    self->initialized = true;
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_did_open(LspServer* self, JsonVal params) {
    /* pass */
    JsonVal td = jv_get(params, "textDocument");
    /* pass */
    char* uri = jv_str(jv_get(td, "uri"));
    /* pass */
    char* lang = jv_str(jv_get(td, "languageId"));
    /* pass */
    long long version = jv_int(jv_get(td, "version"));
    /* pass */
    char* text = jv_str(jv_get(td, "text"));
    /* pass */
    DocumentStore__tr_fn_open(self->store, uri, lang, version, text);
    /* pass */
    LspServer_analyze_and_publish(self, uri);
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_did_change(LspServer* self, JsonVal params) {
    /* pass */
    JsonVal td = jv_get(params, "textDocument");
    /* pass */
    char* uri = jv_str(jv_get(td, "uri"));
    /* pass */
    long long version = jv_int(jv_get(td, "version"));
    /* pass */
    JsonVal changes = jv_get(params, "contentChanges");
    /* pass */
    char* new_text = "";
    /* pass */
    if ((jv_arr_len(changes) > 0LL)) {
        /* pass */
        new_text = jv_str(jv_get(jv_arr_get(changes, 0LL), "text"));
    }
    /* pass */
    DocumentStore_change(self->store, uri, version, new_text);
    /* pass */
    LspServer_analyze_and_publish(self, uri);
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_did_close(LspServer* self, JsonVal params) {
    /* pass */
    JsonVal td = jv_get(params, "textDocument");
    /* pass */
    char* uri = jv_str(jv_get(td, "uri"));
    /* pass */
    DocumentStore__tr_fn_close(self->store, uri);
    /* pass */
    List_JsonVal* empty = (void*)List_JsonVal_new();
    /* pass */
    rpc_write(rpc_notify("textDocument/publishDiagnostics", lsp_publish_diagnostics(uri, empty)));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_did_save(LspServer* self, JsonVal params) {
    /* pass */
    JsonVal td = jv_get(params, "textDocument");
    /* pass */
    char* uri = jv_str(jv_get(td, "uri"));
    /* pass */
    LspServer_analyze_and_publish(self, uri);
    /* pass */
    return true;
}

__attribute__((hot)) void LspServer_analyze_and_publish(LspServer* self, char* uri) {
    /* pass */
    if ((!DocumentStore_has(self->store, uri))) {
        /* pass */
        return;
    }
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    AnalysisResult* result = Analyzer_analyze(self->analyzer, doc);
    /* pass */
    List_JsonVal* diags = (void*)List_JsonVal_new();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < result->diagnostics->len)) {
        /* pass */
        Diagnostic* d = ((Diagnostic*)List_ptr_get(result->diagnostics, i));
        /* pass */
        List_JsonVal_append(diags, lsp_diagnostic(d->line, d->col, d->end_line, d->end_col, d->severity, d->message, d->code));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    rpc_write(rpc_notify("textDocument/publishDiagnostics", lsp_publish_diagnostics(uri, diags)));
    /* pass */
    LspServer_log(self, _tr_str_concat(_tr_str_concat(_tr_str_concat(_tr_str_concat("analyzed ", uri), ": "), _tr_int_to_str((long long)(result->diagnostics->len))), " diags"));
}

__attribute__((hot)) bool LspServer_on_hover(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* uri = jv_str(jv_get_path(params, "textDocument.uri"));
    /* pass */
    JsonVal pos = jv_get(params, "position");
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    rpc_write(rpc_response(id, provide_hover(doc, pos_line(pos), pos_char(pos))));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_completion(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* uri = jv_str(jv_get_path(params, "textDocument.uri"));
    /* pass */
    JsonVal pos = jv_get(params, "position");
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    rpc_write(rpc_response(id, provide_completions(doc, pos_line(pos), pos_char(pos))));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_definition(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* uri = jv_str(jv_get_path(params, "textDocument.uri"));
    /* pass */
    JsonVal pos = jv_get(params, "position");
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    rpc_write(rpc_response(id, provide_definition(self->store, doc, pos_line(pos), pos_char(pos))));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_document_symbols(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* uri = jv_str(jv_get_path(params, "textDocument.uri"));
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    AnalysisResult* ra = Analyzer_analyze(self->analyzer, doc);
    /* pass */
    rpc_write(rpc_response(id, provide_document_symbols(ra->symbols)));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_workspace_symbols(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* query = jv_str(jv_get(params, "query"));
    /* pass */
    rpc_write(rpc_response(id, provide_workspace_symbols(self->store, query)));
    /* pass */
    return true;
}

__attribute__((hot)) bool LspServer_on_semantic_tokens(LspServer* self, JsonVal id, JsonVal params) {
    /* pass */
    char* uri = jv_str(jv_get_path(params, "textDocument.uri"));
    /* pass */
    TextDocument* doc = DocumentStore_get(self->store, uri);
    /* pass */
    rpc_write(rpc_response(id, provide_semantic_tokens(doc)));
    /* pass */
    return true;
}

__attribute__((hot)) void LspServer_log(LspServer* self, char* msg) {
    /* pass */
    if ((_tr_strlen((char*)self->log_file) == 0LL)) {
        /* pass */
        return;
    }
    /* pass */
    File_append_text(self->log_file, _tr_str_concat(_tr_str_concat("[tauraro-lsp] ", msg), "\n"));
}

__attribute__((hot)) JsonVal _str_arr_v(List_str* v) {
    /* pass */
    JArrBuilder* arr = JArrBuilder_init();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < v->len)) {
        /* pass */
        JArrBuilder_add(arr, jstr(List_str_get(v, i)));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return JArrBuilder_build(arr);
}

__attribute__((hot)) JsonVal _semantic_tokens_legend() {
    /* pass */
    List_str* types = (void*)List_str_new();
    /* pass */
    List_str_append(types, "namespace");
    /* pass */
    List_str_append(types, "type");
    /* pass */
    List_str_append(types, "class");
    /* pass */
    List_str_append(types, "enum");
    /* pass */
    List_str_append(types, "interface");
    /* pass */
    List_str_append(types, "struct");
    /* pass */
    List_str_append(types, "function");
    /* pass */
    List_str_append(types, "method");
    /* pass */
    List_str_append(types, "property");
    /* pass */
    List_str_append(types, "variable");
    /* pass */
    List_str_append(types, "parameter");
    /* pass */
    List_str_append(types, "keyword");
    /* pass */
    List_str_append(types, "comment");
    /* pass */
    List_str_append(types, "string");
    /* pass */
    List_str_append(types, "number");
    /* pass */
    List_str_append(types, "operator");
    /* pass */
    List_str* mods = (void*)List_str_new();
    /* pass */
    List_str_append(mods, "declaration");
    /* pass */
    List_str_append(mods, "readonly");
    /* pass */
    List_str_append(mods, "static");
    /* pass */
    List_str_append(mods, "deprecated");
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "tokenTypes", _str_arr_v(types));
    /* pass */
    JObjBuilder_add(b, "tokenModifiers", _str_arr_v(mods));
    /* pass */
    return JObjBuilder_build(b);
}

