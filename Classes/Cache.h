#ifndef __CACHE_H__
#define __CACHE_H__

#include <string>

class Cache {
public:
    static Cache& GetInstance() {
        static Cache instance;
        return instance;
    }

    size_t GetUserId() const;
    void SaveUserId(const std::string& user_id);
};

#endif

