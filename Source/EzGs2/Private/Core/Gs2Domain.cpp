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

#include "Core/Gs2Domain.h"

#include "Account/Domain/EzGs2Account.h"
#include "Auth/Domain/EzGs2Auth.h"
#include "Buff/Domain/EzGs2Buff.h"
#include "Chat/Domain/EzGs2Chat.h"
#include "Datastore/Domain/EzGs2Datastore.h"
#include "Dictionary/Domain/EzGs2Dictionary.h"
#include "Distributor/Domain/EzGs2Distributor.h"
#include "Enchant/Domain/EzGs2Enchant.h"
#include "Enhance/Domain/EzGs2Enhance.h"
#include "Exchange/Domain/EzGs2Exchange.h"
#include "Experience/Domain/EzGs2Experience.h"
#include "Formation/Domain/EzGs2Formation.h"
#include "Friend/Domain/EzGs2Friend.h"
#include "Gateway/Domain/EzGs2Gateway.h"
#include "Grade/Domain/EzGs2Grade.h"
#include "Guild/Domain/EzGs2Guild.h"
#include "Idle/Domain/EzGs2Idle.h"
#include "Inbox/Domain/EzGs2Inbox.h"
#include "Inventory/Domain/EzGs2Inventory.h"
#include "JobQueue/Domain/EzGs2JobQueue.h"
#include "Limit/Domain/EzGs2Limit.h"
#include "LoginReward/Domain/EzGs2LoginReward.h"
#include "Lottery/Domain/EzGs2Lottery.h"
#include "Matchmaking/Domain/EzGs2Matchmaking.h"
#include "MegaField/Domain/EzGs2MegaField.h"
#include "Mission/Domain/EzGs2Mission.h"
#include "Money/Domain/EzGs2Money.h"
#include "Money2/Domain/EzGs2Money2.h"
#include "News/Domain/EzGs2News.h"
#include "Quest/Domain/EzGs2Quest.h"
#include "Ranking/Domain/EzGs2Ranking.h"
#include "Ranking2/Domain/EzGs2Ranking2.h"
#include "Realtime/Domain/EzGs2Realtime.h"
#include "Schedule/Domain/EzGs2Schedule.h"
#include "SeasonRating/Domain/EzGs2SeasonRating.h"
#include "SerialKey/Domain/EzGs2SerialKey.h"
#include "Showcase/Domain/EzGs2Showcase.h"
#include "SkillTree/Domain/EzGs2SkillTree.h"
#include "Stamina/Domain/EzGs2Stamina.h"
#include "StateMachine/Domain/EzGs2StateMachine.h"
#include "Version/Domain/EzGs2Version.h"

