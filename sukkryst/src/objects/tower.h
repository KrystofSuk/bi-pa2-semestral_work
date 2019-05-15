#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <math.h>

#include "../game/maps.h"
#include "../game/enums.h"
#include "unit.h"
#include "../extras/file.h"

namespace GameLogic
{
/**
 * @brief Tower abstract class
 * 
 */
struct Tower
{
public:
    /**
     * @brief Construct a new Tower
     * 
     */
    Tower();
    /**
     * @brief Construct a new Tower and sets its position
     * 
     * @param p tower position
     */
    Tower(const std::pair<int, int> & p);

    /**
     * @brief Get the attack of tower
     * 
     * @return const std::pair<int, AttackType> it's damage , attack type 
     */
    const std::pair<int, AttackType> GetAttack() const;
    /**
     * @brief Get the position of tower
     * 
     * @return const std::pair<int, int>& position
     */
    const std::pair<int, int> & GetPos() const;
    /**
     * @brief Get the price of tower
     * 
     * @return const int& price
     */
    const int & GetPrice() const;
    /**
     * @brief Get the distance of attack of tower
     * 
     * @return const int& distance
     */
    const int & GetDistance() const;
    /**
     * @brief Get the type number of object
     * 
     * @return const int type
     */
    virtual const int GetType() const = 0;

    /**
     * @brief Sets the char array which will be drawn
     * 
     * @param c drawing array
     */
    virtual void GetChar(char **c) const = 0;
    /**
     * @brief Sets the color array which will be drawn
     * 
     * @param c coloring array
     */
    virtual void GetColor(Color **c) const = 0;
    /**
     * @brief UI print of tower
     * 
     * @param os output stream
     */
    virtual void Print(std::ostream &os) const = 0;
    /**
     * @brief Attack process for all units in the field
     * 
     * @param units
     */
    virtual void ProcessAttack(std::vector<Unit *> &units) = 0;

    friend std::ostream &operator<<(std::ostream &os, const Tower &obj)
    {
        obj.Print(os);
        return os;
    }

    /**
     * @brief Destroy the Tower
     * 
     */
    virtual ~Tower();

protected:
    char _c;
    Color _col;
    int _price;
    int _atk;
    int _distance;
    AttackType _type;
    std::string _name;
    std::pair<int, int> _pos;
};

/**
 * @brief Basic tower for multiple uses
 * 
 */
class BasicTower : public Tower
{
public:
    /**
     * @brief Construct a new Basic Tower
     * 
     * @param p position
     * @param n filename in examples/towers
     */
    BasicTower(const std::pair<int, int> & p, const std::string & n);
    /**
     * @brief Attack process for all units in the field and selects the nearest one and apply damage to him
     * 
     * @param units
     */
    virtual void ProcessAttack(std::vector<Unit *> &units);

    /**
     * @brief Sets the char array which will be drawn
     * 
     * @param c drawing array
     */
    void GetChar(char **c) const;
    /**
     * @brief Sets the color array which will be drawn
     * 
     * @param c coloring array
     */
    void GetColor(Color **c) const;
    /**
     * @brief UI print of tower
     * 
     * @param os output stream
     */
    void Print(std::ostream &os) const;
    
    /**
     * @brief Get the type number of object which is -2
     * 
     * @return const int type
     */
    virtual const int GetType() const;
    /**
     * @brief Destroy the Basic Tower object
     * 
     */
    virtual ~BasicTower();
};

class FireTower : public BasicTower
{
public:
    /**
     * @brief Construct a new Fire Tower
     * 
     * @param p position
     * @param n filename in examples/towers
     */
    FireTower(const std::pair<int, int> & p, const std::string & n);
    
    /**
     * @brief Get the type number of object which is -3
     * 
     * @return const int type
     */
    virtual const int GetType() const;

    /**
     * @brief Destroy the Fire Tower
     * 
     */
    virtual ~FireTower();
};

class IceTower : public BasicTower
{
public:
    /**
     * @brief Construct a new Ice Tower
     * 
     * @param p position
     * @param n filename in examples/towers
     */
    IceTower(const std::pair<int, int> & p, const std::string & n);

    /**
     * @brief Get the type number of object which is -4
     * 
     * @return const int type
     */
    virtual const int GetType() const;

    /**
     * @brief Destroy the Ice Tower
     * 
     */
    virtual ~IceTower();
};

class MortarTower : public BasicTower{
public:
    /**
     * @brief Construct a new Mortar Tower
     * 
     * @param p position
     * @param n filename in examples/towers
     */
    MortarTower(const std::pair<int, int> & p, const std::string & n);

    /**
     * @brief Get the type number of object which is -5
     * 
     * @return const int type
     */
    virtual const int GetType() const;

    /**
     * @brief Attack process for all units in the field and selects all enemies in area and apply damage to them
     * 
     * @param units
     */
    virtual void ProcessAttack(std::vector<Unit *> &units);

    /**
     * @brief Destroy the Mortar Tower
     * 
     */
    virtual ~MortarTower();
};

}
#endif