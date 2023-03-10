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

#include "Formation/Domain/Model/Gs2FormationEzUserDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzUserDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

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
        Gs2::Formation::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Formation::Domain::Model::FEzMoldDomainPtr FEzUserDomain::Mold(
        const FString MoldName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzMoldDomain>(
            Domain->Mold(
                MoldName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzPropertyFormDomainPtr FEzUserDomain::PropertyForm(
        const FString FormModelName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormDomain>(
            Domain->PropertyForm(
                FormModelName,
                PropertyId
            ),
            ProfileValue
        );
    }
}
