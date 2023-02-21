/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Account/Domain/EzGs2Account.h"
#include "Auth/Domain/EzGs2Auth.h"
#include "Chat/Domain/EzGs2Chat.h"
#include "Core/Domain/Gs2.h"
#include "Datastore/Domain/EzGs2Datastore.h"
#include "Dictionary/Domain/EzGs2Dictionary.h"
#include "Distributor/Domain/EzGs2Distributor.h"
#include "Enhance/Domain/EzGs2Enhance.h"
#include "Exchange/Domain/EzGs2Exchange.h"
#include "Experience/Domain/EzGs2Experience.h"
#include "Formation/Domain/EzGs2Formation.h"
#include "Friend/Domain/EzGs2Friend.h"
#include "Gateway/Domain/EzGs2Gateway.h"
#include "Inbox/Domain/EzGs2Inbox.h"
#include "Inventory/Domain/EzGs2Inventory.h"
#include "JobQueue/Domain/EzGs2JobQueue.h"
#include "Limit/Domain/EzGs2Limit.h"
#include "Lottery/Domain/EzGs2Lottery.h"
#include "Matchmaking/Domain/EzGs2Matchmaking.h"
#include "MegaField/Domain/EzGs2MegaField.h"
#include "Mission/Domain/EzGs2Mission.h"
#include "Money/Domain/EzGs2Money.h"
#include "News/Domain/EzGs2News.h"
#include "Quest/Domain/EzGs2Quest.h"
#include "Ranking/Domain/EzGs2Ranking.h"
#include "Realtime/Domain/EzGs2Realtime.h"
#include "Schedule/Domain/EzGs2Schedule.h"
#include "SerialKey/Domain/EzGs2SerialKey.h"
#include "Showcase/Domain/EzGs2Showcase.h"
#include "Stamina/Domain/EzGs2Stamina.h"
#include "Version/Domain/EzGs2Version.h"

namespace Gs2::UE5::Util
{
    class FProfile;
}

namespace Gs2::UE5::Core::Domain
{
    class EZGS2_API FGs2Domain :
        public TSharedFromThis<FGs2Domain>
    {
        TSharedPtr<Util::FProfile> Profile;
    public:
        Gs2::Core::Domain::FGs2Ptr Super;

        Gs2::UE5::Account::Domain::FEzGs2AccountPtr Account;
        Gs2::UE5::Auth::Domain::FEzGs2AuthPtr Auth;
        Gs2::UE5::Chat::Domain::FEzGs2ChatPtr Chat;
        Gs2::UE5::Datastore::Domain::FEzGs2DatastorePtr Datastore;
        Gs2::UE5::Dictionary::Domain::FEzGs2DictionaryPtr Dictionary;
        Gs2::UE5::Distributor::Domain::FEzGs2DistributorPtr Distributor;
        Gs2::UE5::Enhance::Domain::FEzGs2EnhancePtr Enhance;
        Gs2::UE5::Exchange::Domain::FEzGs2ExchangePtr Exchange;
        Gs2::UE5::Experience::Domain::FEzGs2ExperiencePtr Experience;
        Gs2::UE5::Formation::Domain::FEzGs2FormationPtr Formation;
        Gs2::UE5::Friend::Domain::FEzGs2FriendPtr Friend;
        Gs2::UE5::Gateway::Domain::FEzGs2GatewayPtr Gateway;
        Gs2::UE5::Inbox::Domain::FEzGs2InboxPtr Inbox;
        Gs2::UE5::Inventory::Domain::FEzGs2InventoryPtr Inventory;
        Gs2::UE5::JobQueue::Domain::FEzGs2JobQueuePtr JobQueue;
        Gs2::UE5::Limit::Domain::FEzGs2LimitPtr Limit;
        Gs2::UE5::Lottery::Domain::FEzGs2LotteryPtr Lottery;
        Gs2::UE5::Matchmaking::Domain::FEzGs2MatchmakingPtr Matchmaking;
        Gs2::UE5::MegaField::Domain::FEzGs2MegaFieldPtr MegaField;
        Gs2::UE5::Mission::Domain::FEzGs2MissionPtr Mission;
        Gs2::UE5::Money::Domain::FEzGs2MoneyPtr Money;
        Gs2::UE5::News::Domain::FEzGs2NewsPtr News;
        Gs2::UE5::Quest::Domain::FEzGs2QuestPtr Quest;
        Gs2::UE5::Ranking::Domain::FEzGs2RankingPtr Ranking;
        Gs2::UE5::Realtime::Domain::FEzGs2RealtimePtr Realtime;
        Gs2::UE5::Schedule::Domain::FEzGs2SchedulePtr Schedule;
        Gs2::UE5::SerialKey::Domain::FEzGs2SerialKeyPtr SerialKey;
        Gs2::UE5::Showcase::Domain::FEzGs2ShowcasePtr Showcase;
        Gs2::UE5::Stamina::Domain::FEzGs2StaminaPtr Stamina;
        Gs2::UE5::Version::Domain::FEzGs2VersionPtr Version;
        
        explicit FGs2Domain(
            TSharedPtr<Util::FProfile> Profile
        );
        ~FGs2Domain() = default;
        
        class EZGS2_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2Domain> Self;
            const Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2Domain> Self,
                const Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        );
    };
    typedef TSharedPtr<FGs2Domain> FGs2DomainPtr;
}
