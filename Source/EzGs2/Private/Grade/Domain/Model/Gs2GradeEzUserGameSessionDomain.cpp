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

#include "Grade/Domain/Model/Gs2GradeEzUserGameSessionDomain.h"

namespace Gs2::UE5::Grade::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::ExperienceNamespaceName() const
    {
        return Domain->ExperienceNamespaceName;
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
        Gs2::Grade::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Grade::Domain::Iterator::FEzDescribeStatusesIteratorPtr FEzUserGameSessionDomain::Statuses(
        const TOptional<FString> GradeName
    ) const
    {
        return MakeShared<Gs2::UE5::Grade::Domain::Iterator::FEzDescribeStatusesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            GradeName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeStatuses(TFunction<void()> Callback)
    {
        return Domain->SubscribeStatuses(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeStatuses(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeStatuses(
            CallbackId
        );
    }

    Gs2::UE5::Grade::Domain::Model::FEzStatusGameSessionDomainPtr FEzUserGameSessionDomain::Status(
        const FString GradeName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Grade::Domain::Model::FEzStatusGameSessionDomain>(
            Domain->Status(
                GradeName,
                PropertyId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
