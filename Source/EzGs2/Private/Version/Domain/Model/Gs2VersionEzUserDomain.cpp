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

#include "Version/Domain/Model/Gs2VersionEzUserDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzUserDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzUserDomain::Signature() const
    {
        return Domain->Signature;
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
        Gs2::Version::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Version::Domain::Model::FEzAcceptVersionDomainPtr FEzUserDomain::AcceptVersion(
        const FString VersionName
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionDomain>(
            Domain->AcceptVersion(
                VersionName
            ),
            ProfileValue
        );
    }
}
