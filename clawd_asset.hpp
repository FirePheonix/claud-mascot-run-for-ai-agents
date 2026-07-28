#ifndef CLAWD_ASSET_HPP
#define CLAWD_ASSET_HPP

#include "sprite_asset.hpp"

#define CLAWD_ORANGE "\033[48;5;208m"
#define CLAWD_EYE "\033[48;5;232m"
#define CLAWD_RESET "\033[0m"

const static std::vector<int> CLAWD_EMPTY_ROW = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const static std::vector<int> CLAWD_TOP_ROW = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

const static std::vector<int> CLAWD_FACE_ROW = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

const static std::vector<int> CLAWD_HAND_ROW = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

const static std::vector<int> CLAWD_BODY_ROW = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

const static std::vector<int> CLAWD_LEGS_ROW = {
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0};

const static std::vector<std::string> CLAWD_ART_TOP = {
    "  " CLAWD_ORANGE "                " CLAWD_RESET "  ",
    "  " CLAWD_ORANGE "  " CLAWD_EYE "  " CLAWD_ORANGE
    "        " CLAWD_EYE "  " CLAWD_ORANGE "  " CLAWD_RESET "  ",
    CLAWD_ORANGE "                    " CLAWD_RESET,
    CLAWD_ORANGE "                    " CLAWD_RESET,
    "  " CLAWD_ORANGE "                " CLAWD_RESET "  ",
    "  " CLAWD_ORANGE "                " CLAWD_RESET "  ",
};

const static std::string CLAWD_ART_LEGS =
    "  " CLAWD_ORANGE "  " CLAWD_RESET "  " CLAWD_ORANGE
    "  " CLAWD_RESET "  " CLAWD_ORANGE "  " CLAWD_RESET
    "  " CLAWD_ORANGE "  " CLAWD_RESET "    ";

const static std::vector<std::string> CLAWD_ART_IDLE = {
    CLAWD_ART_TOP[0], CLAWD_ART_TOP[1], CLAWD_ART_TOP[2], CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4], CLAWD_ART_TOP[5], CLAWD_ART_LEGS,   CLAWD_ART_LEGS,
};

const static std::vector<std::string> CLAWD_ART_RUN1 = {
    CLAWD_ART_TOP[0], CLAWD_ART_TOP[1], CLAWD_ART_TOP[2], CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4], CLAWD_ART_TOP[5], CLAWD_ART_LEGS,   "                    ",
};

const static std::vector<std::string> CLAWD_ART_RUN2 = {
    CLAWD_ART_TOP[0], CLAWD_ART_TOP[1], CLAWD_ART_TOP[2], CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4], CLAWD_ART_TOP[5], "                    ", CLAWD_ART_LEGS,
};

const static std::vector<std::string> CLAWD_ART_JUMP = {
    CLAWD_ART_TOP[0], CLAWD_ART_TOP[1], CLAWD_ART_TOP[2], CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4], CLAWD_ART_TOP[5], CLAWD_ART_LEGS,   CLAWD_ART_LEGS,
};

const static std::vector<std::string> CLAWD_ART_DOWN1 = {
    "                    ", "                    ", CLAWD_ART_TOP[0],
    CLAWD_ART_TOP[1],    CLAWD_ART_TOP[2],      CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4],    CLAWD_ART_LEGS,
};

const static std::vector<std::string> CLAWD_ART_DOWN2 = {
    "                    ", "                    ", CLAWD_ART_TOP[0],
    CLAWD_ART_TOP[1],    CLAWD_ART_TOP[2],      CLAWD_ART_TOP[3],
    CLAWD_ART_TOP[4],    "                    ",
};

const static SpriteAsset CLAWD_ASSET_IDLE = {
    8,
    20,
    {CLAWD_TOP_ROW,  CLAWD_FACE_ROW, CLAWD_HAND_ROW, CLAWD_HAND_ROW,
     CLAWD_BODY_ROW, CLAWD_BODY_ROW, CLAWD_LEGS_ROW, CLAWD_LEGS_ROW},
    CLAWD_ART_IDLE,
};

const static SpriteAsset CLAWD_ASSET_RUN1 = {
    8,
    20,
    {CLAWD_TOP_ROW,  CLAWD_FACE_ROW, CLAWD_HAND_ROW, CLAWD_HAND_ROW,
     CLAWD_BODY_ROW, CLAWD_BODY_ROW, CLAWD_LEGS_ROW, CLAWD_EMPTY_ROW},
    CLAWD_ART_RUN1,
};

const static SpriteAsset CLAWD_ASSET_RUN2 = {
    8,
    20,
    {CLAWD_TOP_ROW,   CLAWD_FACE_ROW, CLAWD_HAND_ROW, CLAWD_HAND_ROW,
     CLAWD_BODY_ROW,  CLAWD_BODY_ROW, CLAWD_EMPTY_ROW, CLAWD_LEGS_ROW},
    CLAWD_ART_RUN2,
};

const static SpriteAsset CLAWD_ASSET_JUMP = {
    8,
    20,
    {CLAWD_TOP_ROW,  CLAWD_FACE_ROW, CLAWD_HAND_ROW, CLAWD_HAND_ROW,
     CLAWD_BODY_ROW, CLAWD_BODY_ROW, CLAWD_LEGS_ROW, CLAWD_LEGS_ROW},
    CLAWD_ART_JUMP,
};

const static SpriteAsset CLAWD_ASSET_DOWN1 = {
    8,
    20,
    {CLAWD_EMPTY_ROW, CLAWD_EMPTY_ROW, CLAWD_TOP_ROW,  CLAWD_FACE_ROW,
     CLAWD_HAND_ROW,  CLAWD_HAND_ROW,  CLAWD_BODY_ROW, CLAWD_LEGS_ROW},
    CLAWD_ART_DOWN1,
};

const static SpriteAsset CLAWD_ASSET_DOWN2 = {
    8,
    20,
    {CLAWD_EMPTY_ROW, CLAWD_EMPTY_ROW, CLAWD_TOP_ROW,  CLAWD_FACE_ROW,
     CLAWD_HAND_ROW,  CLAWD_HAND_ROW,  CLAWD_BODY_ROW, CLAWD_EMPTY_ROW},
    CLAWD_ART_DOWN2,
};

#endif
