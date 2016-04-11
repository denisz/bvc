//
//  AbilityClient.hpp
//  bvunity
//
//  Created by denis zaytcev on 3/24/16.
//
//

#ifndef AbilityClient_hpp
#define AbilityClient_hpp

#include "stdafx.h"
#include "InputManager.hpp"

namespace game {
    class AbilityClient: public internal::AIRef, public InputManager::Delegate {
        
    public:
        class Delegate {
        public:
            virtual void doPass() {};
            virtual void doDialog(const internal::BVValueMap &data) {};
            virtual void doAbility(const internal::BVValueMap &data) {};
        };
        
        struct Trend {
        public:
            enum class Type {CARD, CELL, NONE};
        public:
            int c;
            int x;
            int y;
            Type type;
            std::string hash;
        };
        
        struct Ability {
        public:
            enum class Type {ABILITY, DIALOG, NONE};
        public:
            Type type;
            bool canPass;
            int abilityId;
            int minTargets;
            int maxTargets;
            std::string comment;
            bool canEarlyComplete;
            std::vector<Trend> targets;
            std::vector<Trend> selectedTargets;
        };
        
    private:
        std::forward_list<Ability> _session;
        bool containsInTargets(Trend trend);
    public:
        AbilityClient();
        ~AbilityClient();
        
        Delegate* delegate;
        
        void clearSession();
        void createSessionWithAbility();
        void addAbility(Ability ability, bool clear = false);

        bool init();
        bool pass();
        bool complete();
        bool card(int cardid);
        bool cell(int x, int y);
        
//        MARK: Implementation InputManagerEvents
        virtual void didTapPass(InputManager::CancellationToken& cancel);
        virtual void didTapComplete(InputManager::CancellationToken& cancel);
        virtual void didTapCard(int cardid, InputManager::CancellationToken& cancel);
        virtual void didTapCell(int x, int y, InputManager::CancellationToken& cancel);
        
    public:
        static Trend createTrend(const internal::BVValue &data);
        static Trend createTrend(const internal::BVValueMap &data);
        static Ability createAbility(const internal::BVValue &data);
        static Ability createAbility(const internal::BVValueMap &data);
        static Ability createAbilityFromDialog(const internal::BVValue &dialog);

        static AbilityClient* create();
        static AbilityClient* createWithDelegate(Delegate* delegate);
    };
}

#endif /* AbilityClient_hpp */
