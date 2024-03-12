#ifndef TRAINEDWORKER_H
#define TRAINEDWORKER_H

#include "workers/workerbase.h"
#include "core/gameresourcemaps.hh"

/**
 * @brief The TrainedWorker class represents a trained worker in the game.
 *
 * Worker has following production-efficiency: \n
 * * Money - 0.75 \n
 * * Food - 2.00 \n
 * * Wood - 1.50 \n
 * * Stone - 1.00 \n
 * * Ore - 1.00 \n
 *
 * TrainedWorkers consume Food and money. \n
 * * 1 Food - Or TrainedWorker refuses to work. \n
 * * 1 Money - Or TrainedWorker works at 50% efficiency. \n
 * * Resourcefocus adds 25% efficiency for the focused resource,
 * even if the worker is refusing work.
 */
class TrainedWorker : public Course::WorkerBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    TrainedWorker() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     */
    TrainedWorker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                  const std::shared_ptr<Course::iObjectManager>& objectmanager,
                  const std::shared_ptr<Course::PlayerBase>& owner,
                  const int& tilespaces = 1,
                  const Course::ResourceMap& cost =
                      Course::ConstResourceMaps::TW_RECRUITMENT_COST,
                  const Course::ResourceMapDouble& efficiency =
                      Course::ConstResourceMaps::TW_WORKER_EFFICIENCY
                  );

    /**
     * @brief Default destructor.
     */
    virtual ~TrainedWorker() = default;

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

    // ADD OVERRIDEN FUNCTION tileWorkAction()


};

#endif // TRAINEDWORKER_H
