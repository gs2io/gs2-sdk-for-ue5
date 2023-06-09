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

#pragma once

#include "CoreMinimal.h"
#include "Idle/Domain/Model/UserAccessToken.h"
#include "Idle/Model/Gs2IdleEzCategoryModel.h"
#include "Idle/Model/Gs2IdleEzStatus.h"
#include "Idle/Model/Gs2IdleEzConfig.h"
#include "Idle/Model/Gs2IdleEzAcquireAction.h"
#include "Gs2IdleEzStatusGameSessionDomain.h"
#include "Idle/Domain/Iterator/Gs2IdleEzDescribeStatusesIterator.h"
#include "Gs2IdleEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Idle::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Idle::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Idle::Domain::Iterator::FEzDescribeStatusesIteratorPtr Statuses(
            const TOptional<FString> CategoryName = TOptional<FString>()
        ) const;

        Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomainPtr Status(
            const FString CategoryName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
