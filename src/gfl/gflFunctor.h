#ifndef GFL_FUNCTOR_H
#define GFL_FUNCTOR_H

#include "gflPointer.h"

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
        virtual void operator=(const FunctorBase0<ReturnT>&); // not confirmed

        virtual ~FunctorBase0();
    private:

    };

    template <typename ReturnT, typename PT1>
    class FunctorBase1;

    template <typename ReturnT, typename PT1, typename PT2>
    class FunctorBase2;

    /* FunctorClassMethod */

    // OwnerT is typically a pointer anyways
    // e.g. `gfl::FunctorClassMethod0<void, Gimmick*, void (Gimmick::*)()const>`
    template <typename ReturnT, typename OwnerT, typename FunctionT>
    class FunctorClassMethod0 {
    private:
        typedef FunctorClassMethod0<ReturnT, OwnerT, FunctionT> FunctorT;
    public:
    
        inline FunctorClassMethod0(OwnerT owner, FunctionT function) {
            mOwner = owner;
            mFunction = function;
        }

        virtual ReturnT operator()();
        virtual FunctorT* Clone();
        virtual ~FunctorClassMethod0();

        inline void SetOwner(OwnerT owner) {
            mOwner = owner;
        }

        inline void SetOwner(void* owner) {
            mOwner = (OwnerT)owner;
        }

        inline void SetFunction(FunctionT function) {
            mFunction = function;
        }

        inline void SetFunction(void* function) {
            mFunction = function;
        }
    private:
        OwnerT mOwner;
        FunctionT mFunction;
    };

    /* FunctorImpl */

    // FunctorT - `gfl::FunctorBaseX` class
    template <typename FunctorT>
    class FunctorImpl {
    public:

        // template <typename ReturnT, typename OwnerT, typename FunctionT>
        // inline FunctorImpl(OwnerT* owner, FunctionT function)
        //     : mFunctor(new gfl::FunctorClassMethod0<ReturnT, OwnerT, FunctionT>(owner, function))
        // {

        // }

        

        inline FunctorImpl()
            : mFunctor(new FunctorT)
        {

        }

        virtual ~FunctorImpl() {
            delete mFunctor;
        }

        inline bool HasFunctor() {
            return nullptr != mFunctor;
        }

        inline void operator()() {
            mFunctor->operator()();
        }
    private:
        FunctorT* mFunctor;
    };

    /* Functor0 */
    template <typename ReturnT>
    class Functor0 : public FunctorImpl< FunctorBase0<void> > {
    public:
        inline Functor0()
            : FunctorImpl()
        { }

        inline virtual ~Functor0() { }
    };

    
}

#endif
