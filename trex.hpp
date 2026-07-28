#ifndef TREX_H
#define TREX_H

#include "clawd_asset.hpp"
#include "sprite.hpp"
#include "sprite_asset.hpp"
#include "sprite_asset_ascii.hpp"

enum class TrexAssetName { JUMP, RUN1, RUN2, DOWN1, DOWN2, IDLE };
enum class TrexType { ASCII, UNICODE };
enum class TrexStatus { RUNNING, JUMPING, DOWN };

struct EyePos {
  int row_;
  int col_;
};

struct EyePack {
  EyePos normal_;
  EyePos down_;
};

struct MouthPack {
  EyePos normal_;
  EyePos down_;
};

struct Physics {
  float gravity_;
  float jumpImpulse_;
  float maxFallVelocity_;
};

struct TrexAssetPack {
  const SpriteAsset& jump_;
  const SpriteAsset& run1_;
  const SpriteAsset& run2_;
  const SpriteAsset& down1_;
  const SpriteAsset& down2_;
  const SpriteAsset& idle_;
  EyePack eyes_;
  MouthPack mouth_;
};

const TrexAssetPack TREX_UNICODE_PACK{CLAWD_ASSET_JUMP,
                                      CLAWD_ASSET_RUN1,
                                      CLAWD_ASSET_RUN2,
                                      CLAWD_ASSET_DOWN1,
                                      CLAWD_ASSET_DOWN2,
                                      CLAWD_ASSET_IDLE,
                                      EyePack{{2, 5}, {4, 5}},
                                      MouthPack{{4, 5}, {5, 5}}};

const TrexAssetPack TREX_ASCII_PACK{
    CLAWD_ASSET_JUMP,         CLAWD_ASSET_RUN1,
    CLAWD_ASSET_RUN2,         CLAWD_ASSET_DOWN1,
    CLAWD_ASSET_DOWN2,        CLAWD_ASSET_IDLE,
    EyePack{{2, 5}, {4, 5}},  MouthPack{{4, 5}, {5, 5}}};

class Game;

class Trex : public SpriteInstance {
 private:
  const TrexAssetPack& pack_;

 public:
  Physics physics_;
  TrexStatus currentStatus_ = TrexStatus::RUNNING;
  TrexAssetName name_;
  bool legChange_ = true;
  float legTimer_ = 0.0f;
  const float LEG_SWITCH_INTERVAL = 0.2f;
  float vy_ = 0.0f;
  float dunktime_ = 0.0f;
  int paddingLeft_ = 4;
  int maxHeight_ = 0;
  Trex(const Trex&) = default;
  Trex(Trex&&) = default;
  Trex& operator=(const Trex&) = delete;
  Trex& operator=(Trex&&) = delete;
  Trex(const TrexAssetPack& sp, TrexType t = TrexType::UNICODE, int top = -1,
       int left = -1, Game* g = nullptr);
  Game* game_;
  TrexType type_;
  void setAsset(const SpriteAsset& newAsset);
  void changeAsset(TrexAssetName name);
  void pressJump();
  void fallFast();
  void crouch();
  void standUP();
  void update(float dt);
  void updateLeg(float dt);
  void changeEye();
  void changeMouth();
  void reset();

  const SpriteAsset& getAsset() const;
  int getWidth();
  int getHeight();
};
#endif
