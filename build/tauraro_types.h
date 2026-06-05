#pragma once
#define TAURARO_STD_LIB
#define TAURARO_RT_NO_STRINGBUILDER
#include "tauraro_rt.h"

typedef struct JsonParser JsonParser;
typedef struct JObjBuilder JObjBuilder;
typedef struct JArrBuilder JArrBuilder;
typedef struct StringObj StringObj;
typedef struct StringBuilder StringBuilder;
typedef struct Str Str;
typedef struct File File;
typedef struct Fmt Fmt;
typedef struct Console Console;
typedef struct Path Path;
typedef struct Dir Dir;
typedef struct BufReader BufReader;
typedef struct BufWriter BufWriter;
typedef struct IOEvent IOEvent;
typedef struct IOPoll IOPoll;
typedef struct EventLoop EventLoop;
typedef struct TextDocument TextDocument;
typedef struct DocumentStore DocumentStore;
typedef struct Diagnostic Diagnostic;
typedef struct SymbolInfo SymbolInfo;
typedef struct AnalysisResult AnalysisResult;
typedef struct Analyzer Analyzer;
typedef struct LspServer LspServer;
typedef struct JsonVal JsonVal;


typedef enum {
    JsonVal_JNull,
    JsonVal_JBool,
    JsonVal_JInt,
    JsonVal_JFloat,
    JsonVal_JStr,
    JsonVal_JArr,
    JsonVal_JObj
} JsonVal_tag;

typedef struct JsonVal {
    JsonVal_tag tag;
    union {
        struct {
            bool v;
        } JBool;
        struct {
            long long v;
        } JInt;
        struct {
            double v;
        } JFloat;
        struct {
            char* s;
        } JStr;
        struct {
            List_ptr* items;
        } JArr;
        struct {
            List_str* keys;
            List_ptr* vals;
        } JObj;
    } data;
} JsonVal;

#define JsonVal_make_JNull() ((JsonVal){.tag=JsonVal_JNull})
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JBool(bool v) { JsonVal _r = {.tag=JsonVal_JBool}; _r.data.JBool.v = v; return _r; }
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JInt(long long v) { JsonVal _r = {.tag=JsonVal_JInt}; _r.data.JInt.v = v; return _r; }
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JFloat(double v) { JsonVal _r = {.tag=JsonVal_JFloat}; _r.data.JFloat.v = v; return _r; }
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JStr(char* s) { JsonVal _r = {.tag=JsonVal_JStr}; _r.data.JStr.s = s; return _r; }
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JArr(List_ptr* items) { JsonVal _r = {.tag=JsonVal_JArr}; _r.data.JArr.items = items; return _r; }
static inline __attribute__((always_inline)) JsonVal JsonVal_ctor_JObj(List_str* keys, List_ptr* vals) { JsonVal _r = {.tag=JsonVal_JObj}; _r.data.JObj.keys = keys; _r.data.JObj.vals = vals; return _r; }

#ifndef JsonParser_STRUCT_DEFINED
#define JsonParser_STRUCT_DEFINED
typedef struct JsonParser {
    char* src;
    long long pos;
    long long len;
} JsonParser;
#endif

#ifndef JObjBuilder_STRUCT_DEFINED
#define JObjBuilder_STRUCT_DEFINED
typedef struct JObjBuilder {
    List_str* keys;
    List_ptr* vals;
} JObjBuilder;
#endif

#ifndef JArrBuilder_STRUCT_DEFINED
#define JArrBuilder_STRUCT_DEFINED
typedef struct JArrBuilder {
    List_ptr* items;
} JArrBuilder;
#endif

#ifndef StringObj_STRUCT_DEFINED
#define StringObj_STRUCT_DEFINED
typedef struct StringObj {
    char* data;
    long long len;
    long long capacity;
} StringObj;
#endif

#ifndef StringBuilder_STRUCT_DEFINED
#define StringBuilder_STRUCT_DEFINED
typedef struct StringBuilder {
    StringObj* buf;
} StringBuilder;
#endif

#ifndef Str_STRUCT_DEFINED
#define Str_STRUCT_DEFINED
typedef struct Str {
    long long _dummy;
} Str;
#endif

#ifndef File_STRUCT_DEFINED
#define File_STRUCT_DEFINED
typedef struct File {
    char* path;
    char* mode;
    char* content;
    char* _fp;
} File;
#endif

#ifndef Fmt_STRUCT_DEFINED
#define Fmt_STRUCT_DEFINED
typedef struct Fmt {
    long long _dummy;
} Fmt;
#endif

#ifndef Console_STRUCT_DEFINED
#define Console_STRUCT_DEFINED
typedef struct Console {
    long long _dummy;
} Console;
#endif

#ifndef Path_STRUCT_DEFINED
#define Path_STRUCT_DEFINED
typedef struct Path {
    char* value;
} Path;
#endif

#ifndef Dir_STRUCT_DEFINED
#define Dir_STRUCT_DEFINED
typedef struct Dir {
    char* path;
} Dir;
#endif

#ifndef BufReader_STRUCT_DEFINED
#define BufReader_STRUCT_DEFINED
typedef struct BufReader {
    char* _fp;
    char* _buf;
    long long _cap;
    long long _pos;
    long long _filled;
    char* path;
    bool open;
} BufReader;
#endif

#ifndef BufWriter_STRUCT_DEFINED
#define BufWriter_STRUCT_DEFINED
typedef struct BufWriter {
    char* _fp;
    StringBuilder* _buf;
    long long _cap;
    char* path;
    bool open;
} BufWriter;
#endif

#ifndef IOEvent_STRUCT_DEFINED
#define IOEvent_STRUCT_DEFINED
typedef struct IOEvent {
    long long fd;
    long long events;
    long long userdata;
} IOEvent;
#endif

#ifndef IOPoll_STRUCT_DEFINED
#define IOPoll_STRUCT_DEFINED
typedef struct IOPoll {
    char* handle;
} IOPoll;
#endif

#ifndef EventLoop_STRUCT_DEFINED
#define EventLoop_STRUCT_DEFINED
typedef struct EventLoop {
    IOPoll* poll;
    bool running;
    long long iter_count;
    long long start_ms;
} EventLoop;
#endif

#ifndef TextDocument_STRUCT_DEFINED
#define TextDocument_STRUCT_DEFINED
typedef struct TextDocument {
    char* uri;
    char* language;
    long long version;
    char* text;
    List_str* lines;
} TextDocument;
#endif

#ifndef DocumentStore_STRUCT_DEFINED
#define DocumentStore_STRUCT_DEFINED
typedef struct DocumentStore {
    List_ptr* docs;
    List_str* uris;
} DocumentStore;
#endif

#ifndef Diagnostic_STRUCT_DEFINED
#define Diagnostic_STRUCT_DEFINED
typedef struct Diagnostic {
    long long line;
    long long col;
    long long end_line;
    long long end_col;
    long long severity;
    char* message;
    char* code;
} Diagnostic;
#endif

#ifndef SymbolInfo_STRUCT_DEFINED
#define SymbolInfo_STRUCT_DEFINED
typedef struct SymbolInfo {
    char* name;
    long long kind;
    long long line;
    long long end_line;
    char* detail;
} SymbolInfo;
#endif

#ifndef AnalysisResult_STRUCT_DEFINED
#define AnalysisResult_STRUCT_DEFINED
typedef struct AnalysisResult {
    List_ptr* diagnostics;
    List_ptr* symbols;
    bool ok;
} AnalysisResult;
#endif

#ifndef Analyzer_STRUCT_DEFINED
#define Analyzer_STRUCT_DEFINED
typedef struct Analyzer {
    char* compiler_path;
} Analyzer;
#endif

#ifndef LspServer_STRUCT_DEFINED
#define LspServer_STRUCT_DEFINED
typedef struct LspServer {
    DocumentStore* store;
    Analyzer* analyzer;
    bool initialized;
    bool shutdown;
    char* log_file;
} LspServer;
#endif

typedef struct List_JsonVal { JsonVal* data; size_t len; size_t capacity; } List_JsonVal;
static inline List_JsonVal* List_JsonVal_new(void) { List_JsonVal* l=(List_JsonVal*)malloc(sizeof(List_JsonVal)); l->data=(JsonVal*)malloc(sizeof(JsonVal)*8); l->len=0; l->capacity=8; return l; }
static inline void List_JsonVal_append(List_JsonVal* l, JsonVal val) { if(l->len==l->capacity){ l->capacity*=2; l->data=(JsonVal*)realloc(l->data,sizeof(JsonVal)*l->capacity); } l->data[l->len++]=val; }
static inline JsonVal List_JsonVal_get(List_JsonVal* l, long long i) { _tr_bounds_check(i, l->len); return l->data[i]; }
static inline JsonVal List_JsonVal_pop(List_JsonVal* l) { if(!l||l->len==0) return (JsonVal){0}; l->len--; return l->data[l->len]; }
static inline void List_JsonVal_free(List_JsonVal* l) { if(l){ free(l->data); free(l); } }

