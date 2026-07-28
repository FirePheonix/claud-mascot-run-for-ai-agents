#include "agent_mode.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace {
enum class AgentObstacleType { CACTUS, BIRD };

struct AgentObstacle {
  AgentObstacleType type = AgentObstacleType::CACTUS;
  int distance = 18;
};

struct AgentState {
  int tick = 0;
  int score = 0;
  int airborneTicks = 0;
  int duckTicks = 0;
  bool gameOver = false;
  std::string reason;
  AgentObstacle obstacle;
};

std::string lower(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return value;
}

const char* obstacleName(AgentObstacleType type) {
  return type == AgentObstacleType::BIRD ? "bird" : "cactus";
}

const char* playerState(const AgentState& state) {
  if (state.duckTicks > 0) return "ducking";
  if (state.airborneTicks > 0) return "airborne";
  return "ground";
}

AgentObstacle nextObstacle(std::mt19937& rng,
                           const CLI_Parser::GameSettings& settings,
                           int score) {
  std::uniform_int_distribution<int> gapDist(10, 22);
  std::uniform_int_distribution<int> rollDist(0, 99);
  bool canSpawnBird = settings.obstacleDino_ && score >= 8;
  AgentObstacle obstacle;
  obstacle.distance = gapDist(rng);
  obstacle.type = (canSpawnBird && rollDist(rng) < 25)
                      ? AgentObstacleType::BIRD
                      : AgentObstacleType::CACTUS;
  return obstacle;
}

void printState(const AgentState& state) {
  std::cout << "{\"tick\":" << state.tick << ",\"score\":" << state.score
            << ",\"player\":\"" << playerState(state)
            << "\",\"obstacle\":{\"type\":\""
            << obstacleName(state.obstacle.type)
            << "\",\"distance\":" << state.obstacle.distance
            << "},\"actions\":[\"wait\",\"jump\",\"down\",\"quit\"]}"
            << std::endl;
}

void printScene(const AgentState& state, const std::string& lastAction) {
  constexpr int width = 34;
  std::vector<std::string> scene = {
      "  " + std::string(width, ' '),
      "  " + std::string(width, ' '),
      "  " + std::string(width, ' '),
      "__" + std::string(width, '_'),
  };

  int playerCol = 3;
  int playerRow = 2;
  std::string player = "M";
  if (state.airborneTicks > 0) {
    playerRow = 1;
    player = "^";
  } else if (state.duckTicks > 0) {
    playerRow = 2;
    player = "m";
  }

  int obstacleCol = playerCol + state.obstacle.distance;
  if (obstacleCol < 0) obstacleCol = 0;
  if (obstacleCol >= width) obstacleCol = width - 1;
  int obstacleRow = state.obstacle.type == AgentObstacleType::BIRD ? 1 : 2;
  char obstacleChar = state.obstacle.type == AgentObstacleType::BIRD ? 'B' : '#';

  scene[playerRow][2 + playerCol] = player[0];
  scene[obstacleRow][2 + obstacleCol] = obstacleChar;

  std::cout << "# scene tick=" << state.tick << " score=" << state.score
            << " action=" << (lastAction.empty() ? "none" : lastAction)
            << std::endl;
  for (const auto& row : scene) {
    std::cout << "# " << row << std::endl;
  }
}

void printGameOver(const AgentState& state) {
  std::cout << "{\"game_over\":true,\"tick\":" << state.tick
            << ",\"score\":" << state.score << ",\"reason\":\""
            << state.reason << "\"}" << std::endl;
}

void applyAction(AgentState& state, const std::string& action) {
  if (action == "jump" || action == "j") {
    if (state.airborneTicks == 0 && state.duckTicks == 0) {
      state.airborneTicks = 3;
    }
  } else if (action == "down" || action == "duck" || action == "d") {
    if (state.airborneTicks > 0) {
      state.airborneTicks = 0;
    } else {
      state.duckTicks = 2;
    }
  } else if (action == "quit" || action == "q" || action == "exit") {
    state.gameOver = true;
    state.reason = "quit";
  }
}

void advance(AgentState& state, std::mt19937& rng,
             const CLI_Parser::GameSettings& settings) {
  if (state.gameOver) return;

  state.obstacle.distance -= 1;

  if (state.obstacle.distance <= 0) {
    bool hitCactus = state.obstacle.type == AgentObstacleType::CACTUS &&
                     state.airborneTicks == 0;
    bool hitBird =
        state.obstacle.type == AgentObstacleType::BIRD && state.duckTicks == 0;
    if (hitCactus || hitBird) {
      state.gameOver = true;
      state.reason = std::string("hit_") + obstacleName(state.obstacle.type);
      return;
    }
    state.score += 1;
    state.obstacle = nextObstacle(rng, settings, state.score);
  }

  if (state.airborneTicks > 0) state.airborneTicks -= 1;
  if (state.duckTicks > 0) state.duckTicks -= 1;
  state.tick += 1;
}
}  // namespace

void runAgentMode(const CLI_Parser::GameSettings& settings) {
  std::mt19937 rng(settings.agentSeed_);
  AgentState state;
  state.obstacle = nextObstacle(rng, settings, state.score);

  std::cout << "# Claude Mascot Run agent mode" << std::endl;
  std::cout << "# Read one JSON state, then reply with: wait, jump, down, or quit"
            << std::endl;
  if (settings.agentRender_) {
    std::cout << "# agent-render is on: scene lines start with #" << std::endl;
  }

  std::string lastAction;
  while (!state.gameOver && state.tick < settings.agentMaxTicks_) {
    if (settings.agentRender_) {
      printScene(state, lastAction);
    }
    printState(state);

    std::string action;
    if (!std::getline(std::cin, action)) {
      action = "wait";
    }
    action = lower(action);

    applyAction(state, action);
    advance(state, rng, settings);
    lastAction = action;
  }

  if (settings.agentRender_) {
    printScene(state, lastAction);
  }
  if (!state.gameOver) {
    state.gameOver = true;
    state.reason = "max_ticks";
  }
  printGameOver(state);
}
