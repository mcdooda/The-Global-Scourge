#include <cstdlib>
#include "game.h"
#include "globalstate.h"
#include "gamestate.h"
#include "editorstate.h"
#include "mod/mod.h"
#include "lua/lua.h"
#include "../engine/engine.h"
#include "../engine/time.h"
#include "../engine/input/input.h"
#include "../engine/graphics/graphics.h"
#include "../engine/graphics/window.h"
#include "../engine/singleton.h"

namespace game
{

    Game::Game()
    {
        m_map = NULL;
        m_nextMod = "";
        S(Mod);
    }

    void Game::init(int argc, char* argv[])
    {
        m_view = new engine::graphics::View(engine::Vector2d(0, 0), 1);

        m_running = true;
        engine::init();
        engine::time::setFrameRate(60);

        parseArgs(argc, argv);
    }

    Game::~Game()
    {
        delete m_view;
        
        if (m_interface != NULL)
            delete m_interface;

        if (m_map != NULL)
            delete m_map;

        engine::free();
    }

    void Game::loop()
    {
        while (m_running)
        {
            while (m_running)
            {
                engine::time::beginFrame();
                engine::graphics::beginFrame();
                engine::input::poll();
                getStateMachine()->update();
                engine::graphics::window::resize();
                engine::graphics::endFrame();
                engine::time::endFrame();
            }
            
            openNextMod();
        }
    }

    void Game::stop()
    {
        m_selection->clearSelection();
        m_running = false;
    }

    void Game::setMap(map::Map* map)
    {
        if (m_map != NULL)
            delete m_map;

        m_map = map;
    }

    void Game::setInterface(interface::Interface* interface)
    {
        if (m_interface != NULL)
            delete m_interface;
            
        m_interface = interface;
    }

    void Game::setSelection(interface::Selection* selection)
    {
        m_selection = selection;
    }
    
    void Game::playMod(std::string path)
    {
        S(Mod)->setPath(path);
        getStateMachine()->setGlobalState(new GlobalState());
        getStateMachine()->setState(new GameState());
    }
    
    void Game::editMod(std::string path)
    {
        S(Mod)->setPath(path);
        getStateMachine()->setGlobalState(new GlobalState());
        getStateMachine()->setState(new EditorState());
    }
    
    void Game::openNextMod()
    {
        if (m_nextMod != "")
        {
            if (m_editorMode)
                editMod(m_nextMod);

            else
                playMod(m_nextMod);
            
            m_nextMod = "";
            m_running = true;
        }
    }

    void Game::parseArgs(int argc, char* argv[])
    {
        static const char* defaultModPath = "mods/menu";
        m_editorMode = false;
        bool fullscreen = true;
        const char* modPath = NULL;
        for (int i = 1; i < argc; i++)
        {
            switch(argv[i][0])
            {
                case '-':
                switch (argv[i][1])
                {
                    case 'e':
                    m_editorMode = true;
                    break;
                    
                    case 'w':
                    fullscreen = false;
                    break;
                }
                break;

                default:
                modPath = argv[i];
            }
        }
        
        if (fullscreen)
            engine::graphics::window::open(engine::graphics::window::getDesktopWidth(), engine::graphics::window::getDesktopHeight(), "Gamma Persei", true);
            
        else
            engine::graphics::window::open(1366, 768, "Gamma Persei", false);
            
        if (modPath == NULL)
            modPath = defaultModPath;

        if (m_editorMode)
            editMod(modPath);

        else
            playMod(modPath);
    }

}
