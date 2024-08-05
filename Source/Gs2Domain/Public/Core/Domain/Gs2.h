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
#include "AdReward/Domain/Gs2AdReward.h"
#include "Auth/Domain/Gs2Auth.h"
#include "Buff/Domain/Gs2Buff.h"
#include "Chat/Domain/Gs2Chat.h"
#include "Datastore/Domain/Gs2Datastore.h"
#include "Deploy/Domain/Gs2Deploy.h"
#include "Dictionary/Domain/Gs2Dictionary.h"
#include "Distributor/Domain/Gs2Distributor.h"
#include "Enchant/Domain/Gs2Enchant.h"
#include "Enhance/Domain/Gs2Enhance.h"
#include "Exchange/Domain/Gs2Exchange.h"
#include "Experience/Domain/Gs2Experience.h"
#include "Formation/Domain/Gs2Formation.h"
#include "Friend/Domain/Gs2Friend.h"
#include "Gateway/Domain/Gs2Gateway.h"
#include "Grade/Domain/Gs2Grade.h"
#include "Guild/Domain/Gs2Guild.h"
#include "Identifier/Domain/Gs2Identifier.h"
#include "Idle/Domain/Gs2Idle.h"
#include "Inbox/Domain/Gs2Inbox.h"
#include "Inventory/Domain/Gs2Inventory.h"
#include "JobQueue/Domain/Gs2JobQueue.h"
#include "Key/Domain/Gs2Key.h"
#include "Limit/Domain/Gs2Limit.h"
#include "Log/Domain/Gs2Log.h"
#include "LoginReward/Domain/Gs2LoginReward.h"
#include "Lock/Domain/Gs2Lock.h"
#include "Lottery/Domain/Gs2Lottery.h"
#include "Matchmaking/Domain/Gs2Matchmaking.h"
#include "Math/BigInt.h"
#include "MegaField/Domain/Gs2MegaField.h"
#include "Mission/Domain/Gs2Mission.h"
#include "Money/Domain/Gs2Money.h"
#include "Money2/Domain/Gs2Money2.h"
#include "News/Domain/Gs2News.h"
#include "Quest/Domain/Gs2Quest.h"
#include "Ranking/Domain/Gs2Ranking.h"
#include "Ranking2/Domain/Gs2Ranking2.h"
#include "Realtime/Domain/Gs2Realtime.h"
#include "Schedule/Domain/Gs2Schedule.h"
#include "Script/Domain/Gs2Script.h"
#include "SeasonRating/Domain/Gs2SeasonRating.h"
#include "SerialKey/Domain/Gs2SerialKey.h"
#include "Showcase/Domain/Gs2Showcase.h"
#include "SkillTree/Domain/Gs2SkillTree.h"
#include "SpeculativeExecutor/SpeculativeExecutor.h"
#include "Stamina/Domain/Gs2Stamina.h"
#include "StateMachine/Domain/Gs2StateMachine.h"
#include "Version/Domain/Gs2Version.h"

