//
//  DeckTableView.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/18/16.
//
//

#ifndef DeckTableView_hpp
#define DeckTableView_hpp

#include "stdafx.h"
#include "BaseTableView.hpp"

namespace game {
    
    class DeckTableViewCell: public BaseTableViewCell {
    public:
        virtual void viewDidLoad();
        virtual void prepareView(internal::BVValue* model);
        BV_CREATE_FUNC_WITH_SIZE(DeckTableViewCell)
        BV_CREATE_FUNC(DeckTableViewCell);
    };
    
    
    class DeckTableView: public BaseTableView  {
    public:
        class Delegate {
        public:
            virtual bool tryChooseDeck(const internal::BVValue& deck) = 0;
            virtual void didSelectedDeck(const internal::BVValue& deck) {};
        };
    private:
        virtual void didSelectRowAtIndex(TableView *table, ssize_t idx);
        virtual int heightForRowAtIndexPath(TableView *table, ssize_t idx);
        virtual void viewDidLoad();
        virtual BaseTableViewCell* createNewCell(TableView *table, ssize_t idx);
    public:
        Delegate* delegate;
        BV_CREATE_FUNC_WITH_SIZE(DeckTableView);
        BV_CREATE_FUNC(DeckTableView);
    };
}

#endif /* DeckTableView_hpp */
