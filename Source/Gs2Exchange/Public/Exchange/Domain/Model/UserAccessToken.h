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
#include "Exchange/Gs2Exchange.h"
#include "Exchange/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Exchange::Domain
{
    class FGs2ExchangeDomain;
    typedef TSharedPtr<FGs2ExchangeDomain> FGs2ExchangeDomainPtr;
}

namespace Gs2::Exchange::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FIncrementalRateModelDomain;
    class FIncrementalRateModelMasterDomain;
    class FExchangeDomain;
    class FExchangeAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FAwaitDomain;
    class FAwaitAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2EXCHANGE_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Exchange::Domain::FGs2ExchangeDomainPtr Service;
        const Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<int64> UnlockAt;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<int64> GetUnlockAt() const
        {
            return UnlockAt;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain> Exchange(
        );

        Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIteratorPtr Awaits(
            const TOptional<FString> RateName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAwaits(
            TFunction<void()> Callback
        );

        void UnsubscribeAwaits(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain> Await(
            const FString AwaitName
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

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
