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
#include "SerialKey/Gs2SerialKey.h"
#include "SerialKey/Domain/Iterator/DescribeNamespacesIterator.h"
#include "SerialKey/Domain/Iterator/DescribeIssueJobsIterator.h"
#include "SerialKey/Domain/Iterator/DescribeSerialKeysIterator.h"
#include "SerialKey/Domain/Iterator/DescribeCampaignModelsIterator.h"
#include "SerialKey/Domain/Iterator/DescribeCampaignModelMastersIterator.h"

namespace Gs2::SerialKey::Domain::Model
{
    class FNamespaceDomain;
    class FIssueJobDomain;
    class FSerialKeyDomain;
    class FSerialKeyAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FCampaignModelDomain;
    class FCampaignModelMasterDomain;
    class FCurrentCampaignMasterDomain;

    class GS2SERIALKEY_API FCurrentCampaignMasterDomain:
        public TSharedFromThis<FCurrentCampaignMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentCampaignMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentCampaignMasterDomain(
            const FCurrentCampaignMasterDomain& From
        );

        class GS2SERIALKEY_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentCampaignMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentCampaignMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2SERIALKEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FCurrentCampaignMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentCampaignMasterDomain> Self;
            const Request::FGetCurrentCampaignMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentCampaignMasterDomain> Self,
                const Request::FGetCurrentCampaignMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCurrentCampaignMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentCampaignMasterRequestPtr Request
        );

        class GS2SERIALKEY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentCampaignMasterDomain> Self;
            const Request::FUpdateCurrentCampaignMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentCampaignMasterDomain> Self,
                const Request::FUpdateCurrentCampaignMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentCampaignMasterRequestPtr Request
        );

        class GS2SERIALKEY_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentCampaignMasterDomain> Self;
            const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentCampaignMasterDomain> Self,
                const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCurrentCampaignMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SERIALKEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FCurrentCampaignMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentCampaignMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentCampaignMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCurrentCampaignMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentCampaignMasterDomain> FCurrentCampaignMasterDomainPtr;
}
