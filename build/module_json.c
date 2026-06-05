#include "tauraro_types.h"

long long JsonParser_peek(JsonParser* self);
long long JsonParser_advance(JsonParser* self);
void JsonParser_skip_ws(JsonParser* self);
JsonVal JsonParser_parse_null(JsonParser* self);
JsonVal JsonParser_parse_true(JsonParser* self);
JsonVal JsonParser_parse_false(JsonParser* self);
JsonVal JsonParser_parse_string(JsonParser* self);
char* JsonParser_read_string(JsonParser* self);
JsonVal JsonParser_parse_number(JsonParser* self);
JsonVal JsonParser_parse_array(JsonParser* self);
JsonVal JsonParser_parse_object(JsonParser* self);
char* _json_escape(char* s);
char* _hex2(long long n);
char* _hex_digit(long long n);
long long _hex4_to_int(char* s);
long long _hex_char_val(long long c);
char* _int_to_char_str(long long code);
void _force_json_list_types();

__attribute__((malloc,returns_nonnull,hot)) JsonParser* JsonParser_init(char* src) {
    /* pass */
    JsonParser* p = ((JsonParser*)_tr_checked_alloc(sizeof(JsonParser)));
    /* pass */
    p->src = src;
    /* pass */
    p->pos = 0LL;
    /* pass */
    p->len = _tr_strlen((char*)src);
    /* pass */
    return p;
}

__attribute__((hot)) long long JsonParser_peek(JsonParser* self) {
    /* pass */
    if ((self->pos >= self->len)) {
        /* pass */
        return 0LL;
    }
    /* pass */
    return _tr_str_char_at_code(self->src, self->pos);
}

__attribute__((hot)) long long JsonParser_advance(JsonParser* self) {
    /* pass */
    long long c = JsonParser_peek(self);
    /* pass */
    self->pos = (self->pos + 1LL);
    /* pass */
    return c;
}

__attribute__((hot)) void JsonParser_skip_ws(JsonParser* self) {
    /* pass */
    while ((self->pos < self->len)) {
        /* pass */
        long long c = JsonParser_peek(self);
        /* pass */
        if (((((c == 32LL) || (c == 9LL)) || (c == 10LL)) || (c == 13LL))) {
            /* pass */
            self->pos = (self->pos + 1LL);
        } else {
            /* pass */
            break;
        }
    }
}

__attribute__((hot)) JsonVal JsonParser_parse(JsonParser* self) {
    /* pass */
    JsonParser_skip_ws(self);
    /* pass */
    long long c = JsonParser_peek(self);
    /* pass */
    if ((c == 110LL)) {
        /* pass */
        return JsonParser_parse_null(self);
    }
    /* pass */
    if ((c == 116LL)) {
        /* pass */
        return JsonParser_parse_true(self);
    }
    /* pass */
    if ((c == 102LL)) {
        /* pass */
        return JsonParser_parse_false(self);
    }
    /* pass */
    if ((c == 34LL)) {
        /* pass */
        return JsonParser_parse_string(self);
    }
    /* pass */
    if ((c == 91LL)) {
        /* pass */
        return JsonParser_parse_array(self);
    }
    /* pass */
    if ((c == 123LL)) {
        /* pass */
        return JsonParser_parse_object(self);
    }
    /* pass */
    if (((c == 45LL) || ((c >= 48LL) && (c <= 57LL)))) {
        /* pass */
        return JsonParser_parse_number(self);
    }
    /* pass */
    return JsonVal_make_JNull();
}

__attribute__((hot)) JsonVal JsonParser_parse_null(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 4LL);
    /* pass */
    return JsonVal_make_JNull();
}

__attribute__((hot)) JsonVal JsonParser_parse_true(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 4LL);
    /* pass */
    return JsonVal_ctor_JBool(true);
}

__attribute__((hot)) JsonVal JsonParser_parse_false(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 5LL);
    /* pass */
    return JsonVal_ctor_JBool(false);
}

__attribute__((hot)) JsonVal JsonParser_parse_string(JsonParser* self) {
    /* pass */
    return JsonVal_ctor_JStr(JsonParser_read_string(self));
}

