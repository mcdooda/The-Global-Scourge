#include <iostream>

namespace engine
{

    template <class T> T* ResourceManager<T>::get(std::string name)
    {
        T* resource;
        typename std::map<std::string, T*>::iterator it = m_resources.find(name);

        if (it != m_resources.end())
        {
            resource = it->second;
            //std::cout << name << " already loaded!" << std::endl;
        }
        else
        {
            resource = load(name);
            //std::cout << name << " just loaded" << std::endl;
        }

        return resource;
    }

    template <class T> T* ResourceManager<T>::load(std::string name)
    {
        //std::cout << "loading " << name << std::endl;
        T* resource = new T(name);
        m_resources[name] = resource;
        return resource;
    }

}
