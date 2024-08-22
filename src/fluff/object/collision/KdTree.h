#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H


class KdTree {
private:
    static KdTree* sColObjTree;
public:
    struct HitResult {

    };
public:
    static inline KdTree* ColObjTree() { return sColObjTree; }

    void AddItem(void*);
    void RemoveItem(void*);
};
#endif