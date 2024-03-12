#ifndef SWAMP_H
#define SWAMP_H

#include "tiles/tilebase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The Swamp class represents Swamp in the gameworld.
 *
 * Swamp has BasicProduction: \n
 * * Money = 2
 * * Food = 1
 * * Wood = 4
 * * Stone = 1
 * * Ore = 1
 *
 */
class Swamp : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Swamp() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Swamp(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = Course::ConstResourceMaps::SWAMP_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Swamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // SWAMP_H
