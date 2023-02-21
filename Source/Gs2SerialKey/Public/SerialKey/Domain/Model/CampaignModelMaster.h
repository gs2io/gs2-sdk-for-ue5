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

    class GS2SERIALKEY_API FCampaignModelMasterDomain:
        public TSharedFromThis<FCampaignModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> CampaignModelName;
    private:

        FString ParentKey;

    public:

        FCampaignModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CampaignModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCampaignModelMasterDomain(
            const FCampaignModelMasterDomain& From
        );

        class GS2SERIALKEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FCampaignModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCampaignModelMasterDomain> Self;
            const Request::FGetCampaignModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCampaignModelMasterDomain> Self,
                const Request::FGetCampaignModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCampaignModelMasterRequestPtr Request
        );

        class GS2SERIALKEY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCampaignModelMasterDomain> Self;
            const Request::FUpdateCampaignModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCampaignModelMasterDomain> Self,
                const Request::FUpdateCampaignModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCampaignModelMasterRequestPtr Request
        );

        class GS2SERIALKEY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FCampaignModelMasterDomain> Self;
            const Request::FDeleteCampaignModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FCampaignModelMasterDomain> Self,
                const Request::FDeleteCampaignModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteCampaignModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> CampaignModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CampaignModelName
        );

        class GS2SERIALKEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FCampaignModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCampaignModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCampaignModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCampaignModelMasterDomain> FCampaignModelMasterDomainPtr;
}
