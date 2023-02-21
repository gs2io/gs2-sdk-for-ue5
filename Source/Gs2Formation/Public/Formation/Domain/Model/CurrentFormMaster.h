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
#include "Formation/Gs2Formation.h"
#include "Formation/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Formation/Domain/Iterator/DescribeFormModelsIterator.h"
#include "Formation/Domain/Iterator/DescribeFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsByUserIdIterator.h"

namespace Gs2::Formation::Domain::Model
{
    class FNamespaceDomain;
    class FFormModelDomain;
    class FFormModelMasterDomain;
    class FMoldModelDomain;
    class FMoldModelMasterDomain;
    class FCurrentFormMasterDomain;
    class FMoldDomain;
    class FMoldAccessTokenDomain;
    class FFormDomain;
    class FFormAccessTokenDomain;
    class FPropertyFormDomain;
    class FPropertyFormAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2FORMATION_API FCurrentFormMasterDomain:
        public TSharedFromThis<FCurrentFormMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentFormMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentFormMasterDomain(
            const FCurrentFormMasterDomain& From
        );

        class GS2FORMATION_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentFormMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentFormMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FCurrentFormMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentFormMasterDomain> Self;
            const Request::FGetCurrentFormMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentFormMasterDomain> Self,
                const Request::FGetCurrentFormMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FCurrentFormMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentFormMasterRequestPtr Request
        );

        class GS2FORMATION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentFormMasterDomain> Self;
            const Request::FUpdateCurrentFormMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentFormMasterDomain> Self,
                const Request::FUpdateCurrentFormMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentFormMasterRequestPtr Request
        );

        class GS2FORMATION_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentFormMasterDomain> Self;
            const Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentFormMasterDomain> Self,
                const Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FCurrentFormMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentFormMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentFormMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FCurrentFormMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentFormMasterDomain> FCurrentFormMasterDomainPtr;
}
