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

#include "Experience/Domain/Model/Gs2ExperienceEzUserGameSessionDomain.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
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
        Gs2::Experience::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Experience::Domain::Iterator::FEzDescribeStatusesIteratorPtr FEzUserGameSessionDomain::Statuses(
          const TOptional<FString> ExperienceName
    ) const
    {
        return MakeShared<Gs2::UE5::Experience::Domain::Iterator::FEzDescribeStatusesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            ExperienceName
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

    Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomainPtr FEzUserGameSessionDomain::Status(
        const FString ExperienceName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomain>(
            Domain->Status(
                ExperienceName,
                PropertyId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
