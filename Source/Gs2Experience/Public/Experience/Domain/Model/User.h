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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Experience/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelsIterator.h"
#include "Experience/Domain/Iterator/DescribeThresholdMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Experience::Domain
{
    class FGs2ExperienceDomain;
    typedef TSharedPtr<FGs2ExperienceDomain> FGs2ExperienceDomainPtr;
}

namespace Gs2::Experience::Domain::Model
{
    class FNamespaceDomain;
    class FExperienceModelMasterDomain;
    class FExperienceModelDomain;
    class FThresholdMasterDomain;
    class FCurrentExperienceMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;

    class GS2EXPERIENCE_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Experience::Domain::FGs2ExperienceDomainPtr Service;
        const Gs2::Experience::FGs2ExperienceRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Experience::Domain::FGs2ExperienceDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Experience::Domain::Iterator::FDescribeStatusesByUserIdIteratorPtr Statuses(
            const TOptional<FString> ExperienceName = TOptional<FString>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(
            TFunction<void()> Callback
        );

        void UnsubscribeStatuses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain> Status(
            const FString ExperienceName,
            const FString PropertyId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
