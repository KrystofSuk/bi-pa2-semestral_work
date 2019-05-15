#ifndef UI_H
#define UI_H

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <dirent.h>

#include "maps.h"
#include "../extras/file.h"

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic
{
/**
 * @brief Abstract class for UI
 * 
 */
struct GameUI
{
public:
    /**
     * @brief Construct a new Game UI
     * 
     */
    GameUI();
    /**
     * @brief Draws to cout wanted UI
     * 
     */
    virtual void Draw() const = 0;
    /**
     * @brief Method for cursor move reaction
     * 
     * @param x movement
     * @param y movement
     */
    virtual void Move(const int &x, const int &y) = 0;
    /**
     * @brief Reaction for continue button
     * 
     */
    virtual void Continue() = 0;
    /**
     * @brief Get the int of current state
     * 
     * @return const int state
     */
    virtual const int GetState() const = 0;
    /**
     * @brief Get the msg from UI
     * 
     * @return const std::string message
     */
    virtual const std::string GetMsg() const = 0;
    /**
     * @brief Destroy the UI object
     * 
     */
    virtual ~GameUI();
};
/**
 * @brief Main Menu UI
 * 
 */
class GameMainMenuUI : public GameUI
{
private:
    int current = 0;

public:
    /**
     * @brief Construct a new Main Menu UI
     * 
     */
    GameMainMenuUI();
    /**
     * @brief Draws to cout wanted UI
     * 
     */
    void Draw() const;
    /**
     * @brief Method for cursor move reaction
     * 
     * @param x movement
     * @param y movement
     */
    void Move(const int &x, const int &y);
    /**
     * @brief Reaction for continue button
     * 
     */
    void Continue();
    /**
     * @brief Get the int of current state
     * 
     * @return const int state
     */
    const int GetState() const;
    /**
     * @brief Get the msg from UI
     * 
     * @return const std::string message
     */
    const std::string GetMsg() const;
    /**
     * @brief Destroy the UI object
     * 
     */
    ~GameMainMenuUI();
};
/**
 * @brief Help UI
 * 
 */
class GameHelpUI : public GameUI
{
private:
public:
    /**
     * @brief Construct a new Help UI 
     * 
     */
    GameHelpUI();
    /**
     * @brief Draws to cout wanted UI
     * 
     */
    void Draw() const;
    /**
     * @brief Method for cursor move reaction
     * 
     * @param x movement
     * @param y movement
     */
    void Move(const int &x, const int &y);
    /**
     * @brief Reaction for continue button
     * 
     */
    void Continue();
    /**
     * @brief Get the int of current state
     * 
     * @return const int state
     */
    const int GetState() const;
    /**
     * @brief Get the msg from UI
     * 
     * @return const std::string message
     */
    const std::string GetMsg() const;
    /**
     * @brief Destroy the UI object
     * 
     */
    virtual ~GameHelpUI();
};
/**
 * @brief Level Select UI
 * 
 */
class GameLevelSelectUI : public GameUI
{
private:
    std::vector<std::string> _lvls;
    std::vector<bool> _valid;
    int current = 0;

public:
    /**
     * @brief Construct a new Level Select UI
     * 
     */
    GameLevelSelectUI();
    /**
     * @brief Draws to cout wanted UI
     * 
     */
    void Draw() const;
    /**
     * @brief Method for cursor move reaction
     * 
     * @param x movement
     * @param y movement
     */
    void Move(const int &x, const int &y);
    /**
     * @brief Reaction for continue button
     * 
     */
    void Continue();
    /**
     * @brief Get the int of current state
     * 
     * @return const int state
     */
    const int GetState() const;
    /**
     * @brief Get the msg from UI
     * 
     * @return const std::string message
     */
    const std::string GetMsg() const;
    /**
     * @brief Destroy the UI object
     * 
     */
    virtual ~GameLevelSelectUI();
};

} // namespace GameLogic
#endif