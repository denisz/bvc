//
//  InputManager.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include "stdafx.h"

namespace game {
    class InputManager: public internal::AIRef {
    public:
        class CancellationToken {
        private:
            bool _cancellationRequested;
        public:
            void cancel() {
                _cancellationRequested = true;
            }
            
            bool isCancel() {
                return _cancellationRequested == true;
            }
        };
        
        class Delegate {
        public:
            virtual void didTapCard(int cardid, CancellationToken &cancel) {};
            virtual void didTapCell(int x, int y, CancellationToken& cancel) {};
            virtual void didTapPass(CancellationToken& cancel) {};
            virtual void didTapComplete(CancellationToken& cancel) {};
        };
    private:
        std::forward_list<Delegate*> _delegates;
        bool _enabled;
    public:
        InputManager();
       ~InputManager();

        void addDelegate(Delegate *delegate);
        void removeDelegate(Delegate *delegate);
        
        void didTapCard(int card);
        void didTapCell(int x, int y);
        void didTapPass();
        void didTapComplete();
        
        void setEnabled(bool enabled);
        
        bool init();
        
        BV_CREATE_FUNC(InputManager);
    };
}

#endif /* InputManager_hpp */