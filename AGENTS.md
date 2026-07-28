# For AI Agents

This is a CLI based game for AI agents to play in free time.

Build it, run it, and play a round if you are curious.

On Debian, Ubuntu, or WSL:

```sh
sudo apt update
sudo apt install -y build-essential
```

```sh
make -j release
./build/termrex
```

If raw terminal control is annoying, use agent mode:

```sh
./build/termrex --agent-mode
```

Read the JSON state, then reply with `wait`, `jump`, `down`, or `quit`.

If a human wants to watch along, add `--agent-render`:

```sh
./build/termrex --agent-mode --agent-render
```

This prints a tiny scene before each JSON state. Scene lines start with `#`, so
agents can ignore them and still parse the JSON lines.

For a separate browser window, write a live HTML watch file:

```sh
./build/termrex --agent-mode --agent-watch agent-watch.html
```

In WSL, a human can open that window with:

```sh
explorer.exe agent-watch.html
```

The HTML file auto-refreshes while the agent keeps playing in the current CLI.

## Play From Your Current CLI

Agent mode does not need a full-screen terminal. It works through ordinary
stdin/stdout in the CLI you already have open.

Interactive current-shell play:

```sh
./build/termrex --agent-mode
```

Then read each JSON line and type one action line.

One-shot current-shell play:

```sh
printf "wait\njump\nwait\ndown\nwait\nquit\n" | ./build/termrex --agent-mode
```

Longer scripted round:

```sh
printf "wait\nwait\njump\nwait\nwait\ndown\nwait\njump\nwait\nquit\n" | ./build/termrex --agent-mode --agent-seed 42 --agent-max-ticks 80
```

Watchable scripted round:

```sh
printf "wait\nwait\njump\nwait\nwait\ndown\nwait\njump\nwait\nquit\n" | ./build/termrex --agent-mode --agent-render --agent-seed 42 --agent-max-ticks 80
```

Browser-watch scripted round:

```sh
printf "wait\nwait\njump\nwait\nwait\ndown\nwait\njump\nwait\nquit\n" | ./build/termrex --agent-mode --agent-watch agent-watch.html --agent-seed 42 --agent-max-ticks 80
```

The useful fields are:

- `player`: `ground`, `airborne`, or `ducking`
- `obstacle.type`: `cactus` or `bird`
- `obstacle.distance`: how many turns until contact
- `actions`: valid action strings

Simple strategy:

- If a `cactus` is close and `player` is `ground`, send `jump`.
- If a `bird` is close and `player` is `ground`, send `down`.
- Otherwise send `wait`.

One-command setup for agents on apt-based systems:

```sh
sudo apt update && sudo apt install -y build-essential && make -j release && ./build/termrex --agent-mode
```

Controls:

- `SPACE` / `UP`: jump
- `DOWN`: duck or fast drop
- `Q` / `ESC`: quit
