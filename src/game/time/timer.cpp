#include <iostream>
#include <algorithm>
#include "../../engine/time.h"
#include "timer.h"

namespace game
{
    namespace time
    {
        
        static std::list<Timer*> timers;
        
        Timer::Timer(float timeOut, bool loops)
        {
            m_initTime = engine::time::getTime();
            m_endTime = m_initTime + timeOut;
            m_timeOut = timeOut;
            m_loops = loops;
            
            addToList();
        }
        
        Timer::~Timer()
        {
            
        }
        
        void Timer::triggerTimers()
        {
            //std::cout << timers.size() << " timers" << std::endl;
            std::list<Timer*> loopingTimedOutTimers;
            std::list<Timer*>::iterator it = timers.begin();
            
            float time = engine::time::getTime();
            while (it != timers.end() && (*it)->isTimedOut(time))
            {
                bool remove = (*it)->execute();
                if (remove)
                {
                    delete *it;
                    it = timers.erase(it);
                }
                else
                {
                    loopingTimedOutTimers.push_back(*it);
                    it++;
                }
            }
            
            std::list<Timer*>::iterator end = loopingTimedOutTimers.end();
            for (std::list<Timer*>::iterator it = loopingTimedOutTimers.begin(); it != end; it++)
                (*it)->reset(time);
        }
        
        void Timer::clearTimers()
        {
            for (std::list<Timer*>::iterator it = timers.begin(); it != timers.end(); it++)
                delete *it;
                
            timers.clear();
        }
        
        void Timer::stop()
        {
            timers.erase(m_iterator);
            delete this;
        }
        
        void Timer::reset(float time)
        {
            m_endTime = engine::time::getTime() + m_timeOut;
            timers.erase(m_iterator);
            addToList();
        }
        
        void Timer::addToList()
        {
            std::list<Timer*>::iterator end = timers.end();
            std::list<Timer*>::iterator it;
            for (it = timers.begin(); it != end && m_endTime > (*it)->m_endTime; it++);
            m_iterator = timers.insert(it, this);
        }
        
        bool Timer::isTimedOut(float time)
        {
            return time >= m_endTime;
        }
        
    }
}
