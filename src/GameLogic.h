#pragma once

#include "Cell.h"
#include "Figure.h"
#include "DropSparkle.h"
#include "DropTrail.h"
#include "Bindings.h"

#pragma warning(disable : 4512)

class GameLogic
{
private:
  const int maxLevel;
  double lastStepTimer;

  void initGameProceed(int glassWidth, int glassHeight);
  void playingGameProceed();
  float getStepTime();
  void shiftFigureConveyor();
  bool checkCurrentFigurePos(int dx, int dy);
  bool tryToPlaceCurrentFigure();
  void checkGlassRows();
  void proceedFallingRows();
  void createDropTrail(int x, int y, int height, Globals::Color color);
  void deleteObsoleteEffects();

public:
  enum GameState { gsStartGame, gsPlayingGame, gsPauseGame, gsGameOver };
  enum MenuState { msNone, msMainMenu, msQuitConfirmation};
  Bindings bindings;
  GameState gameState;
  std::vector<Cell> glass;
  Figure nextFigures[Globals::nextFiguresCount];
  Figure holdFigure;
  Figure curFigure;
  int glassWidth = 10;
  int glassHeight = 20;
  int curFigureX;
  int curFigureY;
  int curScore;
  int curGoal;
  int curLevel;
  bool fastDown;
  bool haveHold;
  bool justHolded;
  bool haveFallingRows;
  double rowsDeleteTimer;
  std::vector<int> rowElevation;
  std::vector<float> rowCurrentElevation;
  std::list<DropTrail> dropTrails;
  const float rowsDeletionEffectTime;
  std::vector<int> deletedRows;
  struct CellCoord
  { 
    int x, y; 
    inline CellCoord(int x, int y) : x(x), y(y) {}
    inline bool operator < (const CellCoord & left) const { return left.x < x || (left.x == x && left.y < y); }
  };
  std::set<CellCoord> deletedRowGaps;

  GameLogic();
  ~GameLogic();

  void update();

  void holdCurrentFigure();
  void dropCurrentFigure();
  void rotateCurrentFigureLeft();
  void rotateCurrentFigureRight();
  void shiftCurrentFigureLeft();
  void shiftCurrentFigureRight();
  void storeCurFigureIntoGlass();
};