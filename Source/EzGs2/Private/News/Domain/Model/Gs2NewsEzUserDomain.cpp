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

#include "News/Domain/Model/Gs2NewsEzUserDomain.h"

namespace Gs2::UE5::News::Domain::Model
{

    TOptional<FString> FEzUserDomain::ContentHash() const
    {
        return Domain->ContentHash;
    }

    TOptional<FString> FEzUserDomain::TemplateHash() const
    {
        return Domain->TemplateHash;
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
        Gs2::News::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::News::Domain::Model::FEzNewsDomainPtr FEzUserDomain::News(
    ) const
    {
        return MakeShared<Gs2::UE5::News::Domain::Model::FEzNewsDomain>(
            Domain->News(
            ),
            ProfileValue
        );
    }
}
