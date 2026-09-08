#ifndef FLUFF_LAYOUT_LAYOUTCALLBACK_H
#definendef FLUFF_LAYOUT_LAYOUTCALLBACK_H

namespace layout {
class LayoutCallbackFuncBase {
public:
    LayoutCallbackFuncBase();

    virtual void operator()() = 0;
    virtual ~LayoutCallbackFuncBase();
};

template <typename OwnerT, FunctionT>
class LayoutCallbackFunc : public LayoutCallbackFuncBase {
public:
    LayoutCallbackFunc();
    void operator()() override;
    ~LayoutCallbackFunc();
private:
    /* 0x4 */ OwnerT* mOwner;
    /* 0x8 */ FunctionT* mFunction;
};
}

#endif
