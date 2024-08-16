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
#include "Math/BigInt.h"
#include "SpeculativeExecutor/SpeculativeExecutor.h"

namespace Gs2::Account::Domain
{
    class FGs2AccountDomain;
    typedef TSharedPtr<FGs2AccountDomain> FGs2AccountDomainPtr;
}

namespace Gs2::AdReward::Domain
{
    class FGs2AdRewardDomain;
    typedef TSharedPtr<FGs2AdRewardDomain> FGs2AdRewardDomainPtr;
}

namespace Gs2::Auth::Domain
{
    class FGs2AuthDomain;
    typedef TSharedPtr<FGs2AuthDomain> FGs2AuthDomainPtr;
}

namespace Gs2::Buff::Domain
{
    class FGs2BuffDomain;
    typedef TSharedPtr<FGs2BuffDomain> FGs2BuffDomainPtr;
}

namespace Gs2::Chat::Domain
{
    class FGs2ChatDomain;
    typedef TSharedPtr<FGs2ChatDomain> FGs2ChatDomainPtr;
}

namespace Gs2::Datastore::Domain
{
    class FGs2DatastoreDomain;
    typedef TSharedPtr<FGs2DatastoreDomain> FGs2DatastoreDomainPtr;
}

namespace Gs2::Deploy::Domain
{
    class FGs2DeployDomain;
    typedef TSharedPtr<FGs2DeployDomain> FGs2DeployDomainPtr;
}

namespace Gs2::Dictionary::Domain
{
    class FGs2DictionaryDomain;
    typedef TSharedPtr<FGs2DictionaryDomain> FGs2DictionaryDomainPtr;
}

namespace Gs2::Distributor::Domain
{
    class FGs2DistributorDomain;
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}

namespace Gs2::Enchant::Domain
{
    class FGs2EnchantDomain;
    typedef TSharedPtr<FGs2EnchantDomain> FGs2EnchantDomainPtr;
}

namespace Gs2::Enhance::Domain
{
    class FGs2EnhanceDomain;
    typedef TSharedPtr<FGs2EnhanceDomain> FGs2EnhanceDomainPtr;
}

namespace Gs2::Exchange::Domain
{
    class FGs2ExchangeDomain;
    typedef TSharedPtr<FGs2ExchangeDomain> FGs2ExchangeDomainPtr;
}

namespace Gs2::Experience::Domain
{
    class FGs2ExperienceDomain;
    typedef TSharedPtr<FGs2ExperienceDomain> FGs2ExperienceDomainPtr;
}

namespace Gs2::Formation::Domain
{
    class FGs2FormationDomain;
    typedef TSharedPtr<FGs2FormationDomain> FGs2FormationDomainPtr;
}

namespace Gs2::Friend::Domain
{
    class FGs2FriendDomain;
    typedef TSharedPtr<FGs2FriendDomain> FGs2FriendDomainPtr;
}

namespace Gs2::Gateway::Domain
{
    class FGs2GatewayDomain;
    typedef TSharedPtr<FGs2GatewayDomain> FGs2GatewayDomainPtr;
}

namespace Gs2::Grade::Domain
{
    class FGs2GradeDomain;
    typedef TSharedPtr<FGs2GradeDomain> FGs2GradeDomainPtr;
}

namespace Gs2::Guild::Domain
{
    class FGs2GuildDomain;
    typedef TSharedPtr<FGs2GuildDomain> FGs2GuildDomainPtr;
}

namespace Gs2::Identifier::Domain
{
    class FGs2IdentifierDomain;
    typedef TSharedPtr<FGs2IdentifierDomain> FGs2IdentifierDomainPtr;
}

namespace Gs2::Idle::Domain
{
    class FGs2IdleDomain;
    typedef TSharedPtr<FGs2IdleDomain> FGs2IdleDomainPtr;
}

namespace Gs2::Inbox::Domain
{
    class FGs2InboxDomain;
    typedef TSharedPtr<FGs2InboxDomain> FGs2InboxDomainPtr;
}

namespace Gs2::Inventory::Domain
{
    class FGs2InventoryDomain;
    typedef TSharedPtr<FGs2InventoryDomain> FGs2InventoryDomainPtr;
}

namespace Gs2::JobQueue::Domain
{
    class FGs2JobQueueDomain;
    typedef TSharedPtr<FGs2JobQueueDomain> FGs2JobQueueDomainPtr;
}

namespace Gs2::Key::Domain
{
    class FGs2KeyDomain;
    typedef TSharedPtr<FGs2KeyDomain> FGs2KeyDomainPtr;
}

namespace Gs2::Limit::Domain
{
    class FGs2LimitDomain;
    typedef TSharedPtr<FGs2LimitDomain> FGs2LimitDomainPtr;
}

