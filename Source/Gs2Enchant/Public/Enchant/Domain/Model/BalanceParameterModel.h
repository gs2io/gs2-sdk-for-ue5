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

    class GS2ENCHANT_API FBalanceParameterModelDomain:
        public TSharedFromThis<FBalanceParameterModelDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> ParameterName;
    private:

        FString ParentKey;

    public:

        FBalanceParameterModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ParameterName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBalanceParameterModelDomain(
            const FBalanceParameterModelDomain& From
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBalanceParameterModelDomain> Self;
            const Request::FGetBalanceParameterModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBalanceParameterModelDomain> Self,
                const Request::FGetBalanceParameterModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBalanceParameterModelRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBalanceParameterModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBalanceParameterModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FBalanceParameterModelDomain> FBalanceParameterModelDomainPtr;
}
