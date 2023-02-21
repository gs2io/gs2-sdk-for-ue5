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
#include "Limit/Gs2Limit.h"
#include "Limit/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelMastersIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"

namespace Gs2::Limit::Domain::Model
{
    class FNamespaceDomain;
    class FCounterDomain;
    class FCounterAccessTokenDomain;
    class FLimitModelMasterDomain;
    class FCurrentLimitMasterDomain;
    class FLimitModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LIMIT_API FCurrentLimitMasterDomain:
        public TSharedFromThis<FCurrentLimitMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Limit::FGs2LimitRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentLimitMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentLimitMasterDomain(
            const FCurrentLimitMasterDomain& From
        );

        class GS2LIMIT_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentLimitMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentLimitMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2LIMIT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FCurrentLimitMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentLimitMasterDomain> Self;
            const Request::FGetCurrentLimitMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentLimitMasterDomain> Self,
                const Request::FGetCurrentLimitMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentLimitMasterRequestPtr Request
        );

        class GS2LIMIT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentLimitMasterDomain> Self;
            const Request::FUpdateCurrentLimitMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentLimitMasterDomain> Self,
                const Request::FUpdateCurrentLimitMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentLimitMasterRequestPtr Request
        );

        class GS2LIMIT_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentLimitMasterDomain> Self;
            const Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentLimitMasterDomain> Self,
                const Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCurrentLimitMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2LIMIT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Model::FCurrentLimitMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentLimitMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentLimitMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCurrentLimitMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentLimitMasterDomain> FCurrentLimitMasterDomainPtr;
}
