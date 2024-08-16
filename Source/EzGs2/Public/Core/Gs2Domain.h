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
#include "Core/Domain/Gs2.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Util
{
    class IAuthenticator;
    class FProfile;
}

namespace Gs2::UE5::Account::Domain
{
    class FEzGs2Account;
    typedef TSharedPtr<FEzGs2Account> FEzGs2AccountPtr;
}

namespace Gs2::UE5::AdReward::Domain
{
    class FEzGs2AdReward;
    typedef TSharedPtr<FEzGs2AdReward> FEzGs2AdRewardPtr;
}

namespace Gs2::UE5::Auth::Domain
{
    class FEzGs2Auth;
    typedef TSharedPtr<FEzGs2Auth> FEzGs2AuthPtr;
}

namespace Gs2::UE5::Buff::Domain
{
    class FEzGs2Buff;
    typedef TSharedPtr<FEzGs2Buff> FEzGs2BuffPtr;
}

namespace Gs2::UE5::Chat::Domain
{
    class FEzGs2Chat;
    typedef TSharedPtr<FEzGs2Chat> FEzGs2ChatPtr;
}

namespace Gs2::UE5::Datastore::Domain
{
    class FEzGs2Datastore;
    typedef TSharedPtr<FEzGs2Datastore> FEzGs2DatastorePtr;
}

namespace Gs2::UE5::Dictionary::Domain
{
    class FEzGs2Dictionary;
    typedef TSharedPtr<FEzGs2Dictionary> FEzGs2DictionaryPtr;
}

namespace Gs2::UE5::Distributor::Domain
{
    class FEzGs2Distributor;
    typedef TSharedPtr<FEzGs2Distributor> FEzGs2DistributorPtr;
}

namespace Gs2::UE5::Enchant::Domain
{
    class FEzGs2Enchant;
    typedef TSharedPtr<FEzGs2Enchant> FEzGs2EnchantPtr;
}

namespace Gs2::UE5::Enhance::Domain
{
    class FEzGs2Enhance;
    typedef TSharedPtr<FEzGs2Enhance> FEzGs2EnhancePtr;
}

namespace Gs2::UE5::Exchange::Domain
{
    class FEzGs2Exchange;
    typedef TSharedPtr<FEzGs2Exchange> FEzGs2ExchangePtr;
}

namespace Gs2::UE5::Experience::Domain
{
    class FEzGs2Experience;
    typedef TSharedPtr<FEzGs2Experience> FEzGs2ExperiencePtr;
}

namespace Gs2::UE5::Formation::Domain
{
    class FEzGs2Formation;
    typedef TSharedPtr<FEzGs2Formation> FEzGs2FormationPtr;
}

namespace Gs2::UE5::Friend::Domain
{
    class FEzGs2Friend;
    typedef TSharedPtr<FEzGs2Friend> FEzGs2FriendPtr;
}

namespace Gs2::UE5::Gateway::Domain
{
    class FEzGs2Gateway;
    typedef TSharedPtr<FEzGs2Gateway> FEzGs2GatewayPtr;
}

namespace Gs2::UE5::Grade::Domain
{
    class FEzGs2Grade;
    typedef TSharedPtr<FEzGs2Grade> FEzGs2GradePtr;
}

namespace Gs2::UE5::Guild::Domain
{
    class FEzGs2Guild;
    typedef TSharedPtr<FEzGs2Guild> FEzGs2GuildPtr;
}

namespace Gs2::UE5::Idle::Domain
{
    class FEzGs2Idle;
    typedef TSharedPtr<FEzGs2Idle> FEzGs2IdlePtr;
}

namespace Gs2::UE5::Inbox::Domain
{
    class FEzGs2Inbox;
    typedef TSharedPtr<FEzGs2Inbox> FEzGs2InboxPtr;
}

namespace Gs2::UE5::Inventory::Domain
{
    class FEzGs2Inventory;
    typedef TSharedPtr<FEzGs2Inventory> FEzGs2InventoryPtr;
}

