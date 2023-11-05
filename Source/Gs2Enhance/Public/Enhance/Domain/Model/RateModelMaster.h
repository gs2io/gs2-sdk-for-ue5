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
#include "Enhance/Gs2Enhance.h"
#include "Enhance/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enhance::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FEnhanceDomain;
    class FEnhanceAccessTokenDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2ENHANCE_API FRateModelMasterDomain:
        public TSharedFromThis<FRateModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Enhance::FGs2EnhanceRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RateName;
    private:

        FString ParentKey;

    public:

        FRateModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RateName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRateModelMasterDomain(
            const FRateModelMasterDomain& From
        );

        class GS2ENHANCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FRateModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRateModelMasterDomain> Self;
            const Request::FGetRateModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRateModelMasterDomain> Self,
                const Request::FGetRateModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FRateModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRateModelMasterRequestPtr Request
        );

        class GS2ENHANCE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FRateModelMasterDomain> Self;
            const Request::FUpdateRateModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FRateModelMasterDomain> Self,
                const Request::FUpdateRateModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateRateModelMasterRequestPtr Request
        );

        class GS2ENHANCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRateModelMasterDomain> Self;
            const Request::FDeleteRateModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRateModelMasterDomain> Self,
                const Request::FDeleteRateModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRateModelMasterRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FRateModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRateModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRateModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FRateModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enhance::Model::FRateModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FRateModelMasterDomain> FRateModelMasterDomainPtr;
}
