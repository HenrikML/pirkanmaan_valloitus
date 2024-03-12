#ifndef FISHER_HH
#define FISHER_HH

#include "workers/workerbase.h"
#include "core/gameresourcemaps.hh"

namespace Worker {

/**
 * @brief The Fisher class represents a fisher in the game.
 *
 * Fisher has following production-efficiency: \n
 * * Money - 0.25 \n
 * * Food - 4.00 \n
 * * Wood - 0.25 \n
 * * Stone - 0.20 \n
 * * Ore - 0.25 \n
 *
 * Fisher consume Food and money. \n
 * * 1 Food - Or Fisher refuses to work. \n
 * * 1 Money - Or Fisher works at 50% efficiency. \n
 * * Resourcefocus adds 25% efficiency for the focused resource,
 * even if the worker is refusing work.
 */
class Fisher : public Course::WorkerBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Fisher() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     */
    Fisher(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                  const std::shared_ptr<Course::iObjectManager>& objectmanager,
                  const std::shared_ptr<Course::PlayerBase>& owner,
                  const int& tilespaces = 1,
                  const Course::ResourceMap& cost =
                      Course::ConstResourceMaps::FA_RECRUITMENT_COST,
                  const Course::ResourceMapDouble& efficiency =
                      Course::ConstResourceMaps::FA_WORKER_EFFICIENCY
                  );

    /**
     * @brief Default destructor.
     */
    virtual ~Fisher() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Check if the worker can be placed on the Tile according to
     * it's placement rule. Only rule is that the Tile must have same owner
     * as the worker.
     * @param target is the Tile that worker is being placed on.
     * @return
     * True - If baseclass' method return true and target Tile has space
     * for worker.
     * False - If both conditions aren't met.
     * @note Override to change placement rules for derived worker.
     * @post Exception guarantee: Basic
     */
    virtual bool canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const override;

    /**
     * @brief Performs the Worker's default action.
     */
    virtual void doSpecialAction() override;

    /**
     * @brief Returns Worker's efficiency at resource production.
     * Worker consumes FOOD and MONEY. Resource consumption and resource
     * focus determine final multiplier that is based on WORKER_EFFICIENCY.
     *
     * @return
     */
    virtual const Course::ResourceMapDouble tileWorkAction() override;
};
}
#endif // FISHER_HH
