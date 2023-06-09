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

#include "Idle/Domain/Model/Gs2IdleEzUserGameSessionDomain.h"

namespace Gs2::UE5::Idle::Domain::Model
{

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
        Gs2::Idle::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Idle::Domain::Iterator::FEzDescribeStatusesIteratorPtr FEzUserGameSessionDomain::Statuses(
          const TOptional<FString> CategoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Idle::Domain::Iterator::FEzDescribeStatusesIterator>(
            Domain->Statuses(
                CategoryName
            )
        );
    }

    Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomainPtr FEzUserGameSessionDomain::Status(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomain>(
            Domain->Status(
                CategoryName
            ),
            ProfileValue
        );
    }
}
