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

    class GS2SERIALKEY_API FSerialKeyAccessTokenDomain:
        public TSharedFromThis<FSerialKeyAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SerialKey::Domain::FGs2SerialKeyDomainPtr Service;
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> SerialKeyCode;
    private:

        FString ParentKey;

    public:

        FSerialKeyAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> SerialKeyCode
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSerialKeyAccessTokenDomain(
            const FSerialKeyAccessTokenDomain& From
        );

        class GS2SERIALKEY_API FUseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyAccessTokenDomain>,
            public TSharedFromThis<FUseTask>
        {
            const TSharedPtr<FSerialKeyAccessTokenDomain> Self;
            const Request::FUseRequestPtr Request;
        public:
            explicit FUseTask(
                const TSharedPtr<FSerialKeyAccessTokenDomain>& Self,
                const Request::FUseRequestPtr Request
            );

            FUseTask(
                const FUseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyAccessTokenDomain>> Result
            ) override;
        };
        friend FUseTask;

        TSharedPtr<FAsyncTask<FUseTask>> Use(
            Request::FUseRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> SerialKeyCode,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SerialKeyCode
        );

        class GS2SERIALKEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FSerialKey>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSerialKeyAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSerialKeyAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSerialKeyAccessTokenDomain> FSerialKeyAccessTokenDomainPtr;
}