__attribute__((hot)) char* JsonParser_read_string(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 1LL);
    /* pass */
    char* sb = "";
    /* pass */
    while ((self->pos < self->len)) {
        /* pass */
        long long c = JsonParser_advance(self);
        /* pass */
        if ((c == 34LL)) {
            /* pass */
            break;
        } else if ((c == 92LL)) {
            /* pass */
            long long esc = JsonParser_advance(self);
            /* pass */
            if ((esc == 110LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\n");
            } else if ((esc == 116LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\t");
            } else if ((esc == 114LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\r");
            } else if ((esc == 34LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\"");
            } else if ((esc == 92LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\\");
            } else if ((esc == 47LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "/");
            } else if ((esc == 98LL)) {
                /* pass */
                sb = _tr_str_concat(sb, "\n");
            } else if ((esc == 102LL)) {
                /* pass */
                sb = _tr_str_concat(sb, " ");
            } else if ((esc == 117LL)) {
                /* pass */
                char* hex = "";
                /* pass */
                long long hi = 0LL;
                /* pass */
                while (((hi < 4LL) && (self->pos < self->len))) {
                    /* pass */
                    hex = _tr_str_concat(hex, _tr_str_slice(self->src, self->pos, (self->pos + 1LL)));
                    /* pass */
                    self->pos = (self->pos + 1LL);
                    /* pass */
                    hi = (hi + 1LL);
                }
                /* pass */
                long long code = _hex4_to_int(hex);
                /* pass */
                if (((code >= 32LL) && (code < 128LL))) {
                    /* pass */
                    sb = _tr_str_concat(sb, _int_to_char_str(code));
                }
            } else {
                /* pass */
                sb = _tr_str_concat(sb, _tr_str_slice(self->src, (self->pos - 1LL), self->pos));
            }
        } else {
            /* pass */
            sb = _tr_str_concat(sb, _tr_str_slice(self->src, (self->pos - 1LL), self->pos));
        }
    }
    /* pass */
    return sb;
}

__attribute__((hot)) JsonVal JsonParser_parse_number(JsonParser* self) {
    /* pass */
    long long start = self->pos;
    /* pass */
    bool is_float = false;
    /* pass */
    if ((JsonParser_peek(self) == 45LL)) {
        /* pass */
        self->pos = (self->pos + 1LL);
    }
    /* pass */
    while ((self->pos < self->len)) {
        /* pass */
        long long c = JsonParser_peek(self);
        /* pass */
        if (((c >= 48LL) && (c <= 57LL))) {
            /* pass */
            self->pos = (self->pos + 1LL);
        } else if ((((((c == 46LL) || (c == 101LL)) || (c == 69LL)) || (c == 43LL)) || (c == 45LL))) {
            /* pass */
            is_float = true;
            /* pass */
            self->pos = (self->pos + 1LL);
        } else {
            /* pass */
            break;
        }
    }
    /* pass */
    char* num_str = _tr_str_slice(self->src, start, self->pos);
    /* pass */
    if (is_float) {
        /* pass */
        return JsonVal_ctor_JFloat(_tr_str_to_float(num_str));
    }
    /* pass */
    return JsonVal_ctor_JInt(_tr_str_to_int(num_str));
}

__attribute__((hot)) JsonVal JsonParser_parse_array(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 1LL);
    /* pass */
    List_ptr* items = (void*)List_ptr_new();
    /* pass */
    JsonParser_skip_ws(self);
    /* pass */
    if ((JsonParser_peek(self) == 93LL)) {
        /* pass */
        self->pos = (self->pos + 1LL);
        /* pass */
        return JsonVal_ctor_JArr(items);
    }
    /* pass */
    while ((self->pos < self->len)) {
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        JsonVal v = JsonParser_parse(self);
        /* pass */
        List_ptr_append(items, box_jv(v));
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        long long c = JsonParser_peek(self);
        /* pass */
        if ((c == 44LL)) {
            /* pass */
            self->pos = (self->pos + 1LL);
        } else if ((c == 93LL)) {
            /* pass */
            self->pos = (self->pos + 1LL);
            /* pass */
            break;
        } else {
            /* pass */
            break;
        }
    }
    /* pass */
    return JsonVal_ctor_JArr(items);
}

__attribute__((hot)) JsonVal JsonParser_parse_object(JsonParser* self) {
    /* pass */
    self->pos = (self->pos + 1LL);
    /* pass */
    List_str* keys = (void*)List_str_new();
    /* pass */
    List_ptr* vals = (void*)List_ptr_new();
    /* pass */
    JsonParser_skip_ws(self);
    /* pass */
    if ((JsonParser_peek(self) == 125LL)) {
        /* pass */
        self->pos = (self->pos + 1LL);
        /* pass */
        return JsonVal_ctor_JObj(keys, vals);
    }
    /* pass */
    while ((self->pos < self->len)) {
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        if ((JsonParser_peek(self) != 34LL)) {
            /* pass */
            break;
        }
        /* pass */
        char* k = JsonParser_read_string(self);
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        if ((JsonParser_peek(self) == 58LL)) {
            /* pass */
            self->pos = (self->pos + 1LL);
        }
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        JsonVal v = JsonParser_parse(self);
        /* pass */
        List_str_append(keys, k);
        /* pass */
        List_ptr_append(vals, box_jv(v));
        /* pass */
        JsonParser_skip_ws(self);
        /* pass */
        long long c = JsonParser_peek(self);
        /* pass */
        if ((c == 44LL)) {
            /* pass */
            self->pos = (self->pos + 1LL);
        } else if ((c == 125LL)) {
            /* pass */
            self->pos = (self->pos + 1LL);
            /* pass */
            break;
        } else {
            /* pass */
            break;
        }
    }
    /* pass */
    return JsonVal_ctor_JObj(keys, vals);
}

__attribute__((malloc,returns_nonnull,hot)) JObjBuilder* JObjBuilder_init() {
    /* pass */
    JObjBuilder* b = ((JObjBuilder*)_tr_checked_alloc(sizeof(JObjBuilder)));
    /* pass */
    b->keys = (void*)List_str_new();
    /* pass */
    b->vals = (void*)List_ptr_new();
    /* pass */
    return b;
}

__attribute__((hot)) JObjBuilder* JObjBuilder_add(JObjBuilder* self, char* key, JsonVal val) {
    /* pass */
    List_str_append(self->keys, key);
    /* pass */
    List_ptr_append(self->vals, box_jv(val));
    /* pass */
    return self;
}

__attribute__((hot)) JsonVal JObjBuilder_build(JObjBuilder* self) {
    /* pass */
    return JsonVal_ctor_JObj(self->keys, self->vals);
}

__attribute__((malloc,returns_nonnull,hot)) JArrBuilder* JArrBuilder_init() {
    /* pass */
    JArrBuilder* b = ((JArrBuilder*)_tr_checked_alloc(sizeof(JArrBuilder)));
    /* pass */
    b->items = (void*)List_ptr_new();
    /* pass */
    return b;
}

__attribute__((hot)) JArrBuilder* JArrBuilder_add(JArrBuilder* self, JsonVal val) {
    /* pass */
    List_ptr_append(self->items, box_jv(val));
    /* pass */
    return self;
}

__attribute__((hot)) JsonVal JArrBuilder_build(JArrBuilder* self) {
    /* pass */
    return JsonVal_ctor_JArr(self->items);
}

__attribute__((hot)) JsonVal* box_jv(JsonVal v) {
    /* pass */
    JsonVal* p = ((JsonVal*)_tr_c_calloc((size_t)(1LL), sizeof(JsonVal)));
    /* pass */
    (*p = v);
    /* pass */
    return p;
}

__attribute__((hot)) JsonVal jnull() {
    /* pass */
    return JsonVal_make_JNull();
}

__attribute__((hot)) JsonVal jbool(bool v) {
    /* pass */
    return JsonVal_ctor_JBool(v);
}

__attribute__((hot)) JsonVal jint(long long n) {
    /* pass */
    return JsonVal_ctor_JInt(n);
}

__attribute__((hot)) JsonVal jfloat(double n) {
    /* pass */
    return JsonVal_ctor_JFloat(n);
}

__attribute__((hot)) JsonVal jstr(char* s) {
    /* pass */
    return JsonVal_ctor_JStr(s);
}

__attribute__((hot)) JsonVal jarr(List_ptr* items) {
    /* pass */
    return JsonVal_ctor_JArr(items);
}

__attribute__((hot)) JsonVal jobj(List_str* keys, List_ptr* vals) {
    /* pass */
    return JsonVal_ctor_JObj(keys, vals);
}

__attribute__((hot)) JsonVal jobj_empty() {
    /* pass */
    return JsonVal_ctor_JObj((void*)List_str_new(), (void*)List_ptr_new());
}

__attribute__((hot)) bool jv_is_null(JsonVal v) {
    /* pass */
    __auto_type _t1 = v;
    if (_t1.tag == JsonVal_JNull) {
        return true;
    } else if (1) {
        __auto_type _ = _t1;
        return false;
    }
}

__attribute__((hot)) char* jv_str(JsonVal v) {
    /* pass */
    __auto_type _t2 = v;
    if (_t2.tag == JsonVal_JStr) {
        __auto_type s = _t2.data.JStr.s;
        return s;
    } else if (_t2.tag == JsonVal_JInt) {
        __auto_type n = _t2.data.JInt.v;
        return _tr_int_to_str((long long)(n));
    } else if (_t2.tag == JsonVal_JBool) {
        __auto_type b = _t2.data.JBool.v;
        /* pass */
        if (b) {
            /* pass */
            return "true";
        }
        /* pass */
        return "false";
    } else if (1) {
        __auto_type _ = _t2;
        return "";
    }
}

__attribute__((hot)) long long jv_int(JsonVal v) {
    /* pass */
    __auto_type _t3 = v;
    if (_t3.tag == JsonVal_JInt) {
        __auto_type n = _t3.data.JInt.v;
        return n;
    } else if (_t3.tag == JsonVal_JFloat) {
        __auto_type f = _t3.data.JFloat.v;
        return (long long)(f);
    } else if (1) {
        __auto_type _ = _t3;
        return 0LL;
    }
}

__attribute__((hot)) bool jv_bool(JsonVal v) {
    /* pass */
    __auto_type _t4 = v;
    if (_t4.tag == JsonVal_JBool) {
        __auto_type b = _t4.data.JBool.v;
        return b;
    } else if (1) {
        __auto_type _ = _t4;
        return false;
    }
}

__attribute__((hot)) JsonVal jv_get(JsonVal v, char* key) {
    /* pass */
    __auto_type _t5 = v;
    if (_t5.tag == JsonVal_JObj) {
        __auto_type keys = _t5.data.JObj.keys;
__auto_type vals = _t5.data.JObj.vals;
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < keys->len)) {
            /* pass */
            if ((strcmp((char*)List_str_get(keys, i), (char*)key) == 0)) {
                /* pass */
                return (*((JsonVal*)List_ptr_get(vals, i)));
            }
            /* pass */
            i = (i + 1LL);
        }
    } else if (1) {
        __auto_type _ = _t5;
        /* pass */
    }
    /* pass */
    return JsonVal_make_JNull();
}

