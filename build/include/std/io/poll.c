#include "../../../tauraro_types.h"


__attribute__((hot)) bool IOEvent_readable(IOEvent* self) {
    /* pass */
    return ((self->events & 1LL) != 0LL);
}

__attribute__((hot)) bool IOEvent_writable(IOEvent* self) {
    /* pass */
    return ((self->events & 2LL) != 0LL);
}

__attribute__((hot)) bool IOEvent_error(IOEvent* self) {
    /* pass */
    return ((self->events & 4LL) != 0LL);
}

__attribute__((hot)) bool IOEvent_hangup(IOEvent* self) {
    /* pass */
    return ((self->events & 8LL) != 0LL);
}

__attribute__((hot)) long long IOPoll_POLLIN() {
    /* pass */
    return 1LL;
}

__attribute__((hot)) long long IOPoll_POLLOUT() {
    /* pass */
    return 2LL;
}

__attribute__((hot)) long long IOPoll_POLLERR() {
    /* pass */
    return 4LL;
}

__attribute__((hot)) long long IOPoll_POLLHUP() {
    /* pass */
    return 8LL;
}

__attribute__((hot)) IOPoll* IOPoll__tr_fn_new() {
    /* pass */
    IOPoll* p = ((IOPoll*)_tr_checked_alloc(sizeof(IOPoll)));
    /* pass */
    p->handle = _tr_iopoll_create_h();
    /* pass */
    return p;
}

__attribute__((hot)) bool IOPoll_add(IOPoll* self, long long fd, long long events, long long userdata) {
    /* pass */
    return (_tr_iopoll_add_h(self->handle, fd, events, userdata) == 0LL);
}

__attribute__((hot)) bool IOPoll_modify(IOPoll* self, long long fd, long long events, long long userdata) {
    /* pass */
    return (_tr_iopoll_mod_h(self->handle, fd, events, userdata) == 0LL);
}

__attribute__((hot)) bool IOPoll__tr_fn_remove(IOPoll* self, long long fd) {
    /* pass */
    return (_tr_iopoll_del_h(self->handle, fd) == 0LL);
}

__attribute__((hot)) List_ptr* IOPoll_wait(IOPoll* self, long long timeout_ms) {
    /* pass */
    long long ev_size = 16LL;
    /* pass */
    long long max_evs = 64LL;
    /* pass */
    char* raw_buf = _tr_c_malloc((ev_size * max_evs));
    /* pass */
    long long n = _tr_iopoll_wait_raw(self->handle, raw_buf, max_evs, timeout_ms);
    /* pass */
    List_ptr* result = (void*)List_ptr_new();
    /* pass */
    long long i = 0LL;
    /* pass */
    while ((i < n)) {
        /* pass */
        IOEvent* ev = ((IOEvent*)_tr_checked_alloc(sizeof(IOEvent)));
        /* pass */
        /* unsafe block */
        /* pass */
        char* base = (raw_buf + (i * ev_size));
        /* pass */
        ev->fd = ((long long)((*(base + 0LL))));
        /* pass */
        ev->events = ((long long)((*(base + 4LL))));
        /* pass */
        ev->userdata = ((long long)((*(base + 8LL))));
        /* pass */
        List_ptr_append(result, ev);
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    _tr_free(raw_buf);
    /* pass */
    return result;
}

__attribute__((hot)) void IOPoll_destroy(IOPoll* self) {
    /* pass */
    _tr_iopoll_destroy_h(self->handle);
    /* pass */
    self->handle = ((char*)(0LL));
}

