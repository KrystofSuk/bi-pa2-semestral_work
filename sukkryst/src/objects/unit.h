#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>

#include "../game/maps.h"
#include "../game/enums.h"

namespace GameLogic
{
/**
 * @brief Unit resistant class which processes resistance to specific attack
 * 
 */
struct UnitResistance
{
protected:
    int _resistance;

public:
    /**
     * @brief Construct a new Resistance
     * 
     * @param res index of resistance
     */
    UnitResistance(const int &res);

    /**
     * @brief Processes resistance
     * 
     * @param type attack type 
     * @return true unit is not resistant
     * @return false unit is resistant
     */
    virtual const bool ProcessResistance(const AttackType &type) const = 0;

    /**
     * @brief Destroy the Resistance
     * 
     */
    virtual ~UnitResistance();
};
/**
 * @brief Unit abstract class
 * 
 */
struct Unit
{
protected:
    std::pair<int, int> _pos = std::make_pair<int, int>(0, 0);
    int _hp = 0;
    int _atk = 0;
    char _c = 'u';
    Color _col = White;
    std::string _name = "";
    int _movType = 0;
    std::vector<std::pair<int, int>> _path;

public:
    /**
     * @brief Construct a new Unit
     * 
     */
    Unit();
    /**
     * @brief Construct a new Unit with filename
     * 
     * @param n filename in examples/units
     */
    Unit(const std::string &n);

    /**
     * @brief Checks if unit is alive
     * 
     * @return true unit is living
     * @return false unit is dead
     */
    const bool IsAlive() const;
    /**
     * @brief Get the attack of unit
     * 
     * @return const int& attack
     */
    const int & GetAtk() const;
    /**
     * @brief Gets health of unit
     * 
     * @return const int& health
     */
    const int & GetHP() const;
    /**
     * @brief Get the type number of object
     * 
     * @return const int type
     */
    virtual const int GetType() const = 0;

    /**
     * @brief Sets helath of unit
     * 
     * @param hp wanted health
     */
    void SetHP(const int & hp);
    /**
     * @brief Get the distance fom position
     * 
     * @param pos wanted position
     * @return const int distance 
     */
    const int GetDistance(const std::pair<int, int> & pos) const;
    /**
     * @brief Get the position
     * 
     * @return const std::pair<int, int>& position
     */
    const std::pair<int, int> & GetPos() const;
    /**
     * @brief Clears current path of unit
     * 
     */
    void ClearPath();
    
    /**
     * @brief Sets the char array which will be drawn
     * 
     * @param c drawing array
     */
    virtual void GetChar(char **c) const;
    /**
     * @brief Sets the color array which will be drawn
     * 
     * @param c coloring array
     */
    virtual void GetColor(Color **c) const;

    /**
     * @brief Processes incoming attack
     * 
     * @param a attack
     * @param atk type
     */
    virtual void ProcessAttack(const int &a, const AttackType &atk) = 0;
    /**
     * @brief Move unit
     * 
     * @param m map reference
     */
    virtual void Move(const Map &m) = 0;
    /**
     * @brief Prints unit to ui
     * 
     * @param os output stream
     */
    virtual void Print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Unit &obj)
    {
        obj.Print(os);
        return os;
    }

    /**
     * @brief Destroy the Unit
     * 
     */
    virtual ~Unit();
};

} // namespace GameLogic
#endif