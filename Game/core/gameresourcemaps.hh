#ifndef RESOURCEMAPS_HH
#define RESOURCEMAPS_HH
#include "core/resourcemaps.h"

namespace Course {

namespace ConstResourceMaps {


// Building - Lumbermill
const ResourceMap LM_BUILD_COST = {
    {BasicResource::MONEY, 100},
    {BasicResource::FOOD, 200},
    {BasicResource::WOOD, 50}
};
const ResourceMap LM_PRODUCTION = {
    {BasicResource::WOOD, 10},
    {BasicResource::MONEY, 2},
};

// Building - FishingHut
const ResourceMap FH_BUILD_COST = {
    {BasicResource::MONEY, 100},
    {BasicResource::FOOD, 200},
    {BasicResource::WOOD, 50}
};
const ResourceMap FH_PRODUCTION = {
    {BasicResource::MONEY, 10},
    {BasicResource::FOOD, 5}
};

// Building - Quarry
const ResourceMap QUARRY_BUILD_COST = {
    {BasicResource::MONEY, 100},
    {BasicResource::FOOD, 200},
    {BasicResource::WOOD, 50}
};
const ResourceMap QUARRY_PRODUCTION = {
    {BasicResource::STONE, 10},
     {BasicResource::ORE, 5}
};

// Building - Mine
const ResourceMap MINE_BUILD_COST = {
    {BasicResource::MONEY, 100},
    {BasicResource::FOOD, 200},
    {BasicResource::WOOD, 50}
};
const ResourceMap MINE_PRODUCTION = {
    {BasicResource::MONEY, 5},
    {BasicResource::ORE, 10}
};

// Building - EmploymentOffice
const ResourceMap EMPLOYMENT_OFFICE_BUILD_COST = {
    {BasicResource::MONEY, 200},
    {BasicResource::STONE, 200},
    {BasicResource::ORE, 200},
    {BasicResource::WOOD, 150}
};

const ResourceMap EMPLOYMENT_OFFICE_PRODUCTION = {
    {BasicResource::MONEY, 5},
};

// Worker - TrainedWorker
const ResourceMapDouble TW_WORKER_EFFICIENCY = {
    {MONEY, 0.75},
    {FOOD, 2.00},
    {WOOD, 1.50},
    {STONE, 1.00},
    {ORE, 1.00}
};

const ResourceMap TW_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

// Worker - Miner
const ResourceMapDouble MI_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 0.25},
    {WOOD, 0.25},
    {STONE, 1.00},
    {ORE, 3.00}
};

const ResourceMap MI_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

// Worker - Lumberjack
const ResourceMapDouble LJ_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 0.25},
    {WOOD, 3.00},
    {STONE, 0.25},
    {ORE, 0.25}
};

const ResourceMap LJ_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

// Worker - Farmer
const ResourceMapDouble FA_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 4.00},
    {WOOD, 0.25},
    {STONE, 0.25},
    {ORE, 0.25}
};

const ResourceMap FA_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

// Worker - Fisher
const ResourceMapDouble FISHER_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 4.00},
    {WOOD, 0.25},
    {STONE, 0.25},
    {ORE, 0.25}
};

const ResourceMap FISHER_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

// Worker - Stonemason
const ResourceMapDouble SM_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 0.25},
    {WOOD, 0.25},
    {STONE, 3.00},
    {ORE, 1.00}
};

const ResourceMap SM_RECRUITMENT_COST = {
    {MONEY, 50},
    {FOOD, 25}
};

const ResourceMap HILL_BP = {
    {MONEY, 1},
    {FOOD, 3},
    {WOOD, 2},
    {STONE, 2},
    {ORE, 2},
};

const ResourceMap SWAMP_BP = {
    {MONEY, 2},
    {FOOD, 1},
    {WOOD, 4},
    {STONE, 1},
    {ORE, 1},
};

const ResourceMap DESERT_BP = {
    {MONEY, 0},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 2},
    {ORE, 1},
};

const ResourceMap WATER_BP = {
    {MONEY, 0},
    {FOOD, 7},
    {WOOD, 0},
    {STONE, 0},
    {ORE, 2},
};

}
}


#endif // RESOURCEMAPS_HH
