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

#include "Schedule/Domain/Model/Gs2ScheduleEzUserDomain.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Schedule::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Schedule::Domain::Model::FEzTriggerDomainPtr FEzUserDomain::Trigger(
        const FString TriggerName
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Model::FEzTriggerDomain>(
            Domain->Trigger(
                TriggerName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Schedule::Domain::Model::FEzEventDomainPtr FEzUserDomain::Event(
        const FString EventName
    ) const
    {
        return MakeShared<Gs2::UE5::Schedule::Domain::Model::FEzEventDomain>(
            Domain->Event(
                EventName
            ),
            ConnectionValue
        );
    }
}
