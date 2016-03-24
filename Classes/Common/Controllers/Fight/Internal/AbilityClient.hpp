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
            virtual void doAbility() {};
            virtual void doDialog() {};
            virtual void doPass() {};
        };
        
        struct Trend {
        public:
            enum class Type {CARD, CELL, NONE};
        public:
            Type type;
            int c;
            int x;
            int y;
            std::string hash;
        };
        
        struct Ability {
        public:
            enum class Type {ABILITY, DIALOG, NONE};
        public:
            Type type;
            int abilityId;
            std::string comment;
            std::vector<Trend> targets;
            std::vector<Trend> selectedTargets;
            int minTargets;
            int maxTargets;
            bool canPass;
            bool canEarlyComplete;
        };
        
    private:
        std::forward_list<Ability> _session;
        bool containsInTargets(Trend trend);
    public:
        AbilityClient();
        ~AbilityClient();
        
        Delegate* delegate;
        void addAbility(Ability ability, bool clear = false);
        void createSessionWithAbility();
        void clearSession();
        
        bool card(int cardid);
        bool cell(int x, int y);
        bool complete();
        bool pass();
        
        bool init();
        
//        MARK: Implementation InputManager
        virtual void didTapCard(int cardid, InputManager::CancellationToken& cancel);
        virtual void didTapCell(int x, int y, InputManager::CancellationToken& cancel);
        virtual void didTapPass(InputManager::CancellationToken& cancel);
        virtual void didTapComplete(InputManager::CancellationToken& cancel);
        
    public:
        static Ability createAbility(const internal::BVValueMap &data);
        static Ability createAbility(const internal::BVValue &data);
        static Ability createAbilityFromDialog(const internal::BVValue &dialog);
        static Trend createTrend(const internal::BVValue &data);
        static Trend createTrend(const internal::BVValueMap &data);
        
        BV_CREATE_FUNC(AbilityClient);
    };
}

#endif /* AbilityClient_hpp */
