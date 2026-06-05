#include "../../../tauraro_types.h"


__attribute__((hot)) char* Fmt_int_to_str(long long n) {
    /* pass */
    if ((n == 0LL)) {
        /* pass */
        return "0";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(24LL);
    /* pass */
    bool neg = false;
    /* pass */
    long long x = n;
    /* pass */
    if ((x < 0LL)) {
        /* pass */
        neg = true;
        /* pass */
        x = (0LL - x);
    }
    /* pass */
    while ((x > 0LL)) {
        /* pass */
        long long d = (x - ((x / 10LL) * 10LL));
        /* pass */
        if ((d == 0LL)) {
            /* pass */
            StringBuilder_append_char(sb, 48LL);
        } else if ((d == 1LL)) {
            /* pass */
            StringBuilder_append_char(sb, 49LL);
        } else if ((d == 2LL)) {
            /* pass */
            StringBuilder_append_char(sb, 50LL);
        } else if ((d == 3LL)) {
            /* pass */
            StringBuilder_append_char(sb, 51LL);
        } else if ((d == 4LL)) {
            /* pass */
            StringBuilder_append_char(sb, 52LL);
        } else if ((d == 5LL)) {
            /* pass */
            StringBuilder_append_char(sb, 53LL);
        } else if ((d == 6LL)) {
            /* pass */
            StringBuilder_append_char(sb, 54LL);
        } else if ((d == 7LL)) {
            /* pass */
            StringBuilder_append_char(sb, 55LL);
        } else if ((d == 8LL)) {
            /* pass */
            StringBuilder_append_char(sb, 56LL);
        } else {
            /* pass */
            StringBuilder_append_char(sb, 57LL);
        }
        /* pass */
        x = (x / 10LL);
    }
    /* pass */
    if (neg) {
        /* pass */
        StringBuilder_append_char(sb, 45LL);
    }
    /* pass */
    return Str_reverse(StringBuilder_to_owned(sb));
}

__attribute__((hot)) char* Fmt_int_to_hex(long long n) {
    /* pass */
    if ((n == 0LL)) {
        /* pass */
        return "0";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(18LL);
    /* pass */
    long long x = n;
    /* pass */
    while ((x > 0LL)) {
        /* pass */
        long long d = (x - ((x / 16LL) * 16LL));
        /* pass */
        if ((d < 10LL)) {
            /* pass */
            StringBuilder_append_char(sb, (48LL + d));
        } else {
            /* pass */
            StringBuilder_append_char(sb, (87LL + d));
        }
        /* pass */
        x = (x / 16LL);
    }
    /* pass */
    return Str_reverse(StringBuilder_to_owned(sb));
}

__attribute__((hot)) char* Fmt_int_to_bin(long long n) {
    /* pass */
    if ((n == 0LL)) {
        /* pass */
        return "0";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(66LL);
    /* pass */
    long long x = n;
    /* pass */
    while ((x > 0LL)) {
        /* pass */
        long long bit = (x - ((x / 2LL) * 2LL));
        /* pass */
        if ((bit == 0LL)) {
            /* pass */
            StringBuilder_append_char(sb, 48LL);
        } else {
            /* pass */
            StringBuilder_append_char(sb, 49LL);
        }
        /* pass */
        x = (x / 2LL);
    }
    /* pass */
    return Str_reverse(StringBuilder_to_owned(sb));
}

__attribute__((hot)) char* Fmt_int_to_oct(long long n) {
    /* pass */
    if ((n == 0LL)) {
        /* pass */
        return "0";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(24LL);
    /* pass */
    long long x = n;
    /* pass */
    while ((x > 0LL)) {
        /* pass */
        long long d = (x - ((x / 8LL) * 8LL));
        /* pass */
        StringBuilder_append_char(sb, (48LL + d));
        /* pass */
        x = (x / 8LL);
    }
    /* pass */
    return Str_reverse(StringBuilder_to_owned(sb));
}

__attribute__((hot)) char* Fmt_float_to_str(double f, long long decimals) {
    /* pass */
    return _tr_float_fmt(f, decimals);
}

__attribute__((hot)) char* Fmt_bool_to_str(bool b) {
    /* pass */
    if (b) {
        /* pass */
        return "true";
    }
    /* pass */
    return "false";
}

__attribute__((hot)) char* Fmt_pad_left(char* s, long long width, long long pad_char) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    if ((slen >= width)) {
        /* pass */
        return s;
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init((width + 1LL));
    /* pass */
    long long i = slen;
    /* pass */
    while ((i < width)) {
        /* pass */
        StringBuilder_append_char(sb, pad_char);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    StringBuilder_append(sb, s);
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Fmt_pad_right(char* s, long long width, long long pad_char) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    if ((slen >= width)) {
        /* pass */
        return s;
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init((width + 1LL));
    /* pass */
    StringBuilder_append(sb, s);
    /* pass */
    long long i = slen;
    /* pass */
    while ((i < width)) {
        /* pass */
        StringBuilder_append_char(sb, pad_char);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Fmt_zero_pad(long long n, long long width) {
    /* pass */
    return Fmt_pad_left(Fmt_int_to_str(n), width, 48LL);
}

__attribute__((hot)) char* Fmt_format(char* template, List_str* args) {
    /* pass */
    char* result = template;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < args->len)) {
        /* pass */
        long long pos = Str_index_of(result, "{}");
        /* pass */
        if ((pos < 0LL)) {
            /* pass */
            break;
        }
        /* pass */
        char* before = Str_slice(result, 0LL, pos);
        /* pass */
        char* after = Str_slice(result, (pos + 2LL), Str_len(result));
        /* pass */
        result = _tr_str_concat(_tr_str_concat(before, List_str_get(args, i)), after);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return result;
}

