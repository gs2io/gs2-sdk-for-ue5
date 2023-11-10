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

namespace Gs2::Enchant::Domain
{
    class FGs2EnchantDomain;
    typedef TSharedPtr<FGs2EnchantDomain> FGs2EnchantDomainPtr;
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

    class GS2ENCHANT_API FBalanceParameterStatusAccessTokenDomain:
        public TSharedFromThis<FBalanceParameterStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enchant::Domain::FGs2EnchantDomainPtr Service;
        const Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> ParameterName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FBalanceParameterStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enchant::Domain::FGs2EnchantDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> ParameterName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBalanceParameterStatusAccessTokenDomain(
            const FBalanceParameterStatusAccessTokenDomain& From
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FBalanceParameterStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBalanceParameterStatusAccessTokenDomain> Self;
            const Request::FGetBalanceParameterStatusRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBalanceParameterStatusAccessTokenDomain>& Self,
                const Request::FGetBalanceParameterStatusRequestPtr Request
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
            Request::FGetBalanceParameterStatusRequestPtr Request
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
            const TSharedPtr<FBalanceParameterStatusAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBalanceParameterStatusAccessTokenDomain> Self
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

    typedef TSharedPtr<FBalanceParameterStatusAccessTokenDomain> FBalanceParameterStatusAccessTokenDomainPtr;
}
