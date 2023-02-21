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
#include "Lock/Gs2Lock.h"
#include "Lock/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesIterator.h"
#include "Lock/Domain/Iterator/DescribeMutexesByUserIdIterator.h"

namespace Gs2::Lock::Domain::Model
{
    class FNamespaceDomain;
    class FMutexDomain;
    class FMutexAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LOCK_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lock::FGs2LockRestClientPtr Client;

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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Lock::Domain::Iterator::FDescribeMutexesByUserIdIteratorPtr Mutexes(
        ) const;

        TSharedPtr<Gs2::Lock::Domain::Model::FMutexDomain> Mutex(
            const FString PropertyId
        ) const;

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
