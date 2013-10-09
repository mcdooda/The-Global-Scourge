#include <cmath>
#include "../../engine/singleton.h"
#include "../../engine/graphics/color.h"
#include "../../engine/time.h"
#include "../../engine/resourcemanager.h"
#include "unit.h"
#include "../game.h"
#include "../mod/mod.h"

namespace game
{
    namespace entity
    {

        Unit::Unit(EntityModel* model, engine::Vector2d position) :
            Entity(model, position)
        {
            engine::graphics::Texture* texture = m_model->getTexture();
            setCenter(engine::Vector2d(texture->getWidth() / 16, 3));
            setDimensions(texture->getDimensions() / 8);
            m_textureCoordX = 0;
            m_textureCoordY = 0;
            setDirection(0);
            m_selectionImage = new Selection(S(Mod)->getTexture("interface/selectionunit.png"), model->getRadius());
            m_selectedImage = new Selection(S(Mod)->getTexture("interface/selectedunit.png"), model->getRadius());
        }

        static float textureCoords[8][8][8];

        void Unit::init()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    textureCoords[i][j][0] = (float)  i      / 8; textureCoords[i][j][1] = (float) (j + 1) / 8;
                    textureCoords[i][j][2] = (float) (i + 1) / 8; textureCoords[i][j][3] = (float) (j + 1) / 8;
                    textureCoords[i][j][4] = (float) (i + 1) / 8; textureCoords[i][j][5] = (float)  j      / 8;
                    textureCoords[i][j][6] = (float)  i      / 8; textureCoords[i][j][7] = (float)  j      / 8;
                }
            }
        }

        void Unit::followPath(float frameTime)
        {
            if (isMoving())
            {
                m_textureCoordX = ((unsigned int) round(engine::time::getTime() * 5 * m_speed.distance())) % 8;
                setTextureCoords(textureCoords[m_textureCoordX][m_textureCoordY]);
                Entity::followPath(frameTime);
            }
            else
                m_textureCoordX = 0;
        }

        void Unit::setDirection(float direction)
        {
            m_textureCoordY = ((unsigned int) round(direction / (M_PI * 2) * 8)) % 8;
            setTextureCoords(textureCoords[m_textureCoordX][m_textureCoordY]);
            Entity::setDirection(direction);
        }

        void Unit::setActive(bool active)
        {
            if (!active)
            {
                m_textureCoordX = 0;
                setTextureCoords(textureCoords[m_textureCoordX][m_textureCoordY]);
            }

            m_active = active;
        }

        void Unit::calcDepth(float x, float y, float radius)
        {
            setDepth(x + y + radius + 0.5);
        }

    }
}
