#ifndef HILL_HH
#define HILL_HH

#include "tiles/tilebase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The Desert class represents Desert in the gameworld.
 *
 * Desert has BasicProduction: \n
 * * Money = 1
 * * Food = 3
 * * Wood = 2
 * * Stone = 2
 * * Ore = 2
 *
 * Building on hills takes time. So buildings get an extra hold-marker.
 */
class Hill : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Hill() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Hill(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 2,
         const unsigned int& max_work = 2,
         const Course::ResourceMap& production = Course::ConstResourceMaps::HILL_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Hill() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in hill adds
     * one hold-marker to the building.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase> &building) override;

    void removeBuilding(const std::shared_ptr<Course::BuildingBase> &building) override;

    void addWorker(const std::shared_ptr<Course::WorkerBase> &worker) override;

    void removeWorker(const std::shared_ptr<Course::WorkerBase> &worker) override;




};

#endif // HILL_HH
