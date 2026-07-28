#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "version.hpp"

namespace CLI_Parser {
struct GameSettings {
  bool asciiOnly_ = false;
  bool obstacleDino_ = true;
  int keyRepeat_ = 200;
  bool skipIntro_ = false;
  bool agentMode_ = false;
  bool agentRender_ = false;
  std::string agentWatchPath_;
  int agentSeed_ = 7;
  int agentMaxTicks_ = 300;
};

inline void printHelp() {
  std::cout << "TermRex Runner Game CLI\n"
            << "=======================\n\n"
            << "Usage:\n"
            << "    termrex [options]\n\n"
            << "Options:\n"
            << "    -h, --help               Show this help menu\n"
            << "    -v, --version            Show game version\n"
            << "    --ascii-only             Use ASCII characters only\n"
            << "    --unicode                Use Unicode characters (default)\n"
            << "    --no-obstacle-dino       Disable flying dinosaur "
            << "(Pterodactyl) obstacles\n"
            << "    --keyrepeat <ms>         Set custom key repeat delay in "
            << "milliseconds\n"
            << "    --skip-intro             Skip the intro screen and start "
            << "game immediately\n"
            << "    --agent-mode             Use line-based stdin/stdout mode "
            << "for agents\n"
            << "    --agent-render           Show a small ASCII scene in "
            << "agent mode\n"
            << "    --agent-watch <file>     Write a live-refreshing HTML "
            << "watch view\n"
            << "    --agent-seed <n>         Set agent-mode obstacle seed "
            << "(default 7)\n"
            << "    --agent-max-ticks <n>    Stop agent mode after this many "
            << "ticks (default 300)\n";
}

inline void printVersion() {
  std::cout << "v" << TERMREX_VERSION_STRING << "\n";
}

inline GameSettings parseArguments(int argc, char* argv[]) {
  GameSettings settings;
  static const struct option LONG_OPTIONS[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 'v'},
      {"ascii-only", no_argument, 0, 0},
      {"unicode", no_argument, 0, 0},
      {"no-obstacle-dino", no_argument, 0, 0},
      {"keyrepeat", required_argument, 0, 0},
      {"skip-intro", no_argument, 0, 0},
      {"agent-mode", no_argument, 0, 0},
      {"agent-render", no_argument, 0, 0},
      {"agent-watch", required_argument, 0, 0},
      {"agent-seed", required_argument, 0, 0},
      {"agent-max-ticks", required_argument, 0, 0},
      {0, 0, 0, 0}};

  int optionIndex = 0;
  int c;
  optind = 1;
  while ((c = getopt_long(argc, argv, "hv", LONG_OPTIONS, &optionIndex)) !=
         -1) {
    if (c == 'h') {
      printHelp();
      exit(0);
    } else if (c == 'v') {
      printVersion();
      exit(0);
    } else if (c == 0) {
      std::string optname = LONG_OPTIONS[optionIndex].name;
      if (optname == "ascii-only") {
        settings.asciiOnly_ = true;
      } else if (optname == "unicode") {
        settings.asciiOnly_ = false;
      } else if (optname == "no-obstacle-dino") {
        settings.obstacleDino_ = false;
      } else if (optname == "skip-intro") {
        settings.skipIntro_ = true;
      } else if (optname == "agent-mode") {
        settings.agentMode_ = true;
      } else if (optname == "agent-render") {
        settings.agentMode_ = true;
        settings.agentRender_ = true;
      } else if (optname == "agent-watch") {
        settings.agentMode_ = true;
        if (optarg) {
          settings.agentWatchPath_ = optarg;
        }
      } else if (optname == "agent-seed") {
        if (optarg) {
          settings.agentSeed_ = std::stoi(optarg);
        }
      } else if (optname == "agent-max-ticks") {
        if (optarg) {
          settings.agentMaxTicks_ = std::stoi(optarg);
          if (settings.agentMaxTicks_ < 1) {
            std::cerr << "Error: --agent-max-ticks must be positive.\n";
            exit(1);
          }
        }
      } else if (optname == "keyrepeat") {
        if (optarg) {
          try {
            settings.keyRepeat_ = std::stoi(optarg);
            if (settings.keyRepeat_ < 50) {
              std::cerr << "Warning: Key repeat delay is very low ("
                        << settings.keyRepeat_
                        << "ms). Performance may suffer.\n";
              exit(1);
            } else if (settings.keyRepeat_ > 1200) {
              std::cerr << "Warning: Key repeat delay is very high ("
                        << settings.keyRepeat_
                        << "ms). Performance may suffer.\n";
              exit(1);
            }
          } catch (const std::exception& e) {
            std::cerr << "Error: Invalid number for --keyrepeat: " << optarg
                      << ". Must be an integer.\n";
            exit(1);
          }
        } else {
          std::cerr << "Error: --keyrepeat requires a numeric argument.\n";
          exit(1);
        }
      }
    } else if (c == '?') {
      exit(1);
    } else {
      std::cerr << "Unknown error during argument parsing (c=" << c << ").\n";
      exit(1);
    }
  }

  return settings;
}
}  // namespace CLI_Parser

#endif
