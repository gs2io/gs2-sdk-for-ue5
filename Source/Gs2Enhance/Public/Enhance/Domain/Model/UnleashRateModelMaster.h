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
#include "Enhance/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelMastersIterator.h"
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enhance::Domain
{
    class FGs2EnhanceDomain;
    typedef TSharedPtr<FGs2EnhanceDomain> FGs2EnhanceDomainPtr;
}

namespace Gs2::Enhance::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FUnleashRateModelDomain;
    class FUnleashRateModelMasterDomain;
    class FEnhanceDomain;
    class FEnhanceAccessTokenDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2ENHANCE_API FUnleashRateModelMasterDomain:
        public TSharedFromThis<FUnleashRateModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enhance::Domain::FGs2EnhanceDomainPtr Service;
        const Gs2::Enhance::FGs2EnhanceRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RateName;
    private:

        FString ParentKey;

    public:

        FUnleashRateModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RateName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUnleashRateModelMasterDomain(
            const FUnleashRateModelMasterDomain& From
        );

        class GS2ENHANCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FUnleashRateModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FUnleashRateModelMasterDomain> Self;
            const Request::FGetUnleashRateModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
                const Request::FGetUnleashRateModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetUnleashRateModelMasterRequestPtr Request
        );

        class GS2ENHANCE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FUnleashRateModelMasterDomain> Self;
            const Request::FUpdateUnleashRateModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
                const Request::FUpdateUnleashRateModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateUnleashRateModelMasterRequestPtr Request
        );

        class GS2ENHANCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FUnleashRateModelMasterDomain> Self;
            const Request::FDeleteUnleashRateModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
                const Request::FDeleteUnleashRateModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteUnleashRateModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RateName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RateName
        );

        class GS2ENHANCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FUnleashRateModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FUnleashRateModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FUnleashRateModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enhance::Model::FUnleashRateModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FUnleashRateModelMasterDomain> FUnleashRateModelMasterDomainPtr;
}
