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

#include "Enhance/Domain/Model/Gs2EnhanceEzEnhanceDomain.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    TOptional<int64> FEzEnhanceDomain::AcquireExperience() const
    {
        return Domain->AcquireExperience;
    }

    TOptional<float> FEzEnhanceDomain::BonusRate() const
    {
        return Domain->BonusRate;
    }

    TOptional<FString> FEzEnhanceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzEnhanceDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzEnhanceDomain::FEzEnhanceDomain(
        Gs2::Enhance::Domain::Model::FEnhanceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }
}
