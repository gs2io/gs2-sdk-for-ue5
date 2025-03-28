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

    class GS2SERIALKEY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SerialKey::Domain::FGs2SerialKeyDomainPtr Service;
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

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
            const Core::Domain::FGs2Ptr& Gs2,
            const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
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
                const TSharedPtr<FUserDomain>& Self,
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

        class GS2SERIALKEY_API FIssueOnceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>,
            public TSharedFromThis<FIssueOnceTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FIssueOnceRequestPtr Request;
        public:
            explicit FIssueOnceTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FIssueOnceRequestPtr Request
            );

            FIssueOnceTask(
                const FIssueOnceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
            ) override;
        };
        friend FIssueOnceTask;

        TSharedPtr<FAsyncTask<FIssueOnceTask>> IssueOnce(
            Request::FIssueOnceRequestPtr Request
        );

        class GS2SERIALKEY_API FVerifyCodeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>,
            public TSharedFromThis<FVerifyCodeTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FVerifyCodeByUserIdRequestPtr Request;
        public:
            explicit FVerifyCodeTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FVerifyCodeByUserIdRequestPtr Request
            );

            FVerifyCodeTask(
                const FVerifyCodeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
            ) override;
        };
        friend FVerifyCodeTask;

        TSharedPtr<FAsyncTask<FVerifyCodeTask>> VerifyCode(
            Request::FVerifyCodeByUserIdRequestPtr Request
        );

        class GS2SERIALKEY_API FRevertUseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>,
            public TSharedFromThis<FRevertUseTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRevertUseByUserIdRequestPtr Request;
        public:
            explicit FRevertUseTask(
                const TSharedPtr<FUserDomain>& Self,
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
            const TOptional<FString> IssueJobName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSerialKeys(
            TFunction<void()> Callback
        );

        void UnsubscribeSerialKeys(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain> SerialKey(
            const FString SerialKeyCode
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

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
