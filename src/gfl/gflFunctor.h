#ifndef GFL_FUNCTOR_H
#define GFL_FUNCTOR_H

#include "gflPointer.h"

namespace gfl {
    // todo: clean up this mess

    // the number at the end indicates how many parameters
    // this class takes. e.g. FunctorBase0, takes 0 parameters

    // FunctorBase is presumably an interface; there are no members

    template <typename ReturnT>
    class FunctorBase0 {
    public:
        /* Virtual Methods */

        /* 0x08 */ DECL_WEAK virtual ReturnT operator()() = 0;
        /* 0x0C */ virtual FunctorBase0<ReturnT>* Clone() = 0;
        /* 0x10 */ DECL_WEAK virtual ~FunctorBase0() = 0;
    };


    template <typename ReturnT, typename OwnerT, typename FunctionT>
    class FunctorClassMethod0 : public FunctorBase0<ReturnT> {
        typedef FunctorClassMethod0<ReturnT, OwnerT, FunctionT> FunctorType;
    public:
        inline FunctorClassMethod0(OwnerT owner, FunctionT function)
            : mOwner(owner)
            , mFunction(function)
        { }

        inline FunctorClassMethod0(FunctorClassMethod0* pOther)
            : mOwner(pOther->mOwner)
            , mFunction(pOther->mFunction)
        { }
        
        /* 0x08 */ DECL_WEAK virtual ReturnT operator()() {
            (mOwner->*mFunction)();
        }
        
        /* 0x0C */ virtual FunctorBase0<ReturnT>* Clone() {
            return new (gfl::HeapID::LIB1) FunctorType(this);
        }
        

        /* 0x10 */ DECL_WEAK virtual ~FunctorClassMethod0();

        /* Class Members */

        /* 0x4 */ OwnerT mOwner;
        /* 0x8 */ FunctionT mFunction;
    };


    template <typename FunctorT>
    class FunctorImpl {
    public:
        /* Virtual Methods */
    
        /* 0x8 */ virtual ~FunctorImpl() { }
    };

    template <typename ReturnT>
    class Functor0 : public FunctorImpl<FunctorBase0<ReturnT> > {
    public:
        /* Virtual Methods */

        /* 0x8 */ virtual ~Functor0() { }
    };


    template <typename FunctionT, typename ReturnT>
    class FunctorFunc0 {
    public:
        FunctorFunc0(FunctionT function)
            : mFunction(function)
        { }

        virtual ReturnT operator()();
        virtual void Clone(const FunctorFunc0* pOther);
        virtual ~FunctorFunc0();

        /* 0x8 */ FunctionT mFunction;
    };


    template <typename ReturnT, typename Arg1T>
    class FunctorBase1;

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
