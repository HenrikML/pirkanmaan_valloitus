#ifndef QUARRY_HH
#define QUARRY_HH

#include "buildings/buildingbase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The Quarry class represents a quarry-building in the game.
 *
 * The quarry increases stone production. Production is doubled when built on
 * a hill.
 */
class Quarry : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Quarry() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit Quarry(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::QUARRY_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::QUARRY_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Quarry() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Returns boolean based on wheter the building can or can't be
     * placed on a Tile-object.
     * @param target is a pointer to the target Tile.
     * @return
     * True - Base class' method return true and Tile has space for building.
     * False - If both conditions are not met.
     * @note Override to modify placementrules for derived classes.
     * @post Exception guarantee: Basic
     */
    virtual bool canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const override;
};

#endif // QUARRY_HH