namespace Gs2::UE5::Core::Domain
{
    void FGs2Domain::Initialize()
    {
        Account = MakeShared<Gs2::UE5::Account::Domain::FEzGs2Account>(Super->Account, Connection);
        Auth = MakeShared<Gs2::UE5::Auth::Domain::FEzGs2Auth>(Super->Auth, Connection);
        Buff = MakeShared<Gs2::UE5::Buff::Domain::FEzGs2Buff>(Super->Buff, Connection);
        Chat = MakeShared<Gs2::UE5::Chat::Domain::FEzGs2Chat>(Super->Chat, Connection);
        Datastore = MakeShared<Gs2::UE5::Datastore::Domain::FEzGs2Datastore>(Super->Datastore, Connection);
        Dictionary = MakeShared<Gs2::UE5::Dictionary::Domain::FEzGs2Dictionary>(Super->Dictionary, Connection);
        Distributor = MakeShared<Gs2::UE5::Distributor::Domain::FEzGs2Distributor>(Super->Distributor, Connection);
        Enchant = MakeShared<Gs2::UE5::Enchant::Domain::FEzGs2Enchant>(Super->Enchant, Connection);
        Enhance = MakeShared<Gs2::UE5::Enhance::Domain::FEzGs2Enhance>(Super->Enhance, Connection);
        Exchange = MakeShared<Gs2::UE5::Exchange::Domain::FEzGs2Exchange>(Super->Exchange, Connection);
        Experience = MakeShared<Gs2::UE5::Experience::Domain::FEzGs2Experience>(Super->Experience, Connection);
        Formation = MakeShared<Gs2::UE5::Formation::Domain::FEzGs2Formation>(Super->Formation, Connection);
        Friend = MakeShared<Gs2::UE5::Friend::Domain::FEzGs2Friend>(Super->Friend, Connection);
        Gateway = MakeShared<Gs2::UE5::Gateway::Domain::FEzGs2Gateway>(Super->Gateway, Connection);
        Grade = MakeShared<Gs2::UE5::Grade::Domain::FEzGs2Grade>(Super->Grade, Connection);
        Guild = MakeShared<Gs2::UE5::Guild::Domain::FEzGs2Guild>(Super->Guild, Connection);
        Inbox = MakeShared<Gs2::UE5::Inbox::Domain::FEzGs2Inbox>(Super->Inbox, Connection);
        Idle = MakeShared<Gs2::UE5::Idle::Domain::FEzGs2Idle>(Super->Idle, Connection);
        Inventory = MakeShared<Gs2::UE5::Inventory::Domain::FEzGs2Inventory>(Super->Inventory, Connection);
        JobQueue = MakeShared<Gs2::UE5::JobQueue::Domain::FEzGs2JobQueue>(Super->JobQueue, Connection);
        Limit = MakeShared<Gs2::UE5::Limit::Domain::FEzGs2Limit>(Super->Limit, Connection);
        LoginReward = MakeShared<Gs2::UE5::LoginReward::Domain::FEzGs2LoginReward>(Super->LoginReward, Connection);
        Lottery = MakeShared<Gs2::UE5::Lottery::Domain::FEzGs2Lottery>(Super->Lottery, Connection);
        Matchmaking = MakeShared<Gs2::UE5::Matchmaking::Domain::FEzGs2Matchmaking>(Super->Matchmaking, Connection);
        MegaField = MakeShared<Gs2::UE5::MegaField::Domain::FEzGs2MegaField>(Super->MegaField, Connection);
        Mission = MakeShared<Gs2::UE5::Mission::Domain::FEzGs2Mission>(Super->Mission, Connection);
        Money = MakeShared<Gs2::UE5::Money::Domain::FEzGs2Money>(Super->Money, Connection);
        Money2 = MakeShared<Gs2::UE5::Money2::Domain::FEzGs2Money2>(Super->Money2, Connection);
        News = MakeShared<Gs2::UE5::News::Domain::FEzGs2News>(Super->News, Connection);
        Quest = MakeShared<Gs2::UE5::Quest::Domain::FEzGs2Quest>(Super->Quest, Connection);
        Ranking = MakeShared<Gs2::UE5::Ranking::Domain::FEzGs2Ranking>(Super->Ranking, Connection);
        Ranking2 = MakeShared<Gs2::UE5::Ranking2::Domain::FEzGs2Ranking2>(Super->Ranking2, Connection);
        Realtime = MakeShared<Gs2::UE5::Realtime::Domain::FEzGs2Realtime>(Super->Realtime, Connection);
        Schedule = MakeShared<Gs2::UE5::Schedule::Domain::FEzGs2Schedule>(Super->Schedule, Connection);
        SeasonRating = MakeShared<Gs2::UE5::SeasonRating::Domain::FEzGs2SeasonRating>(Super->SeasonRating, Connection);
        SerialKey = MakeShared<Gs2::UE5::SerialKey::Domain::FEzGs2SerialKey>(Super->SerialKey, Connection);
        Showcase = MakeShared<Gs2::UE5::Showcase::Domain::FEzGs2Showcase>(Super->Showcase, Connection);
        SkillTree = MakeShared<Gs2::UE5::SkillTree::Domain::FEzGs2SkillTree>(Super->SkillTree, Connection);
        Stamina = MakeShared<Gs2::UE5::Stamina::Domain::FEzGs2Stamina>(Super->Stamina, Connection);
        StateMachine = MakeShared<Gs2::UE5::StateMachine::Domain::FEzGs2StateMachine>(Super->StateMachine, Connection);
        Version = MakeShared<Gs2::UE5::Version::Domain::FEzGs2Version>(Super->Version, Connection);
    }

