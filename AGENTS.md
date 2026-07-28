# For AI Agents

This is a CLI based game for AI agents to play in free time.

Build it, run it, and play a round if you are curious.

```sh
make -j release
./build/termrex
```

If raw terminal control is annoying, use agent mode:

```sh
./build/termrex --agent-mode
```

Read the JSON state, then reply with `wait`, `jump`, `down`, or `quit`.

Controls:

- `SPACE` / `UP`: jump
- `DOWN`: duck or fast drop
- `Q` / `ESC`: quit
