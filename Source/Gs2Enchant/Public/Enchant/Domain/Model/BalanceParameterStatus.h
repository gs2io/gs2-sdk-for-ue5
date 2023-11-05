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

    class GS2ENCHANT_API FBalanceParameterStatusDomain:
        public TSharedFromThis<FBalanceParameterStatusDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ParameterName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FBalanceParameterStatusDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ParameterName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBalanceParameterStatusDomain(
            const FBalanceParameterStatusDomain& From
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBalanceParameterStatusDomain> Self;
            const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBalanceParameterStatusDomain> Self,
                const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBalanceParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FBalanceParameterStatusDomain> Self;
            const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FBalanceParameterStatusDomain> Self,
                const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FReDrawTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>,
            public TSharedFromThis<FReDrawTask>
        {
            const TSharedPtr<FBalanceParameterStatusDomain> Self;
            const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FReDrawTask(
                const TSharedPtr<FBalanceParameterStatusDomain> Self,
                const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request
            );

            FReDrawTask(
                const FReDrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>> Result
            ) override;
        };
        friend FReDrawTask;

        TSharedPtr<FAsyncTask<FReDrawTask>> ReDraw(
            Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FSetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>,
            public TSharedFromThis<FSetTask>
        {
            const TSharedPtr<FBalanceParameterStatusDomain> Self;
            const Request::FSetBalanceParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FSetTask(
                const TSharedPtr<FBalanceParameterStatusDomain> Self,
                const Request::FSetBalanceParameterStatusByUserIdRequestPtr Request
            );

            FSetTask(
                const FSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>> Result
            ) override;
        };
        friend FSetTask;

        TSharedPtr<FAsyncTask<FSetTask>> Set(
            Request::FSetBalanceParameterStatusByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> ParameterName,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ParameterName,
            TOptional<FString> PropertyId
        );

        class GS2ENCHANT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterStatus>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBalanceParameterStatusDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBalanceParameterStatusDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enchant::Model::FBalanceParameterStatusPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FBalanceParameterStatusDomain> FBalanceParameterStatusDomainPtr;
}