__attribute__((hot)) char* raw_alloc(long long size);
__attribute__((hot)) char* raw_realloc(char* ptr, long long size);
__attribute__((hot)) void raw_free(char* ptr);
__attribute__((hot)) void raw_copy(char* dst, char* src, long long n);
__attribute__((hot)) void raw_zero(char* ptr, long long n);
__attribute__((hot)) void raw_move(char* dst, char* src, long long n);
__attribute__((hot)) void* alloc(long long n_elems);
__attribute__((hot)) void dealloc(void* ptr);
__attribute__((hot)) void* resize(void* ptr, long long new_count);
__attribute__((hot)) void copy(void* dst, void* src, long long n_elems);
__attribute__((hot)) JsonVal* box_jv(JsonVal v);
__attribute__((hot)) JsonVal jnull();
__attribute__((hot)) JsonVal jbool(bool v);
__attribute__((hot)) JsonVal jint(long long n);
__attribute__((hot)) JsonVal jfloat(double n);
__attribute__((hot)) JsonVal jstr(char* s);
__attribute__((hot)) JsonVal jarr(List_ptr* items);
__attribute__((hot)) JsonVal jobj(List_str* keys, List_ptr* vals);
__attribute__((hot)) JsonVal jobj_empty();
__attribute__((hot)) bool jv_is_null(JsonVal v);
__attribute__((hot)) char* jv_str(JsonVal v);
__attribute__((hot)) long long jv_int(JsonVal v);
__attribute__((hot)) bool jv_bool(JsonVal v);
__attribute__((hot)) JsonVal jv_get(JsonVal v, char* key);
__attribute__((hot)) JsonVal jv_get_path(JsonVal v, char* path);
__attribute__((hot)) long long jv_arr_len(JsonVal v);
__attribute__((hot)) JsonVal jv_arr_get(JsonVal v, long long i);
__attribute__((malloc,returns_nonnull,hot)) JsonParser* JsonParser_init(char* src);
__attribute__((hot)) long long JsonParser_peek(JsonParser* self);
__attribute__((hot)) long long JsonParser_advance(JsonParser* self);
__attribute__((hot)) void JsonParser_skip_ws(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_null(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_true(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_false(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_string(JsonParser* self);
__attribute__((hot)) char* JsonParser_read_string(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_number(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_array(JsonParser* self);
__attribute__((hot)) JsonVal JsonParser_parse_object(JsonParser* self);
__attribute__((hot)) JsonVal json_parse(char* s);
__attribute__((hot)) char* json_str(JsonVal v);
__attribute__((malloc,returns_nonnull,hot)) JObjBuilder* JObjBuilder_init();
__attribute__((hot)) JObjBuilder* JObjBuilder_add(JObjBuilder* self, char* key, JsonVal val);
__attribute__((hot)) JsonVal JObjBuilder_build(JObjBuilder* self);
__attribute__((malloc,returns_nonnull,hot)) JArrBuilder* JArrBuilder_init();
__attribute__((hot)) JArrBuilder* JArrBuilder_add(JArrBuilder* self, JsonVal val);
__attribute__((hot)) JsonVal JArrBuilder_build(JArrBuilder* self);
__attribute__((hot)) char* _json_escape(char* s);
__attribute__((hot)) char* _hex2(long long n);
__attribute__((hot)) char* _hex_digit(long long n);
__attribute__((hot)) long long _hex4_to_int(char* s);
__attribute__((hot)) long long _hex_char_val(long long c);
__attribute__((hot)) char* _int_to_char_str(long long code);
__attribute__((hot)) void _force_json_list_types();
__attribute__((hot)) bool rpc_is_terminal();
__attribute__((hot)) JsonVal rpc_read();
__attribute__((hot)) void rpc_write(JsonVal v);
__attribute__((hot)) JsonVal rpc_response(JsonVal id, JsonVal result);
__attribute__((hot)) JsonVal rpc_error(JsonVal id, long long code, char* message);
__attribute__((hot)) JsonVal rpc_notify(char* method, JsonVal params);
__attribute__((hot)) long long LSP_ERR_METHOD_NOT_FOUND();
__attribute__((hot)) long long LSP_ERR_SERVER_NOT_INIT();
__attribute__((malloc,returns_nonnull,hot)) StringObj* StringObj_init(char* s);
__attribute__((hot)) char* StringObj_as_str(StringObj* self);
__attribute__((hot)) void StringObj_append(StringObj* self, char* other);
__attribute__((hot)) void StringObj_destroy(StringObj* self);
__attribute__((malloc,returns_nonnull,hot)) StringBuilder* StringBuilder_init(long long initial_capacity);
__attribute__((hot)) void StringBuilder_append(StringBuilder* self, char* s);
__attribute__((hot)) void StringBuilder_append_char(StringBuilder* self, long long c);
__attribute__((hot)) void StringBuilder_append_int(StringBuilder* self, long long n);
__attribute__((hot)) void StringBuilder_append_float(StringBuilder* self, double f);
__attribute__((hot)) long long StringBuilder_len(StringBuilder* self);
__attribute__((hot)) StringObj* StringBuilder_to_string(StringBuilder* self);
__attribute__((hot)) char* StringBuilder_to_owned(StringBuilder* self);
__attribute__((hot)) char* StringBuilder_as_str(StringBuilder* self);
__attribute__((hot)) void StringBuilder_clear(StringBuilder* self);
__attribute__((hot)) void StringBuilder__tr_fn_free(StringBuilder* self);
__attribute__((hot)) long long Str_len(char* s);
__attribute__((hot)) bool Str_starts_with(char* s, char* prefix);
__attribute__((hot)) bool Str_ends_with(char* s, char* suffix);
__attribute__((hot)) bool Str_contains_char(char* s, long long c);
__attribute__((hot)) bool Str_contains(char* s, char* sub);
__attribute__((hot)) bool Str_eq(char* a, char* b);
__attribute__((hot)) bool Str_is_digit(char* s);
__attribute__((hot)) bool Str_is_alpha(char* s);
__attribute__((hot)) bool Str_is_alnum(char* s);
__attribute__((hot)) bool Str_is_space(char* s);
__attribute__((hot)) bool Str_is_upper(char* s);
__attribute__((hot)) bool Str_is_lower(char* s);
__attribute__((hot)) char* Str_slice(char* s, long long start, long long end);
__attribute__((hot)) char* Str_repeat(char* s, long long n);
__attribute__((hot)) char* Str_reverse(char* s);
__attribute__((hot)) char* Str_to_upper(char* s);
__attribute__((hot)) char* Str_to_lower(char* s);
__attribute__((hot)) char* Str_capitalize(char* s);
__attribute__((hot)) char* Str_title(char* s);
__attribute__((hot)) char* Str_trim_left(char* s);
__attribute__((hot)) char* Str_trim_right(char* s);
__attribute__((hot)) char* Str_trim(char* s);
__attribute__((hot)) long long Str_char_at(char* s, long long i);
__attribute__((hot)) char* Str_lpad(char* s, long long width, long long pad_char);
__attribute__((hot)) char* Str_rpad(char* s, long long width, long long pad_char);
__attribute__((hot)) char* Str_center(char* s, long long width);
__attribute__((hot)) long long Str_index_of(char* s, char* sub);
__attribute__((hot)) long long Str_last_index_of(char* s, char* sub);
__attribute__((hot)) long long Str__tr_fn_count(char* s, char* sub);
__attribute__((hot)) List_str* Str_split(char* s, char* sep);
__attribute__((hot)) List_str* Str_split_to_vec(char* s, char* sep);
__attribute__((hot)) char* Str_join(List_str* parts, char* sep);
__attribute__((hot)) char* Str_replace(char* s, char* old, char* new_);
__attribute__((hot)) char* Str_replace_first(char* s, char* old, char* new_);
__attribute__((hot)) char* Str_format(char* template, List_str* values);
__attribute__((hot)) long long Str_parse_int(char* s);
__attribute__((hot)) double Str_parse_float(char* s);
__attribute__((hot)) bool Str_parse_bool(char* s);
__attribute__((hot)) List_str* Str_lines(char* s);
__attribute__((hot)) List_str* Str_words(char* s);
__attribute__((hot)) char* Str_strip_prefix(char* s, char* prefix);
__attribute__((hot)) char* Str_strip_suffix(char* s, char* suffix);
__attribute__((hot)) char* Str_remove_char(char* s, long long c);
__attribute__((malloc,returns_nonnull,hot)) File* File_init(char* path, char* mode);
__attribute__((hot)) bool File_is_open(File* self);
__attribute__((hot)) char* File__tr_fn_read(File* self);
__attribute__((hot)) List_str* File_readlines(File* self);
__attribute__((hot)) void File__tr_fn_write(File* self, char* data);
__attribute__((hot)) void File_append(File* self, char* data);
__attribute__((hot)) void File_writeln(File* self, char* line);
__attribute__((hot)) void File_seek(File* self, long long offset, long long whence);
__attribute__((hot)) long long File_tell(File* self);
__attribute__((hot)) long long File_size(File* self);
__attribute__((hot)) void File__tr_fn_close(File* self);
__attribute__((hot)) bool File_exists(File* self);
__attribute__((hot)) char* File_read_text(char* path);
__attribute__((hot)) List_str* File_lines(char* path);
__attribute__((hot)) bool File_write_text(char* path, char* data);
__attribute__((hot)) bool File_append_text(char* path, char* data);
__attribute__((hot)) bool File_file_exists(char* path);
__attribute__((hot)) long long File_file_size(char* path);
__attribute__((hot)) char* read_file(char* path);
__attribute__((hot)) bool write_file(char* path, char* data);
__attribute__((hot)) bool append_file(char* path, char* data);
__attribute__((hot)) bool file_exists(char* path);
__attribute__((hot)) char* Fmt_int_to_str(long long n);
__attribute__((hot)) char* Fmt_int_to_hex(long long n);
__attribute__((hot)) char* Fmt_int_to_bin(long long n);
__attribute__((hot)) char* Fmt_int_to_oct(long long n);
__attribute__((hot)) char* Fmt_float_to_str(double f, long long decimals);
__attribute__((hot)) char* Fmt_bool_to_str(bool b);
__attribute__((hot)) char* Fmt_pad_left(char* s, long long width, long long pad_char);
__attribute__((hot)) char* Fmt_pad_right(char* s, long long width, long long pad_char);
__attribute__((hot)) char* Fmt_zero_pad(long long n, long long width);
__attribute__((hot)) char* Fmt_format(char* template, List_str* args);
__attribute__((hot)) void Console_println(char* s);
__attribute__((hot)) void Console_print(char* s);
__attribute__((hot)) void Console_eprint(char* s);
__attribute__((hot)) void Console_eprintln(char* s);
__attribute__((hot)) char* Console_read_line(char* prompt);
__attribute__((hot)) char* Console_input_line();
__attribute__((hot)) long long Console_read_int(char* prompt);
__attribute__((hot)) double Console_read_float(char* prompt);
__attribute__((hot)) void Console_clear();
__attribute__((hot)) void Console_set_color(long long code);
__attribute__((hot)) void Console_reset_color();
__attribute__((hot)) void Console_print_colored(char* s, long long code);
__attribute__((hot)) void Console_println_colored(char* s, long long code);
__attribute__((hot)) long long Console_BLACK();
__attribute__((hot)) long long Console_RED();
__attribute__((hot)) long long Console_GREEN();
__attribute__((hot)) long long Console_YELLOW();
__attribute__((hot)) long long Console_BLUE();
__attribute__((hot)) long long Console_MAGENTA();
__attribute__((hot)) long long Console_CYAN();
__attribute__((hot)) long long Console_WHITE();
__attribute__((hot)) long long Console_BRIGHT_RED();
__attribute__((hot)) long long Console_BRIGHT_GREEN();
__attribute__((hot)) long long Console_BRIGHT_YELLOW();
__attribute__((hot)) long long Console_BRIGHT_BLUE();
__attribute__((hot)) long long Console_BRIGHT_MAGENTA();
__attribute__((hot)) long long Console_BRIGHT_CYAN();
__attribute__((hot)) long long Console_BRIGHT_WHITE();
__attribute__((malloc,returns_nonnull,hot)) Path* Path_init(char* p);
__attribute__((hot)) char* Path_normalize(Path* self);
__attribute__((hot)) char* Path_join(Path* self, char* other);
__attribute__((hot)) char* Path_dirname(Path* self);
__attribute__((hot)) char* Path_basename(Path* self);
__attribute__((hot)) char* Path_extension(Path* self);
__attribute__((hot)) char* Path_strip_extension(Path* self);
__attribute__((hot)) bool Path_is_absolute(Path* self);
__attribute__((hot)) char* Path_to_str(Path* self);
__attribute__((malloc,returns_nonnull,hot)) Dir* Dir_init(char* path);
__attribute__((hot)) bool Dir_make(Dir* self);
__attribute__((hot)) bool Dir__tr_fn_remove(Dir* self);
__attribute__((hot)) bool Dir_exists(Dir* self);
__attribute__((hot)) List_str* Dir_list(Dir* self);
__attribute__((hot)) long long Dir__tr_fn_count(Dir* self);
__attribute__((hot)) BufReader* BufReader__tr_fn_open(char* path, long long buf_size);
__attribute__((hot)) char* BufReader_read_all(BufReader* self);
__attribute__((hot)) List_str* BufReader_readlines(BufReader* self);
__attribute__((hot)) char* BufReader_readline(BufReader* self);
__attribute__((hot)) void BufReader__tr_fn_close(BufReader* self);
__attribute__((hot)) BufWriter* BufWriter__tr_fn_open(char* path, long long buf_size);
__attribute__((hot)) BufWriter* BufWriter_open_append(char* path, long long buf_size);
__attribute__((hot)) void BufWriter__tr_fn_write(BufWriter* self, char* s);
__attribute__((hot)) void BufWriter_writeln(BufWriter* self, char* s);
__attribute__((hot)) void BufWriter_flush(BufWriter* self);
__attribute__((hot)) void BufWriter__tr_fn_close(BufWriter* self);
__attribute__((hot)) bool IOEvent_readable(IOEvent* self);
__attribute__((hot)) bool IOEvent_writable(IOEvent* self);
__attribute__((hot)) bool IOEvent_error(IOEvent* self);
__attribute__((hot)) bool IOEvent_hangup(IOEvent* self);
__attribute__((hot)) long long IOPoll_POLLIN();
__attribute__((hot)) long long IOPoll_POLLOUT();
__attribute__((hot)) long long IOPoll_POLLERR();
__attribute__((hot)) long long IOPoll_POLLHUP();
__attribute__((hot)) IOPoll* IOPoll__tr_fn_new();
__attribute__((hot)) bool IOPoll_add(IOPoll* self, long long fd, long long events, long long userdata);
__attribute__((hot)) bool IOPoll_modify(IOPoll* self, long long fd, long long events, long long userdata);
__attribute__((hot)) bool IOPoll__tr_fn_remove(IOPoll* self, long long fd);
__attribute__((hot)) List_ptr* IOPoll_wait(IOPoll* self, long long timeout_ms);
__attribute__((hot)) void IOPoll_destroy(IOPoll* self);
__attribute__((hot)) EventLoop* EventLoop__tr_fn_new();
__attribute__((hot)) bool EventLoop_add_fd(EventLoop* self, long long fd, long long events, long long userdata);
__attribute__((hot)) bool EventLoop_modify_fd(EventLoop* self, long long fd, long long events, long long userdata);
__attribute__((hot)) bool EventLoop_remove_fd(EventLoop* self, long long fd);
__attribute__((hot)) List_ptr* EventLoop_poll_once(EventLoop* self, long long timeout_ms);
__attribute__((hot)) long long EventLoop_run(EventLoop* self, long long max_iter, long long timeout_ms);
__attribute__((hot)) void EventLoop_stop(EventLoop* self);
__attribute__((hot)) bool EventLoop_is_running(EventLoop* self);
__attribute__((hot)) long long EventLoop_elapsed_ms(EventLoop* self);
__attribute__((hot)) void EventLoop_destroy(EventLoop* self);
__attribute__((malloc,returns_nonnull,hot)) TextDocument* TextDocument_init(char* uri, char* language, long long version, char* text);
__attribute__((hot)) void TextDocument_update(TextDocument* self, long long version, char* new_text);
__attribute__((hot)) long long TextDocument_line_count(TextDocument* self);
__attribute__((hot)) char* TextDocument_get_line(TextDocument* self, long long n);
__attribute__((hot)) char* TextDocument_word_at(TextDocument* self, long long line, long long character);
__attribute__((hot)) long long TextDocument_offset_of(TextDocument* self, long long line, long long character);
__attribute__((malloc,returns_nonnull,hot)) DocumentStore* DocumentStore_init();
__attribute__((hot)) void DocumentStore__tr_fn_open(DocumentStore* self, char* uri, char* language, long long version, char* text);
__attribute__((hot)) void DocumentStore_change(DocumentStore* self, char* uri, long long version, char* new_text);
__attribute__((hot)) void DocumentStore__tr_fn_close(DocumentStore* self, char* uri);
__attribute__((hot)) TextDocument* DocumentStore_get(DocumentStore* self, char* uri);
__attribute__((hot)) bool DocumentStore_has(DocumentStore* self, char* uri);
__attribute__((hot)) long long DocumentStore__find(DocumentStore* self, char* uri);
__attribute__((hot)) char* uri_to_path(char* uri);
__attribute__((hot)) char* path_to_uri(char* path);
__attribute__((hot)) bool _has_drive_letter(char* s);
__attribute__((hot)) List_str* _split_lines(char* text);
__attribute__((hot)) bool _is_ident_char(long long c);
__attribute__((malloc,returns_nonnull,hot)) Diagnostic* Diagnostic_init(long long line, long long col, long long severity, char* message, char* code);
__attribute__((malloc,returns_nonnull,hot)) AnalysisResult* AnalysisResult_init();
__attribute__((malloc,returns_nonnull,hot)) Analyzer* Analyzer_init(char* compiler_path);
__attribute__((hot)) AnalysisResult* Analyzer_analyze(Analyzer* self, TextDocument* doc);
__attribute__((hot)) void _parse_output(char* output, AnalysisResult* result);
__attribute__((hot)) void _extract_symbols(TextDocument* doc, AnalysisResult* result);
__attribute__((hot)) char* _extract_ident(char* s, long long start);
__attribute__((hot)) char* _extract_return_type(char* line);
__attribute__((hot)) long long _find_block_end(TextDocument* doc, long long start);
__attribute__((hot)) char* _find_compiler();
__attribute__((hot)) List_str* _list_dirs(char* path);
__attribute__((hot)) char* _tmp_path(char* uri);
__attribute__((hot)) char* _str_hash(char* s);
__attribute__((hot)) char* _hex_nibble(long long n);
__attribute__((hot)) char* _capture(char* cmd);
__attribute__((hot)) JsonVal lsp_position(long long line, long long character);
__attribute__((hot)) JsonVal lsp_range(long long start_line, long long start_char, long long end_line, long long end_char);
__attribute__((hot)) JsonVal lsp_range_line(long long line);
__attribute__((hot)) JsonVal lsp_location(char* uri, long long start_line, long long start_char, long long end_line, long long end_char);
__attribute__((hot)) JsonVal lsp_diagnostic(long long start_line, long long start_char, long long end_line, long long end_char, long long severity, char* message, char* code);
__attribute__((hot)) JsonVal lsp_publish_diagnostics(char* uri, List_JsonVal* diagnostics);
__attribute__((hot)) JsonVal lsp_completion_item(char* label, long long kind, char* detail, char* insert_text);
__attribute__((hot)) JsonVal lsp_completion_list(List_JsonVal* items, bool is_incomplete);
__attribute__((hot)) JsonVal lsp_hover(char* contents, long long start_line, long long start_char, long long end_line, long long end_char);
__attribute__((hot)) JsonVal lsp_document_symbol(char* name, long long kind, long long line, long long end_line, char* detail);
__attribute__((hot)) JsonVal lsp_text_edit(long long start_line, long long start_char, long long end_line, long long end_char, char* new_text);
__attribute__((hot)) long long STT_NAMESPACE();
__attribute__((hot)) long long STT_TYPE();
__attribute__((hot)) long long STT_CLASS();
__attribute__((hot)) long long STT_ENUM();
__attribute__((hot)) long long STT_INTERFACE();
__attribute__((hot)) long long STT_STRUCT();
__attribute__((hot)) long long STT_FUNCTION();
__attribute__((hot)) long long STT_METHOD();
__attribute__((hot)) long long STT_PROPERTY();
__attribute__((hot)) long long STT_VARIABLE();
__attribute__((hot)) long long STT_PARAMETER();
__attribute__((hot)) long long STT_KEYWORD();
__attribute__((hot)) long long STT_COMMENT();
__attribute__((hot)) long long STT_STRING();
__attribute__((hot)) long long STT_NUMBER();
__attribute__((hot)) long long STT_OPERATOR();
__attribute__((hot)) long long pos_line(JsonVal p);
__attribute__((hot)) long long pos_char(JsonVal p);
__attribute__((hot)) JsonVal provide_completions(TextDocument* doc, long long line, long long character);
__attribute__((hot)) void _add_keywords(List_JsonVal* items, char* prefix);
__attribute__((hot)) void _add_builtin_types(List_JsonVal* items, char* prefix);
__attribute__((hot)) void _add_method_completions(List_JsonVal* items, char* type_name, char* prefix);
__attribute__((hot)) void _add_str_methods(List_JsonVal* items, List_str* methods, char* prefix, char* detail);
__attribute__((hot)) void _add_doc_identifiers(TextDocument* doc, List_JsonVal* items, char* prefix);
__attribute__((hot)) void _collect_idents(char* line, List_str* seen, char* prefix);
__attribute__((hot)) char* _get_prefix(TextDocument* doc, long long line, long long character);
__attribute__((hot)) bool _is_after_dot(TextDocument* doc, long long line, long long character);
__attribute__((hot)) char* _infer_receiver_type(TextDocument* doc, long long line, long long character);
__attribute__((hot)) char* _extract_ident_from(char* s, long long start);
__attribute__((hot)) bool _is_keyword_prefix(char* s);
__attribute__((hot)) bool _is_in(List_str* v, char* s);
__attribute__((hot)) bool _is_keyword(char* s);
__attribute__((hot)) bool _is_alpha(long long c);
__attribute__((hot)) bool _is_digit(long long c);
__attribute__((hot)) JsonVal provide_hover(TextDocument* doc, long long line, long long character);
__attribute__((hot)) char* _error_code_at(char* line, long long character);
__attribute__((hot)) char* _error_code_doc(char* code);
__attribute__((hot)) char* _builtin_type_info(char* word);
__attribute__((hot)) char* _keyword_info(char* word);
__attribute__((hot)) char* _find_decl(TextDocument* doc, char* word, long long from_line);
__attribute__((hot)) char* _extract_ret(char* line);
__attribute__((hot)) char* _extract_params(char* line);
__attribute__((hot)) JsonVal provide_definition(DocumentStore* store, TextDocument* doc, long long line, long long character);
__attribute__((hot)) JsonVal _search_doc(TextDocument* doc, char* word, long long skip_line);
__attribute__((hot)) bool _is_decl_of(char* line, char* keyword, char* name);
__attribute__((hot)) List_str* _collect_imports(TextDocument* doc);
__attribute__((hot)) char* _extract_import_path(char* line);
__attribute__((hot)) bool _is_builtin(char* word);
__attribute__((hot)) bool jv_is_null_def(JsonVal v);
__attribute__((hot)) JsonVal provide_document_symbols(List_ptr* symbols);
__attribute__((hot)) JsonVal provide_workspace_symbols(DocumentStore* store, char* query);
__attribute__((hot)) bool _is_top_decl(char* line, char* keyword, char* query);
__attribute__((hot)) char* _ident_after(char* line, char* keyword);
__attribute__((hot)) List_str* _tauraro_keywords();
__attribute__((hot)) bool _is_kw(char* word, List_str* kws);
__attribute__((hot)) JsonVal provide_semantic_tokens(TextDocument* doc);
__attribute__((hot)) void _push_token(List_i64* data, long long line, long long start, long long length, long long tok_type, long long modifiers, long long prev_line, long long prev_start);
__attribute__((hot)) bool _is_type_name(char* word);
__attribute__((hot)) bool _is_upper_start(char* word);
__attribute__((hot)) bool _is_alpha_c(long long c);
__attribute__((hot)) bool _is_digit_c(long long c);
__attribute__((malloc,returns_nonnull,hot)) LspServer* LspServer_init();
__attribute__((hot)) bool LspServer_handle(LspServer* self, JsonVal msg);
__attribute__((hot)) bool LspServer_on_initialize(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_did_open(LspServer* self, JsonVal params);
__attribute__((hot)) bool LspServer_on_did_change(LspServer* self, JsonVal params);
__attribute__((hot)) bool LspServer_on_did_close(LspServer* self, JsonVal params);
__attribute__((hot)) bool LspServer_on_did_save(LspServer* self, JsonVal params);
__attribute__((hot)) void LspServer_analyze_and_publish(LspServer* self, char* uri);
__attribute__((hot)) bool LspServer_on_hover(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_completion(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_definition(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_document_symbols(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_workspace_symbols(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) bool LspServer_on_semantic_tokens(LspServer* self, JsonVal id, JsonVal params);
__attribute__((hot)) void LspServer_log(LspServer* self, char* msg);
__attribute__((hot)) JsonVal _str_arr_v(List_str* v);
__attribute__((hot)) JsonVal _semantic_tokens_legend();
__attribute__((hot)) void _print_help();



/* === Module-prefixed typedef aliases (auto-generated) === */
/* Maps module-qualified C names to short-name types in tauraro_types.h */

#ifndef TAURARO_RT_NO_STRINGBUILDER
typedef struct core_string_StringObj core_string_StringObj;
typedef core_string_StringObj StringObj;
typedef struct core_string_StringBuilder core_string_StringBuilder;
typedef core_string_StringBuilder StringBuilder;
#endif

typedef JsonVal json_JsonVal;
struct core_vec_Vec_json_JsonVal { json_JsonVal* data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JsonVal core_vec_Vec_json_JsonVal;
struct core_vec_Vec_json_JsonVal_ptr { json_JsonVal** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JsonVal_ptr core_vec_Vec_json_JsonVal_ptr;
__attribute__((hot)) json_JsonVal* core_alloc_alloc_json_JsonVal(long long count);
__attribute__((hot)) json_JsonVal* core_alloc_resize_json_JsonVal(json_JsonVal* ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JsonVal(json_JsonVal* ptr);
__attribute__((hot)) json_JsonVal** core_alloc_alloc_json_JsonVal_ptr(long long count);
__attribute__((hot)) json_JsonVal** core_alloc_resize_json_JsonVal_ptr(json_JsonVal** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JsonVal_ptr(json_JsonVal** ptr);

typedef JsonParser json_JsonParser;
struct core_vec_Vec_json_JsonParser { json_JsonParser** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JsonParser core_vec_Vec_json_JsonParser;
struct core_vec_Vec_json_JsonParser_ptr { json_JsonParser*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JsonParser_ptr core_vec_Vec_json_JsonParser_ptr;
struct core_map_MapNode_str_json_JsonParser { char* key; json_JsonParser* value; struct core_map_MapNode_str_json_JsonParser* next; };
typedef struct core_map_MapNode_str_json_JsonParser core_map_MapNode_str_json_JsonParser;
struct core_map_Map_str_json_JsonParser { core_map_MapNode_str_json_JsonParser** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_json_JsonParser core_map_Map_str_json_JsonParser;
__attribute__((hot)) json_JsonParser** core_alloc_alloc_json_JsonParser(long long count);
__attribute__((hot)) json_JsonParser** core_alloc_resize_json_JsonParser(json_JsonParser** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JsonParser(json_JsonParser** ptr);
__attribute__((hot)) json_JsonParser*** core_alloc_alloc_json_JsonParser_ptr(long long count);
__attribute__((hot)) json_JsonParser*** core_alloc_resize_json_JsonParser_ptr(json_JsonParser*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JsonParser_ptr(json_JsonParser*** ptr);
__attribute__((hot)) core_map_MapNode_str_json_JsonParser** core_alloc_alloc_core_map_MapNode_str_json_JsonParser(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_json_JsonParser(core_map_MapNode_str_json_JsonParser** ptr);

typedef JObjBuilder json_JObjBuilder;
struct core_vec_Vec_json_JObjBuilder { json_JObjBuilder** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JObjBuilder core_vec_Vec_json_JObjBuilder;
struct core_vec_Vec_json_JObjBuilder_ptr { json_JObjBuilder*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JObjBuilder_ptr core_vec_Vec_json_JObjBuilder_ptr;
struct core_map_MapNode_str_json_JObjBuilder { char* key; json_JObjBuilder* value; struct core_map_MapNode_str_json_JObjBuilder* next; };
typedef struct core_map_MapNode_str_json_JObjBuilder core_map_MapNode_str_json_JObjBuilder;
struct core_map_Map_str_json_JObjBuilder { core_map_MapNode_str_json_JObjBuilder** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_json_JObjBuilder core_map_Map_str_json_JObjBuilder;
__attribute__((hot)) json_JObjBuilder** core_alloc_alloc_json_JObjBuilder(long long count);
__attribute__((hot)) json_JObjBuilder** core_alloc_resize_json_JObjBuilder(json_JObjBuilder** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JObjBuilder(json_JObjBuilder** ptr);
__attribute__((hot)) json_JObjBuilder*** core_alloc_alloc_json_JObjBuilder_ptr(long long count);
__attribute__((hot)) json_JObjBuilder*** core_alloc_resize_json_JObjBuilder_ptr(json_JObjBuilder*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JObjBuilder_ptr(json_JObjBuilder*** ptr);
__attribute__((hot)) core_map_MapNode_str_json_JObjBuilder** core_alloc_alloc_core_map_MapNode_str_json_JObjBuilder(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_json_JObjBuilder(core_map_MapNode_str_json_JObjBuilder** ptr);

typedef JArrBuilder json_JArrBuilder;
struct core_vec_Vec_json_JArrBuilder { json_JArrBuilder** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JArrBuilder core_vec_Vec_json_JArrBuilder;
struct core_vec_Vec_json_JArrBuilder_ptr { json_JArrBuilder*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_json_JArrBuilder_ptr core_vec_Vec_json_JArrBuilder_ptr;
struct core_map_MapNode_str_json_JArrBuilder { char* key; json_JArrBuilder* value; struct core_map_MapNode_str_json_JArrBuilder* next; };
typedef struct core_map_MapNode_str_json_JArrBuilder core_map_MapNode_str_json_JArrBuilder;
struct core_map_Map_str_json_JArrBuilder { core_map_MapNode_str_json_JArrBuilder** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_json_JArrBuilder core_map_Map_str_json_JArrBuilder;
__attribute__((hot)) json_JArrBuilder** core_alloc_alloc_json_JArrBuilder(long long count);
__attribute__((hot)) json_JArrBuilder** core_alloc_resize_json_JArrBuilder(json_JArrBuilder** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JArrBuilder(json_JArrBuilder** ptr);
__attribute__((hot)) json_JArrBuilder*** core_alloc_alloc_json_JArrBuilder_ptr(long long count);
__attribute__((hot)) json_JArrBuilder*** core_alloc_resize_json_JArrBuilder_ptr(json_JArrBuilder*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_json_JArrBuilder_ptr(json_JArrBuilder*** ptr);
__attribute__((hot)) core_map_MapNode_str_json_JArrBuilder** core_alloc_alloc_core_map_MapNode_str_json_JArrBuilder(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_json_JArrBuilder(core_map_MapNode_str_json_JArrBuilder** ptr);

typedef StringObj std_core_string_StringObj;
struct core_vec_Vec_std_core_string_StringObj { std_core_string_StringObj** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_core_string_StringObj core_vec_Vec_std_core_string_StringObj;
struct core_vec_Vec_std_core_string_StringObj_ptr { std_core_string_StringObj*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_core_string_StringObj_ptr core_vec_Vec_std_core_string_StringObj_ptr;
struct core_map_MapNode_str_std_core_string_StringObj { char* key; std_core_string_StringObj* value; struct core_map_MapNode_str_std_core_string_StringObj* next; };
typedef struct core_map_MapNode_str_std_core_string_StringObj core_map_MapNode_str_std_core_string_StringObj;
struct core_map_Map_str_std_core_string_StringObj { core_map_MapNode_str_std_core_string_StringObj** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_core_string_StringObj core_map_Map_str_std_core_string_StringObj;
__attribute__((hot)) std_core_string_StringObj** core_alloc_alloc_std_core_string_StringObj(long long count);
__attribute__((hot)) std_core_string_StringObj** core_alloc_resize_std_core_string_StringObj(std_core_string_StringObj** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_core_string_StringObj(std_core_string_StringObj** ptr);
__attribute__((hot)) std_core_string_StringObj*** core_alloc_alloc_std_core_string_StringObj_ptr(long long count);
__attribute__((hot)) std_core_string_StringObj*** core_alloc_resize_std_core_string_StringObj_ptr(std_core_string_StringObj*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_core_string_StringObj_ptr(std_core_string_StringObj*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_core_string_StringObj** core_alloc_alloc_core_map_MapNode_str_std_core_string_StringObj(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_core_string_StringObj(core_map_MapNode_str_std_core_string_StringObj** ptr);

typedef StringBuilder std_core_string_StringBuilder;
struct core_vec_Vec_std_core_string_StringBuilder { std_core_string_StringBuilder** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_core_string_StringBuilder core_vec_Vec_std_core_string_StringBuilder;
struct core_vec_Vec_std_core_string_StringBuilder_ptr { std_core_string_StringBuilder*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_core_string_StringBuilder_ptr core_vec_Vec_std_core_string_StringBuilder_ptr;
struct core_map_MapNode_str_std_core_string_StringBuilder { char* key; std_core_string_StringBuilder* value; struct core_map_MapNode_str_std_core_string_StringBuilder* next; };
typedef struct core_map_MapNode_str_std_core_string_StringBuilder core_map_MapNode_str_std_core_string_StringBuilder;
struct core_map_Map_str_std_core_string_StringBuilder { core_map_MapNode_str_std_core_string_StringBuilder** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_core_string_StringBuilder core_map_Map_str_std_core_string_StringBuilder;
__attribute__((hot)) std_core_string_StringBuilder** core_alloc_alloc_std_core_string_StringBuilder(long long count);
__attribute__((hot)) std_core_string_StringBuilder** core_alloc_resize_std_core_string_StringBuilder(std_core_string_StringBuilder** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_core_string_StringBuilder(std_core_string_StringBuilder** ptr);
__attribute__((hot)) std_core_string_StringBuilder*** core_alloc_alloc_std_core_string_StringBuilder_ptr(long long count);
__attribute__((hot)) std_core_string_StringBuilder*** core_alloc_resize_std_core_string_StringBuilder_ptr(std_core_string_StringBuilder*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_core_string_StringBuilder_ptr(std_core_string_StringBuilder*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_core_string_StringBuilder** core_alloc_alloc_core_map_MapNode_str_std_core_string_StringBuilder(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_core_string_StringBuilder(core_map_MapNode_str_std_core_string_StringBuilder** ptr);

typedef Str std_string_str_Str;
struct core_vec_Vec_std_string_str_Str { std_string_str_Str** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_string_str_Str core_vec_Vec_std_string_str_Str;
struct core_vec_Vec_std_string_str_Str_ptr { std_string_str_Str*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_string_str_Str_ptr core_vec_Vec_std_string_str_Str_ptr;
struct core_map_MapNode_str_std_string_str_Str { char* key; std_string_str_Str* value; struct core_map_MapNode_str_std_string_str_Str* next; };
typedef struct core_map_MapNode_str_std_string_str_Str core_map_MapNode_str_std_string_str_Str;
struct core_map_Map_str_std_string_str_Str { core_map_MapNode_str_std_string_str_Str** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_string_str_Str core_map_Map_str_std_string_str_Str;
__attribute__((hot)) std_string_str_Str** core_alloc_alloc_std_string_str_Str(long long count);
__attribute__((hot)) std_string_str_Str** core_alloc_resize_std_string_str_Str(std_string_str_Str** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_string_str_Str(std_string_str_Str** ptr);
__attribute__((hot)) std_string_str_Str*** core_alloc_alloc_std_string_str_Str_ptr(long long count);
__attribute__((hot)) std_string_str_Str*** core_alloc_resize_std_string_str_Str_ptr(std_string_str_Str*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_string_str_Str_ptr(std_string_str_Str*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_string_str_Str** core_alloc_alloc_core_map_MapNode_str_std_string_str_Str(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_string_str_Str(core_map_MapNode_str_std_string_str_Str** ptr);

typedef File std_io_file_File;
struct core_vec_Vec_std_io_file_File { std_io_file_File** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_file_File core_vec_Vec_std_io_file_File;
struct core_vec_Vec_std_io_file_File_ptr { std_io_file_File*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_file_File_ptr core_vec_Vec_std_io_file_File_ptr;
struct core_map_MapNode_str_std_io_file_File { char* key; std_io_file_File* value; struct core_map_MapNode_str_std_io_file_File* next; };
typedef struct core_map_MapNode_str_std_io_file_File core_map_MapNode_str_std_io_file_File;
struct core_map_Map_str_std_io_file_File { core_map_MapNode_str_std_io_file_File** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_file_File core_map_Map_str_std_io_file_File;
__attribute__((hot)) std_io_file_File** core_alloc_alloc_std_io_file_File(long long count);
__attribute__((hot)) std_io_file_File** core_alloc_resize_std_io_file_File(std_io_file_File** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_file_File(std_io_file_File** ptr);
__attribute__((hot)) std_io_file_File*** core_alloc_alloc_std_io_file_File_ptr(long long count);
__attribute__((hot)) std_io_file_File*** core_alloc_resize_std_io_file_File_ptr(std_io_file_File*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_file_File_ptr(std_io_file_File*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_file_File** core_alloc_alloc_core_map_MapNode_str_std_io_file_File(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_file_File(core_map_MapNode_str_std_io_file_File** ptr);

typedef Fmt std_string_fmt_Fmt;
struct core_vec_Vec_std_string_fmt_Fmt { std_string_fmt_Fmt** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_string_fmt_Fmt core_vec_Vec_std_string_fmt_Fmt;
struct core_vec_Vec_std_string_fmt_Fmt_ptr { std_string_fmt_Fmt*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_string_fmt_Fmt_ptr core_vec_Vec_std_string_fmt_Fmt_ptr;
struct core_map_MapNode_str_std_string_fmt_Fmt { char* key; std_string_fmt_Fmt* value; struct core_map_MapNode_str_std_string_fmt_Fmt* next; };
typedef struct core_map_MapNode_str_std_string_fmt_Fmt core_map_MapNode_str_std_string_fmt_Fmt;
struct core_map_Map_str_std_string_fmt_Fmt { core_map_MapNode_str_std_string_fmt_Fmt** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_string_fmt_Fmt core_map_Map_str_std_string_fmt_Fmt;
__attribute__((hot)) std_string_fmt_Fmt** core_alloc_alloc_std_string_fmt_Fmt(long long count);
__attribute__((hot)) std_string_fmt_Fmt** core_alloc_resize_std_string_fmt_Fmt(std_string_fmt_Fmt** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_string_fmt_Fmt(std_string_fmt_Fmt** ptr);
__attribute__((hot)) std_string_fmt_Fmt*** core_alloc_alloc_std_string_fmt_Fmt_ptr(long long count);
__attribute__((hot)) std_string_fmt_Fmt*** core_alloc_resize_std_string_fmt_Fmt_ptr(std_string_fmt_Fmt*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_string_fmt_Fmt_ptr(std_string_fmt_Fmt*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_string_fmt_Fmt** core_alloc_alloc_core_map_MapNode_str_std_string_fmt_Fmt(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_string_fmt_Fmt(core_map_MapNode_str_std_string_fmt_Fmt** ptr);

typedef Console std_io_console_Console;
struct core_vec_Vec_std_io_console_Console { std_io_console_Console** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_console_Console core_vec_Vec_std_io_console_Console;
struct core_vec_Vec_std_io_console_Console_ptr { std_io_console_Console*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_console_Console_ptr core_vec_Vec_std_io_console_Console_ptr;
struct core_map_MapNode_str_std_io_console_Console { char* key; std_io_console_Console* value; struct core_map_MapNode_str_std_io_console_Console* next; };
typedef struct core_map_MapNode_str_std_io_console_Console core_map_MapNode_str_std_io_console_Console;
struct core_map_Map_str_std_io_console_Console { core_map_MapNode_str_std_io_console_Console** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_console_Console core_map_Map_str_std_io_console_Console;
__attribute__((hot)) std_io_console_Console** core_alloc_alloc_std_io_console_Console(long long count);
__attribute__((hot)) std_io_console_Console** core_alloc_resize_std_io_console_Console(std_io_console_Console** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_console_Console(std_io_console_Console** ptr);
__attribute__((hot)) std_io_console_Console*** core_alloc_alloc_std_io_console_Console_ptr(long long count);
__attribute__((hot)) std_io_console_Console*** core_alloc_resize_std_io_console_Console_ptr(std_io_console_Console*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_console_Console_ptr(std_io_console_Console*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_console_Console** core_alloc_alloc_core_map_MapNode_str_std_io_console_Console(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_console_Console(core_map_MapNode_str_std_io_console_Console** ptr);

typedef Path std_io_path_Path;
struct core_vec_Vec_std_io_path_Path { std_io_path_Path** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_path_Path core_vec_Vec_std_io_path_Path;
struct core_vec_Vec_std_io_path_Path_ptr { std_io_path_Path*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_path_Path_ptr core_vec_Vec_std_io_path_Path_ptr;
struct core_map_MapNode_str_std_io_path_Path { char* key; std_io_path_Path* value; struct core_map_MapNode_str_std_io_path_Path* next; };
typedef struct core_map_MapNode_str_std_io_path_Path core_map_MapNode_str_std_io_path_Path;
struct core_map_Map_str_std_io_path_Path { core_map_MapNode_str_std_io_path_Path** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_path_Path core_map_Map_str_std_io_path_Path;
__attribute__((hot)) std_io_path_Path** core_alloc_alloc_std_io_path_Path(long long count);
__attribute__((hot)) std_io_path_Path** core_alloc_resize_std_io_path_Path(std_io_path_Path** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_path_Path(std_io_path_Path** ptr);
__attribute__((hot)) std_io_path_Path*** core_alloc_alloc_std_io_path_Path_ptr(long long count);
__attribute__((hot)) std_io_path_Path*** core_alloc_resize_std_io_path_Path_ptr(std_io_path_Path*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_path_Path_ptr(std_io_path_Path*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_path_Path** core_alloc_alloc_core_map_MapNode_str_std_io_path_Path(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_path_Path(core_map_MapNode_str_std_io_path_Path** ptr);

typedef Dir std_io_dir_Dir;
struct core_vec_Vec_std_io_dir_Dir { std_io_dir_Dir** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_dir_Dir core_vec_Vec_std_io_dir_Dir;
struct core_vec_Vec_std_io_dir_Dir_ptr { std_io_dir_Dir*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_dir_Dir_ptr core_vec_Vec_std_io_dir_Dir_ptr;
struct core_map_MapNode_str_std_io_dir_Dir { char* key; std_io_dir_Dir* value; struct core_map_MapNode_str_std_io_dir_Dir* next; };
typedef struct core_map_MapNode_str_std_io_dir_Dir core_map_MapNode_str_std_io_dir_Dir;
struct core_map_Map_str_std_io_dir_Dir { core_map_MapNode_str_std_io_dir_Dir** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_dir_Dir core_map_Map_str_std_io_dir_Dir;
__attribute__((hot)) std_io_dir_Dir** core_alloc_alloc_std_io_dir_Dir(long long count);
__attribute__((hot)) std_io_dir_Dir** core_alloc_resize_std_io_dir_Dir(std_io_dir_Dir** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_dir_Dir(std_io_dir_Dir** ptr);
__attribute__((hot)) std_io_dir_Dir*** core_alloc_alloc_std_io_dir_Dir_ptr(long long count);
__attribute__((hot)) std_io_dir_Dir*** core_alloc_resize_std_io_dir_Dir_ptr(std_io_dir_Dir*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_dir_Dir_ptr(std_io_dir_Dir*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_dir_Dir** core_alloc_alloc_core_map_MapNode_str_std_io_dir_Dir(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_dir_Dir(core_map_MapNode_str_std_io_dir_Dir** ptr);

typedef BufReader std_io_bufio_BufReader;
struct core_vec_Vec_std_io_bufio_BufReader { std_io_bufio_BufReader** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_bufio_BufReader core_vec_Vec_std_io_bufio_BufReader;
struct core_vec_Vec_std_io_bufio_BufReader_ptr { std_io_bufio_BufReader*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_bufio_BufReader_ptr core_vec_Vec_std_io_bufio_BufReader_ptr;
struct core_map_MapNode_str_std_io_bufio_BufReader { char* key; std_io_bufio_BufReader* value; struct core_map_MapNode_str_std_io_bufio_BufReader* next; };
typedef struct core_map_MapNode_str_std_io_bufio_BufReader core_map_MapNode_str_std_io_bufio_BufReader;
struct core_map_Map_str_std_io_bufio_BufReader { core_map_MapNode_str_std_io_bufio_BufReader** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_bufio_BufReader core_map_Map_str_std_io_bufio_BufReader;
__attribute__((hot)) std_io_bufio_BufReader** core_alloc_alloc_std_io_bufio_BufReader(long long count);
__attribute__((hot)) std_io_bufio_BufReader** core_alloc_resize_std_io_bufio_BufReader(std_io_bufio_BufReader** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_bufio_BufReader(std_io_bufio_BufReader** ptr);
__attribute__((hot)) std_io_bufio_BufReader*** core_alloc_alloc_std_io_bufio_BufReader_ptr(long long count);
__attribute__((hot)) std_io_bufio_BufReader*** core_alloc_resize_std_io_bufio_BufReader_ptr(std_io_bufio_BufReader*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_bufio_BufReader_ptr(std_io_bufio_BufReader*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_bufio_BufReader** core_alloc_alloc_core_map_MapNode_str_std_io_bufio_BufReader(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_bufio_BufReader(core_map_MapNode_str_std_io_bufio_BufReader** ptr);

typedef BufWriter std_io_bufio_BufWriter;
struct core_vec_Vec_std_io_bufio_BufWriter { std_io_bufio_BufWriter** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_bufio_BufWriter core_vec_Vec_std_io_bufio_BufWriter;
struct core_vec_Vec_std_io_bufio_BufWriter_ptr { std_io_bufio_BufWriter*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_bufio_BufWriter_ptr core_vec_Vec_std_io_bufio_BufWriter_ptr;
struct core_map_MapNode_str_std_io_bufio_BufWriter { char* key; std_io_bufio_BufWriter* value; struct core_map_MapNode_str_std_io_bufio_BufWriter* next; };
typedef struct core_map_MapNode_str_std_io_bufio_BufWriter core_map_MapNode_str_std_io_bufio_BufWriter;
struct core_map_Map_str_std_io_bufio_BufWriter { core_map_MapNode_str_std_io_bufio_BufWriter** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_bufio_BufWriter core_map_Map_str_std_io_bufio_BufWriter;
__attribute__((hot)) std_io_bufio_BufWriter** core_alloc_alloc_std_io_bufio_BufWriter(long long count);
__attribute__((hot)) std_io_bufio_BufWriter** core_alloc_resize_std_io_bufio_BufWriter(std_io_bufio_BufWriter** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_bufio_BufWriter(std_io_bufio_BufWriter** ptr);
__attribute__((hot)) std_io_bufio_BufWriter*** core_alloc_alloc_std_io_bufio_BufWriter_ptr(long long count);
__attribute__((hot)) std_io_bufio_BufWriter*** core_alloc_resize_std_io_bufio_BufWriter_ptr(std_io_bufio_BufWriter*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_bufio_BufWriter_ptr(std_io_bufio_BufWriter*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_bufio_BufWriter** core_alloc_alloc_core_map_MapNode_str_std_io_bufio_BufWriter(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_bufio_BufWriter(core_map_MapNode_str_std_io_bufio_BufWriter** ptr);

typedef IOEvent std_io_poll_IOEvent;
struct core_vec_Vec_std_io_poll_IOEvent { std_io_poll_IOEvent** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_poll_IOEvent core_vec_Vec_std_io_poll_IOEvent;
struct core_vec_Vec_std_io_poll_IOEvent_ptr { std_io_poll_IOEvent*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_poll_IOEvent_ptr core_vec_Vec_std_io_poll_IOEvent_ptr;
struct core_map_MapNode_str_std_io_poll_IOEvent { char* key; std_io_poll_IOEvent* value; struct core_map_MapNode_str_std_io_poll_IOEvent* next; };
typedef struct core_map_MapNode_str_std_io_poll_IOEvent core_map_MapNode_str_std_io_poll_IOEvent;
struct core_map_Map_str_std_io_poll_IOEvent { core_map_MapNode_str_std_io_poll_IOEvent** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_poll_IOEvent core_map_Map_str_std_io_poll_IOEvent;
__attribute__((hot)) std_io_poll_IOEvent** core_alloc_alloc_std_io_poll_IOEvent(long long count);
__attribute__((hot)) std_io_poll_IOEvent** core_alloc_resize_std_io_poll_IOEvent(std_io_poll_IOEvent** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_poll_IOEvent(std_io_poll_IOEvent** ptr);
__attribute__((hot)) std_io_poll_IOEvent*** core_alloc_alloc_std_io_poll_IOEvent_ptr(long long count);
__attribute__((hot)) std_io_poll_IOEvent*** core_alloc_resize_std_io_poll_IOEvent_ptr(std_io_poll_IOEvent*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_poll_IOEvent_ptr(std_io_poll_IOEvent*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_poll_IOEvent** core_alloc_alloc_core_map_MapNode_str_std_io_poll_IOEvent(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_poll_IOEvent(core_map_MapNode_str_std_io_poll_IOEvent** ptr);

typedef IOPoll std_io_poll_IOPoll;
struct core_vec_Vec_std_io_poll_IOPoll { std_io_poll_IOPoll** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_poll_IOPoll core_vec_Vec_std_io_poll_IOPoll;
struct core_vec_Vec_std_io_poll_IOPoll_ptr { std_io_poll_IOPoll*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_poll_IOPoll_ptr core_vec_Vec_std_io_poll_IOPoll_ptr;
struct core_map_MapNode_str_std_io_poll_IOPoll { char* key; std_io_poll_IOPoll* value; struct core_map_MapNode_str_std_io_poll_IOPoll* next; };
typedef struct core_map_MapNode_str_std_io_poll_IOPoll core_map_MapNode_str_std_io_poll_IOPoll;
struct core_map_Map_str_std_io_poll_IOPoll { core_map_MapNode_str_std_io_poll_IOPoll** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_poll_IOPoll core_map_Map_str_std_io_poll_IOPoll;
__attribute__((hot)) std_io_poll_IOPoll** core_alloc_alloc_std_io_poll_IOPoll(long long count);
__attribute__((hot)) std_io_poll_IOPoll** core_alloc_resize_std_io_poll_IOPoll(std_io_poll_IOPoll** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_poll_IOPoll(std_io_poll_IOPoll** ptr);
__attribute__((hot)) std_io_poll_IOPoll*** core_alloc_alloc_std_io_poll_IOPoll_ptr(long long count);
__attribute__((hot)) std_io_poll_IOPoll*** core_alloc_resize_std_io_poll_IOPoll_ptr(std_io_poll_IOPoll*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_poll_IOPoll_ptr(std_io_poll_IOPoll*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_poll_IOPoll** core_alloc_alloc_core_map_MapNode_str_std_io_poll_IOPoll(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_poll_IOPoll(core_map_MapNode_str_std_io_poll_IOPoll** ptr);

typedef EventLoop std_io_event_loop_EventLoop;
struct core_vec_Vec_std_io_event_loop_EventLoop { std_io_event_loop_EventLoop** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_event_loop_EventLoop core_vec_Vec_std_io_event_loop_EventLoop;
struct core_vec_Vec_std_io_event_loop_EventLoop_ptr { std_io_event_loop_EventLoop*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_std_io_event_loop_EventLoop_ptr core_vec_Vec_std_io_event_loop_EventLoop_ptr;
struct core_map_MapNode_str_std_io_event_loop_EventLoop { char* key; std_io_event_loop_EventLoop* value; struct core_map_MapNode_str_std_io_event_loop_EventLoop* next; };
typedef struct core_map_MapNode_str_std_io_event_loop_EventLoop core_map_MapNode_str_std_io_event_loop_EventLoop;
struct core_map_Map_str_std_io_event_loop_EventLoop { core_map_MapNode_str_std_io_event_loop_EventLoop** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_std_io_event_loop_EventLoop core_map_Map_str_std_io_event_loop_EventLoop;
__attribute__((hot)) std_io_event_loop_EventLoop** core_alloc_alloc_std_io_event_loop_EventLoop(long long count);
__attribute__((hot)) std_io_event_loop_EventLoop** core_alloc_resize_std_io_event_loop_EventLoop(std_io_event_loop_EventLoop** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_event_loop_EventLoop(std_io_event_loop_EventLoop** ptr);
__attribute__((hot)) std_io_event_loop_EventLoop*** core_alloc_alloc_std_io_event_loop_EventLoop_ptr(long long count);
__attribute__((hot)) std_io_event_loop_EventLoop*** core_alloc_resize_std_io_event_loop_EventLoop_ptr(std_io_event_loop_EventLoop*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_std_io_event_loop_EventLoop_ptr(std_io_event_loop_EventLoop*** ptr);
__attribute__((hot)) core_map_MapNode_str_std_io_event_loop_EventLoop** core_alloc_alloc_core_map_MapNode_str_std_io_event_loop_EventLoop(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_std_io_event_loop_EventLoop(core_map_MapNode_str_std_io_event_loop_EventLoop** ptr);

typedef TextDocument document_TextDocument;
struct core_vec_Vec_document_TextDocument { document_TextDocument** data; long long len; long long capacity; };
typedef struct core_vec_Vec_document_TextDocument core_vec_Vec_document_TextDocument;
struct core_vec_Vec_document_TextDocument_ptr { document_TextDocument*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_document_TextDocument_ptr core_vec_Vec_document_TextDocument_ptr;
struct core_map_MapNode_str_document_TextDocument { char* key; document_TextDocument* value; struct core_map_MapNode_str_document_TextDocument* next; };
typedef struct core_map_MapNode_str_document_TextDocument core_map_MapNode_str_document_TextDocument;
struct core_map_Map_str_document_TextDocument { core_map_MapNode_str_document_TextDocument** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_document_TextDocument core_map_Map_str_document_TextDocument;
__attribute__((hot)) document_TextDocument** core_alloc_alloc_document_TextDocument(long long count);
__attribute__((hot)) document_TextDocument** core_alloc_resize_document_TextDocument(document_TextDocument** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_document_TextDocument(document_TextDocument** ptr);
__attribute__((hot)) document_TextDocument*** core_alloc_alloc_document_TextDocument_ptr(long long count);
__attribute__((hot)) document_TextDocument*** core_alloc_resize_document_TextDocument_ptr(document_TextDocument*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_document_TextDocument_ptr(document_TextDocument*** ptr);
__attribute__((hot)) core_map_MapNode_str_document_TextDocument** core_alloc_alloc_core_map_MapNode_str_document_TextDocument(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_document_TextDocument(core_map_MapNode_str_document_TextDocument** ptr);

typedef DocumentStore document_DocumentStore;
struct core_vec_Vec_document_DocumentStore { document_DocumentStore** data; long long len; long long capacity; };
typedef struct core_vec_Vec_document_DocumentStore core_vec_Vec_document_DocumentStore;
struct core_vec_Vec_document_DocumentStore_ptr { document_DocumentStore*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_document_DocumentStore_ptr core_vec_Vec_document_DocumentStore_ptr;
struct core_map_MapNode_str_document_DocumentStore { char* key; document_DocumentStore* value; struct core_map_MapNode_str_document_DocumentStore* next; };
typedef struct core_map_MapNode_str_document_DocumentStore core_map_MapNode_str_document_DocumentStore;
struct core_map_Map_str_document_DocumentStore { core_map_MapNode_str_document_DocumentStore** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_document_DocumentStore core_map_Map_str_document_DocumentStore;
__attribute__((hot)) document_DocumentStore** core_alloc_alloc_document_DocumentStore(long long count);
__attribute__((hot)) document_DocumentStore** core_alloc_resize_document_DocumentStore(document_DocumentStore** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_document_DocumentStore(document_DocumentStore** ptr);
__attribute__((hot)) document_DocumentStore*** core_alloc_alloc_document_DocumentStore_ptr(long long count);
__attribute__((hot)) document_DocumentStore*** core_alloc_resize_document_DocumentStore_ptr(document_DocumentStore*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_document_DocumentStore_ptr(document_DocumentStore*** ptr);
__attribute__((hot)) core_map_MapNode_str_document_DocumentStore** core_alloc_alloc_core_map_MapNode_str_document_DocumentStore(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_document_DocumentStore(core_map_MapNode_str_document_DocumentStore** ptr);

typedef Diagnostic analyzer_Diagnostic;
struct core_vec_Vec_analyzer_Diagnostic { analyzer_Diagnostic** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_Diagnostic core_vec_Vec_analyzer_Diagnostic;
struct core_vec_Vec_analyzer_Diagnostic_ptr { analyzer_Diagnostic*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_Diagnostic_ptr core_vec_Vec_analyzer_Diagnostic_ptr;
struct core_map_MapNode_str_analyzer_Diagnostic { char* key; analyzer_Diagnostic* value; struct core_map_MapNode_str_analyzer_Diagnostic* next; };
typedef struct core_map_MapNode_str_analyzer_Diagnostic core_map_MapNode_str_analyzer_Diagnostic;
struct core_map_Map_str_analyzer_Diagnostic { core_map_MapNode_str_analyzer_Diagnostic** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_analyzer_Diagnostic core_map_Map_str_analyzer_Diagnostic;
__attribute__((hot)) analyzer_Diagnostic** core_alloc_alloc_analyzer_Diagnostic(long long count);
__attribute__((hot)) analyzer_Diagnostic** core_alloc_resize_analyzer_Diagnostic(analyzer_Diagnostic** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_Diagnostic(analyzer_Diagnostic** ptr);
__attribute__((hot)) analyzer_Diagnostic*** core_alloc_alloc_analyzer_Diagnostic_ptr(long long count);
__attribute__((hot)) analyzer_Diagnostic*** core_alloc_resize_analyzer_Diagnostic_ptr(analyzer_Diagnostic*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_Diagnostic_ptr(analyzer_Diagnostic*** ptr);
__attribute__((hot)) core_map_MapNode_str_analyzer_Diagnostic** core_alloc_alloc_core_map_MapNode_str_analyzer_Diagnostic(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_analyzer_Diagnostic(core_map_MapNode_str_analyzer_Diagnostic** ptr);

typedef SymbolInfo analyzer_SymbolInfo;
struct core_vec_Vec_analyzer_SymbolInfo { analyzer_SymbolInfo** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_SymbolInfo core_vec_Vec_analyzer_SymbolInfo;
struct core_vec_Vec_analyzer_SymbolInfo_ptr { analyzer_SymbolInfo*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_SymbolInfo_ptr core_vec_Vec_analyzer_SymbolInfo_ptr;
struct core_map_MapNode_str_analyzer_SymbolInfo { char* key; analyzer_SymbolInfo* value; struct core_map_MapNode_str_analyzer_SymbolInfo* next; };
typedef struct core_map_MapNode_str_analyzer_SymbolInfo core_map_MapNode_str_analyzer_SymbolInfo;
struct core_map_Map_str_analyzer_SymbolInfo { core_map_MapNode_str_analyzer_SymbolInfo** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_analyzer_SymbolInfo core_map_Map_str_analyzer_SymbolInfo;
__attribute__((hot)) analyzer_SymbolInfo** core_alloc_alloc_analyzer_SymbolInfo(long long count);
__attribute__((hot)) analyzer_SymbolInfo** core_alloc_resize_analyzer_SymbolInfo(analyzer_SymbolInfo** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_SymbolInfo(analyzer_SymbolInfo** ptr);
__attribute__((hot)) analyzer_SymbolInfo*** core_alloc_alloc_analyzer_SymbolInfo_ptr(long long count);
__attribute__((hot)) analyzer_SymbolInfo*** core_alloc_resize_analyzer_SymbolInfo_ptr(analyzer_SymbolInfo*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_SymbolInfo_ptr(analyzer_SymbolInfo*** ptr);
__attribute__((hot)) core_map_MapNode_str_analyzer_SymbolInfo** core_alloc_alloc_core_map_MapNode_str_analyzer_SymbolInfo(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_analyzer_SymbolInfo(core_map_MapNode_str_analyzer_SymbolInfo** ptr);

typedef AnalysisResult analyzer_AnalysisResult;
struct core_vec_Vec_analyzer_AnalysisResult { analyzer_AnalysisResult** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_AnalysisResult core_vec_Vec_analyzer_AnalysisResult;
struct core_vec_Vec_analyzer_AnalysisResult_ptr { analyzer_AnalysisResult*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_AnalysisResult_ptr core_vec_Vec_analyzer_AnalysisResult_ptr;
struct core_map_MapNode_str_analyzer_AnalysisResult { char* key; analyzer_AnalysisResult* value; struct core_map_MapNode_str_analyzer_AnalysisResult* next; };
typedef struct core_map_MapNode_str_analyzer_AnalysisResult core_map_MapNode_str_analyzer_AnalysisResult;
struct core_map_Map_str_analyzer_AnalysisResult { core_map_MapNode_str_analyzer_AnalysisResult** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_analyzer_AnalysisResult core_map_Map_str_analyzer_AnalysisResult;
__attribute__((hot)) analyzer_AnalysisResult** core_alloc_alloc_analyzer_AnalysisResult(long long count);
__attribute__((hot)) analyzer_AnalysisResult** core_alloc_resize_analyzer_AnalysisResult(analyzer_AnalysisResult** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_AnalysisResult(analyzer_AnalysisResult** ptr);
__attribute__((hot)) analyzer_AnalysisResult*** core_alloc_alloc_analyzer_AnalysisResult_ptr(long long count);
__attribute__((hot)) analyzer_AnalysisResult*** core_alloc_resize_analyzer_AnalysisResult_ptr(analyzer_AnalysisResult*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_AnalysisResult_ptr(analyzer_AnalysisResult*** ptr);
__attribute__((hot)) core_map_MapNode_str_analyzer_AnalysisResult** core_alloc_alloc_core_map_MapNode_str_analyzer_AnalysisResult(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_analyzer_AnalysisResult(core_map_MapNode_str_analyzer_AnalysisResult** ptr);

typedef Analyzer analyzer_Analyzer;
struct core_vec_Vec_analyzer_Analyzer { analyzer_Analyzer** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_Analyzer core_vec_Vec_analyzer_Analyzer;
struct core_vec_Vec_analyzer_Analyzer_ptr { analyzer_Analyzer*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_analyzer_Analyzer_ptr core_vec_Vec_analyzer_Analyzer_ptr;
struct core_map_MapNode_str_analyzer_Analyzer { char* key; analyzer_Analyzer* value; struct core_map_MapNode_str_analyzer_Analyzer* next; };
typedef struct core_map_MapNode_str_analyzer_Analyzer core_map_MapNode_str_analyzer_Analyzer;
struct core_map_Map_str_analyzer_Analyzer { core_map_MapNode_str_analyzer_Analyzer** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_analyzer_Analyzer core_map_Map_str_analyzer_Analyzer;
__attribute__((hot)) analyzer_Analyzer** core_alloc_alloc_analyzer_Analyzer(long long count);
__attribute__((hot)) analyzer_Analyzer** core_alloc_resize_analyzer_Analyzer(analyzer_Analyzer** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_Analyzer(analyzer_Analyzer** ptr);
__attribute__((hot)) analyzer_Analyzer*** core_alloc_alloc_analyzer_Analyzer_ptr(long long count);
__attribute__((hot)) analyzer_Analyzer*** core_alloc_resize_analyzer_Analyzer_ptr(analyzer_Analyzer*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_analyzer_Analyzer_ptr(analyzer_Analyzer*** ptr);
__attribute__((hot)) core_map_MapNode_str_analyzer_Analyzer** core_alloc_alloc_core_map_MapNode_str_analyzer_Analyzer(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_analyzer_Analyzer(core_map_MapNode_str_analyzer_Analyzer** ptr);

typedef LspServer server_LspServer;
struct core_vec_Vec_server_LspServer { server_LspServer** data; long long len; long long capacity; };
typedef struct core_vec_Vec_server_LspServer core_vec_Vec_server_LspServer;
struct core_vec_Vec_server_LspServer_ptr { server_LspServer*** data; long long len; long long capacity; };
typedef struct core_vec_Vec_server_LspServer_ptr core_vec_Vec_server_LspServer_ptr;
struct core_map_MapNode_str_server_LspServer { char* key; server_LspServer* value; struct core_map_MapNode_str_server_LspServer* next; };
typedef struct core_map_MapNode_str_server_LspServer core_map_MapNode_str_server_LspServer;
struct core_map_Map_str_server_LspServer { core_map_MapNode_str_server_LspServer** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_server_LspServer core_map_Map_str_server_LspServer;
__attribute__((hot)) server_LspServer** core_alloc_alloc_server_LspServer(long long count);
__attribute__((hot)) server_LspServer** core_alloc_resize_server_LspServer(server_LspServer** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_server_LspServer(server_LspServer** ptr);
__attribute__((hot)) server_LspServer*** core_alloc_alloc_server_LspServer_ptr(long long count);
__attribute__((hot)) server_LspServer*** core_alloc_resize_server_LspServer_ptr(server_LspServer*** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_server_LspServer_ptr(server_LspServer*** ptr);
__attribute__((hot)) core_map_MapNode_str_server_LspServer** core_alloc_alloc_core_map_MapNode_str_server_LspServer(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_server_LspServer(core_map_MapNode_str_server_LspServer** ptr);

/* Primitive vec/map types for core modules */
struct core_vec_Vec_str { char** data; long long len; long long capacity; };
typedef struct core_vec_Vec_str core_vec_Vec_str;
__attribute__((hot)) char** core_alloc_alloc_str(long long count);
__attribute__((hot)) char** core_alloc_resize_str(char** ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_str(char** ptr);
struct core_vec_Vec_i64 { long long* data; long long len; long long capacity; };
typedef struct core_vec_Vec_i64 core_vec_Vec_i64;
__attribute__((hot)) long long* core_alloc_alloc_i64(long long count);
__attribute__((hot)) long long* core_alloc_resize_i64(long long* ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_i64(long long* ptr);
struct core_map_MapNode_str_bool { char* key; bool value; struct core_map_MapNode_str_bool* next; };
typedef struct core_map_MapNode_str_bool core_map_MapNode_str_bool;
struct core_map_Map_str_bool { core_map_MapNode_str_bool** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_bool core_map_Map_str_bool;
__attribute__((hot)) core_map_MapNode_str_bool** core_alloc_alloc_core_map_MapNode_str_bool(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_bool(core_map_MapNode_str_bool** ptr);
struct core_map_MapNode_str_str { char* key; char* value; struct core_map_MapNode_str_str* next; };
typedef struct core_map_MapNode_str_str core_map_MapNode_str_str;
struct core_map_Map_str_str { core_map_MapNode_str_str** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_str core_map_Map_str_str;
__attribute__((hot)) core_map_MapNode_str_str** core_alloc_alloc_core_map_MapNode_str_str(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_str(core_map_MapNode_str_str** ptr);
struct core_map_MapNode_str_i64 { char* key; long long value; struct core_map_MapNode_str_i64* next; };
typedef struct core_map_MapNode_str_i64 core_map_MapNode_str_i64;
struct core_map_Map_str_i64 { core_map_MapNode_str_i64** buckets; long long capacity; long long len; };
typedef struct core_map_Map_str_i64 core_map_Map_str_i64;
__attribute__((hot)) core_map_MapNode_str_i64** core_alloc_alloc_core_map_MapNode_str_i64(long long count);
__attribute__((hot)) void core_alloc_dealloc_core_map_MapNode_str_i64(core_map_MapNode_str_i64** ptr);
__attribute__((hot)) char* core_alloc_alloc_char(long long count);
__attribute__((hot)) void core_alloc_copy_char(char* dst, char* src, long long count);
__attribute__((hot)) char* core_alloc_resize_char(char* ptr, long long new_count);
__attribute__((hot)) void core_alloc_dealloc_char(char* ptr);
