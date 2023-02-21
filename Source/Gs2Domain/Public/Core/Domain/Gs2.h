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
#include "Gs2Core.h"
#include "Account/Domain/Gs2Account.h"
#include "Auth/Domain/Gs2Auth.h"
#include "Chat/Domain/Gs2Chat.h"
#include "Datastore/Domain/Gs2Datastore.h"
//#include "Deploy/Domain/Gs2Deploy.h"
#include "Dictionary/Domain/Gs2Dictionary.h"
#include "Distributor/Domain/Gs2Distributor.h"
#include "Enhance/Domain/Gs2Enhance.h"
#include "Exchange/Domain/Gs2Exchange.h"
#include "Experience/Domain/Gs2Experience.h"
#include "Formation/Domain/Gs2Formation.h"
#include "Friend/Domain/Gs2Friend.h"
#include "Gateway/Domain/Gs2Gateway.h"
#include "Identifier/Domain/Gs2Identifier.h"
#include "Inbox/Domain/Gs2Inbox.h"
#include "Inventory/Domain/Gs2Inventory.h"
#include "JobQueue/Domain/Gs2JobQueue.h"
#include "Key/Domain/Gs2Key.h"
#include "Limit/Domain/Gs2Limit.h"
#include "Lock/Domain/Gs2Lock.h"
#include "Lottery/Domain/Gs2Lottery.h"
#include "Matchmaking/Domain/Gs2Matchmaking.h"
#include "MegaField/Domain/Gs2MegaField.h"
#include "Mission/Domain/Gs2Mission.h"
#include "Money/Domain/Gs2Money.h"
#include "News/Domain/Gs2News.h"
#include "Quest/Domain/Gs2Quest.h"
#include "Ranking/Domain/Gs2Ranking.h"
#include "Realtime/Domain/Gs2Realtime.h"
#include "Schedule/Domain/Gs2Schedule.h"
#include "Script/Domain/Gs2Script.h"
#include "SerialKey/Domain/Gs2SerialKey.h"
#include "Showcase/Domain/Gs2Showcase.h"
#include "Stamina/Domain/Gs2Stamina.h"
#include "Version/Domain/Gs2Version.h"

namespace Gs2::Core::Domain
{
    class GS2DOMAIN_API FGs2 :
        public TSharedFromThis<FGs2>
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession;
        const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession;
        const TOptional<FString> DistributorNamespaceName;

    public:
    
        const Gs2::Account::Domain::FGs2AccountDomainPtr Account;
        const Gs2::Auth::Domain::FGs2AuthDomainPtr Auth;
        const Gs2::Chat::Domain::FGs2ChatDomainPtr Chat;
        const Gs2::Datastore::Domain::FGs2DatastoreDomainPtr Datastore;
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr Dictionary;
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr Distributor;
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr Enhance;
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr Exchange;
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr Experience;
        const Gs2::Formation::Domain::FGs2FormationDomainPtr Formation;
        const Gs2::Friend::Domain::FGs2FriendDomainPtr Friend;
        const Gs2::Gateway::Domain::FGs2GatewayDomainPtr Gateway;
        const Gs2::Identifier::Domain::FGs2IdentifierDomainPtr Identifier;
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr Inbox;
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr Inventory;
        const Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr JobQueue;
        const Gs2::Key::Domain::FGs2KeyDomainPtr Key;
        const Gs2::Limit::Domain::FGs2LimitDomainPtr Limit;
        const Gs2::Lock::Domain::FGs2LockDomainPtr Lock;
        const Gs2::Lottery::Domain::FGs2LotteryDomainPtr Lottery;
        const Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr Matchmaking;
        const Gs2::MegaField::Domain::FGs2MegaFieldDomainPtr MegaField;
        const Gs2::Mission::Domain::FGs2MissionDomainPtr Mission;
        const Gs2::Money::Domain::FGs2MoneyDomainPtr Money;
        const Gs2::News::Domain::FGs2NewsDomainPtr News;
        const Gs2::Quest::Domain::FGs2QuestDomainPtr Quest;
        const Gs2::Ranking::Domain::FGs2RankingDomainPtr Ranking;
        const Gs2::Realtime::Domain::FGs2RealtimeDomainPtr Realtime;
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr Schedule;
        const Gs2::Script::Domain::FGs2ScriptDomainPtr Script;
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr SerialKey;
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr Showcase;
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr Stamina;
        const Gs2::Version::Domain::FGs2VersionDomainPtr Version;

        bool Disposed;

        explicit FGs2(
            Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
            Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession = nullptr,
            TOptional<FString> DistributorNamespaceName = TOptional<FString>()
        );
        FGs2(
            const FGs2& From
        );
        virtual ~FGs2();
    
        void ClearCache() const
        {
            Cache->Clear();
        }
        void UpdateCacheFromStampSheet(
            FString Action,
            FString Request,
            FString Result
        ) const;
        void UpdateCacheFromStampTask(
            FString Action,
            FString Request,
            FString Result
        ) const;

        void PushJobQueue(
            TOptional<FString> NamespaceName
            ) const;
        
        void UpdateCacheFromJobResult(
            Gs2::JobQueue::Model::FJobPtr Job,
            Gs2::JobQueue::Model::FJobResultBodyPtr Result
            );
        
        class GS2DOMAIN_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );
        
        class GS2DOMAIN_API FDisconnectTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDisconnectTask>
        {
            const TSharedPtr<FGs2> Self;
        public:
            explicit FDisconnectTask(
                const TSharedPtr<FGs2> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDisconnectTask;

        TSharedPtr<FAsyncTask<FDisconnectTask>> Disconnect();
    };
    typedef TSharedPtr<FGs2> FGs2Ptr;
}