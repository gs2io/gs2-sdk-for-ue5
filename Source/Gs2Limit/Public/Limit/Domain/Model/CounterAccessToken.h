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
#include "Limit/Gs2Limit.h"
#include "Limit/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelMastersIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"

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

    class GS2LIMIT_API FCounterAccessTokenDomain:
        public TSharedFromThis<FCounterAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Limit::FGs2LimitRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> LimitName;
        TOptional<FString> CounterName;
    private:

        FString ParentKey;

    public:

        FCounterAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> LimitName,
            const TOptional<FString> CounterName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCounterAccessTokenDomain(
            const FCounterAccessTokenDomain& From
        );

        class GS2LIMIT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FCounter>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCounterAccessTokenDomain> Self;
            const Request::FGetCounterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCounterAccessTokenDomain> Self,
                const Request::FGetCounterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCounterRequestPtr Request
        );

        class GS2LIMIT_API FCountUpTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>,
            public TSharedFromThis<FCountUpTask>
        {
            const TSharedPtr<FCounterAccessTokenDomain> Self;
            const Request::FCountUpRequestPtr Request;
        public:
            explicit FCountUpTask(
                const TSharedPtr<FCounterAccessTokenDomain> Self,
                const Request::FCountUpRequestPtr Request
            );

            FCountUpTask(
                const FCountUpTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>> Result
            ) override;
        };
        friend FCountUpTask;

        TSharedPtr<FAsyncTask<FCountUpTask>> CountUp(
            Request::FCountUpRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> LimitName,
            TOptional<FString> CounterName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> LimitName,
            TOptional<FString> CounterName
        );

        class GS2LIMIT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FCounter>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCounterAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCounterAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Limit::Model::FCounterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCounterAccessTokenDomain> FCounterAccessTokenDomainPtr;
}
