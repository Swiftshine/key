#ifndef GFL_FUNCTOR_H
#define GFL_FUNCTOR_H

namespace gfl {

    // the number at the end indicates how many parameters
    // this class takes. e.g. FunctorBase0, takes 0 parameters

    /* FunctorBaseX */

    // FunctorBase is presumably an interface; there are no members


    // ReturnT - return type
    template <typename ReturnT>
    class FunctorBase0 {
    public:
        inline FunctorBase0() {

        }

        virtual ReturnT operator()(); // not confirmed
        virtual void operator=(); // not confirmed

        virtual ~FunctorBase0();
    private:

    };

    template <typename ReturnT, typename PT1>
    class FunctorBase1;

    template <typename ReturnT, typename PT1, typename PT2>
    class FunctorBase2;

    /* FunctorImpl */

    // FunctorT - `gfl::FunctorBaseX` class
    template <typename FunctorT>
    class FunctorImpl {
    public:
        FunctorImpl();
        virtual ~FunctorImpl();
    private:
        FunctorT* mFunctor;
    };


    /* FunctorClassMethod */

    // OwnerT is typically a pointer anyways
    // e.g. `gfl::FunctorClassMethod0<void, Gimmick*, void (Gimmick::*)()const>`
    template <typename ReturnT, typename OwnerT, typename FunctionT>
    class FunctorClassMethod0 {
    public:
    
        inline FunctorClassMethod0(OwnerT owner, FunctionT function) {
            mOwner = owner;
            mFunction = function;
        }

        virtual ReturnT operator()();
        virtual void operator=();
        virtual ~FunctorClassMethod0();
    private:
        OwnerT mOwner;
        FunctionT mFunction;
    };
}

#endif
