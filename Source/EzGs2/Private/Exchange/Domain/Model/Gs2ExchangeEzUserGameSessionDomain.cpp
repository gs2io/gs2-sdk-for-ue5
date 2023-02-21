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

#include "Exchange/Domain/Model/Gs2ExchangeEzUserGameSessionDomain.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<int64> FEzUserGameSessionDomain::UnlockAt() const
    {
        return Domain->UnlockAt;
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
        Gs2::Exchange::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomainPtr FEzUserGameSessionDomain::Exchange(
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>(
            Domain->Exchange(
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeAwaitsIteratorPtr FEzUserGameSessionDomain::Awaits(
          const TOptional<FString> RateName
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeAwaitsIterator>(
            Domain->Awaits(
                RateName
            )
        );
    }

    Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomainPtr FEzUserGameSessionDomain::Await(
        const FString AwaitName
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>(
            Domain->Await(
                AwaitName
            ),
            ProfileValue
        );
    }
}
