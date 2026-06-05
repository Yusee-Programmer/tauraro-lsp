#include "../../../tauraro_types.h"


__attribute__((malloc,returns_nonnull,hot)) Path* Path_init(char* p) {
    /* pass */
    Path* path = ((Path*)_tr_checked_alloc(sizeof(Path)));
    /* pass */
    path->value = p;
    /* pass */
    return path;
}

__attribute__((hot)) char* Path_normalize(Path* self) {
    /* pass */
    long long n = 0LL;
    /* pass */
    char* ptr = ((char*)(self->value));
    /* pass */
    while ((((long long)((*(ptr + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    __auto_type buf = _tr_str_slice(self->value, 0LL, n);
    /* pass */
    char* bp = ((char*)(buf));
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        if ((((long long)((*(bp + i)))) == 92LL)) {
            /* pass */
            (*(bp + i) = ((char)(47LL)));
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    return buf;
}

__attribute__((hot)) char* Path_join(Path* self, char* other) {
    /* pass */
    long long an = 0LL;
    /* pass */
    char* ap = ((char*)(self->value));
    /* pass */
    while ((((long long)((*(ap + an)))) != 0LL)) {
        /* pass */
        an = (an + 1LL);
    }
    /* pass */
    if ((an == 0LL)) {
        /* pass */
        return other;
    }
    /* pass */
    long long bn = 0LL;
    /* pass */
    char* bp = ((char*)(other));
    /* pass */
    while ((((long long)((*(bp + bn)))) != 0LL)) {
        /* pass */
        bn = (bn + 1LL);
    }
    /* pass */
    if ((bn == 0LL)) {
        /* pass */
        return self->value;
    }
    /* pass */
    long long last_a = ((long long)((*(ap + (an - 1LL)))));
    /* pass */
    long long first_b = ((long long)((*(bp + 0LL))));
    /* pass */
    if ((((last_a == 47LL) || (last_a == 92LL)) && ((first_b == 47LL) || (first_b == 92LL)))) {
        /* pass */
        return _tr_str_concat(self->value, _tr_str_slice(other, 1LL, bn));
    }
    /* pass */
    if (((last_a == 47LL) || (last_a == 92LL))) {
        /* pass */
        return _tr_str_concat(self->value, other);
    }
    /* pass */
    if (((first_b == 47LL) || (first_b == 92LL))) {
        /* pass */
        return _tr_str_concat(self->value, other);
    }
    /* pass */
    return _tr_str_concat(_tr_str_concat(self->value, "/"), other);
}

__attribute__((hot)) char* Path_dirname(Path* self) {
    /* pass */
    long long n = 0LL;
    /* pass */
    char* ptr = ((char*)(self->value));
    /* pass */
    while ((((long long)((*(ptr + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    long long last_sep = (-1LL);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = ((long long)((*(ptr + i))));
        /* pass */
        if (((c == 47LL) || (c == 92LL))) {
            /* pass */
            last_sep = i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((last_sep < 0LL)) {
        /* pass */
        return "./";
    }
    /* pass */
    return _tr_str_slice(self->value, 0LL, (last_sep + 1LL));
}

__attribute__((hot)) char* Path_basename(Path* self) {
    /* pass */
    long long n = 0LL;
    /* pass */
    char* ptr = ((char*)(self->value));
    /* pass */
    while ((((long long)((*(ptr + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    long long last_sep = (-1LL);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        long long c = ((long long)((*(ptr + i))));
        /* pass */
        if (((c == 47LL) || (c == 92LL))) {
            /* pass */
            last_sep = i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((last_sep < 0LL)) {
        /* pass */
        return self->value;
    }
    /* pass */
    return _tr_str_slice(self->value, (last_sep + 1LL), n);
}

__attribute__((hot)) char* Path_extension(Path* self) {
    /* pass */
    char* base = Path_basename(self);
    /* pass */
    long long n = 0LL;
    /* pass */
    char* ptr = ((char*)(base));
    /* pass */
    while ((((long long)((*(ptr + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    long long last_dot = (-1LL);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        if ((((long long)((*(ptr + i)))) == 46LL)) {
            /* pass */
            last_dot = i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((last_dot <= 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    return _tr_str_slice(base, last_dot, n);
}

__attribute__((hot)) char* Path_strip_extension(Path* self) {
    /* pass */
    long long n = 0LL;
    /* pass */
    char* ptr = ((char*)(self->value));
    /* pass */
    while ((((long long)((*(ptr + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    long long last_dot = (-1LL);
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        if ((((long long)((*(ptr + i)))) == 46LL)) {
            /* pass */
            last_dot = i;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if ((last_dot <= 0LL)) {
        /* pass */
        return self->value;
    }
    /* pass */
    return _tr_str_slice(self->value, 0LL, last_dot);
}

__attribute__((hot)) bool Path_is_absolute(Path* self) {
    /* pass */
    char* ptr = ((char*)(self->value));
    /* pass */
    long long c0 = ((long long)((*(ptr + 0LL))));
    /* pass */
    if ((c0 == 47LL)) {
        /* pass */
        return true;
    }
    /* pass */
    long long c1 = ((long long)((*(ptr + 1LL))));
    /* pass */
    if ((c1 == 58LL)) {
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) char* Path_to_str(Path* self) {
    /* pass */
    return self->value;
}

