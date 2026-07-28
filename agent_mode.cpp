#include "agent_mode.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
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

std::string cssClassForPlayer(const AgentState& state) {
  if (state.duckTicks > 0) return "player duck";
  if (state.airborneTicks > 0) return "player jump";
  return "player";
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

void writeWatchFile(const AgentState& state, const std::string& lastAction,
                    const std::string& path) {
  if (path.empty()) return;

  int obstacleLeft = 14 + state.obstacle.distance * 3;
  if (obstacleLeft < 14) obstacleLeft = 14;
  if (obstacleLeft > 92) obstacleLeft = 92;

  int playerBottom = state.airborneTicks > 0 ? 38 : 18;
  int playerHeight = state.duckTicks > 0 ? 24 : 42;
  int obstacleBottom =
      state.obstacle.type == AgentObstacleType::BIRD ? 47 : 18;
  int obstacleHeight =
      state.obstacle.type == AgentObstacleType::BIRD ? 18 : 34;

  std::ofstream out(path, std::ios::trunc);
  if (!out.is_open()) return;

  out << "<!doctype html><html><head><meta charset=\"utf-8\">";
  out << "<meta http-equiv=\"refresh\" content=\"0.35\">";
  out << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  out << "<title>Claude Mascot Run Watch</title>";
  out << "<style>";
  out << "body{margin:0;background:#090909;color:#eee;font-family:ui-monospace,"
         "SFMono-Regular,Consolas,monospace;display:grid;place-items:center;"
         "min-height:100vh}";
  out << ".wrap{width:min(980px,94vw)}";
  out << ".hud{display:flex;justify-content:space-between;color:#aaa;"
         "font-size:14px;margin:0 0 10px}";
  out << ".stage{position:relative;height:300px;border:2px solid #eee;"
         "border-radius:6px;background:#050505;overflow:hidden}";
  out << ".title{text-align:center;margin-top:20px;font-size:34px;"
         "letter-spacing:2px;color:#f5f5f5}";
  out << ".ground{position:absolute;left:0;right:0;bottom:54px;"
         "border-top:2px dashed #777}";
  out << ".player{position:absolute;left:54px;bottom:" << playerBottom
      << "px;width:72px;height:" << playerHeight
      << "px;background:#ff8a00;box-shadow:16px 0 0 #ff8a00,"
         "32px 0 0 #ff8a00}";
  out << ".player:before{content:'';position:absolute;left:10px;top:8px;"
         "width:10px;height:10px;background:#090909;box-shadow:42px 0 0 #090909}";
  out << ".player:after{content:'';position:absolute;left:8px;bottom:-24px;"
         "width:10px;height:24px;background:#ff8a00;box-shadow:24px 0 0 #ff8a00,"
         "48px 0 0 #ff8a00,64px 0 0 #ff8a00}";
  out << ".duck{height:24px}.jump{transform:translateY(-38px)}";
  out << ".obstacle{position:absolute;left:" << obstacleLeft
      << "%;bottom:" << obstacleBottom << "px;width:22px;height:"
      << obstacleHeight << "px;background:#ddd}";
  out << ".bird{height:14px;width:36px;border-radius:2px;box-shadow:12px -8px 0 #ddd}";
  out << ".meta{margin-top:12px;color:#ddd;font-size:14px;line-height:1.5}";
  out << ".action{color:#ffcf33}.over{color:#ff6666}";
  out << "</style></head><body><main class=\"wrap\">";
  out << "<div class=\"hud\"><span>tick " << state.tick << "</span><span>score "
      << state.score << "</span><span>last action <b class=\"action\">"
      << (lastAction.empty() ? "none" : lastAction) << "</b></span></div>";
  out << "<section class=\"stage\"><div class=\"title\">CLAUDE MASCOT RUN</div>";
  out << "<div class=\"" << cssClassForPlayer(state) << "\"></div>";
  out << "<div class=\"obstacle "
      << (state.obstacle.type == AgentObstacleType::BIRD ? "bird" : "cactus")
      << "\"></div><div class=\"ground\"></div></section>";
  out << "<div class=\"meta\">player: " << playerState(state)
      << " | obstacle: " << obstacleName(state.obstacle.type)
      << " | distance: " << state.obstacle.distance;
  if (state.gameOver) {
    out << " | <b class=\"over\">game over: " << state.reason << "</b>";
  }
  out << "</div></main></body></html>";
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
  if (!settings.agentWatchPath_.empty()) {
    std::cout << "# writing watch view: " << settings.agentWatchPath_
              << std::endl;
  }

  std::string lastAction;
  while (!state.gameOver && state.tick < settings.agentMaxTicks_) {
    writeWatchFile(state, lastAction, settings.agentWatchPath_);
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
  writeWatchFile(state, lastAction, settings.agentWatchPath_);
  printGameOver(state);
}
