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

    class GS2LIMIT_API FLimitModelMasterDomain:
        public TSharedFromThis<FLimitModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Limit::Domain::FGs2LimitDomainPtr Service;
        const Gs2::Limit::FGs2LimitRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> LimitName;
    private:

        FString ParentKey;

    public:

        FLimitModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Limit::Domain::FGs2LimitDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> LimitName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FLimitModelMasterDomain(
            const FLimitModelMasterDomain& From
        );

        class GS2LIMIT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FLimitModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FLimitModelMasterDomain> Self;
            const Request::FGetLimitModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FLimitModelMasterDomain>& Self,
                const Request::FGetLimitModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetLimitModelMasterRequestPtr Request
        );

        class GS2LIMIT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FLimitModelMasterDomain> Self;
            const Request::FUpdateLimitModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FLimitModelMasterDomain>& Self,
                const Request::FUpdateLimitModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateLimitModelMasterRequestPtr Request
        );

        class GS2LIMIT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FLimitModelMasterDomain> Self;
            const Request::FDeleteLimitModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FLimitModelMasterDomain>& Self,
                const Request::FDeleteLimitModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteLimitModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> LimitName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> LimitName
        );

        class GS2LIMIT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FLimitModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FLimitModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FLimitModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Limit::Model::FLimitModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FLimitModelMasterDomain> FLimitModelMasterDomainPtr;
}
