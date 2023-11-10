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
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    class FGs2DistributorDomain;
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}

namespace Gs2::Distributor::Domain::Model
{
    class FNamespaceDomain;
    class FDistributorModelMasterDomain;
    class FDistributorModelDomain;
    class FCurrentDistributorMasterDomain;
    class FDistributeDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStampSheetResultDomain;
    class FStampSheetResultAccessTokenDomain;

    class GS2DISTRIBUTOR_API FDistributeDomain:
        public TSharedFromThis<FDistributeDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> InboxNamespaceId;
        TOptional<FString> Result;
        TOptional<FString> ContextStack;
        TSharedPtr<TArray<FString>> TaskResults;
        TOptional<FString> SheetResult;
        TOptional<FString> GetInboxNamespaceId() const
        {
            return InboxNamespaceId;
        }
        TOptional<FString> GetResult() const
        {
            return Result;
        }
        TOptional<FString> GetContextStack() const
        {
            return ContextStack;
        }
        TSharedPtr<TArray<FString>> GetTaskResults() const
        {
            return TaskResults;
        }
        TOptional<FString> GetSheetResult() const
        {
            return SheetResult;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FDistributeDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDistributeDomain(
            const FDistributeDomain& From
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FDistributeDomain> FDistributeDomainPtr;
}
