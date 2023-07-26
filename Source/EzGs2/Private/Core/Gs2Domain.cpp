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
#include "EzGs2/Public/Util/Profile.h"

namespace Gs2::UE5::Core::Domain
{
    FGs2Domain::FGs2Domain(
        TSharedPtr<Util::FProfile> Profile
    ): Profile(Profile)
    {
        Super = MakeShared<Gs2::Core::Domain::FGs2>(
            Profile->Gs2RestSession,
            Profile->Gs2WebSocketSession,
            Profile->DistributorNamespaceName
        );

        Account = MakeShared<Gs2::UE5::Account::Domain::FEzGs2Account>(Super->Account, Profile);
        Auth = MakeShared<Gs2::UE5::Auth::Domain::FEzGs2Auth>(Super->Auth, Profile);
        Chat = MakeShared<Gs2::UE5::Chat::Domain::FEzGs2Chat>(Super->Chat, Profile);
        Datastore = MakeShared<Gs2::UE5::Datastore::Domain::FEzGs2Datastore>(Super->Datastore, Profile);
        Dictionary = MakeShared<Gs2::UE5::Dictionary::Domain::FEzGs2Dictionary>(Super->Dictionary, Profile);
        Distributor = MakeShared<Gs2::UE5::Distributor::Domain::FEzGs2Distributor>(Super->Distributor, Profile);
        Enchant = MakeShared<Gs2::UE5::Enchant::Domain::FEzGs2Enchant>(Super->Enchant, Profile);
        Enhance = MakeShared<Gs2::UE5::Enhance::Domain::FEzGs2Enhance>(Super->Enhance, Profile);
        Exchange = MakeShared<Gs2::UE5::Exchange::Domain::FEzGs2Exchange>(Super->Exchange, Profile);
        Experience = MakeShared<Gs2::UE5::Experience::Domain::FEzGs2Experience>(Super->Experience, Profile);
        Formation = MakeShared<Gs2::UE5::Formation::Domain::FEzGs2Formation>(Super->Formation, Profile);
        Friend = MakeShared<Gs2::UE5::Friend::Domain::FEzGs2Friend>(Super->Friend, Profile);
        Gateway = MakeShared<Gs2::UE5::Gateway::Domain::FEzGs2Gateway>(Super->Gateway, Profile);
        Inbox = MakeShared<Gs2::UE5::Inbox::Domain::FEzGs2Inbox>(Super->Inbox, Profile);
        Idle = MakeShared<Gs2::UE5::Idle::Domain::FEzGs2Idle>(Super->Idle, Profile);
        Inventory = MakeShared<Gs2::UE5::Inventory::Domain::FEzGs2Inventory>(Super->Inventory, Profile);
        JobQueue = MakeShared<Gs2::UE5::JobQueue::Domain::FEzGs2JobQueue>(Super->JobQueue, Profile);
        Limit = MakeShared<Gs2::UE5::Limit::Domain::FEzGs2Limit>(Super->Limit, Profile);
        LoginReward = MakeShared<Gs2::UE5::LoginReward::Domain::FEzGs2LoginReward>(Super->LoginReward, Profile);
        Lottery = MakeShared<Gs2::UE5::Lottery::Domain::FEzGs2Lottery>(Super->Lottery, Profile);
        Matchmaking = MakeShared<Gs2::UE5::Matchmaking::Domain::FEzGs2Matchmaking>(Super->Matchmaking, Profile);
        MegaField = MakeShared<Gs2::UE5::MegaField::Domain::FEzGs2MegaField>(Super->MegaField, Profile);
        Mission = MakeShared<Gs2::UE5::Mission::Domain::FEzGs2Mission>(Super->Mission, Profile);
        Money = MakeShared<Gs2::UE5::Money::Domain::FEzGs2Money>(Super->Money, Profile);
        News = MakeShared<Gs2::UE5::News::Domain::FEzGs2News>(Super->News, Profile);
        Quest = MakeShared<Gs2::UE5::Quest::Domain::FEzGs2Quest>(Super->Quest, Profile);
        Ranking = MakeShared<Gs2::UE5::Ranking::Domain::FEzGs2Ranking>(Super->Ranking, Profile);
        Realtime = MakeShared<Gs2::UE5::Realtime::Domain::FEzGs2Realtime>(Super->Realtime, Profile);
        Schedule = MakeShared<Gs2::UE5::Schedule::Domain::FEzGs2Schedule>(Super->Schedule, Profile);
        SerialKey = MakeShared<Gs2::UE5::SerialKey::Domain::FEzGs2SerialKey>(Super->SerialKey, Profile);
        Showcase = MakeShared<Gs2::UE5::Showcase::Domain::FEzGs2Showcase>(Super->Showcase, Profile);
        Stamina = MakeShared<Gs2::UE5::Stamina::Domain::FEzGs2Stamina>(Super->Stamina, Profile);
        StateMachine = MakeShared<Gs2::UE5::StateMachine::Domain::FEzGs2StateMachine>(Super->StateMachine, Profile);
        Version = MakeShared<Gs2::UE5::Version::Domain::FEzGs2Version>(Super->Version, Profile);
    }

    FGs2Domain::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2Domain> Self,
        const Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2Domain::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        const auto Future = Self->Super->Dispatch(AccessToken->ToModel());
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2Domain::FDispatchTask>> FGs2Domain::Dispatch(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2Domain::FDispatchTask>>(AsShared(), AccessToken);
    }
}
