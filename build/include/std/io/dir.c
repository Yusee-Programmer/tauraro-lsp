#include "../../../tauraro_types.h"


__attribute__((malloc,returns_nonnull,hot)) Dir* Dir_init(char* path) {
    /* pass */
    Dir* d = ((Dir*)_tr_checked_alloc(sizeof(Dir)));
    /* pass */
    d->path = path;
    /* pass */
    return d;
}

__attribute__((hot)) bool Dir_make(Dir* self) {
    /* pass */
    if (_tr_dir_exists(self->path)) {
        /* pass */
        return true;
    }
    /* pass */
    return (_tr_mkdir(self->path) == 0LL);
}

__attribute__((hot)) bool Dir__tr_fn_remove(Dir* self) {
    /* pass */
    return (_tr_rmdir(self->path) == 0LL);
}

__attribute__((hot)) bool Dir_exists(Dir* self) {
    /* pass */
    return _tr_dir_exists(self->path);
}

__attribute__((hot)) List_str* Dir_list(Dir* self) {
    /* pass */
    List_str* entries = (void*)List_str_new();
    /* pass */
    char* handle = _tr_opendir(self->path);
    /* pass */
    if ((((long long)(handle)) == 0LL)) {
        /* pass */
        return entries;
    }
    /* pass */
    while (true) {
        /* pass */
        char* name = _tr_readdir(handle);
        /* pass */
        if ((strcmp((char*)name, (char*)"") == 0)) {
            /* pass */
            break;
        }
        /* pass */
        if (((strcmp((char*)name, (char*)".") != 0) && (strcmp((char*)name, (char*)"..") != 0))) {
            /* pass */
            List_str_append(entries, name);
        }
    }
    /* pass */
    _tr_closedir(handle);
    /* pass */
    return entries;
}

__attribute__((hot)) long long Dir__tr_fn_count(Dir* self) {
    /* pass */
    List_str* entries = Dir_list(self);
    /* pass */
    return entries->len;
}

