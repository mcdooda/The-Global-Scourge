#ifndef GAME_ENTITY_ENTITYMODEL_H
 #define GAME_ENTITY_ENTITYMODEL_H

#include <map>
#include "../../engine/graphics/texture.h"

namespace game
{
    namespace entity
    {

        class EntityModel
        {
            public:
                EntityModel(std::string name, std::string textureName, float radius, float speed, float weight, float jumpForce);

                static EntityModel* getModelByName(std::string modelName);
                static const std::map<std::string, EntityModel*>& getAll();
                
                virtual bool isUnitModel() const = 0;
                virtual bool isBuildingModel() const = 0;
                virtual bool isAbstractModel() const = 0;

                inline const std::string& getName() const { return m_name; }
                inline engine::graphics::Texture* getTexture() const { return m_texture; }
                inline float getSpeed() const { return m_speed; }
                inline float getRadius() const { return m_radius; }
                inline float getWeight() const { return m_weight; }
                inline float getJumpForce() const { return m_jumpForce; }
                inline float getJumpAltitude() const { return m_jumpAltitude; }
                inline float getHalfJumpDuration() const { return m_halfJumpDuration; }

            private:
                std::string m_name;
                engine::graphics::Texture* m_texture;
                float m_radius;
                float m_speed;
                float m_weight;
                float m_jumpForce;
                float m_jumpAltitude;
                float m_halfJumpDuration;
        };

    }
}

#endif
