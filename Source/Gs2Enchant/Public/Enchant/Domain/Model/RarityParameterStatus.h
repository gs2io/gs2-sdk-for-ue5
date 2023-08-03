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

    class GS2ENCHANT_API FRarityParameterStatusDomain:
        public TSharedFromThis<FRarityParameterStatusDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ParameterName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FRarityParameterStatusDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ParameterName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRarityParameterStatusDomain(
            const FRarityParameterStatusDomain& From
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FRarityParameterStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FGetRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FGetRarityParameterStatusByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRarityParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FReDrawTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>,
            public TSharedFromThis<FReDrawTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FReDrawTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
            );

            FReDrawTask(
                const FReDrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
            ) override;
        };
        friend FReDrawTask;

        TSharedPtr<FAsyncTask<FReDrawTask>> ReDraw(
            Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FAddTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>,
            public TSharedFromThis<FAddTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FAddRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FAddTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FAddRarityParameterStatusByUserIdRequestPtr Request
            );

            FAddTask(
                const FAddTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
            ) override;
        };
        friend FAddTask;

        TSharedPtr<FAsyncTask<FAddTask>> Add(
            Request::FAddRarityParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FSetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>,
            public TSharedFromThis<FSetTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
            const Request::FSetRarityParameterStatusByUserIdRequestPtr Request;
        public:
            explicit FSetTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self,
                const Request::FSetRarityParameterStatusByUserIdRequestPtr Request
            );

            FSetTask(
                const FSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
            ) override;
        };
        friend FSetTask;

        TSharedPtr<FAsyncTask<FSetTask>> Set(
            Request::FSetRarityParameterStatusByUserIdRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FRarityParameterStatus>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRarityParameterStatusDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRarityParameterStatusDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FRarityParameterStatusDomain> FRarityParameterStatusDomainPtr;
}
