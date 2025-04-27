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
#include "Money2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByDateIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesByCurrencyIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesIterator.h"
#include "Money2/Domain/Iterator/DescribeUnusedBalancesIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Money2::Domain
{
    class FGs2Money2Domain;
    typedef TSharedPtr<FGs2Money2Domain> FGs2Money2DomainPtr;
}

namespace Gs2::Money2::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FWalletDomain;
    class FWalletAccessTokenDomain;
    class FEventDomain;
    class FEventAccessTokenDomain;
    class FSubscriptionStatusDomain;
    class FSubscriptionStatusAccessTokenDomain;
    class FRefundHistoryDomain;
    class FStoreContentModelDomain;
    class FStoreContentModelMasterDomain;
    class FStoreSubscriptionContentModelDomain;
    class FStoreSubscriptionContentModelMasterDomain;
    class FCurrentModelMasterDomain;
    class FDailyTransactionHistoryDomain;
    class FUnusedBalanceDomain;

    class GS2MONEY2_API FCurrentModelMasterDomain:
        public TSharedFromThis<FCurrentModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Money2::Domain::FGs2Money2DomainPtr Service;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Money2::Domain::FGs2Money2DomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentModelMasterDomain(
            const FCurrentModelMasterDomain& From
        );

        class GS2MONEY2_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2MONEY2_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FCurrentModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FGetCurrentModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FGetCurrentModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FCurrentModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentModelMasterRequestPtr Request
        );

        class GS2MONEY2_API FPreUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FPreUpdateTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request;
        public:
            explicit FPreUpdateTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FPreUpdateCurrentModelMasterRequestPtr Request
            );

            FPreUpdateTask(
                const FPreUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FPreUpdateTask;

        TSharedPtr<FAsyncTask<FPreUpdateTask>> PreUpdate(
            Request::FPreUpdateCurrentModelMasterRequestPtr Request
        );

        class GS2MONEY2_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FUpdateCurrentModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FUpdateCurrentModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentModelMasterRequestPtr Request
        );

        class GS2MONEY2_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2MONEY2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FCurrentModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FCurrentModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Money2::Model::FCurrentModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentModelMasterDomain> FCurrentModelMasterDomainPtr;
}
