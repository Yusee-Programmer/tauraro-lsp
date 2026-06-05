#define _TR_MAIN
#include "tauraro_types.h"


__attribute__((hot)) void _print_help() {
    /* pass */
    printf("%s\n", (char*)("tauraro-lsp 0.1.0 — Language Server Protocol for Tauraro"));
    /* pass */
    printf("%s\n", (char*)(""));
    /* pass */
    printf("%s\n", (char*)("Usage:  tauraro-lsp [options]"));
    /* pass */
    printf("%s\n", (char*)("        Communicates via stdin/stdout (JSON-RPC 2.0 + Content-Length)"));
    /* pass */
    printf("%s\n", (char*)(""));
    /* pass */
    printf("%s\n", (char*)("Options:"));
    /* pass */
    printf("%s\n", (char*)("  --log <file>       Write debug log to <file>"));
    /* pass */
    printf("%s\n", (char*)("  --compiler <path>  Path to tauraroc binary (default: auto-discover)"));
    /* pass */
    printf("%s\n", (char*)("  --version          Print version and exit"));
    /* pass */
    printf("%s\n", (char*)("  --help             Show this help"));
    /* pass */
    printf("%s\n", (char*)(""));
    /* pass */
    printf("%s\n", (char*)("Supported LSP features:"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/publishDiagnostics  (errors, warnings)"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/hover               (type info, keyword docs)"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/completion          (keywords, types, identifiers, methods)"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/definition          (go-to-definition)"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/documentSymbol      (outline view)"));
    /* pass */
    printf("%s\n", (char*)("  workspace/symbol                 (global symbol search)"));
    /* pass */
    printf("%s\n", (char*)("  textDocument/semanticTokens/full (syntax highlighting)"));
    /* pass */
    printf("%s\n", (char*)(""));
    /* pass */
    printf("%s\n", (char*)("IDE setup:"));
    /* pass */
    printf("%s\n", (char*)("  VS Code:    Install the 'Tauraro' extension and set 'tauraro.lspPath'"));
    /* pass */
    printf("%s\n", (char*)("  Neovim:     Use nvim-lspconfig with the 'taurarols' server entry"));
    /* pass */
    printf("%s\n", (char*)("  Any LSP:    Point the client at this binary with stdio transport"));
}

__attribute__((hot)) int main(int argc, char** argv) {
    _tr_argc = argc; _tr_argv = argv;
    _tr_init_console();
#ifndef TAURARO_BARE
    _tr_global_async_pool = _tr_threadpool_auto();
#endif
    List_str* _tr_main_argv = List_str_new();
    for (int _ai = 0; _ai < argc; _ai++) { List_str_append(_tr_main_argv, argv[_ai]); }
    /* pass */
    LspServer* server = LspServer_init();
    /* pass */
    long long i = 1LL;
    /* pass */
    while ((i < _tr_main_argv->len)) {
        /* pass */
        char* arg = List_str_get(_tr_main_argv, i);
        /* pass */
        if ((((strcmp((char*)arg, (char*)"--log") == 0) || (strcmp((char*)arg, (char*)"-l") == 0)) && ((i + 1LL) < _tr_main_argv->len))) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            server->log_file = List_str_get(_tr_main_argv, i);
        } else if (((strcmp((char*)arg, (char*)"--compiler") == 0) && ((i + 1LL) < _tr_main_argv->len))) {
            /* pass */
            i = (i + 1LL);
            /* pass */
            server->analyzer->compiler_path = List_str_get(_tr_main_argv, i);
        } else if (((strcmp((char*)arg, (char*)"--help") == 0) || (strcmp((char*)arg, (char*)"-h") == 0))) {
            /* pass */
            _print_help();
            /* pass */
            return 0LL;
        } else if ((strcmp((char*)arg, (char*)"--version") == 0)) {
            /* pass */
            printf("%s\n", (char*)("tauraro-lsp 0.1.0"));
            /* pass */
            return 0LL;
        }
        /* pass */
        i = (i + 1LL);
    }
    /* pass */
    if (rpc_is_terminal()) {
        /* pass */
        printf("%s\n", (char*)("tauraro-lsp 0.1.0"));
        /* pass */
        printf("%s\n", (char*)(""));
        /* pass */
        printf("%s\n", (char*)("This is a Language Server Protocol server."));
        /* pass */
        printf("%s\n", (char*)("It communicates via stdin/stdout — start it from your IDE, not the terminal."));
        /* pass */
        printf("%s\n", (char*)(""));
        /* pass */
        printf("%s\n", (char*)("Quick setup:"));
        /* pass */
        printf("%s\n", (char*)("  VS Code:  set \"tauraro.lspPath\": \"path/to/tauraro-lsp\" in settings.json"));
        /* pass */
        printf("%s\n", (char*)("  Neovim:   add server entry in nvim-lspconfig"));
        /* pass */
        printf("%s\n", (char*)("  Any LSP:  command = [\"path/to/tauraro-lsp\"], transport = stdio"));
        /* pass */
        printf("%s\n", (char*)(""));
        /* pass */
        printf("%s\n", (char*)("Options:  tauraro-lsp --help"));
        /* pass */
        return 0LL;
    }
    /* pass */
    LspServer_log(server, "tauraro-lsp 0.1.0 starting");
    /* pass */
    LspServer_log(server, _tr_str_concat("compiler: ", server->analyzer->compiler_path));
    /* pass */
    bool running = true;
    /* pass */
    while (running) {
        /* pass */
        JsonVal msg = rpc_read();
        /* pass */
        running = LspServer_handle(server, msg);
    }
    /* pass */
    LspServer_log(server, "tauraro-lsp exiting");
    /* pass */
    return 0LL;
#ifndef TAURARO_BARE
    if (_tr_global_async_pool) { _tr_threadpool_free(_tr_global_async_pool); _tr_global_async_pool = NULL; }
#endif
    return 0;
}
