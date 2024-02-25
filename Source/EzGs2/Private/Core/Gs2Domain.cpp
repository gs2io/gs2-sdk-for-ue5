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

namespace Gs2::UE5::Core::Domain
{
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

        Account = MakeShared<Gs2::UE5::Account::Domain::FEzGs2Account>(Super->Account, Connection);
        Auth = MakeShared<Gs2::UE5::Auth::Domain::FEzGs2Auth>(Super->Auth, Connection);
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
        News = MakeShared<Gs2::UE5::News::Domain::FEzGs2News>(Super->News, Connection);
        Quest = MakeShared<Gs2::UE5::Quest::Domain::FEzGs2Quest>(Super->Quest, Connection);
        Ranking = MakeShared<Gs2::UE5::Ranking::Domain::FEzGs2Ranking>(Super->Ranking, Connection);
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
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        const auto Future = Self->Super->Dispatch(GameSession->AccessToken()->ToModel());
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

    Gs2::Core::Model::FGs2ErrorPtr FGs2Domain::FDisconnectTask::Action(TSharedPtr<TSharedPtr<void*>> Result)
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