namespace Gs2::Core::Domain
{
    class GS2DOMAIN_API FGs2 :
        public TSharedFromThis<FGs2>
    {
    public:
    
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        const Gs2::Core::Domain::Model::FTransactionConfigurationPtr TransactionConfiguration;
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession;
        const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession;
        const TOptional<FString> DistributorNamespaceName;

        Gs2::Account::Domain::FGs2AccountDomainPtr Account;
        Gs2::AdReward::Domain::FGs2AdRewardDomainPtr AdReward;
        Gs2::Auth::Domain::FGs2AuthDomainPtr Auth;
        Gs2::Buff::Domain::FGs2BuffDomainPtr Buff;
        Gs2::Chat::Domain::FGs2ChatDomainPtr Chat;
        Gs2::Datastore::Domain::FGs2DatastoreDomainPtr Datastore;
        Gs2::Deploy::Domain::FGs2DeployDomainPtr Deploy;
        Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr Dictionary;
        Gs2::Distributor::Domain::FGs2DistributorDomainPtr Distributor;
        Gs2::Enchant::Domain::FGs2EnchantDomainPtr Enchant;
        Gs2::Enhance::Domain::FGs2EnhanceDomainPtr Enhance;
        Gs2::Exchange::Domain::FGs2ExchangeDomainPtr Exchange;
        Gs2::Experience::Domain::FGs2ExperienceDomainPtr Experience;
        Gs2::Formation::Domain::FGs2FormationDomainPtr Formation;
        Gs2::Friend::Domain::FGs2FriendDomainPtr Friend;
        Gs2::Gateway::Domain::FGs2GatewayDomainPtr Gateway;
        Gs2::Grade::Domain::FGs2GradeDomainPtr Grade;
        Gs2::Guild::Domain::FGs2GuildDomainPtr Guild;
        Gs2::Identifier::Domain::FGs2IdentifierDomainPtr Identifier;
        Gs2::Idle::Domain::FGs2IdleDomainPtr Idle;
        Gs2::Inbox::Domain::FGs2InboxDomainPtr Inbox;
        Gs2::Inventory::Domain::FGs2InventoryDomainPtr Inventory;
        Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr JobQueue;
        Gs2::Key::Domain::FGs2KeyDomainPtr Key;
        Gs2::Limit::Domain::FGs2LimitDomainPtr Limit;
        Gs2::Log::Domain::FGs2LogDomainPtr Log;
        Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr LoginReward;
        Gs2::Lock::Domain::FGs2LockDomainPtr Lock;
        Gs2::Lottery::Domain::FGs2LotteryDomainPtr Lottery;
        Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr Matchmaking;
        Gs2::MegaField::Domain::FGs2MegaFieldDomainPtr MegaField;
        Gs2::Mission::Domain::FGs2MissionDomainPtr Mission;
        Gs2::Money::Domain::FGs2MoneyDomainPtr Money;
        Gs2::Money2::Domain::FGs2Money2DomainPtr Money2;
        Gs2::News::Domain::FGs2NewsDomainPtr News;
        Gs2::Quest::Domain::FGs2QuestDomainPtr Quest;
        Gs2::Ranking::Domain::FGs2RankingDomainPtr Ranking;
        Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr Ranking2;
        Gs2::Realtime::Domain::FGs2RealtimeDomainPtr Realtime;
        Gs2::Schedule::Domain::FGs2ScheduleDomainPtr Schedule;
        Gs2::Script::Domain::FGs2ScriptDomainPtr Script;
        Gs2::SeasonRating::Domain::FGs2SeasonRatingDomainPtr SeasonRating;
        Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr SerialKey;
        Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr Showcase;
        Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr SkillTree;
        Gs2::Stamina::Domain::FGs2StaminaDomainPtr Stamina;
        Gs2::StateMachine::Domain::FGs2StateMachineDomainPtr StateMachine;
        Gs2::Version::Domain::FGs2VersionDomainPtr Version;

        TOptional<FString> DefaultContextStack;

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

        void Initialize();
    
        void ClearCache()
        {
            if (Account == nullptr)
            {
                Initialize();
            }
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
            public Gs2::Core::Util::TGs2Future<void>,
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
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );
        
        class GS2DOMAIN_API FDispatchByUserIdTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FDispatchByUserIdTask>
        {
            const TSharedPtr<FGs2> Self;
            const FString UserId;
        public:
            explicit FDispatchByUserIdTask(
                const TSharedPtr<FGs2> Self,
                const FString UserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };
        friend FDispatchByUserIdTask;

        TSharedPtr<FAsyncTask<FDispatchByUserIdTask>> DispatchByUserId(
            const FString UserId
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

        Gs2::Core::Model::FGs2ErrorPtr TransactionExecute(
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
            const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireAction,
            TBigInt<1024, false> Rate
        );
    };
    typedef TSharedPtr<FGs2> FGs2Ptr;
}