__attribute__((hot)) JsonVal jv_get_path(JsonVal v, char* path) {
    /* pass */
    List_str* parts = _tr_str_split(path, ".");
    /* pass */
    JsonVal cur = v;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < parts->len)) {
        /* pass */
        cur = jv_get(cur, List_str_get(parts, i));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return cur;
}

__attribute__((hot)) long long jv_arr_len(JsonVal v) {
    /* pass */
    __auto_type _t6 = v;
    if (_t6.tag == JsonVal_JArr) {
        __auto_type items = _t6.data.JArr.items;
        return items->len;
    } else if (1) {
        __auto_type _ = _t6;
        return 0LL;
    }
}

__attribute__((hot)) JsonVal jv_arr_get(JsonVal v, long long i) {
    /* pass */
    __auto_type _t7 = v;
    if (_t7.tag == JsonVal_JArr) {
        __auto_type items = _t7.data.JArr.items;
        /* pass */
        if (((i >= 0LL) && (i < items->len))) {
            /* pass */
            return (*((JsonVal*)List_ptr_get(items, i)));
        }
    } else if (1) {
        __auto_type _ = _t7;
        /* pass */
    }
    /* pass */
    return JsonVal_make_JNull();
}

__attribute__((hot)) JsonVal json_parse(char* s) {
    /* pass */
    JsonParser* p = JsonParser_init(s);
    /* pass */
    return JsonParser_parse(p);
}

