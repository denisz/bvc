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
#include "StepFightViewController.hpp"
#include "DeckListController.hpp"
#include "DeckTableView.hpp"
#include "Deck.hpp"

namespace game {
    class ChooseDeckViewController:
                public StepFightViewController,
                public DataSourceControllerDelegate,
                public DataSourceViewControllerReload,
                public DeckTableView::Delegate {
    private:
        virtual bool tryChooseDeck(const internal::BVValue &deck);
        virtual void didSelectedDeck(const internal::BVValue &deck);
        virtual void viewDidLoad();
        virtual void didChange(DataSourceController* ds, DSOptions options, internal::BVValue &value);
    public:
        BV_CREATE_FUNC_WITH_FIGHT_CONTEXT(ChooseDeckViewController);
    };
}


#endif /* ChooseDeckViewController_hpp */
