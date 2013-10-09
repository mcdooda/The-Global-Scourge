#include <iostream>
#include <cmath>
#include "../../engine/singleton.h"
#include "../../engine/resourcemanager.h"
#include "entitymodel.h"

namespace game
{
    namespace entity
    {

        static std::map<std::string, EntityModel*> models;

        EntityModel::EntityModel(std::string name, std::string textureName, float radius, float speed, float weight, float jumpForce) :
            m_name(name),
            m_radius(radius),
            m_speed(speed),
            m_weight(weight),
            m_jumpForce(jumpForce)
        {
            m_texture = S(engine::TextureManager)->get(textureName);
            models[name] = this;

            m_halfJumpDuration = m_jumpForce / m_weight;
            m_jumpAltitude = m_halfJumpDuration * m_jumpForce + m_halfJumpDuration * m_halfJumpDuration * m_weight / 2;
        }

        EntityModel* EntityModel::getModelByName(std::string modelName)
        {
            return models[modelName];
        }
        
        const std::map<std::string, EntityModel*>& EntityModel::getAll()
        {
            return models;
        }

    }
}
