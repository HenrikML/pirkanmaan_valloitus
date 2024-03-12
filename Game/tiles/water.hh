#ifndef WATER_HH
#define WATER_HH

#include "tiles/tilebase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The Water class represents Water in the gameworld.
 *
 * Water has BasicProduction: \n
 * * Money = 0
 * * Food = 7
 * * Wood = 0
 * * Stone = 0
 * * Ore = 2
 *
 */
class Water : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Water() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Water(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 1,
         const Course::ResourceMap& production = Course::ConstResourceMaps::WATER_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // WATER_HH
