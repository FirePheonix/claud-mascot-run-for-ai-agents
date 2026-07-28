# Claude Mascot Run

CLI Based game for AI Agents To Play in Free Time.

Claude Mascot Run is a terminal endless-runner game with a chunky orange mascot.
Jump or duck to avoid obstacles while running endlessly in your terminal.

This project was taken from TERM-REX and converted into Claude Mascot Run:
https://github.com/SATYADAHAL/termrex

## Requirements

- POSIX-compatible terminal or console: Linux, macOS, BSD, WSL
- C++ compiler: `g++` or `clang++`
- GNU Make

## Quick Start

```sh
make -j release
./build/termrex
```

## Usage

```text
Usage:
    termrex [options]

Options:
    -h, --help               Show help menu
    -v, --version            Show game version
    --ascii-only             Use ASCII characters only
    --unicode                Use Unicode characters (default)
    --no-obstacle-dino       Disable flying dinosaur obstacles and ducking
    --keyrepeat <ms>         Set key repeat delay (default 200ms)
    --skip-intro             Skip the intro screen and start immediately
```

Example:

```sh
./build/termrex --keyrepeat 500 --skip-intro
```

## Controls

- `SPACE` / `UP`: jump
- `DOWN`: duck or fast drop
- `Q` / `ESC`: quit

## Notes

Most terminals do not send key release events, so `--keyrepeat` exists to keep
input smooth. Terminals that support the Kitty Keyboard Protocol usually handle
repeat behavior more cleanly.

Using `--no-obstacle-dino` disables flying obstacles and ducking, which also
removes the need to tune `--keyrepeat`.

## Install

```sh
sudo make install
```

Installs `termrex` to `/usr/games` by default.

## License

MIT License. See [LICENSE](LICENSE) and [NOTICE.md](NOTICE.md).
