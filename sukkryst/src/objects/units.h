#ifndef UNITS_H
#define UNITS_H

#include <string>
#include <iostream>
#include <limits>
#include <math.h>

#include "unit.h"
#include "../game/maps.h"
#include "../game/enums.h"
#include "../extras/file.h"

namespace GameLogic
{
/**
 * @brief Slime unit class
 * 
 */
class Slime : public Unit
{
public:
    /**
     * @brief Construct a new Slime
     * 
     */
    Slime();
    /**
     * @brief Construct a new Slime
     * 
     * @param s start position
     */
    Slime(const std::pair<int, int> & s);
    /**
     * @brief Construct a new Slime
     * 
     * @param s start position
     * @param n filename in examples/units
     */
    Slime(const std::pair<int, int> & s, const std::string & n);
    
    /**
     * @brief Get the type number of object for slime it's 0
     * 
     * @return const int type
     */
    virtual const int GetType() const;
    
    /**
     * @brief Processes incoming attack
     * 
     * @param a attack
     * @param atk type
     */
    virtual void ProcessAttack(const int &a, const AttackType &atk);
    /**
     * @brief Prints unit to ui
     * 
     * @param os output stream
     */
    virtual void Print(std::ostream &os) const;
    /**
     * @brief Move unit
     * 
     * @param m map reference
     */
    virtual void Move(const Map &m);
    /**
     * @brief Destroy the Slime
     * 
     */
    virtual ~Slime();
};
/**
 * @brief Slime King which is like better slime
 * 
 */
class SlimeKing : public Slime
{
public:
    /**
     * @brief Construct a new Slime King
     * 
     */
    SlimeKing();
    /**
     * @brief Construct a new Slime King
     * 
     * @param s start position
     */
    SlimeKing(const std::pair<int, int> & s);
    /**
     * @brief Get the type number of object for slimeking it's 1
     * 
     * @return const int type
     */
    virtual const int GetType() const;
    /**
     * @brief Destroy the Slime King
     * 
     */
    virtual ~SlimeKing();
};
/**
 * @brief Orc, first resistant enemy
 * 
 */
class Orc : public Unit, public UnitResistance
{
public:
    /**
     * @brief Construct a new Orc
     * 
     */
    Orc();
    /**
     * @brief Construct a new Orc
     * 
     * @param s start position
     */
    Orc(const std::pair<int, int> & s);
    /**
     * @brief Get the type number of object for slime it's 0
     * 
     * @return const int type
     */
    virtual const int GetType() const;
    
    /**
     * @brief Processes incoming attack
     * 
     * @param a attack
     * @param atk type
     */
    virtual void ProcessAttack(const int &a, const AttackType &atk);
    /**
     * @brief Prints unit to ui
     * 
     * @param os output stream
     */
    virtual void Print(std::ostream &os) const;
    /**
     * @brief Move unit
     * 
     * @param m map reference
     */
    virtual void Move(const Map &m);
    /**
     * @brief Processes resistance
     * 
     * @param type attack type 
     * @return true unit is not resistant
     * @return false unit is resistant
     */
    const bool ProcessResistance(const AttackType &type) const;
    /**
     * @brief Destroy the Orc
     * 
     */
    virtual ~Orc();
};
/**
 * @brief Golem strongest enemy in game
 * 
 */
class Golem : public Unit, public UnitResistance
{
public:
    Golem();
    Golem(const std::pair<int, int> & s);
    /**
     * @brief Get the type number of object for slime it's 0
     * 
     * @return const int type
     */
    virtual const int GetType() const;
    
    /**
     * @brief Processes incoming attack
     * 
     * @param a attack
     * @param atk type
     */
    virtual void ProcessAttack(const int &a, const AttackType &atk);
    /**
     * @brief Prints unit to ui
     * 
     * @param os output stream
     */
    virtual void Print(std::ostream &os) const;
    /**
     * @brief Move unit
     * 
     * @param m map reference
     */
    virtual void Move(const Map &m);
    /**
     * @brief Processes resistance
     * 
     * @param type attack type 
     * @return true unit is not resistant
     * @return false unit is resistant
     */
    const bool ProcessResistance(const AttackType &type) const;
    /**
     * @brief Destroy the Golem object
     * 
     */
    virtual ~Golem();
};
} // namespace GameLogic
#endif