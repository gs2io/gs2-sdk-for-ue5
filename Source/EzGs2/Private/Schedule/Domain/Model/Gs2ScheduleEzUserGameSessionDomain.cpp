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

#include "Schedule/Domain/Model/Gs2ScheduleEzUserGameSessionDomain.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    TOptional<bool> FEzUserGameSessionDomain::InSchedule() const
    {
        return Domain->InSchedule;
    }

    TOptional<int64> FEzUserGameSessionDomain::ScheduleStartAt() const
    {
        return Domain->ScheduleStartAt;
    }

    TOptional<int64> FEzUserGameSessionDomain::ScheduleEndAt() const
    {
        return Domain->ScheduleEndAt;
    }

    TOptional<bool> FEzUserGameSessionDomain::IsGlobalSchedule() const
    {
        return Domain->IsGlobalSchedule;
    }

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Schedule::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeTriggersIteratorPtr FEzUserGameSessionDomain::Triggers(
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeTriggersIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeTriggers(TFunction<void()> Callback)
    {
        return Domain->SubscribeTriggers(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeTriggers(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeTriggers(
            CallbackId
        );
    }

    Gs2::UE5::Schedule::Domain::Model::FEzTriggerGameSessionDomainPtr FEzUserGameSessionDomain::Trigger(
        const FString TriggerName
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Model::FEzTriggerGameSessionDomain>(
            Domain->Trigger(
                TriggerName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeEventsIteratorPtr FEzUserGameSessionDomain::Events(
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeEventsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeEvents(TFunction<void()> Callback)
    {
        return Domain->SubscribeEvents(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeEvents(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeEvents(
            CallbackId
        );
    }

    Gs2::UE5::Schedule::Domain::Model::FEzEventGameSessionDomainPtr FEzUserGameSessionDomain::Event(
        const FString EventName
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Model::FEzEventGameSessionDomain>(
            Domain->Event(
                EventName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
