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
#include "Enchant/Gs2Enchant.h"
#include "Enchant/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesByUserIdIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enchant::Domain::Model
{
    class FNamespaceDomain;
    class FBalanceParameterModelDomain;
    class FBalanceParameterModelMasterDomain;
    class FRarityParameterModelDomain;
    class FRarityParameterModelMasterDomain;
    class FCurrentParameterMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FBalanceParameterStatusDomain;
    class FBalanceParameterStatusAccessTokenDomain;
    class FRarityParameterStatusDomain;
    class FRarityParameterStatusAccessTokenDomain;

    class GS2ENCHANT_API FBalanceParameterModelMasterDomain:
        public TSharedFromThis<FBalanceParameterModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> ParameterName;
    private:

        FString ParentKey;

    public:

        FBalanceParameterModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ParameterName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBalanceParameterModelMasterDomain(
            const FBalanceParameterModelMasterDomain& From
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBalanceParameterModelMasterDomain> Self;
            const Request::FGetBalanceParameterModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBalanceParameterModelMasterDomain> Self,
                const Request::FGetBalanceParameterModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBalanceParameterModelMasterRequestPtr Request
        );

        class GS2ENCHANT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FBalanceParameterModelMasterDomain> Self;
            const Request::FUpdateBalanceParameterModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FBalanceParameterModelMasterDomain> Self,
                const Request::FUpdateBalanceParameterModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateBalanceParameterModelMasterRequestPtr Request
        );

        class GS2ENCHANT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FBalanceParameterModelMasterDomain> Self;
            const Request::FDeleteBalanceParameterModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FBalanceParameterModelMasterDomain> Self,
                const Request::FDeleteBalanceParameterModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteBalanceParameterModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> ParameterName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ParameterName
        );

        class GS2ENCHANT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBalanceParameterModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBalanceParameterModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enchant::Model::FBalanceParameterModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FBalanceParameterModelMasterDomain> FBalanceParameterModelMasterDomainPtr;
}
