#include "world/World.hpp"

void World::update_entities(float dt)
{
    for (auto &entity : entities) {
        entity->on_ground = entity->buffer_on_ground;

        update_entity_gravity(entity);

        entity->update_next_pos(dt);

        bool collision_happened = false;
        if (glm::distance(entity->pos, entity->next_pos) > collision_step) {
            collision_happened = interpolate_collision(entity, dt);
        }

        if (!collision_happened) {
            entity->update_pos();
            check_collision_step(entity, dt);
        }

        entity->update(dt);
    }
}

void World::update_entity_gravity(Entity *const &entity)
{
    glm::vec2 final_gravity(0.0f);

    for (auto &gravity_center : gravity_centers) {
        float distance = glm::distance(gravity_center.pos, entity->pos);
        if (distance == 0.0f) continue;

        float force = 100.0f * gravity_center.power / (distance * distance);
        final_gravity += glm::normalize(gravity_center.pos - entity->pos) * force;
    }

    entity->gravity = final_gravity;
}

bool World::interpolate_collision(Entity *const &entity, float dt)
{
    float dist = glm::distance(entity->next_pos, entity->pos);
    int div = glm::ceil(dist / collision_step);
    glm::vec2 d_pos = (entity->next_pos - entity->pos) / (float)div;

    int no_steps = div - 1;
    for (int steps = 0; steps < no_steps; steps++) {
        entity->pos += d_pos;
        if (check_collision_step(entity, dt)) {
            return true;
        }
    }

    return false;
}

bool World::check_collision_step(Entity *const &entity, float dt)
{
    glm::ivec2 center = glm::floor(entity->pos);
    int range = glm::ceil(entity->collision_size);
    int square_side = (2 * range - 1);
    const int square_size = square_side * square_side;

    std::vector<glm::ivec2> blocks_to_check;
    blocks_to_check.reserve(square_size);

    for (int y = center.y - range; y <= center.y + range; y++) {
        for (int x = center.x - range; x <= center.x + range; x++) {
            glm::ivec2 block_pos = {x, y};
            if (world_grid.contains(block_pos)) {
                blocks_to_check.push_back(block_pos);
            }
        }
    }

    std::sort(blocks_to_check.begin(), blocks_to_check.end(), [&](glm::ivec2 a, glm::ivec2 b) {
        return glm::distance(entity->pos, glm::vec2(a)) < glm::distance(entity->pos, glm::vec2(b));
    });

    glm::vec2 final_sep_vec = {0.0f, 0.0f};

    bool collision_happened = false;

    for (auto &block : blocks_to_check) {
        glm::vec2 closest_point = {
            glm::clamp(entity->pos.x, (float)block.x, (float)(block.x + 1)),
            glm::clamp(entity->pos.y, (float)block.y, (float)(block.y + 1))
        };

        glm::vec2 diff = entity->pos - closest_point;
        float diff_len = glm::length(diff);
        if (diff_len >= entity->collision_size || diff_len == 0.0f) continue;

        collision_happened = true;

        float sep = entity->collision_size - diff_len;
        glm::vec2 sep_vec = glm::normalize(diff) * sep;
        final_sep_vec += sep_vec;
        entity->pos += sep_vec;
    }

    if (glm::length(final_sep_vec) != 0.0f) {
        entity->velocity += final_sep_vec / dt;

        if (glm::dot(entity->gravity, final_sep_vec) <= on_ground_sensitivity) {
            entity->buffer_on_ground = true;
        }
        else {
            entity->buffer_on_ground = false;
        }
    }
    else {
        entity->buffer_on_ground = false;
    }

    return collision_happened;
}

void World::generate_planet(glm::ivec2 center_pos, int radius, BlockType block_type)
{
    int r_sqr = radius * radius;
    Block block;
    block.block_type = block_type;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= r_sqr) {
                glm::ivec2 pos = center_pos + glm::ivec2(x, y);
                world_grid[pos] = block;
            }
        }
    }
    if (block_type == BlockType::CORE) {
        GravityCenter gravity_center;
        gravity_center.pos = glm::vec2(center_pos) + glm::vec2(0.5f);
        gravity_center.power = glm::pi<float>() * radius * radius;
        
        gravity_centers.push_back(gravity_center);
    }
}

void World::update(float dt)
{
    update_entities(dt);
}
