#include "../../../tauraro_types.h"


__attribute__((hot)) long long Str_len(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long n = 0LL;
    /* pass */
    while ((((long long)((*(p + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    return n;
}

__attribute__((hot)) bool Str_starts_with(char* s, char* prefix) {
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    char* pp = ((char*)(prefix));
    /* pass */
    long long i = 0LL;
    /* pass */
    while (true) {
        /* pass */
        long long pc = ((long long)((*(pp + i))));
        /* pass */
        if ((pc == 0LL)) {
            /* pass */
            return true;
        }
        /* pass */
        long long sc = ((long long)((*(sp + i))));
        /* pass */
        if (((sc == 0LL) || (sc != pc))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool Str_ends_with(char* s, char* suffix) {
    /* pass */
    long long sl = Str_len(s);
    /* pass */
    long long el = Str_len(suffix);
    /* pass */
    if ((el > sl)) {
        /* pass */
        return false;
    }
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    char* ep = ((char*)(suffix));
    /* pass */
    long long off = (sl - el);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < el)) {
        /* pass */
        if ((((long long)((*(sp + (off + i))))) != ((long long)((*(ep + i)))))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_contains_char(char* s, long long c) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while (true) {
        /* pass */
        long long ch = ((long long)((*(p + i))));
        /* pass */
        if ((ch == 0LL)) {
            /* pass */
            return false;
        }
        /* pass */
        if ((ch == c)) {
            /* pass */
            return true;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return false;
}

__attribute__((hot)) bool Str_contains(char* s, char* sub) {
    /* pass */
    return (Str_index_of(s, sub) >= 0LL);
}

__attribute__((hot)) bool Str_eq(char* a, char* b) {
    /* pass */
    char* pa = ((char*)(a));
    /* pass */
    char* pb = ((char*)(b));
    /* pass */
    long long i = 0LL;
    /* pass */
    while (true) {
        /* pass */
        long long ca = ((long long)((*(pa + i))));
        /* pass */
        long long cb = ((long long)((*(pb + i))));
        /* pass */
        if ((ca != cb)) {
            /* pass */
            return false;
        }
        /* pass */
        if ((ca == 0LL)) {
            /* pass */
            return true;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_digit(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        if (((c < 48LL) || (c > 57LL))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_alpha(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        if ((!(((c >= 65LL) && (c <= 90LL)) || ((c >= 97LL) && (c <= 122LL))))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_alnum(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        bool ok = ((((c >= 48LL) && (c <= 57LL)) || ((c >= 65LL) && (c <= 90LL))) || ((c >= 97LL) && (c <= 122LL)));
        /* pass */
        if ((!ok)) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_space(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        if (((((c != 32LL) && (c != 9LL)) && (c != 10LL)) && (c != 13LL))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_upper(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        if (((c >= 97LL) && (c <= 122LL))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) bool Str_is_lower(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    while ((c != 0LL)) {
        /* pass */
        if (((c >= 65LL) && (c <= 90LL))) {
            /* pass */
            return false;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c = ((long long)((*(p + i))));
    }
    /* pass */
    return true;
}

__attribute__((hot)) char* Str_slice(char* s, long long start, long long end) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    long long real_s = start;
    /* pass */
    long long real_e = end;
    /* pass */
    if ((real_s < 0LL)) {
        /* pass */
        real_s = 0LL;
    }
    /* pass */
    if ((real_e > slen)) {
        /* pass */
        real_e = slen;
    }
    /* pass */
    if ((real_s >= real_e)) {
        /* pass */
        return "";
    }
    /* pass */
    long long sz = (real_e - real_s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((sz + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = real_s;
    /* pass */
    while ((i < real_e)) {
        /* pass */
        StringBuilder_append_char(sb, ((long long)((*(p + i)))));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_repeat(char* s, long long n) {
    /* pass */
    if ((n <= 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(((Str_len(s) * n) + 1LL));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        StringBuilder_append(sb, s);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_reverse(char* s) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((slen + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = (slen - 1LL);
    /* pass */
    while ((i >= 0LL)) {
        /* pass */
        StringBuilder_append_char(sb, ((long long)((*(p + i)))));
        /* pass */
        i = (i - 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_to_upper(char* s) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((slen + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long ch = ((long long)((*(p + i))));
        /* pass */
        if (((ch >= 97LL) && (ch <= 122LL))) {
            /* pass */
            ch = (ch - 32LL);
        }
        /* pass */
        StringBuilder_append_char(sb, ch);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_to_lower(char* s) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((slen + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long ch = ((long long)((*(p + i))));
        /* pass */
        if (((ch >= 65LL) && (ch <= 90LL))) {
            /* pass */
            ch = (ch + 32LL);
        }
        /* pass */
        StringBuilder_append_char(sb, ch);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_capitalize(char* s) {
    /* pass */
    char* low = Str_to_lower(s);
    /* pass */
    if ((Str_len(low) == 0LL)) {
        /* pass */
        return low;
    }
    /* pass */
    char* p = ((char*)(low));
    /* pass */
    long long ch = ((long long)((*(p + 0LL))));
    /* pass */
    if (((ch >= 97LL) && (ch <= 122LL))) {
        /* pass */
        return _tr_str_concat(Str_to_upper(Str_slice(low, 0LL, 1LL)), Str_slice(low, 1LL, Str_len(low)));
    }
    /* pass */
    return low;
}

__attribute__((hot)) char* Str_title(char* s) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((slen + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long prev = 32LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long ch = ((long long)((*(p + i))));
        /* pass */
        if ((((prev == 32LL) && (ch >= 97LL)) && (ch <= 122LL))) {
            /* pass */
            StringBuilder_append_char(sb, (ch - 32LL));
        } else if ((((prev != 32LL) && (ch >= 65LL)) && (ch <= 90LL))) {
            /* pass */
            StringBuilder_append_char(sb, (ch + 32LL));
        } else {
            /* pass */
            StringBuilder_append_char(sb, ch);
        }
        /* pass */
        prev = ch;
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_trim_left(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while (true) {
        /* pass */
        long long c = ((long long)((*(p + i))));
        /* pass */
        if (((c == 0LL) || ((((c != 32LL) && (c != 9LL)) && (c != 10LL)) && (c != 13LL)))) {
            /* pass */
            break;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return Str_slice(s, i, Str_len(s));
}

__attribute__((hot)) char* Str_trim_right(char* s) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = (slen - 1LL);
    /* pass */
    while ((i >= 0LL)) {
        /* pass */
        long long c = ((long long)((*(p + i))));
        /* pass */
        if (((((c != 32LL) && (c != 9LL)) && (c != 10LL)) && (c != 13LL))) {
            /* pass */
            break;
        }
        /* pass */
        i = (i - 1LL);
    }
    /* pass */
    return Str_slice(s, 0LL, (i + 1LL));
}

__attribute__((hot)) char* Str_trim(char* s) {
    /* pass */
    return Str_trim_left(Str_trim_right(s));
}

__attribute__((hot)) long long Str_char_at(char* s, long long i) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    return ((long long)((*(p + i))));
}

__attribute__((hot)) char* Str_lpad(char* s, long long width, long long pad_char) {
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

__attribute__((hot)) char* Str_rpad(char* s, long long width, long long pad_char) {
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

__attribute__((hot)) char* Str_center(char* s, long long width) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    if ((slen >= width)) {
        /* pass */
        return s;
    }
    /* pass */
    long long total = (width - slen);
    /* pass */
    long long left = (total / 2LL);
    /* pass */
    long long right = (total - left);
    /* pass */
    StringBuilder* sb = StringBuilder_init((width + 1LL));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < left)) {
        /* pass */
        StringBuilder_append_char(sb, 32LL);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    StringBuilder_append(sb, s);
    /* pass */
    i = 0LL;
    /* pass */
    while ((i < right)) {
        /* pass */
        StringBuilder_append_char(sb, 32LL);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) long long Str_index_of(char* s, char* sub) {
    /* pass */
    long long sl = Str_len(s);
    /* pass */
    long long subl = Str_len(sub);
    /* pass */
    if ((subl == 0LL)) {
        /* pass */
        return 0LL;
    }
    /* pass */
    if ((subl > sl)) {
        /* pass */
        return (-1LL);
    }
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    char* subp = ((char*)(sub));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i <= (sl - subl))) {
        /* pass */
        long long j = 0LL;
        /* pass */
        bool found = true;
        /* pass */
        while ((j < subl)) {
            /* pass */
            if ((((long long)((*(sp + (i + j))))) != ((long long)((*(subp + j)))))) {
                /* pass */
                found = false;
                /* pass */
                j = subl;
            }
            /* pass */
            j = (j + 1LL);
        }
        /* pass */
        if (found) {
            /* pass */
            return i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return (-1LL);
}

__attribute__((hot)) long long Str_last_index_of(char* s, char* sub) {
    /* pass */
    long long sl = Str_len(s);
    /* pass */
    long long subl = Str_len(sub);
    /* pass */
    if ((subl == 0LL)) {
        /* pass */
        return sl;
    }
    /* pass */
    if ((subl > sl)) {
        /* pass */
        return (-1LL);
    }
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    char* subp = ((char*)(sub));
    /* pass */
    long long i = (sl - subl);
    /* pass */
    while ((i >= 0LL)) {
        /* pass */
        long long j = 0LL;
        /* pass */
        bool found = true;
        /* pass */
        while ((j < subl)) {
            /* pass */
            if ((((long long)((*(sp + (i + j))))) != ((long long)((*(subp + j)))))) {
                /* pass */
                found = false;
                /* pass */
                j = subl;
            }
            /* pass */
            j = (j + 1LL);
        }
        /* pass */
        if (found) {
            /* pass */
            return i;
        }
        /* pass */
        i = (i - 1LL);
    }
    /* pass */
    return (-1LL);
}

__attribute__((hot)) long long Str__tr_fn_count(char* s, char* sub) {
    /* pass */
    long long subl = Str_len(sub);
    /* pass */
    if ((subl == 0LL)) {
        /* pass */
        return 0LL;
    }
    /* pass */
    long long n = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while (true) {
        /* pass */
        long long pos = Str_index_of(Str_slice(s, i, Str_len(s)), sub);
        /* pass */
        if ((pos < 0LL)) {
            /* pass */
            break;
        }
        /* pass */
        n = (n + 1LL);
        /* pass */
        i = ((i + pos) + subl);
    }
    /* pass */
    return n;
}

__attribute__((hot)) List_str* Str_split(char* s, char* sep) {
    /* pass */
    return _tr_str_split(s, sep);
}

__attribute__((hot)) List_str* Str_split_to_vec(char* s, char* sep) {
    /* pass */
    List_str* out = (void*)List_str_new();
    /* pass */
    long long sl = Str_len(s);
    /* pass */
    long long sepl = Str_len(sep);
    /* pass */
    if ((sepl == 0LL)) {
        /* pass */
        long long i = 0LL;
        /* pass */
        while ((i < sl)) {
            /* pass */
            List_str_append(out, Str_slice(s, i, (i + 1LL)));
            /* pass */
            i = (i + 1LL);
        }
        /* pass */
        return out;
    }
    /* pass */
    long long start = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i <= (sl - sepl))) {
        /* pass */
        long long j = 0LL;
        /* pass */
        bool match_ = true;
        /* pass */
        while ((j < sepl)) {
            /* pass */
            if ((Str_char_at(s, (i + j)) != Str_char_at(sep, j))) {
                /* pass */
                match_ = false;
                /* pass */
                j = sepl;
            }
            /* pass */
            j = (j + 1LL);
        }
        /* pass */
        if (match_) {
            /* pass */
            List_str_append(out, Str_slice(s, start, i));
            /* pass */
            start = (i + sepl);
            /* pass */
            i = start;
        } else {
            /* pass */
            i = (i + 1LL);
        }
    }
    /* pass */
    List_str_append(out, Str_slice(s, start, sl));
    /* pass */
    return out;
}

__attribute__((hot)) char* Str_join(List_str* parts, char* sep) {
    /* pass */
    return _tr_str_join(parts, sep);
}

__attribute__((hot)) char* Str_replace(char* s, char* old, char* new_) {
    /* pass */
    StringBuilder* result = StringBuilder_init((Str_len(s) + 1LL));
    /* pass */
    long long oldl = Str_len(old);
    /* pass */
    if ((oldl == 0LL)) {
        /* pass */
        return s;
    }
    /* pass */
    long long sl = Str_len(s);
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < sl)) {
        /* pass */
        bool found = true;
        /* pass */
        if (((i + oldl) > sl)) {
            /* pass */
            found = false;
        }
        /* pass */
        if (found) {
            /* pass */
            long long j = 0LL;
            /* pass */
            while ((j < oldl)) {
                /* pass */
                if ((((long long)((*(sp + (i + j))))) != ((long long)((*(((char*)(old)) + j)))))) {
                    /* pass */
                    found = false;
                    /* pass */
                    j = oldl;
                }
                /* pass */
                j = (j + 1LL);
            }
        }
        /* pass */
        if (found) {
            /* pass */
            StringBuilder_append(result, new_);
            /* pass */
            i = (i + oldl);
        } else {
            /* pass */
            StringBuilder_append_char(result, ((long long)((*(sp + i)))));
            /* pass */
            i = (i + 1LL);
        }
    }
    /* pass */
    return StringBuilder_to_owned(result);
}

__attribute__((hot)) char* Str_replace_first(char* s, char* old, char* new_) {
    /* pass */
    long long pos = Str_index_of(s, old);
    /* pass */
    if ((pos < 0LL)) {
        /* pass */
        return s;
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init((Str_len(s) + Str_len(new_)));
    /* pass */
    StringBuilder_append(sb, Str_slice(s, 0LL, pos));
    /* pass */
    StringBuilder_append(sb, new_);
    /* pass */
    StringBuilder_append(sb, Str_slice(s, (pos + Str_len(old)), Str_len(s)));
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) char* Str_format(char* template, List_str* values) {
    /* pass */
    char* result = template;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < values->len)) {
        /* pass */
        result = Str_replace_first(result, "{}", List_str_get(values, i));
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return result;
}

__attribute__((hot)) long long Str_parse_int(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    bool neg = false;
    /* pass */
    long long c = ((long long)((*(p + 0LL))));
    /* pass */
    if ((c == 45LL)) {
        /* pass */
        neg = true;
        /* pass */
        i = 1LL;
    } else if ((c == 43LL)) {
        /* pass */
        i = 1LL;
    }
    /* pass */
    long long result = 0LL;
    /* pass */
    long long c2 = ((long long)((*(p + i))));
    /* pass */
    while (((c2 >= 48LL) && (c2 <= 57LL))) {
        /* pass */
        result = ((result * 10LL) + (c2 - 48LL));
        /* pass */
        i = (i + 1LL);
        /* pass */
        c2 = ((long long)((*(p + i))));
    }
    /* pass */
    if (neg) {
        /* pass */
        return (0LL - result);
    }
    /* pass */
    return result;
}

__attribute__((hot)) double Str_parse_float(char* s) {
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    bool neg = false;
    /* pass */
    long long c = ((long long)((*(p + 0LL))));
    /* pass */
    if ((c == 45LL)) {
        /* pass */
        neg = true;
        /* pass */
        i = 1LL;
    } else if ((c == 43LL)) {
        /* pass */
        i = 1LL;
    }
    /* pass */
    long long int_part = 0LL;
    /* pass */
    long long frac_part = 0LL;
    /* pass */
    long long frac_div = 1LL;
    /* pass */
    bool in_frac = false;
    /* pass */
    long long c2 = ((long long)((*(p + i))));
    /* pass */
    while ((c2 != 0LL)) {
        /* pass */
        if (((c2 >= 48LL) && (c2 <= 57LL))) {
            /* pass */
            if ((!in_frac)) {
                /* pass */
                int_part = ((int_part * 10LL) + (c2 - 48LL));
            } else {
                /* pass */
                frac_part = ((frac_part * 10LL) + (c2 - 48LL));
                /* pass */
                frac_div = (frac_div * 10LL);
            }
        } else if ((c2 == 46LL)) {
            /* pass */
            in_frac = true;
        } else {
            /* pass */
            break;
        }
        /* pass */
        i = (i + 1LL);
        /* pass */
        c2 = ((long long)((*(p + i))));
    }
    /* pass */
    double result = (((double)(int_part)) + (((double)(frac_part)) / ((double)(frac_div))));
    /* pass */
    if (neg) {
        /* pass */
        return (0 - result);
    }
    /* pass */
    return result;
}

__attribute__((hot)) bool Str_parse_bool(char* s) {
    /* pass */
    if (Str_eq(s, "true")) {
        /* pass */
        return true;
    }
    /* pass */
    if (Str_eq(s, "1")) {
        /* pass */
        return true;
    }
    /* pass */
    if (Str_eq(s, "yes")) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) List_str* Str_lines(char* s) {
    /* pass */
    List_str* out = (void*)List_str_new();
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    long long start = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long c = ((long long)((*(sp + i))));
        /* pass */
        if ((c == 10LL)) {
            /* pass */
            List_str_append(out, Str_slice(s, start, i));
            /* pass */
            start = (i + 1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((start < slen)) {
        /* pass */
        List_str_append(out, Str_slice(s, start, slen));
    }
    /* pass */
    return out;
}

__attribute__((hot)) List_str* Str_words(char* s) {
    /* pass */
    List_str* out = (void*)List_str_new();
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    char* sp = ((char*)(s));
    /* pass */
    long long start = (-1LL);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long c = ((long long)((*(sp + i))));
        /* pass */
        bool ws = ((((c == 32LL) || (c == 9LL)) || (c == 10LL)) || (c == 13LL));
        /* pass */
        if (((!ws) && (start < 0LL))) {
            /* pass */
            start = i;
        } else if ((ws && (start >= 0LL))) {
            /* pass */
            List_str_append(out, Str_slice(s, start, i));
            /* pass */
            start = (-1LL);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((start >= 0LL)) {
        /* pass */
        List_str_append(out, Str_slice(s, start, slen));
    }
    /* pass */
    return out;
}

__attribute__((hot)) char* Str_strip_prefix(char* s, char* prefix) {
    /* pass */
    if (Str_starts_with(s, prefix)) {
        /* pass */
        return Str_slice(s, Str_len(prefix), Str_len(s));
    }
    /* pass */
    return s;
}

__attribute__((hot)) char* Str_strip_suffix(char* s, char* suffix) {
    /* pass */
    if (Str_ends_with(s, suffix)) {
        /* pass */
        return Str_slice(s, 0LL, (Str_len(s) - Str_len(suffix)));
    }
    /* pass */
    return s;
}

__attribute__((hot)) char* Str_remove_char(char* s, long long c) {
    /* pass */
    long long slen = Str_len(s);
    /* pass */
    StringBuilder* sb = StringBuilder_init((slen + 1LL));
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < slen)) {
        /* pass */
        long long ch = ((long long)((*(p + i))));
        /* pass */
        if ((ch != c)) {
            /* pass */
            StringBuilder_append_char(sb, ch);
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

