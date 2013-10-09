#ifndef GAME_MAP_IO_WRITER_H
 #define GAME_MAP_IO_WRITER_H

#include <set>
#include <fstream>
#include "../editormap.h"

namespace game
{
    namespace map
    {
        namespace io
        {

            class Writer
            {
                public:
                    Writer(EditorMap* map);

                    void write();

                private:
                    std::string getRelativePath(std::string root, std::string path);

                    void writeBool(bool boolean);
                    void writeFloat(float f);
                    void writeUint16(Uint16 integer);
                    void writeString(std::string string);

                    EditorMap* m_map;
                    std::ofstream m_file;

                    std::set<std::string> m_tiles;
                    std::set<std::string> m_doodads;
                    std::set<std::string> m_entities;

                    std::map<std::string, Uint16> m_tilesIndices;
                    std::map<std::string, Uint16> m_doodadsIndices;
                    std::map<std::string, Uint16> m_entitiesIndices;
            };

        }
    }
}

#endif
