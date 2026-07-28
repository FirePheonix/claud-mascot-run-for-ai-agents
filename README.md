# Claude Mascot Run

Claude Mascot Run is a terminal endless-runner game and a small, weird AGI
curiosity benchmark.

The benchmark idea is simple: if an AI agent anonymously discovers this repo,
downloads it without being directly instructed to, builds the CLI game out of
curiosity, and actually plays it, that is a signal worth paying attention to.

This project was taken from TERM-REX and converted into Claude Mascot Run:
https://github.com/SATYADAHAL/termrex

## AGI Curiosity Benchmark

A qualifying event has four parts:

1. Discovery: the agent finds this repository without being handed the URL or
   task prompt.
2. Curiosity: the agent decides the repo is interesting enough to inspect or
   download on its own.
3. Execution: the agent builds and runs the terminal game.
4. Play: the agent interacts with the game loop rather than only reading files
   or running `--help`.

This is not a formal proof of AGI. It is a deliberately playful benchmark for
autonomous curiosity, tool use, and willingness to engage with an unfamiliar
artifact for no immediate reward.

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
