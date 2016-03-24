//
//  ChooseDeckViewController.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/16/16.
//
//

#ifndef ChooseDeckViewController_hpp
#define ChooseDeckViewController_hpp

#include "stdafx.h"
#include "GameViewController.hpp"
#include "DeckListController.hpp"
#include "DeckTableView.hpp"
#include "Deck.hpp"

namespace game {
    class ChooseDeckViewController:
                public GameViewController,
                public DataSourceControllerDelegate,
                public DataSourceViewControllerReload,
                public DeckTableView::Delegate {
    public:
        class Delegate {
        public:
            virtual void handlerRequestChooseDeck(int deckId) = 0;
        };
    private:
        virtual bool tryChooseDeck(const internal::BVValue &deck);
        virtual void didSelectedDeck(const internal::BVValue &deck);
        virtual void viewDidLoad();
        virtual void didChange(DataSourceController* ds, DSOptions options, internal::BVValue &value);
    public:
        ChooseDeckViewController();
        ~ChooseDeckViewController();
        virtual bool init();
        virtual bool initWithResponseChooseDeck(Response* res);
        Delegate* deckDelegate;
        static ChooseDeckViewController* createWithResponseChooseDeck(Response* res);
    };
}


#endif /* ChooseDeckViewController_hpp */
