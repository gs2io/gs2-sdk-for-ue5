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
#include "Idle/Gs2Idle.h"
#include "Idle/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelMastersIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Idle::Domain::Model
{
    class FNamespaceDomain;
    class FCategoryModelMasterDomain;
    class FCategoryModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FCurrentCategoryMasterDomain;

    class GS2IDLE_API FCurrentCategoryMasterDomain:
        public TSharedFromThis<FCurrentCategoryMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Idle::FGs2IdleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentCategoryMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentCategoryMasterDomain(
            const FCurrentCategoryMasterDomain& From
        );

        class GS2IDLE_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentCategoryMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentCategoryMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2IDLE_API FGetCurrentIdleMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>,
            public TSharedFromThis<FGetCurrentIdleMasterTask>
        {
            const TSharedPtr<FCurrentCategoryMasterDomain> Self;
            const Request::FGetCurrentIdleMasterRequestPtr Request;
        public:
            explicit FGetCurrentIdleMasterTask(
                const TSharedPtr<FCurrentCategoryMasterDomain> Self,
                const Request::FGetCurrentIdleMasterRequestPtr Request
            );

            FGetCurrentIdleMasterTask(
                const FGetCurrentIdleMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
            ) override;
        };
        friend FGetCurrentIdleMasterTask;

        TSharedPtr<FAsyncTask<FGetCurrentIdleMasterTask>> GetCurrentIdleMaster(
            Request::FGetCurrentIdleMasterRequestPtr Request
        );

        class GS2IDLE_API FUpdateCurrentIdleMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>,
            public TSharedFromThis<FUpdateCurrentIdleMasterTask>
        {
            const TSharedPtr<FCurrentCategoryMasterDomain> Self;
            const Request::FUpdateCurrentIdleMasterRequestPtr Request;
        public:
            explicit FUpdateCurrentIdleMasterTask(
                const TSharedPtr<FCurrentCategoryMasterDomain> Self,
                const Request::FUpdateCurrentIdleMasterRequestPtr Request
            );

            FUpdateCurrentIdleMasterTask(
                const FUpdateCurrentIdleMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
            ) override;
        };
        friend FUpdateCurrentIdleMasterTask;

        TSharedPtr<FAsyncTask<FUpdateCurrentIdleMasterTask>> UpdateCurrentIdleMaster(
            Request::FUpdateCurrentIdleMasterRequestPtr Request
        );

        class GS2IDLE_API FUpdateCurrentIdleMasterFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>,
            public TSharedFromThis<FUpdateCurrentIdleMasterFromGitHubTask>
        {
            const TSharedPtr<FCurrentCategoryMasterDomain> Self;
            const Request::FUpdateCurrentIdleMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateCurrentIdleMasterFromGitHubTask(
                const TSharedPtr<FCurrentCategoryMasterDomain> Self,
                const Request::FUpdateCurrentIdleMasterFromGitHubRequestPtr Request
            );

            FUpdateCurrentIdleMasterFromGitHubTask(
                const FUpdateCurrentIdleMasterFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCurrentCategoryMasterDomain>> Result
            ) override;
        };
        friend FUpdateCurrentIdleMasterFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateCurrentIdleMasterFromGitHubTask>> UpdateCurrentIdleMasterFromGitHub(
            Request::FUpdateCurrentIdleMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2IDLE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FCurrentCategoryMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentCategoryMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentCategoryMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCurrentCategoryMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentCategoryMasterDomain> FCurrentCategoryMasterDomainPtr;
}
