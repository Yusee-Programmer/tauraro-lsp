#include "tauraro_types.h"


__attribute__((hot)) bool rpc_is_terminal() {
    /* pass */
    return (_tr_stdin_isatty() != 0LL);
}

__attribute__((hot)) JsonVal rpc_read() {
    /* pass */
    long long content_length = (-1LL);
    /* pass */
    while (true) {
        /* pass */
        char* line = _tr_read_stdin_line();
        /* pass */
        if ((_tr_strlen((char*)line) == 0LL)) {
            /* pass */
            return JsonVal_make_JNull();
        }
        /* pass */
        char* trimmed = _tr_str_strip(line);
        /* pass */
        if ((_tr_strlen((char*)trimmed) == 0LL)) {
            /* pass */
            break;
        }
        /* pass */
        if (_tr_str_starts_with(trimmed, "Content-Length:")) {
            /* pass */
            char* val_s = _tr_str_strip(_tr_str_slice(trimmed, 15LL, _tr_strlen((char*)trimmed)));
            /* pass */
            content_length = _tr_str_to_int(val_s);
        }
    }
    /* pass */
    if ((content_length <= 0LL)) {
        /* pass */
        return JsonVal_make_JNull();
    }
    /* pass */
    char* body = _tr_read_stdin_bytes(content_length);
    /* pass */
    if ((_tr_strlen((char*)body) == 0LL)) {
        /* pass */
        return JsonVal_make_JNull();
    }
    /* pass */
    return json_parse(body);
}

__attribute__((hot)) void rpc_write(JsonVal v) {
    /* pass */
    char* body = json_str(v);
    /* pass */
    char* msg = _tr_str_concat(_tr_str_concat(_tr_str_concat("Content-Length: ", _tr_int_to_str((long long)(_tr_strlen((char*)body)))), "\r\n\r\n"), body);
    /* pass */
    _tr_write_stdout(msg);
    /* pass */
    _tr_flush_stdout();
}

__attribute__((hot)) JsonVal rpc_response(JsonVal id, JsonVal result) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "jsonrpc", jstr("2.0"));
    /* pass */
    JObjBuilder_add(b, "id", id);
    /* pass */
    JObjBuilder_add(b, "result", result);
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal rpc_error(JsonVal id, long long code, char* message) {
    /* pass */
    JObjBuilder* err = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(err, "code", jint(code));
    /* pass */
    JObjBuilder_add(err, "message", jstr(message));
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "jsonrpc", jstr("2.0"));
    /* pass */
    JObjBuilder_add(b, "id", id);
    /* pass */
    JObjBuilder_add(b, "error", JObjBuilder_build(err));
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) JsonVal rpc_notify(char* method, JsonVal params) {
    /* pass */
    JObjBuilder* b = JObjBuilder_init();
    /* pass */
    JObjBuilder_add(b, "jsonrpc", jstr("2.0"));
    /* pass */
    JObjBuilder_add(b, "method", jstr(method));
    /* pass */
    JObjBuilder_add(b, "params", params);
    /* pass */
    return JObjBuilder_build(b);
}

__attribute__((hot)) long long LSP_ERR_METHOD_NOT_FOUND() {
    /* pass */
    return (-32601LL);
}

__attribute__((hot)) long long LSP_ERR_SERVER_NOT_INIT() {
    /* pass */
    return (-32002LL);
}

