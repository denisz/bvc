//
//  FightCardController.hpp
//  bvunity
//
//  Created by denis zaytcev on 4/5/16.
//
//

#ifndef FightCardController_hpp
#define FightCardController_hpp

#include "stdafx.h"
#include "UIKit.h"
#include "AssemblerCard.hpp"
#include "FightEffectController.hpp"

namespace game {
    class FightCardController;
    
    class FightCardContextTransitioning: public internal::AIRef {
    public:
        enum class Transition {Exit, Enter, Move};
        typedef Bolts::BFTaskCompletionSource<Bolts::BFBool> Promise;
    private:
        Promise*                _promise;
        bool                    _completed;
        std::mutex              _mutex;
        Transition              _transition;
        FightCardController*    _card;
    public:
        FightCardContextTransitioning();
        ~FightCardContextTransitioning();

        Bolts::BFTask<Bolts::BFBool>* task();
        
        bool isCompleted();
        FightCardController* card();
        Transition transition();
        void setCard(FightCardController* card);
        void setTransition(const Transition& transition);
        
        void completeTransition(bool didComplete = true);
        void completeTransitionAsync(bool didComplete = true);
    };
    typedef FightCardContextTransitioning FCCT;
    
    class FigthCardAnimatedTransitioning {
    public:
        virtual void animateTransition(FCCT* transitionContext) {};
    };
    typedef FigthCardAnimatedTransitioning FCAT;
    
    class FightCardController: public UIKit::UIView {
    public:
        enum class Location {Undefined, BattleField, Deck, Additional, Cemetery};
        class Delegate {
        public:
            virtual FCAT* coordinatorForPresentedCard(FightCardController& card) = 0;
        };
    private:
        virtual void viewDidLoad();
    private:
        AssemblerCard* _assemblerCard;
        FightEffectController* _effectController;
    public:
        Delegate* delegate;
    public:
        FightCardController();
        ~FightCardController();
        bool init();
        
        Location location();
        int x();
        int y();
        
        void commit(const internal::BVValueMap& map);
        
        static FightCardController* Create();
        BV_CREATE_FUNC_WITH_SIZE(FightCardController);
    };
}
#endif /* FightCardController_hpp */