namespace Gs2::UE5::JobQueue::Domain
{
    class FEzGs2JobQueue;
    typedef TSharedPtr<FEzGs2JobQueue> FEzGs2JobQueuePtr;
}

namespace Gs2::UE5::Limit::Domain
{
    class FEzGs2Limit;
    typedef TSharedPtr<FEzGs2Limit> FEzGs2LimitPtr;
}

namespace Gs2::UE5::LoginReward::Domain
{
    class FEzGs2LoginReward;
    typedef TSharedPtr<FEzGs2LoginReward> FEzGs2LoginRewardPtr;
}

namespace Gs2::UE5::Lottery::Domain
{
    class FEzGs2Lottery;
    typedef TSharedPtr<FEzGs2Lottery> FEzGs2LotteryPtr;
}

namespace Gs2::UE5::Matchmaking::Domain
{
    class FEzGs2Matchmaking;
    typedef TSharedPtr<FEzGs2Matchmaking> FEzGs2MatchmakingPtr;
}

namespace Gs2::UE5::MegaField::Domain
{
    class FEzGs2MegaField;
    typedef TSharedPtr<FEzGs2MegaField> FEzGs2MegaFieldPtr;
}

namespace Gs2::UE5::Mission::Domain
{
    class FEzGs2Mission;
    typedef TSharedPtr<FEzGs2Mission> FEzGs2MissionPtr;
}

namespace Gs2::UE5::Money::Domain
{
    class FEzGs2Money;
    typedef TSharedPtr<FEzGs2Money> FEzGs2MoneyPtr;
}

namespace Gs2::UE5::Money2::Domain
{
    class FEzGs2Money2;
    typedef TSharedPtr<FEzGs2Money2> FEzGs2Money2Ptr;
}

namespace Gs2::UE5::News::Domain
{
    class FEzGs2News;
    typedef TSharedPtr<FEzGs2News> FEzGs2NewsPtr;
}

namespace Gs2::UE5::Quest::Domain
{
    class FEzGs2Quest;
    typedef TSharedPtr<FEzGs2Quest> FEzGs2QuestPtr;
}

namespace Gs2::UE5::Ranking::Domain
{
    class FEzGs2Ranking;
    typedef TSharedPtr<FEzGs2Ranking> FEzGs2RankingPtr;
}

namespace Gs2::UE5::Ranking2::Domain
{
    class FEzGs2Ranking2;
    typedef TSharedPtr<FEzGs2Ranking2> FEzGs2Ranking2Ptr;
}

namespace Gs2::UE5::Realtime::Domain
{
    class FEzGs2Realtime;
    typedef TSharedPtr<FEzGs2Realtime> FEzGs2RealtimePtr;
}

namespace Gs2::UE5::Schedule::Domain
{
    class FEzGs2Schedule;
    typedef TSharedPtr<FEzGs2Schedule> FEzGs2SchedulePtr;
}

namespace Gs2::UE5::SeasonRating::Domain
{
    class FEzGs2SeasonRating;
    typedef TSharedPtr<FEzGs2SeasonRating> FEzGs2SeasonRatingPtr;
}

namespace Gs2::UE5::SerialKey::Domain
{
    class FEzGs2SerialKey;
    typedef TSharedPtr<FEzGs2SerialKey> FEzGs2SerialKeyPtr;
}

namespace Gs2::UE5::Showcase::Domain
{
    class FEzGs2Showcase;
    typedef TSharedPtr<FEzGs2Showcase> FEzGs2ShowcasePtr;
}

namespace Gs2::UE5::SkillTree::Domain
{
    class FEzGs2SkillTree;
    typedef TSharedPtr<FEzGs2SkillTree> FEzGs2SkillTreePtr;
}

namespace Gs2::UE5::Stamina::Domain
{
    class FEzGs2Stamina;
    typedef TSharedPtr<FEzGs2Stamina> FEzGs2StaminaPtr;
}