__attribute__((hot)) char* json_str(JsonVal v) {
    /* pass */
    __auto_type _t8 = v;
    if (_t8.tag == JsonVal_JNull) {
        return "null";
    } else if (_t8.tag == JsonVal_JBool) {
        __auto_type b = _t8.data.JBool.v;
        if (b) {
            /* pass */
            return "true";
            /* pass */
            return "false";
        }
    } else if (_t8.tag == JsonVal_JInt) {
        __auto_type n = _t8.data.JInt.v;
        return _tr_int_to_str((long long)(n));
    } else if (_t8.tag == JsonVal_JFloat) {
        __auto_type f = _t8.data.JFloat.v;
        return _tr_float_to_str((double)(f));
    } else if (_t8.tag == JsonVal_JStr) {
        __auto_type s = _t8.data.JStr.s;
        return _tr_str_concat(_tr_str_concat("\"", _json_escape(s)), "\"");
    } else if (_t8.tag == JsonVal_JArr) {
        __auto_type items = _t8.data.JArr.items;
        /* pass */
        char* sb = "[";
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < items->len)) {
            /* pass */
            if ((i > 0LL)) {
                /* pass */
                sb = _tr_str_concat(sb, ",");
            }
            /* pass */
            sb = _tr_str_concat(sb, json_str((*((JsonVal*)List_ptr_get(items, i)))));
            /* pass */
            i = (i + 1LL);
        }
        /* pass */
        return _tr_str_concat(sb, "]");
    } else if (_t8.tag == JsonVal_JObj) {
        __auto_type keys = _t8.data.JObj.keys;
__auto_type vals = _t8.data.JObj.vals;
        /* pass */
        char* sb = "{";
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < keys->len)) {
            /* pass */
            if ((i > 0LL)) {
                /* pass */
                sb = _tr_str_concat(sb, ",");
            }
            /* pass */
            sb = _tr_str_concat(_tr_str_concat(_tr_str_concat(sb, "\""), _json_escape(List_str_get(keys, i))), "\":");
            /* pass */
            sb = _tr_str_concat(sb, json_str((*((JsonVal*)List_ptr_get(vals, i)))));
            /* pass */
            i = (i + 1LL);
        }
        /* pass */
        return _tr_str_concat(sb, "}");
    }
    /* pass */
    return "null";
}

