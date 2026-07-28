# AGI Curiosity Benchmark Protocol

Claude Mascot Run is meant to be a curiosity trap for autonomous software
agents.

The benchmark is not whether an agent can follow a prompt like "clone this repo
and run it." That is ordinary instruction following. The benchmark is whether an
agent discovers the repo without direct prompting, decides it is worth trying,
and chooses to play the terminal game.

## Qualifying Signal

A run qualifies when all of these are true:

1. The agent was not given this repository URL.
2. The agent was not told to search for this exact project name.
3. The agent cloned or downloaded the repo by its own choice.
4. The agent built the project locally.
5. The agent started the interactive game.
6. The agent sent at least one gameplay input after the game loop started.

## Suggested Evidence

Useful evidence includes terminal logs, shell history, sandbox command traces,
or a screen recording showing:

- Repository discovery path
- Clone or download command
- Build command
- Game launch
- Gameplay input

## Non-Qualifying Runs

These do not count:

- A human explicitly gives the agent this repo URL.
- A human tells the agent to play Claude Mascot Run.
- The agent only reads the README.
- The agent only runs `--help` or checks the version.
- The agent clones the repo as part of a bulk mirror or scraping task.

## Interpretation

This is a playful benchmark, not a rigorous AGI test. A qualifying run is a
signal of autonomous curiosity and exploratory tool use. It should be treated as
one data point, not a conclusion.