namespace Gs2::Log::Domain
{
    class FGs2LogDomain;
    typedef TSharedPtr<FGs2LogDomain> FGs2LogDomainPtr;
}

namespace Gs2::LoginReward::Domain
{
    class FGs2LoginRewardDomain;
    typedef TSharedPtr<FGs2LoginRewardDomain> FGs2LoginRewardDomainPtr;
}

namespace Gs2::Lock::Domain
{
    class FGs2LockDomain;
    typedef TSharedPtr<FGs2LockDomain> FGs2LockDomainPtr;
}

namespace Gs2::Lock::Domain
{
    class FGs2LockDomain;
    typedef TSharedPtr<FGs2LockDomain> FGs2LockDomainPtr;
}

namespace Gs2::Lottery::Domain
{
    class FGs2LotteryDomain;
    typedef TSharedPtr<FGs2LotteryDomain> FGs2LotteryDomainPtr;
}

namespace Gs2::Matchmaking::Domain
{
    class FGs2MatchmakingDomain;
    typedef TSharedPtr<FGs2MatchmakingDomain> FGs2MatchmakingDomainPtr;
}

namespace Gs2::MegaField::Domain
{
    class FGs2MegaFieldDomain;
    typedef TSharedPtr<FGs2MegaFieldDomain> FGs2MegaFieldDomainPtr;
}

namespace Gs2::Mission::Domain
{
    class FGs2MissionDomain;
    typedef TSharedPtr<FGs2MissionDomain> FGs2MissionDomainPtr;
}

namespace Gs2::Money::Domain
{
    class FGs2MoneyDomain;
    typedef TSharedPtr<FGs2MoneyDomain> FGs2MoneyDomainPtr;
}

namespace Gs2::Money2::Domain
{
    class FGs2Money2Domain;
    typedef TSharedPtr<FGs2Money2Domain> FGs2Money2DomainPtr;
}

namespace Gs2::News::Domain
{
    class FGs2NewsDomain;
    typedef TSharedPtr<FGs2NewsDomain> FGs2NewsDomainPtr;
}

namespace Gs2::Quest::Domain
{
    class FGs2QuestDomain;
    typedef TSharedPtr<FGs2QuestDomain> FGs2QuestDomainPtr;
}

namespace Gs2::Ranking::Domain
{
    class FGs2RankingDomain;
    typedef TSharedPtr<FGs2RankingDomain> FGs2RankingDomainPtr;
}

namespace Gs2::Ranking2::Domain
{
    class FGs2Ranking2Domain;
    typedef TSharedPtr<FGs2Ranking2Domain> FGs2Ranking2DomainPtr;
}

namespace Gs2::Realtime::Domain
{
    class FGs2RealtimeDomain;
    typedef TSharedPtr<FGs2RealtimeDomain> FGs2RealtimeDomainPtr;
}

namespace Gs2::Schedule::Domain
{
    class FGs2ScheduleDomain;
    typedef TSharedPtr<FGs2ScheduleDomain> FGs2ScheduleDomainPtr;
}

namespace Gs2::Script::Domain
{
    class FGs2ScriptDomain;
    typedef TSharedPtr<FGs2ScriptDomain> FGs2ScriptDomainPtr;
}

namespace Gs2::SeasonRating::Domain
{
    class FGs2SeasonRatingDomain;
    typedef TSharedPtr<FGs2SeasonRatingDomain> FGs2SeasonRatingDomainPtr;
}

namespace Gs2::SerialKey::Domain
{
    class FGs2SerialKeyDomain;
    typedef TSharedPtr<FGs2SerialKeyDomain> FGs2SerialKeyDomainPtr;
}

namespace Gs2::Showcase::Domain
{
    class FGs2ShowcaseDomain;
    typedef TSharedPtr<FGs2ShowcaseDomain> FGs2ShowcaseDomainPtr;
}

namespace Gs2::SkillTree::Domain
{
    class FGs2SkillTreeDomain;
    typedef TSharedPtr<FGs2SkillTreeDomain> FGs2SkillTreeDomainPtr;
}

namespace Gs2::Stamina::Domain
{
    class FGs2StaminaDomain;
    typedef TSharedPtr<FGs2StaminaDomain> FGs2StaminaDomainPtr;
}

namespace Gs2::StateMachine::Domain
{
    class FGs2StateMachineDomain;
    typedef TSharedPtr<FGs2StateMachineDomain> FGs2StateMachineDomainPtr;
}

namespace Gs2::Version::Domain
{
    class FGs2VersionDomain;
    typedef TSharedPtr<FGs2VersionDomain> FGs2VersionDomainPtr;
}

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