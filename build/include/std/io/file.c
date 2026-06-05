#include "../../../tauraro_types.h"


__attribute__((malloc,returns_nonnull,hot)) File* File_init(char* path, char* mode) {
    /* pass */
    File* f = ((File*)_tr_checked_alloc(sizeof(File)));
    /* pass */
    f->path = path;
    /* pass */
    f->mode = mode;
    /* pass */
    f->content = "";
    /* pass */
    f->_fp = _tr_c_fopen(path, mode);
    /* pass */
    return f;
}

__attribute__((hot)) bool File_is_open(File* self) {
    /* pass */
    return (((long long)(self->_fp)) != 0LL);
}

__attribute__((hot)) char* File__tr_fn_read(File* self) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
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
    self->content = ((char*)(buf));
    /* pass */
    return self->content;
}

__attribute__((hot)) List_str* File_readlines(File* self) {
    /* pass */
    char* text = File__tr_fn_read(self);
    /* pass */
    return Str_split(text, "\n");
}

__attribute__((hot)) void File__tr_fn_write(File* self, char* data) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
        /* pass */
        return;
    }
    /* pass */
    char* p = ((char*)(data));
    /* pass */
    long long n = 0LL;
    /* pass */
    while ((((long long)((*(p + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    _tr_c_fwrite(p, 1LL, n, self->_fp);
    /* pass */
    self->content = data;
}

__attribute__((hot)) void File_append(File* self, char* data) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
        /* pass */
        return;
    }
    /* pass */
    char* p = ((char*)(data));
    /* pass */
    long long n = 0LL;
    /* pass */
    while ((((long long)((*(p + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    _tr_c_fwrite(p, 1LL, n, self->_fp);
    /* pass */
    self->content = _tr_str_concat(self->content, data);
}

__attribute__((hot)) void File_writeln(File* self, char* line) {
    /* pass */
    File__tr_fn_write(self, line);
    /* pass */
    File__tr_fn_write(self, "\n");
}

__attribute__((hot)) void File_seek(File* self, long long offset, long long whence) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
        /* pass */
        return;
    }
    /* pass */
    _tr_c_fseek(self->_fp, offset, whence);
}

__attribute__((hot)) long long File_tell(File* self) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
        /* pass */
        return (-1LL);
    }
    /* pass */
    return _tr_c_ftell(self->_fp);
}

__attribute__((hot)) long long File_size(File* self) {
    /* pass */
    if ((((long long)(self->_fp)) == 0LL)) {
        /* pass */
        return (-1LL);
    }
    /* pass */
    long long pos = _tr_c_ftell(self->_fp);
    /* pass */
    _tr_c_fseek(self->_fp, 0LL, 2LL);
    /* pass */
    long long sz = _tr_c_ftell(self->_fp);
    /* pass */
    _tr_c_fseek(self->_fp, pos, 0LL);
    /* pass */
    return sz;
}

__attribute__((hot)) void File__tr_fn_close(File* self) {
    /* pass */
    if ((((long long)(self->_fp)) != 0LL)) {
        /* pass */
        _tr_c_fclose(self->_fp);
    }
}

__attribute__((hot)) bool File_exists(File* self) {
    /* pass */
    char* fp = _tr_c_fopen(self->path, "rb");
    /* pass */
    if ((((long long)(fp)) != 0LL)) {
        /* pass */
        _tr_c_fclose(fp);
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) char* File_read_text(char* path) {
    /* pass */
    char* fp = _tr_c_fopen(path, "rb");
    /* pass */
    if ((((long long)(fp)) == 0LL)) {
        /* pass */
        return "";
    }
    /* pass */
    _tr_c_fseek(fp, 0LL, 2LL);
    /* pass */
    long long size = _tr_c_ftell(fp);
    /* pass */
    _tr_c_fseek(fp, 0LL, 0LL);
    /* pass */
    if ((size <= 0LL)) {
        /* pass */
        _tr_c_fclose(fp);
        /* pass */
        return "";
    }
    /* pass */
    char* buf = _tr_c_malloc((size + 1LL));
    /* pass */
    _tr_c_fread(buf, 1LL, size, fp);
    /* pass */
    /* unsafe block */
    /* pass */
    (*(buf + size) = '\0');
    /* pass */
    _tr_c_fclose(fp);
    /* pass */
    return ((char*)(buf));
}

__attribute__((hot)) List_str* File_lines(char* path) {
    /* pass */
    char* text = File_read_text(path);
    /* pass */
    return Str_split(text, "\n");
}

__attribute__((hot)) bool File_write_text(char* path, char* data) {
    /* pass */
    char* fp = _tr_c_fopen(path, "wb");
    /* pass */
    if ((((long long)(fp)) == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    char* p = ((char*)(data));
    /* pass */
    long long n = 0LL;
    /* pass */
    while ((((long long)((*(p + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    _tr_c_fwrite(p, 1LL, n, fp);
    /* pass */
    _tr_c_fclose(fp);
    /* pass */
    return true;
}

__attribute__((hot)) bool File_append_text(char* path, char* data) {
    /* pass */
    char* fp = _tr_c_fopen(path, "ab");
    /* pass */
    if ((((long long)(fp)) == 0LL)) {
        /* pass */
        return false;
    }
    /* pass */
    char* p = ((char*)(data));
    /* pass */
    long long n = 0LL;
    /* pass */
    while ((((long long)((*(p + n)))) != 0LL)) {
        /* pass */
        n = (n + 1LL);
    }
    /* pass */
    _tr_c_fwrite(p, 1LL, n, fp);
    /* pass */
    _tr_c_fclose(fp);
    /* pass */
    return true;
}

__attribute__((hot)) bool File_file_exists(char* path) {
    /* pass */
    char* fp = _tr_c_fopen(path, "rb");
    /* pass */
    if ((((long long)(fp)) != 0LL)) {
        /* pass */
        _tr_c_fclose(fp);
        /* pass */
        return true;
    }
    /* pass */
    return false;
}

__attribute__((hot)) long long File_file_size(char* path) {
    /* pass */
    char* fp = _tr_c_fopen(path, "rb");
    /* pass */
    if ((((long long)(fp)) == 0LL)) {
        /* pass */
        return (-1LL);
    }
    /* pass */
    _tr_c_fseek(fp, 0LL, 2LL);
    /* pass */
    long long sz = _tr_c_ftell(fp);
    /* pass */
    _tr_c_fclose(fp);
    /* pass */
    return sz;
}

__attribute__((hot)) char* read_file(char* path) {
    /* pass */
    return File_read_text(path);
}

__attribute__((hot)) bool write_file(char* path, char* data) {
    /* pass */
    return File_write_text(path, data);
}

__attribute__((hot)) bool append_file(char* path, char* data) {
    /* pass */
    return File_append_text(path, data);
}

__attribute__((hot)) bool file_exists(char* path) {
    /* pass */
    return File_file_exists(path);
}