namespace Gs2::UE5::StateMachine::Domain
{
    class FEzGs2StateMachine;
    typedef TSharedPtr<FEzGs2StateMachine> FEzGs2StateMachinePtr;
}

namespace Gs2::UE5::Version::Domain
{
    class FEzGs2Version;
    typedef TSharedPtr<FEzGs2Version> FEzGs2VersionPtr;
}

namespace Gs2::UE5::Core::Domain
{
    class FGs2Domain;

    class EZGS2_API FGs2Domain :
        public TSharedFromThis<FGs2Domain>
    {
        void Initialize();
        
    public:
        Util::FGs2ConnectionPtr Connection;
        Gs2::Core::Domain::FGs2Ptr Super;

        Gs2::UE5::Account::Domain::FEzGs2AccountPtr Account;
        Gs2::UE5::AdReward::Domain::FEzGs2AdRewardPtr AdReward;
        Gs2::UE5::Auth::Domain::FEzGs2AuthPtr Auth;
        Gs2::UE5::Buff::Domain::FEzGs2BuffPtr Buff;
        Gs2::UE5::Chat::Domain::FEzGs2ChatPtr Chat;
        Gs2::UE5::Datastore::Domain::FEzGs2DatastorePtr Datastore;
        Gs2::UE5::Dictionary::Domain::FEzGs2DictionaryPtr Dictionary;
        Gs2::UE5::Distributor::Domain::FEzGs2DistributorPtr Distributor;
        Gs2::UE5::Enchant::Domain::FEzGs2EnchantPtr Enchant;
        Gs2::UE5::Enhance::Domain::FEzGs2EnhancePtr Enhance;
        Gs2::UE5::Exchange::Domain::FEzGs2ExchangePtr Exchange;
        Gs2::UE5::Experience::Domain::FEzGs2ExperiencePtr Experience;
        Gs2::UE5::Formation::Domain::FEzGs2FormationPtr Formation;
        Gs2::UE5::Friend::Domain::FEzGs2FriendPtr Friend;
        Gs2::UE5::Gateway::Domain::FEzGs2GatewayPtr Gateway;
        Gs2::UE5::Grade::Domain::FEzGs2GradePtr Grade;
        Gs2::UE5::Guild::Domain::FEzGs2GuildPtr Guild;
        Gs2::UE5::Idle::Domain::FEzGs2IdlePtr Idle;
        Gs2::UE5::Inbox::Domain::FEzGs2InboxPtr Inbox;
        Gs2::UE5::Inventory::Domain::FEzGs2InventoryPtr Inventory;
        Gs2::UE5::JobQueue::Domain::FEzGs2JobQueuePtr JobQueue;
        Gs2::UE5::Limit::Domain::FEzGs2LimitPtr Limit;
        Gs2::UE5::LoginReward::Domain::FEzGs2LoginRewardPtr LoginReward;
        Gs2::UE5::Lottery::Domain::FEzGs2LotteryPtr Lottery;
        Gs2::UE5::Matchmaking::Domain::FEzGs2MatchmakingPtr Matchmaking;
        Gs2::UE5::MegaField::Domain::FEzGs2MegaFieldPtr MegaField;
        Gs2::UE5::Mission::Domain::FEzGs2MissionPtr Mission;
        Gs2::UE5::Money::Domain::FEzGs2MoneyPtr Money;
        Gs2::UE5::Money2::Domain::FEzGs2Money2Ptr Money2;
        Gs2::UE5::News::Domain::FEzGs2NewsPtr News;
        Gs2::UE5::Quest::Domain::FEzGs2QuestPtr Quest;
        Gs2::UE5::Ranking::Domain::FEzGs2RankingPtr Ranking;
        Gs2::UE5::Ranking2::Domain::FEzGs2Ranking2Ptr Ranking2;
        Gs2::UE5::Realtime::Domain::FEzGs2RealtimePtr Realtime;
        Gs2::UE5::Schedule::Domain::FEzGs2SchedulePtr Schedule;
        Gs2::UE5::SeasonRating::Domain::FEzGs2SeasonRatingPtr SeasonRating;
        Gs2::UE5::SerialKey::Domain::FEzGs2SerialKeyPtr SerialKey;
        Gs2::UE5::Showcase::Domain::FEzGs2ShowcasePtr Showcase;
        Gs2::UE5::SkillTree::Domain::FEzGs2SkillTreePtr SkillTree;
        Gs2::UE5::Stamina::Domain::FEzGs2StaminaPtr Stamina;
        Gs2::UE5::StateMachine::Domain::FEzGs2StateMachinePtr StateMachine;
        Gs2::UE5::Version::Domain::FEzGs2VersionPtr Version;
        
        explicit FGs2Domain(
            Util::FGs2ConnectionPtr Connection,
            FString DistributorNamespaceName = "default"
            );
        FGs2Domain(
            FGs2Domain& From
        );
        explicit FGs2Domain(
            Gs2::Core::Domain::FGs2Ptr Gs2
        );
        ~FGs2Domain() = default;
        
        class EZGS2_API FLoginTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Util::FGameSession>,
            public TSharedFromThis<FLoginTask>
        {
            TSharedPtr<FGs2Domain> Self;
            TSharedPtr<Util::IAuthenticator> Authenticator;
            FString UserId;
            FString Password;

        public:
            explicit FLoginTask(
                const TSharedPtr<FGs2Domain> Self,
                const TSharedPtr<Util::IAuthenticator> Authenticator,
                const FString UserId,
                const FString Password
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Util::FGameSession>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FLoginTask>> Login(
            const TSharedPtr<Util::IAuthenticator> Authenticator,
            const FString UserId,
            const FString Password
            );

        class EZGS2_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2Domain> Self;
            const Gs2::UE5::Util::FGameSessionPtr GameSession;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2Domain> Self,
                const Gs2::UE5::Util::FGameSessionPtr GameSession
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            Gs2::UE5::Util::FGameSessionPtr GameSession
            );

        class EZGS2_API FDisconnectTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FDisconnectTask>
        {
            const TSharedPtr<FGs2Domain> Self;
        public:
            explicit FDisconnectTask(
                const TSharedPtr<FGs2Domain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };
        friend FDisconnectTask;

        TSharedPtr<FAsyncTask<FDisconnectTask>> Disconnect(
        );
    };
    typedef TSharedPtr<FGs2Domain> FGs2DomainPtr;
    
}

namespace Gs2::UE5::Core
{
    class EZGS2_API FGs2Client
    {
        class EZGS2_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Domain::FGs2Domain>,
            public TSharedFromThis<FCreateTask>
        {
            Gs2::Core::Model::FGs2CredentialPtr Credential;
            Gs2::Core::Model::ERegion Region;
            FString DistributorNamespaceName;
        public:
            explicit FCreateTask(
                Gs2::Core::Model::FGs2CredentialPtr Credential,
                Gs2::Core::Model::ERegion Region,
                FString DistributorNamespaceName
            ):
                Credential(Credential),
                Region(Region),
                DistributorNamespaceName(DistributorNamespaceName)
            {
                
            }

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Domain::FGs2Domain>> Result
            ) override
            {
                auto Connection = MakeShared<Util::FGs2Connection>(
                    Credential,
                    Region
                );
                auto Future = Connection->Connect();
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    return Future->GetTask().Error();
                }
                *Result = MakeShared<Domain::FGs2Domain>(
                    Connection,
                    DistributorNamespaceName
                );
                return nullptr;
            }
        };
        friend FCreateTask;

    public:
        
        static TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Gs2::Core::Model::FGs2CredentialPtr Credential,
            Gs2::Core::Model::ERegion Region,
            FString DistributorNamespaceName = "default"
        )
        {
            return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(
                Credential,
                Region,
                DistributorNamespaceName
            );
        }
    };
}
