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

    class GS2ENCHANT_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enchant::Domain::FGs2EnchantDomainPtr Service;
        const Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enchant::Domain::FGs2EnchantDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterStatusesIteratorPtr BalanceParameterStatuses(
            const TOptional<FString> ParameterName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBalanceParameterStatuses(
            TFunction<void()> Callback
            , const TOptional<FString> ParameterName = TOptional<FString>()
        );

        class FCollectBalanceParameterStatusesTask;

        Gs2::Core::Domain::CallbackID SubscribeBalanceParameterStatuses(
            TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName = TOptional<FString>()
        );

        void InvalidateBalanceParameterStatuses(const TOptional<FString> ParameterName = TOptional<FString>());

        class GS2ENCHANT_API FSubscribeBalanceParameterStatusesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeBalanceParameterStatusesWithInitialCallTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback;
        const TOptional<FString> QueryParameterName;
        public:
            FSubscribeBalanceParameterStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName);
            FSubscribeBalanceParameterStatusesWithInitialCallTask(const FSubscribeBalanceParameterStatusesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeBalanceParameterStatusesWithInitialCallTask>> SubscribeBalanceParameterStatusesWithInitialCall(
            TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName = TOptional<FString>()
        );
        void UnsubscribeBalanceParameterStatuses(

            Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> ParameterName = TOptional<FString>()
        );

        TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusAccessTokenDomain> BalanceParameterStatus(
            const FString ParameterName,
            const FString PropertyId
        );

        Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterStatusesIteratorPtr RarityParameterStatuses(
            const TOptional<FString> ParameterName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRarityParameterStatuses(
            TFunction<void()> Callback
            , const TOptional<FString> ParameterName = TOptional<FString>()
        );

        class FCollectRarityParameterStatusesTask;

        Gs2::Core::Domain::CallbackID SubscribeRarityParameterStatuses(
            TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName = TOptional<FString>()
        );

        void InvalidateRarityParameterStatuses(const TOptional<FString> ParameterName = TOptional<FString>());

        class GS2ENCHANT_API FSubscribeRarityParameterStatusesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeRarityParameterStatusesWithInitialCallTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback;
        const TOptional<FString> QueryParameterName;
        public:
            FSubscribeRarityParameterStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName);
            FSubscribeRarityParameterStatusesWithInitialCallTask(const FSubscribeRarityParameterStatusesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeRarityParameterStatusesWithInitialCallTask>> SubscribeRarityParameterStatusesWithInitialCall(
            TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName = TOptional<FString>()
        );
        void UnsubscribeRarityParameterStatuses(

            Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> ParameterName = TOptional<FString>()
        );

        TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusAccessTokenDomain> RarityParameterStatus(
            const FString ParameterName,
            const FString PropertyId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
