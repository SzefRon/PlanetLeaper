#include "entity/Entity.hpp"

void Entity::update_next_pos(float dt)
{
    velocity += gravity * dt;
    next_pos = pos + velocity * dt;
}

void Entity::update_pos()
{
    pos = next_pos;
}
