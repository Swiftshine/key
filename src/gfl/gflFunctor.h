#ifndef GFL_FUNCTOR_H
#define GFL_FUNCTOR_H

#include "gflPointer.h"

namespace gfl {
    // todo: clean up this mess

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

    template <typename ReturnT, typename Arg1T>
    class FunctorBase1;


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

        inline virtual ~FunctorImpl() {
            if (mFunctor != nullptr) {
                delete mFunctor;
            }
        }

        inline bool HasFunctor() {
            return mFunctor != nullptr;
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



    template <typename ReturnT, typename Arg1T, typename Arg2T>
    class FunctorBase2 {
        typedef FunctorBase2<ReturnT, Arg1T, Arg2T> ClassT;
    public:
        /* Virtual Methods */

        /* 0x08 */ virtual ReturnT operator()(Arg1T, Arg2T) = 0;
        /* 0x0C */ virtual void operator=(const ClassT*) = 0;
        /* 0x10 */ virtual ~FunctorBase2() = 0;
    };


    template <typename ReturnT, typename Arg1T, typename Arg2T, typename OwnerT, typename FunctionT>
    class FunctorClassMethod2 : public FunctorBase2<ReturnT, Arg1T, Arg2T> {
        typedef FunctorBase2<ReturnT, Arg1T, Arg2T> BaseClassT;
        typedef FunctorClassMethod2<ReturnT, Arg1T, Arg2T, OwnerT, FunctionT> ClassT;
    public:
        inline FunctorClassMethod2(OwnerT* pOwner, FunctionT function) {
            mOwner = pOwner;
            mFunction = function;
        }

        /* Virtual Methods */

        /* 0x08 */ virtual ReturnT operator()(Arg1T, Arg2T) override;
        /* 0x0C */ virtual void operator=(const BaseClassT*) override;
        /* 0x10 */ virtual ~FunctorClassMethod2();
    private:
        /* Class Members */
        /* 0x4 */ OwnerT* mOwner;
        /* 0x8 */ FunctionT mFunction;
    };

    /* Functor2 */


    template <typename ReturnT, typename Arg1T, typename Arg2T>
    class Functor2 {
    public:
        inline ~Functor2() {

        }
    private:
        /* Class Members */

        /* 0x0 */ Pointer<FunctorImpl<FunctorBase2<ReturnT, Arg1T, Arg2T> > > mFunctorImpl;
        // /* 0x4 */ FunctorClassMethod2<ReturnT, Arg1T, Arg2T, 
        void* m_4;
        /* 0x8 */ void* m_8;
    };
}

#endif
