#include "../../../tauraro_types.h"


__attribute__((hot)) BufReader* BufReader__tr_fn_open(char* path, long long buf_size) {
    /* pass */
    BufReader* r = ((BufReader*)_tr_checked_alloc(sizeof(BufReader)));
    /* pass */
    r->path = path;
    /* pass */
    r->_cap = buf_size;
    /* pass */
    r->_pos = 0LL;
    /* pass */
    r->_filled = 0LL;
    /* pass */
    r->_fp = _tr_c_fopen(path, "rb");
    /* pass */
    r->open = (((long long)(r->_fp)) != 0LL);
    /* pass */
    r->_buf = _tr_c_malloc((buf_size + 1LL));
    /* pass */
    return r;
}

__attribute__((hot)) char* BufReader_read_all(BufReader* self) {
    /* pass */
    if ((!self->open)) {
        /* pass */
        return "";
    }
    /* pass */
    _tr_c_fseek(self->_fp, 0LL, 2LL);
    /* pass */
    long long size = _tr_c_ftell(self->_fp);
    /* pass */
    _tr_c_fseek(self->_fp, 0LL, 0LL);
    /* pass */
    if ((size <= 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    char* buf = _tr_c_malloc((size + 1LL));
    /* pass */
    _tr_c_fread(buf, 1LL, size, self->_fp);
    /* pass */
    /* unsafe block */
    /* pass */
    (*(buf + size) = '\0');
    /* pass */
    return ((char*)(buf));
}

__attribute__((hot)) List_str* BufReader_readlines(BufReader* self) {
    /* pass */
    char* content = BufReader_read_all(self);
    /* pass */
    return Str_split(content, "\n");
}

__attribute__((hot)) char* BufReader_readline(BufReader* self) {
    /* pass */
    if ((!self->open)) {
        /* pass */
        return "";
    }
    /* pass */
    StringBuilder* sb = StringBuilder_init(128LL);
    /* pass */
    bool done = false;
    /* pass */
    while ((!done)) {
        /* pass */
        if ((self->_pos >= self->_filled)) {
            /* pass */
            self->_filled = _tr_c_fread(self->_buf, 1LL, self->_cap, self->_fp);
            /* pass */
            self->_pos = 0LL;
            /* pass */
            if ((self->_filled <= 0LL)) {
                /* pass */
                done = true;
            }
        }
        /* pass */
        if ((!done)) {
            /* pass */
            long long ch = ((long long)((*(self->_buf + self->_pos))));
            /* pass */
            self->_pos = (self->_pos + 1LL);
            /* pass */
            if ((ch == 10LL)) {
                /* pass */
                done = true;
            } else if ((ch == 13LL)) {
                /* pass */
                long long n = self->_pos;
                /* pass */
                if ((n < self->_filled)) {
                    /* pass */
                    long long next = ((long long)((*(self->_buf + n))));
                    /* pass */
                    if ((next == 10LL)) {
                        /* pass */
                        self->_pos = (n + 1LL);
                    }
                }
                /* pass */
                done = true;
            } else {
                /* pass */
                StringBuilder_append_char(sb, ch);
            }
        }
    }
    /* pass */
    return StringBuilder_to_owned(sb);
}

__attribute__((hot)) void BufReader__tr_fn_close(BufReader* self) {
    /* pass */
    if (self->open) {
        /* pass */
        _tr_c_fclose(self->_fp);
        /* pass */
        self->open = false;
    }
}

__attribute__((hot)) BufWriter* BufWriter__tr_fn_open(char* path, long long buf_size) {
    /* pass */
    BufWriter* w = ((BufWriter*)_tr_checked_alloc(sizeof(BufWriter)));
    /* pass */
    w->path = path;
    /* pass */
    w->_cap = buf_size;
    /* pass */
    w->_fp = _tr_c_fopen(path, "wb");
    /* pass */
    w->open = (((long long)(w->_fp)) != 0LL);
    /* pass */
    w->_buf = StringBuilder_init(buf_size);
    /* pass */
    return w;
}

__attribute__((hot)) BufWriter* BufWriter_open_append(char* path, long long buf_size) {
    /* pass */
    BufWriter* w = ((BufWriter*)_tr_checked_alloc(sizeof(BufWriter)));
    /* pass */
    w->path = path;
    /* pass */
    w->_cap = buf_size;
    /* pass */
    w->_fp = _tr_c_fopen(path, "ab");
    /* pass */
    w->open = (((long long)(w->_fp)) != 0LL);
    /* pass */
    w->_buf = StringBuilder_init(buf_size);
    /* pass */
    return w;
}

__attribute__((hot)) void BufWriter__tr_fn_write(BufWriter* self, char* s) {
    /* pass */
    if ((!self->open)) {
        /* pass */
        return;
    }
    /* pass */
    StringBuilder_append(self->_buf, s);
    /* pass */
    if (((self->_buf->buf->len) >= self->_cap)) {
        /* pass */
        BufWriter_flush(self);
    }
}

__attribute__((hot)) void BufWriter_writeln(BufWriter* self, char* s) {
    /* pass */
    BufWriter__tr_fn_write(self, s);
    /* pass */
    BufWriter__tr_fn_write(self, "\n");
}

__attribute__((hot)) void BufWriter_flush(BufWriter* self) {
    /* pass */
    if ((!self->open)) {
        /* pass */
        return;
    }
    /* pass */
    long long n = (self->_buf->buf->len);
    /* pass */
    if ((n > 0LL)) {
        /* pass */
        char* content = StringBuilder_to_owned(self->_buf);
        /* pass */
        char* p = ((char*)(content));
        /* pass */
        _tr_c_fwrite(p, 1LL, n, self->_fp);
    }
    /* pass */
    StringBuilder_clear(self->_buf);
}

__attribute__((hot)) void BufWriter__tr_fn_close(BufWriter* self) {
    /* pass */
    if (self->open) {
        /* pass */
        BufWriter_flush(self);
        /* pass */
        _tr_c_fclose(self->_fp);
        /* pass */
        self->open = false;
    }
}

