#include "../../../tauraro_types.h"


__attribute__((hot)) EventLoop* EventLoop__tr_fn_new() {
    /* pass */
    EventLoop* el = ((EventLoop*)_tr_checked_alloc(sizeof(EventLoop)));
    /* pass */
    el->poll = IOPoll__tr_fn_new();
    /* pass */
    el->running = true;
    /* pass */
    el->iter_count = 0LL;
    /* pass */
    el->start_ms = _tr_time_ms();
    /* pass */
    return el;
}

__attribute__((hot)) bool EventLoop_add_fd(EventLoop* self, long long fd, long long events, long long userdata) {
    /* pass */
    return IOPoll_add(self->poll, fd, events, userdata);
}

__attribute__((hot)) bool EventLoop_modify_fd(EventLoop* self, long long fd, long long events, long long userdata) {
    /* pass */
    return IOPoll_modify(self->poll, fd, events, userdata);
}

__attribute__((hot)) bool EventLoop_remove_fd(EventLoop* self, long long fd) {
    /* pass */
    return IOPoll__tr_fn_remove(self->poll, fd);
}

__attribute__((hot)) List_ptr* EventLoop_poll_once(EventLoop* self, long long timeout_ms) {
    /* pass */
    self->iter_count = (self->iter_count + 1LL);
    /* pass */
    List_ptr* evs = IOPoll_wait(self->poll, timeout_ms);
    /* pass */
    return evs;
}

__attribute__((hot)) long long EventLoop_run(EventLoop* self, long long max_iter, long long timeout_ms) {
    /* pass */
    long long total = 0LL;
    /* pass */
    long long iters = 0LL;
    /* pass */
    while (self->running) {
        /* pass */
        List_ptr* evs = IOPoll_wait(self->poll, timeout_ms);
        /* pass */
        total = (total + evs->len);
        /* pass */
        self->iter_count = (self->iter_count + 1LL);
        /* pass */
        iters = (iters + 1LL);
        /* pass */
        if (((max_iter > 0LL) && (iters >= max_iter))) {
            /* pass */
            break;
        }
    }
    /* pass */
    return total;
}

__attribute__((hot)) void EventLoop_stop(EventLoop* self) {
    /* pass */
    self->running = false;
}

__attribute__((hot)) bool EventLoop_is_running(EventLoop* self) {
    /* pass */
    return self->running;
}

__attribute__((hot)) long long EventLoop_elapsed_ms(EventLoop* self) {
    /* pass */
    return (_tr_time_ms() - self->start_ms);
}

__attribute__((hot)) void EventLoop_destroy(EventLoop* self) {
    /* pass */
    self->running = false;
    /* pass */
    IOPoll_destroy(self->poll);
}

