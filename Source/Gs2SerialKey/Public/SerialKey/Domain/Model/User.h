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

    class GS2SERIALKEY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2SERIALKEY_API FDownloadSerialCodesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FUserDomain>,
            public TSharedFromThis<FDownloadSerialCodesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDownloadSerialCodesRequestPtr Request;
        public:
            explicit FDownloadSerialCodesTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FDownloadSerialCodesRequestPtr Request
            );

            FDownloadSerialCodesTask(
                const FDownloadSerialCodesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FDownloadSerialCodesTask;

        TSharedPtr<FAsyncTask<FDownloadSerialCodesTask>> DownloadSerialCodes(
            Request::FDownloadSerialCodesRequestPtr Request
        );

        class GS2SERIALKEY_API FGetSerialKeyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FSerialKey>,
            public TSharedFromThis<FGetSerialKeyTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FGetSerialKeyRequestPtr Request;
        public:
            explicit FGetSerialKeyTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FGetSerialKeyRequestPtr Request
            );

            FGetSerialKeyTask(
                const FGetSerialKeyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
            ) override;
        };
        friend FGetSerialKeyTask;

        TSharedPtr<FAsyncTask<FGetSerialKeyTask>> GetSerialKey(
            Request::FGetSerialKeyRequestPtr Request
        );

        class GS2SERIALKEY_API FRevertUseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>,
            public TSharedFromThis<FRevertUseTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRevertUseByUserIdRequestPtr Request;
        public:
            explicit FRevertUseTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FRevertUseByUserIdRequestPtr Request
            );

            FRevertUseTask(
                const FRevertUseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
            ) override;
        };
        friend FRevertUseTask;

        TSharedPtr<FAsyncTask<FRevertUseTask>> RevertUse(
            Request::FRevertUseByUserIdRequestPtr Request
        );

        Gs2::SerialKey::Domain::Iterator::FDescribeSerialKeysIteratorPtr SerialKeys(
            const FString CampaignModelName,
            const TOptional<FString> IssueJobName
        ) const;

        TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain> SerialKey(
            const FString SerialKeyCode
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
