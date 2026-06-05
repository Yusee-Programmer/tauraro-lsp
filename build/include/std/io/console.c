#include "../../../tauraro_types.h"


__attribute__((hot)) void Console_println(char* s) {
    /* pass */
    printf("%s\n", (char*)(s));
}

__attribute__((hot)) void Console_print(char* s) {
    /* pass */
    _tr_print_raw(s);
}

__attribute__((hot)) void Console_eprint(char* s) {
    /* pass */
    _tr_eprint(s);
}

__attribute__((hot)) void Console_eprintln(char* s) {
    /* pass */
    _tr_eprint(s);
}

__attribute__((hot)) char* Console_read_line(char* prompt) {
    /* pass */
    return _tr_read_line(prompt);
}

__attribute__((hot)) char* Console_input_line() {
    /* pass */
    return _tr_read_line("");
}

__attribute__((hot)) long long Console_read_int(char* prompt) {
    /* pass */
    char* s = _tr_read_line(prompt);
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    bool neg = false;
    /* pass */
    long long val = 0LL;
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 45LL)) {
        /* pass */
        neg = true;
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    while (true) {
        /* pass */
        c = ((long long)((*(p + i))));
        /* pass */
        if ((c == 0LL)) {
            /* pass */
            break;
        }
        /* pass */
        if (((c >= 48LL) && (c <= 57LL))) {
            /* pass */
            val = ((val * 10LL) + (c - 48LL));
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if (neg) {
        /* pass */
        return (0LL - val);
    }
    /* pass */
    return val;
}

__attribute__((hot)) double Console_read_float(char* prompt) {
    /* pass */
    char* s = _tr_read_line(prompt);
    /* pass */
    char* p = ((char*)(s));
    /* pass */
    bool neg = false;
    /* pass */
    long long intpart = 0LL;
    /* pass */
    long long fracpart = 0LL;
    /* pass */
    long long fracdiv = 1LL;
    /* pass */
    bool dot = false;
    /* pass */
    long long i = 0LL;
    /* pass */
    long long c = ((long long)((*(p + i))));
    /* pass */
    if ((c == 45LL)) {
        /* pass */
        neg = true;
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    while (true) {
        /* pass */
        c = ((long long)((*(p + i))));
        /* pass */
        if ((c == 0LL)) {
            /* pass */
            break;
        }
        /* pass */
        if ((c == 46LL)) {
            /* pass */
            dot = true;
        } else if (((c >= 48LL) && (c <= 57LL))) {
            /* pass */
            if (dot) {
                /* pass */
                fracpart = ((fracpart * 10LL) + (c - 48LL));
                /* pass */
                fracdiv = (fracdiv * 10LL);
            } else {
                /* pass */
                intpart = ((intpart * 10LL) + (c - 48LL));
            }
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    double result = (((double)(intpart)) + (((double)(fracpart)) / ((double)(fracdiv))));
    /* pass */
    if (neg) {
        /* pass */
        return (0 - result);
    }
    /* pass */
    return result;
}

__attribute__((hot)) void Console_clear() {
    /* pass */
    _tr_console_clear();
}

__attribute__((hot)) void Console_set_color(long long code) {
    /* pass */
    _tr_console_color(code);
}

__attribute__((hot)) void Console_reset_color() {
    /* pass */
    _tr_console_reset();
}

__attribute__((hot)) void Console_print_colored(char* s, long long code) {
    /* pass */
    _tr_console_color(code);
    /* pass */
    _tr_print_raw(s);
    /* pass */
    _tr_console_reset();
}

__attribute__((hot)) void Console_println_colored(char* s, long long code) {
    /* pass */
    _tr_console_color(code);
    /* pass */
    printf("%s\n", (char*)(s));
    /* pass */
    _tr_console_reset();
}

__attribute__((hot)) long long Console_BLACK() {
    /* pass */
    return 30LL;
}

__attribute__((hot)) long long Console_RED() {
    /* pass */
    return 31LL;
}

__attribute__((hot)) long long Console_GREEN() {
    /* pass */
    return 32LL;
}

__attribute__((hot)) long long Console_YELLOW() {
    /* pass */
    return 33LL;
}

__attribute__((hot)) long long Console_BLUE() {
    /* pass */
    return 34LL;
}

__attribute__((hot)) long long Console_MAGENTA() {
    /* pass */
    return 35LL;
}

__attribute__((hot)) long long Console_CYAN() {
    /* pass */
    return 36LL;
}

__attribute__((hot)) long long Console_WHITE() {
    /* pass */
    return 37LL;
}

__attribute__((hot)) long long Console_BRIGHT_RED() {
    /* pass */
    return 91LL;
}

__attribute__((hot)) long long Console_BRIGHT_GREEN() {
    /* pass */
    return 92LL;
}

__attribute__((hot)) long long Console_BRIGHT_YELLOW() {
    /* pass */
    return 93LL;
}

__attribute__((hot)) long long Console_BRIGHT_BLUE() {
    /* pass */
    return 94LL;
}

__attribute__((hot)) long long Console_BRIGHT_MAGENTA() {
    /* pass */
    return 95LL;
}

__attribute__((hot)) long long Console_BRIGHT_CYAN() {
    /* pass */
    return 96LL;
}

__attribute__((hot)) long long Console_BRIGHT_WHITE() {
    /* pass */
    return 97LL;
}