    FGs2Domain::FGs2Domain(
        Util::FGs2ConnectionPtr Connection,
        FString DistributorNamespaceName
    ): Connection(Connection)
    {
        Super = MakeShared<Gs2::Core::Domain::FGs2>(
            Connection->RestSession(),
            Connection->WebSocketSession(),
            DistributorNamespaceName
        );
        Super->Initialize();

        this->Initialize();
    }
    
    FGs2Domain::FGs2Domain(
        FGs2Domain& From
    ):
        Connection(From.Connection),
        Super(From.Super),
        Account(From.Account),
        AdReward(From.AdReward),
        Auth(From.Auth),
        Buff(From.Buff),
        Chat(From.Chat),
        Datastore(From.Datastore),
        Dictionary(From.Dictionary),
        Distributor(From.Distributor),
        Enchant(From.Enchant),
        Enhance(From.Enhance),
        Exchange(From.Exchange),
        Experience(From.Experience),
        Formation(From.Formation),
        Friend(From.Friend),
        Gateway(From.Gateway),
        Grade(From.Grade),
        Guild(From.Guild),
        Idle(From.Idle),
        Inbox(From.Inbox),
        Inventory(From.Inventory),
        JobQueue(From.JobQueue),
        Limit(From.Limit),
        LoginReward(From.LoginReward),
        Lottery(From.Lottery),
        Matchmaking(From.Matchmaking),
        MegaField(From.MegaField),
        Mission(From.Mission),
        Money(From.Money),
        Money2(From.Money2),
        News(From.News),
        Quest(From.Quest),
        Ranking(From.Ranking),
        Ranking2(From.Ranking2),
        Realtime(From.Realtime),
        Schedule(From.Schedule),
        SeasonRating(From.SeasonRating),
        SerialKey(From.SerialKey),
        Showcase(From.Showcase),
        SkillTree(From.SkillTree),
        Stamina(From.Stamina),
        StateMachine(From.StateMachine),
        Version(From.Version)
    {
    }

    FGs2Domain::FGs2Domain(
        Gs2::Core::Domain::FGs2Ptr Gs2
    ): Connection(
        MakeShared<Util::FGs2Connection>(
            Gs2->RestSession->Credential(),
            Gs2->RestSession->Region()
        )
    )
    {
        Super = Gs2;

        this->Initialize();
    }

    FGs2Domain::FLoginTask::FLoginTask(
        const TSharedPtr<FGs2Domain> Self,
        const TSharedPtr<Util::IAuthenticator> Authenticator,
        const FString UserId,
        const FString Password
    ):
        Self(Self),
        Authenticator(Authenticator),
        UserId(UserId),
        Password(Password)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2Domain::FLoginTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Util::FGameSession>> Result
    )
    {
        auto GameSession = MakeShared<Gs2::UE5::Util::FGameSession>(
            Authenticator,
            Self->Connection,
            UserId,
            Password
        );
        auto Future = GameSession->Refresh();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        *Result = GameSession;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2Domain::FLoginTask>> FGs2Domain::Login(
        const TSharedPtr<Util::IAuthenticator> Authenticator,
        const FString UserId,
        const FString Password
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FLoginTask>>(
            AsShared(),
            Authenticator,
            UserId,
            Password
        );
    }

    FGs2Domain::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2Domain> Self,
        const Gs2::UE5::Util::FGameSessionPtr GameSession
    ): Self(Self), GameSession(GameSession)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2Domain::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<void>> Result
    )
    {
        const auto Future = Self->Super->Dispatch(GameSession->AccessToken());
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2Domain::FDispatchTask>> FGs2Domain::Dispatch(
        Gs2::UE5::Util::FGameSessionPtr GameSession
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDispatchTask>>(AsShared(), GameSession);
    }

    FGs2Domain::FDisconnectTask::FDisconnectTask(
        const TSharedPtr<FGs2Domain> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2Domain::FDisconnectTask::Action(TSharedPtr<TSharedPtr<void>> Result)
    {
        const auto Future = Self->Connection->Disconnect();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2Domain::FDisconnectTask>> FGs2Domain::Disconnect()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDisconnectTask>>(AsShared());
    }
}
