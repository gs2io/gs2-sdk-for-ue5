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
 *
 * deny overwrite
 */

#include "Lottery/Domain/Model/Gs2LotteryEzBoxGameSessionDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzBoxGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBoxGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzBoxGameSessionDomain::PrizeTableName() const
    {
        return Domain->PrizeTableName;
    }

    FEzBoxGameSessionDomain::FEzBoxGameSessionDomain(
        Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }
}
