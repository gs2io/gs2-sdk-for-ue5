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
#include "SerialKey/Domain/Iterator/DescribeNamespacesIterator.h"
#include "SerialKey/Domain/Iterator/DescribeIssueJobsIterator.h"
#include "SerialKey/Domain/Iterator/DescribeSerialKeysIterator.h"
#include "SerialKey/Domain/Iterator/DescribeCampaignModelsIterator.h"
#include "SerialKey/Domain/Iterator/DescribeCampaignModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::SerialKey::Domain
{
    class FGs2SerialKeyDomain;
    typedef TSharedPtr<FGs2SerialKeyDomain> FGs2SerialKeyDomainPtr;
}

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

    class GS2SERIALKEY_API FIssueJobDomain:
        public TSharedFromThis<FIssueJobDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SerialKey::Domain::FGs2SerialKeyDomainPtr Service;
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TSharedPtr<TArray<FString>> SerialCodes;
        TSharedPtr<TArray<FString>> GetSerialCodes() const
        {
            return SerialCodes;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> CampaignModelName;
        TOptional<FString> IssueJobName;
    private:

        FString ParentKey;

    public:

        FIssueJobDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CampaignModelName,
            const TOptional<FString> IssueJobName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FIssueJobDomain(
            const FIssueJobDomain& From
        );

        class GS2SERIALKEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FIssueJob>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FIssueJobDomain> Self;
            const Request::FGetIssueJobRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FIssueJobDomain>& Self,
                const Request::FGetIssueJobRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FIssueJob>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetIssueJobRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> CampaignModelName,
            TOptional<FString> IssueJobName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> IssueJobName
        );

        class GS2SERIALKEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FIssueJob>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FIssueJobDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FIssueJobDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FIssueJob>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SerialKey::Model::FIssueJobPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FIssueJobDomain> FIssueJobDomainPtr;
}
