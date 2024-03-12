#ifndef DESERT_H
#define DESERT_H

#include "tiles/tilebase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The Desert class represents Desert in the gameworld.
 *
 * Desert has BasicProduction: \n
 * * Money = 0
 * * Food = 0
 * * Wood = 0
 * * Stone = 2
 * * Ore = 1
 *
 */
class Desert : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Desert() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Desert(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 1,
         const Course::ResourceMap& production = Course::ConstResourceMaps::DESERT_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Desert() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // DESERT_H
