#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "ui.h"
#include "game.h"

using namespace std;

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic
{


struct GameUI
{
public:
    GameUI();
    virtual void Draw() const = 0;
    virtual void Move(int x, int y) = 0;
    virtual void Continue() = 0;
    virtual int GetState() const = 0;
    virtual string GetMsg() const = 0;
    virtual ~GameUI();
};

class GameMainMenuUI : public GameUI
{
private:
    int current = 0;
public:
    GameMainMenuUI();
    void Draw() const;
    void Move(int x, int y);
    void Continue();
    int GetState() const;
    string GetMsg() const;
    virtual ~GameMainMenuUI();
};

class GameHelpUI : public GameUI
{
private:
public:
    GameHelpUI();
    void Draw() const;
    void Move(int x, int y);
    void Continue();
    int GetState() const;
    string GetMsg() const;
    virtual ~GameHelpUI();
};

class GameLevelSelectUI : public GameUI
{
private:
    vector<string> _lvls;
    vector<bool> _valid;
    int current = 0;
public:
    GameLevelSelectUI();
    void Draw() const;
    void Move(int x, int y);
    void Continue();
    int GetState() const;
    string GetMsg() const;
    virtual ~GameLevelSelectUI();
};



} // namespace GameLogic
#endif