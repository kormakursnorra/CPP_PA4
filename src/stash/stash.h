#ifndef STASH_H
#define STASH_H

#include <cassert>
#include <sys/types.h>
#include <unordered_map>

class Hobo;
class Battle;

template<typename T> 
class Stash {
private:
    const Hobo *stashOwner;

protected:
    using ContentMap = std::unordered_map<int, T>;
    ContentMap contents;
    int maxContents;
    int numContents;
    
    virtual void onInsert(T) {}
    virtual void onRemove(T) {}
    
    bool isOwner(const Hobo* caller) const {
        return caller == stashOwner; 
    }

    bool isInStash(int contentKey) const {
        return contents.count(contentKey) > 0; 
    }

public:
    Stash(const Hobo *stashOwner) 
    : stashOwner(stashOwner), maxContents(6), numContents(0) {} 

    const ContentMap* getStash(const Hobo *stashOwner) const {
        assert(isOwner(stashOwner));
        return &contents;
    }
    
    T getStashItem(const Hobo *stashOwner, int contentKey) const {
        assert(isOwner(stashOwner));
        assert(isInStash(contentKey));

        return contents.at(contentKey);
    }
    
    int getNumContents(const Hobo *stashOwner) const {
        assert(isOwner(stashOwner));
        return numContents;
    }
    
    bool insert(const Hobo *stashOwner, T newItem) {
        assert(isOwner(stashOwner));
        if (numContents == maxContents) {
            return false;
        }

        contents.insert({numContents + 1, newItem});
        numContents++;
        onInsert(newItem);
        return true;
    }
    
    bool remove(const Hobo *stashOwner, int contentKey) {
        assert(isOwner(stashOwner));
        assert(isInStash(contentKey));
        assert(maxContents > 0);
        
        contents.erase(contentKey);
        numContents--;
        return true;
    }
    
    virtual ~Stash() {}

    friend class Battle;
    friend class Hobo;
};

#endif 