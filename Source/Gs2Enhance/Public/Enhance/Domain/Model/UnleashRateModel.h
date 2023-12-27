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

    class GS2ENHANCE_API FUnleashRateModelDomain:
        public TSharedFromThis<FUnleashRateModelDomain>
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

        FUnleashRateModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RateName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUnleashRateModelDomain(
            const FUnleashRateModelDomain& From
        );

        class GS2ENHANCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FUnleashRateModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FUnleashRateModelDomain> Self;
            const Request::FGetUnleashRateModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FUnleashRateModelDomain>& Self,
                const Request::FGetUnleashRateModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetUnleashRateModelRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FUnleashRateModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FUnleashRateModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FUnleashRateModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enhance::Model::FUnleashRateModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FUnleashRateModelDomain> FUnleashRateModelDomainPtr;
}
