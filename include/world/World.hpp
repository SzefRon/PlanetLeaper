#pragma once

#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"

#include "Block.hpp"
#include "entity/Entity.hpp"
#include "GravityCenter.hpp"

class World
{
private:
    const float collision_step = 0.5f;
    void update_entities(float dt);
    void update_entity_gravity(Entity *const &entity);
    bool interpolate_collision(Entity *const &entity);
    bool check_collision_step(Entity *const &entity);

public:
    std::unordered_map<glm::ivec2, Block> world_grid;
    std::unordered_set<Entity *> entities;
    std::vector<GravityCenter> gravity_centers;

    void generate_planet(glm::ivec2 center_pos, int radius, BlockType block_type);

    void update(float dt);
};