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
#include "Limit/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelMastersIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Limit::Domain
{
    class FGs2LimitDomain;
    typedef TSharedPtr<FGs2LimitDomain> FGs2LimitDomainPtr;
}

namespace Gs2::Limit::Domain::Model
{
    class FNamespaceDomain;
    class FCounterDomain;
    class FCounterAccessTokenDomain;
    class FLimitModelMasterDomain;
    class FCurrentLimitMasterDomain;
    class FLimitModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LIMIT_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Limit::Domain::FGs2LimitDomainPtr Service;
        const Gs2::Limit::FGs2LimitRestClientPtr Client;

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
            const Limit::Domain::FGs2LimitDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Limit::Domain::Iterator::FDescribeCountersByUserIdIteratorPtr Counters(
            const TOptional<FString> LimitName = TOptional<FString>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCounters(
            TFunction<void()> Callback
        );

        void UnsubscribeCounters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain> Counter(
            const FString LimitName,
            const FString CounterName
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
