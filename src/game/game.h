#ifndef GAME_GAME_H
 #define GAME_GAME_H

#include "../engine/state/agent.h"
#include "../engine/graphics/view.h"
#include "map/map.h"
#include "interface/interface.h"
#include "interface/selection.h"

namespace game
{

    class Game : public engine::state::Agent
    {
        public:
            Game();
            ~Game();

            void init(int argc, char* argv[]);
            void loop();
            void stop();

            void setMap(map::Map* map);
            inline map::Map* getMap() const { return m_map; }

            void setInterface(interface::Interface* interface);
            inline interface::Interface* getInterface() const { return m_interface; }

            void setSelection(interface::Selection* selection);
            inline interface::Selection* getSelection() const { return m_selection; }

            inline engine::graphics::View* getView() const { return m_view; }
            
            void playMod(std::string path);
            void editMod(std::string path);
            
            void openNextMod();
            inline void setNextMod(std::string nextMod) { m_nextMod = nextMod; }

        private:
            void parseArgs(int argc, char* argv[]);

            bool m_running;
            bool m_editorMode;
            std::string m_nextMod;

            map::Map* m_map;
            interface::Interface* m_interface;
            interface::Selection* m_selection;
            engine::graphics::View* m_view;
    };

}

#endif
