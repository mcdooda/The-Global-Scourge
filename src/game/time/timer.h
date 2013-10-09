#ifndef GAME_TIME_TIMER_H
 #define GAME_TIME_TIMER_H

#include <list>

namespace game
{
    namespace time
    {
        
        class Timer
        {
            public:
                Timer(float timeOut, bool loops);
                
                static void triggerTimers();
                static void clearTimers();
                
                void stop();
                
                void reset(float time);
                
                inline void setLoops(bool loops) { m_loops = loops; }
                
            protected:
                float m_initTime;
                float m_endTime;
                float m_timeOut;
                bool m_loops;
                
                std::list<Timer*>::iterator m_iterator; // list iterators remain valid after modifications in the list
                
                void addToList();
                void removeFromList();
                
                bool isTimedOut(float time);
                
                virtual bool execute() = 0;
        };
        
    }
}

#endif
