//
//  Constants.h
//  bvunity
//
//  Created by denis zaytcev on 2/9/16.
//
//

#ifndef Constants_h
#define Constants_h

#define kAppVersion "1.0.0"
#define kServerUrl  "ws://br3.office.bytexgames.ru/atmosphere/websocket"
#include "ValueMap.h"

/**
 Ключ для определение ответа на запрос
 **/
const std::string kKeyCallbackID = "callback_id";

/**
 The query does not load from the cache or save results to the cache.
 This is the default cache policy.
 */
const int kCachePolicyIgnoreCache = 0;
/**
 The query only loads from the cache, ignoring the network.
 If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
 */
const int kCachePolicyCacheOnly = 1;
/**
 The query does not load from the cache, but it will save results to the cache.
 */
const int kCachePolicyNetworkOnly = 2;
/**
 The query first tries to load from the cache, but if that fails, it loads results from the network.
 If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
 */
const int kCachePolicyCacheElseNetwork = 3;
/**
 The query first tries to load from the network, but if that fails, it loads results from the cache.
 If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
 */
const int kCachePolicyNetworkElseCache = 4;
/**
 The query first loads from the cache, then loads from the network.
 The callback will be called twice - first with the cached results, then with the network results.
 Since it returns two results at different times, this cache policy cannot be used with synchronous or task methods.
 */
const int kCachePolicyCacheThenNetwork = 5;

enum class kGameStage {
    /** Инициализация игры */   INIT,
    /** Во время муллиганов   */  MULLIGAN,
    /** Во время броска кубиков на очерёдность хода */  DICETURN,
    /**Выбор отряда*/  CHOOSEARMY,
    /**Расстановка отряда*/  SETUPARMY,
    /**Вскрытие скрытых карт (кроме 3 ряда)*/  UNHIDE,
    /**Во время рассадки экипировки */  EQUIPMENT,
    /**В начале игры */  BEGINGAME,
    /**До начала хода (и до открытия карт) */   BEFORETURN,
    /**В начале хода */  BEGINTURN,
    /**В течение хода (медленные действия) */  TURN,
    /**После объявления действия (реакция) */  DECLARE,
    /**Объявление цели атаки */  TARGET,
    /**При нападении */  ASSAULT,
    /**Броски кубиков */  DICES,
    /**Нанесение ударов */  KICKS,
    /**Нанесение одного отдельно взятого удара */  KICK,
    /**Нанесение ран  */  DAMAGE,
    /**После нанесения ран */  AFTERDAMAGE,
    /**Перемещение карты на кладбище */  DEATH,
    /**После смерти */  AFTERDEATH,
    /**После атаки */  AFTERATTACK,
    /**До открытия */  UNTAP,
    /**При излечении */  HEALING,
    /**После закрытия карты */  AFTERTAP,
    /**После открытия  */  AFTERUNTAP,
    /**После движения  */ AFTERDISPLACEMENT,
     /**После вызова */  AFTERSUMMON,
    /**После инкарнации  */  AFTERINCARNATION,
    /**В конце хода */  AFTERTURN,
    /**В конце игры */  ENDGAME
};


const std::string kHiddenUserName   = "Hidden";
const std::string kHiddenUserAvatar = "Hidden";

const std::string kEventuallyDirPath = "eventually/";
const std::string kCacheDirPath = "cache/";

const std::string kResponseParamsAttribute = "/params";

#endif /* Constants_h */
