# tauraro-lsp

Language Server Protocol (LSP) implementation for the [Tauraro](https://github.com/tauraro/tauraro)
programming language. Provides real-time diagnostics, hover docs, completion, go-to-definition,
and more — written entirely in Tauraro with no C shim files.

---

## Table of contents

- [Features](#features)
- [Installation](#installation)
- [IDE setup](#ide-setup)
  - [VS Code](#vs-code)
  - [Neovim](#neovim)
  - [Vim](#vim)
  - [Emacs](#emacs)
  - [Helix](#helix)
  - [Sublime Text](#sublime-text)
  - [JetBrains IDEs](#jetbrains-ides)
  - [Zed](#zed)
- [Options](#options)
- [How it works](#how-it-works)
- [Building from source](#building-from-source)
- [Troubleshooting](#troubleshooting)

---

## Features

| LSP method | What you get |
|---|---|
| `textDocument/publishDiagnostics` | Inline errors and warnings from `tauraroc --check` as you type |
| `textDocument/hover` | Type info, keyword docs, error-code explanations (`[M-1]`, `[F-3]` etc.) |
| `textDocument/completion` | Keywords, built-in types, method completions, identifiers from the current file |
| `textDocument/definition` | Jump to the declaration of any symbol (current file + imported modules) |
| `textDocument/documentSymbol` | File outline: functions, classes, enums with line numbers |
| `workspace/symbol` | Search all open files for a symbol by name prefix |
| `textDocument/semanticTokens/full` | Accurate syntax highlighting: keywords, strings, numbers, types, functions |

---

## Installation

### Download a pre-built binary

Download the latest release for your platform from the
[releases page](https://github.com/tauraro/tauraro-lsp/releases):

| Platform | Binary |
|---|---|
| Linux x64 | `tauraro-lsp-linux-x64.zip` |
| Linux ARM64 | `tauraro-lsp-linux-arm64.zip` |
| Windows x64 | `tauraro-lsp-windows-x64.zip` |
| macOS ARM64 | `tauraro-lsp-macos-arm64.zip` |

Unzip and place `tauraro-lsp` (or `tauraro-lsp.exe`) somewhere on your `PATH`.

### Install via taupkg

```sh
taupkg install-tauraro          # install tauraroc first
taupkg add tauraro-lsp          # coming soon
```

### Build from source

See [Building from source](#building-from-source).

---

## IDE setup

In every case, replace `/path/to/tauraro-lsp` with the actual path to the binary.
The LSP communicates over **stdin/stdout** (transport = `stdio`).

---

### VS Code

**Option A — Manual `settings.json` (no extension required)**

Install the generic LSP client extension
[`vscode-glspc`](https://marketplace.visualstudio.com/items?itemName=michaelcfanning.glspc)
or use the built-in [generic language client](https://code.visualstudio.com/api/language-extensions/language-server-extension-guide),
then add to your `settings.json`:

```json
{
  "tauraro.lspPath": "/path/to/tauraro-lsp",
  "tauraro.lspArgs": ["--log", "/tmp/tauraro-lsp.log"]
}
```

**Option B — Dedicated Tauraro extension (recommended)**

Once the Tauraro VS Code extension is published, install it from the Marketplace
and set:

```json
{
  "[tauraro]": {
    "editor.formatOnSave": true,
    "editor.defaultFormatter": "tauraro.tauraro"
  },
  "tauraro.lspPath": "/path/to/tauraro-lsp",
  "tauraro.compilerPath": "/path/to/tauraroc"
}
```

**Manual `.vscode/tasks.json` (build on save)**

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Tauraro",
      "type": "shell",
      "command": "tauraroc",
      "args": ["src/main.tr", "-o", "${workspaceFolder}/build/app"],
      "group": { "kind": "build", "isDefault": true },
      "problemMatcher": {
        "owner": "tauraro",
        "fileLocation": ["relative", "${workspaceFolder}"],
        "pattern": {
          "regexp": "^error: line (\\d+): (.*)$",
          "line": 1,
          "message": 2
        }
      }
    }
  ]
}
```

---

### Neovim

**Using `nvim-lspconfig` (Neovim ≥ 0.8)**

Add a custom server configuration in your `init.lua`:

```lua
-- ~/.config/nvim/init.lua  (or lua/lsp.lua)

local lspconfig = require('lspconfig')
local configs   = require('lspconfig.configs')

-- Register the Tauraro language server
if not configs.taurarols then
  configs.taurarols = {
    default_config = {
      cmd          = { '/path/to/tauraro-lsp' },
      filetypes    = { 'tauraro' },
      root_dir     = lspconfig.util.root_pattern('taupkg.toml', '.git'),
      settings     = {},
    },
  }
end

lspconfig.taurarols.setup {
  on_attach = function(client, bufnr)
    -- Key mappings
    local opts = { noremap = true, silent = true, buffer = bufnr }
    vim.keymap.set('n', 'gd', vim.lsp.buf.definition,      opts)
    vim.keymap.set('n', 'K',  vim.lsp.buf.hover,           opts)
    vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, opts)
    vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename,  opts)
    vim.keymap.set('n', '[d', vim.diagnostic.goto_prev,    opts)
    vim.keymap.set('n', ']d', vim.diagnostic.goto_next,    opts)
  end,
  capabilities = require('cmp_nvim_lsp').default_capabilities(),
}
```

**Associate `.tr` files with the `tauraro` filetype**

```lua
-- In init.lua or ftdetect/tauraro.lua
vim.filetype.add({
  extension = { tr = 'tauraro' },
})
```

**Using `lazy.nvim`**

```lua
{
  'neovim/nvim-lspconfig',
  config = function()
    -- paste the lspconfig setup above here
  end,
}
```

**Enable semantic tokens (better highlighting)**

```lua
lspconfig.taurarols.setup {
  on_attach = function(client, bufnr)
    -- Enable semantic tokens
    if client.server_capabilities.semanticTokensProvider then
      vim.lsp.semantic_tokens.start(bufnr, client.id)
    end
    -- ... rest of on_attach
  end,
}
```

---

### Vim

**Using `vim-lsp`**

```vim
" ~/.vimrc

if executable('/path/to/tauraro-lsp')
  au User lsp_setup call lsp#register_server({
    \ 'name': 'tauraro-lsp',
    \ 'cmd': {server_info -> ['/path/to/tauraro-lsp']},
    \ 'allowlist': ['tauraro'],
    \ })
endif

" Associate .tr files
autocmd BufNewFile,BufRead *.tr setfiletype tauraro

" Key mappings
autocmd FileType tauraro nmap <buffer> gd <plug>(lsp-definition)
autocmd FileType tauraro nmap <buffer> K  <plug>(lsp-hover)
autocmd FileType tauraro nmap <buffer> [g <plug>(lsp-previous-diagnostic)
autocmd FileType tauraro nmap <buffer> ]g <plug>(lsp-next-diagnostic)
```

**Using `coc.nvim`**

Add to `coc-settings.json` (`:CocConfig`):

```json
{
  "languageserver": {
    "tauraro": {
      "command": "/path/to/tauraro-lsp",
      "args": [],
      "filetypes": ["tauraro"],
      "rootPatterns": ["taupkg.toml", ".git"]
    }
  }
}
```

Add to `.vimrc`:
```vim
autocmd BufNewFile,BufRead *.tr setfiletype tauraro
```

---

### Emacs

**Using `eglot` (built-in since Emacs 29)**

```elisp
;; ~/.emacs.d/init.el

;; Associate .tr files with a tauraro major mode (or prog-mode as fallback)
(add-to-list 'auto-mode-alist '("\\.tr\\'" . tauraro-mode))

;; Register the server with eglot
(with-eval-after-load 'eglot
  (add-to-list 'eglot-server-programs
    '(tauraro-mode . ("/path/to/tauraro-lsp"))))

;; Auto-start eglot for .tr files
(add-hook 'tauraro-mode-hook 'eglot-ensure)
```

If you don't have a `tauraro-mode`, use `prog-mode` as the host:

```elisp
(add-to-list 'auto-mode-alist '("\\.tr\\'" . prog-mode))
(with-eval-after-load 'eglot
  (add-to-list 'eglot-server-programs
    `((prog-mode :language-id "tauraro") . ("/path/to/tauraro-lsp"))))
```

**Using `lsp-mode`**

```elisp
(use-package lsp-mode
  :hook (tauraro-mode . lsp-deferred)
  :config
  (lsp-register-client
    (make-lsp-client
      :new-connection (lsp-stdio-connection '("/path/to/tauraro-lsp"))
      :major-modes '(tauraro-mode)
      :server-id 'tauraro-lsp)))
```

---

### Helix

Add to `~/.config/helix/languages.toml`:

```toml
[[language]]
name              = "tauraro"
scope             = "source.tauraro"
injection-regex   = "tauraro"
file-types        = ["tr"]
comment-token     = "#"
indent            = { tab-width = 4, unit = "    " }
language-servers  = ["tauraro-lsp"]

[language-server.tauraro-lsp]
command = "/path/to/tauraro-lsp"
```

After saving, run `:config-reload` in Helix.  Check the server started with
`:lsp-workspace-command`, diagnostics appear in the gutter automatically.

---

### Sublime Text

**Install the LSP package**

`Package Control` → `Install Package` → `LSP`

**Add configuration**

`Preferences` → `Package Settings` → `LSP` → `Settings`, add to `clients`:

```json
{
  "clients": {
    "tauraro-lsp": {
      "command": ["/path/to/tauraro-lsp"],
      "enabled": true,
      "selector": "source.tauraro"
    }
  }
}
```

**Add a syntax definition** (`Packages/User/tauraro.sublime-syntax`):

```yaml
%YAML 1.2
---
name: Tauraro
file_extensions: [tr]
scope: source.tauraro
contexts:
  main:
    - match: \b(def|pub|mut|class|extend|enum|interface|if|elif|else|while|for|in|return|match|case|from|import|unsafe|extern|true|false|none|and|or|not)\b
      scope: keyword.control.tauraro
    - match: '"[^"]*"'
      scope: string.quoted.double.tauraro
    - match: '#.*$'
      scope: comment.line.number-sign.tauraro
```

---

### JetBrains IDEs

*(IntelliJ IDEA, PyCharm, CLion, GoLand, WebStorm, etc.)*

**Install LSP4IJ**

`File` → `Settings` → `Plugins` → search `LSP4IJ` → Install → Restart

**Configure the server**

`File` → `Settings` → `Languages & Frameworks` → `LSP` → `+` → `New Language Server`:

| Field | Value |
|---|---|
| Name | `Tauraro` |
| Command | `/path/to/tauraro-lsp` |
| File name patterns | `*.tr` |

Click OK, then restart the IDE. Open any `.tr` file — the LSP icon in the
status bar shows the connection status.

---

### Zed

Add to `~/.config/zed/settings.json`:

```json
{
  "languages": {
    "Tauraro": {
      "language_servers": ["tauraro-lsp"]
    }
  },
  "lsp": {
    "tauraro-lsp": {
      "binary": {
        "path": "/path/to/tauraro-lsp",
        "arguments": []
      }
    }
  }
}
```

Add to `~/.config/zed/languages/tauraro/config.toml`
(create the directory if it doesn't exist):

```toml
name       = "Tauraro"
path_suffixes = ["tr"]
line_comment   = "# "
```

---

## Options

```
tauraro-lsp [--compiler <path>] [--log <file>]
```

| Flag | Description |
|---|---|
| `--compiler <path>` | Path to the `tauraroc` binary. Auto-discovered if not set (see below). |
| `--log <file>` | Write debug messages to `<file>`. Useful for troubleshooting. |
| `--version` | Print version and exit. |
| `--help` | Show usage. |

### Compiler auto-discovery order

1. `TAURARO` environment variable
2. Each directory in `TAURARO_PATH` (colon/semicolon-separated)
3. `~/.taupkg/bin/tauraroc-{platform}/tauraroc[.exe]` (installed via `taupkg install-tauraro`)
4. `tauraroc` on `PATH`

---

## How it works

```
  IDE                  tauraro-lsp               tauraroc
  ───                  ────────────               ────────
  didOpen  ─────────►  parse + analyze  ─────►  --check file.tr
  didChange ────────►  re-analyze       ─────►  --check tmp.tr
           ◄─────────  publishDiagnostics (errors, warnings)

  hover    ─────────►  word lookup + hover.tr
           ◄─────────  markdown: type info / keyword docs / error-code explanation

  completion ───────►  keyword list + doc identifiers + method completions
             ◄───────  67 items (keywords, types, methods)

  definition ───────►  scan current file + imported modules for declaration
             ◄───────  Location (uri + line)

  documentSymbol ───►  line-by-line scan: def / class / enum / extend
                ◄────  list of SymbolInformation with line ranges

  semanticTokens ───►  lexer-based tokenisation pass
                 ◄───  delta-encoded [line, char, len, type, modifier] array
```

Diagnostics use `tauraroc --check <tempfile>` which runs the full parser + sema
pipeline without emitting C or invoking GCC.  Error messages from tauraroc have
the format `error: line N: [CODE] message` which the LSP parses directly.

---

## Building from source

Prerequisites: `tauraroc` and `gcc`.

```sh
git clone https://github.com/tauraro/tauraro-lsp
cd tauraro-lsp

# Emit C (build/ is created in the current directory)
tauraroc src/main.tr --emit c

# Linux / macOS
cd src
gcc -O2 -std=c11 -Wno-misleading-indentation -Ibuild \
  ../build/main.c ../build/module_*.c \
  ../build/include/std/core/*.c \
  ../build/include/std/io/*.c ../build/include/std/io.c \
  ../build/include/std/string/*.c \
  -o ../tauraro-lsp -lm

# Windows (Git Bash or PowerShell with gcc on PATH)
gcc -O2 -std=c11 -Wno-misleading-indentation -Ibuild \
  ../build/main.c ../build/module_*.c \
  ../build/include/std/core/*.c \
  ../build/include/std/io/*.c ../build/include/std/io.c \
  ../build/include/std/string/*.c \
  -o ../tauraro-lsp.exe -lm -lws2_32
```

> **Note**: `tauraro-lsp` is written entirely in Tauraro — there are no hand-written
> C files. All I/O primitives (`_tr_read_stdin_line`, `_tr_write_stdout`, etc.)
> live in the Tauraro runtime header `tauraro_rt.h` and are accessed via
> `extern "C"` declarations.

---

## Troubleshooting

**LSP not starting / no diagnostics**

1. Verify the binary works:
   ```sh
   tauraro-lsp --version      # should print: tauraro-lsp 0.1.0
   tauraro-lsp --help
   ```

2. Enable the debug log and check it:
   ```sh
   # Start the server manually with logging (for testing)
   tauraro-lsp --log /tmp/tau-lsp.log
   # Then open a .tr file in your IDE
   cat /tmp/tau-lsp.log
   ```

3. Check that `tauraroc` is found:
   ```sh
   tauraro-lsp --log /tmp/tau-lsp.log
   grep "compiler:" /tmp/tau-lsp.log
   ```
   If the compiler isn't found, pass it explicitly:
   ```
   --compiler /path/to/tauraroc
   ```

**Diagnostics are slow**

Every `textDocument/didChange` runs `tauraroc --check` as a subprocess.
If `tauraroc` is slow to start on your machine, set `--check-debounce 500`
(500 ms) once that flag is implemented.

**Wrong file associations**

Make sure your editor associates `.tr` files with `tauraro` (not TypeScript,
which also uses `.tr` in some projects):

- **VS Code**: add `"files.associations": {"*.tr": "tauraro"}` to `settings.json`
- **Neovim**: `vim.filetype.add({ extension = { tr = 'tauraro' } })`
- **Vim**: `autocmd BufNewFile,BufRead *.tr setfiletype tauraro`

**Hover shows nothing**

Hover returns `null` for whitespace, operators, and punctuation.
Place the cursor directly ON an identifier, keyword, or error code like `[M-1]`.

**`_tr_` functions not found at link time**

Make sure you are using the runtime header from tauraroc ≥ v0.0.4.  Earlier
versions did not include `_tr_read_stdin_line`, `_tr_write_stdout` etc.
Run `tauraroc --version` to check.

---

## Supported error codes (hover docs)

| Code | Meaning |
|---|---|
| `[M-1]` | Use after move |
| `[M-2]` | Double move |
| `[M-4]` | Container mutated while borrow is live |
| `[F-3]` | Non-void function missing return on some path |
| `[N-1]` | Reserved built-in name used as identifier |
| `[T-1]` | Non-Sendable type passed to `spawn` |
| `[L-1]` | Local `Pointer[T]` escaping its function without lifetime annotation |
| `[E-1]` | Explicit call to `main()` is forbidden |
| `[U-1]` | `unsafe:` used in `--strict` mode |

Hovering over any `[X-N]` code in a comment or diagnostic message shows
the full explanation and suggested fix.

---

## License

MIT — see [LICENSE](LICENSE) for details.