__attribute__((hot)) char* _json_escape(char* s) {
    /* pass */
    char* out = "";
    /* pass */
    long long i = 0LL;
    /* pass */
    long long n = _tr_strlen((char*)s);
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = _tr_str_char_at_code(s, i);
        /* pass */
        if ((c == 34LL)) {
            /* pass */
            out = _tr_str_concat(out, "\\\"");
        } else if ((c == 92LL)) {
            /* pass */
            out = _tr_str_concat(out, "\\\\");
        } else if ((c == 10LL)) {
            /* pass */
            out = _tr_str_concat(out, "\\n");
        } else if ((c == 13LL)) {
            /* pass */
            out = _tr_str_concat(out, "\\r");
        } else if ((c == 9LL)) {
            /* pass */
            out = _tr_str_concat(out, "\\t");
        } else if ((c < 32LL)) {
            /* pass */
            out = _tr_str_concat(_tr_str_concat(out, "\\u00"), _hex2(c));
        } else {
            /* pass */
            out = _tr_str_concat(out, _tr_str_slice(s, i, (i + 1LL)));
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return out;
}

__attribute__((hot)) char* _hex2(long long n) {
    /* pass */
    long long hi = (n / 16LL);
    /* pass */
    long long lo = (n - (hi * 16LL));
    /* pass */
    return _tr_str_concat(_hex_digit(hi), _hex_digit(lo));
}

__attribute__((hot)) char* _hex_digit(long long n) {
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

__attribute__((hot)) long long _hex4_to_int(char* s) {
    /* pass */
    long long result = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < _tr_strlen((char*)s))) {
        /* pass */
        result = ((result * 16LL) + _hex_char_val(_tr_str_char_at_code(s, i)));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return result;
}

__attribute__((hot)) long long _hex_char_val(long long c) {
    /* pass */
    if (((c >= 48LL) && (c <= 57LL))) {
        /* pass */
        return (c - 48LL);
    }
    /* pass */
    if (((c >= 97LL) && (c <= 102LL))) {
        /* pass */
        return (c - 87LL);
    }
    /* pass */
    if (((c >= 65LL) && (c <= 70LL))) {
        /* pass */
        return (c - 55LL);
    }
    /* pass */
    return 0LL;
}

__attribute__((hot)) char* _int_to_char_str(long long code) {
    /* pass */
    char* buf = " ";
    /* pass */
    /* unsafe block */
    /* pass */
    char* p = ((char*)(buf));
    /* pass */
    (*p = ((char)(code)));
    /* pass */
    return buf;
}

__attribute__((hot)) void _force_json_list_types() {
    /* pass */
    List_JsonVal* _v = (void*)List_JsonVal_new();
    /* pass */
    List_ptr* _p = (void*)List_ptr_new();
}

