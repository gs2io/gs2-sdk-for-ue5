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
 *
 * deny overwrite
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

    class GS2SERIALKEY_API FSerialKeyDomain:
        public TSharedFromThis<FSerialKeyDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> SerialKeyCode;
    private:

        FString ParentKey;

    public:

        FSerialKeyDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> SerialKeyCode
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSerialKeyDomain(
            const FSerialKeyDomain& From
        );

        class GS2SERIALKEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FSerialKey>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSerialKeyDomain> Self;
            const Request::FGetSerialKeyRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSerialKeyDomain> Self,
                const Request::FGetSerialKeyRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSerialKeyRequestPtr Request
        );

        class GS2SERIALKEY_API FUseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>,
            public TSharedFromThis<FUseTask>
        {
            const TSharedPtr<FSerialKeyDomain> Self;
            const Request::FUseByUserIdRequestPtr Request;
        public:
            explicit FUseTask(
                const TSharedPtr<FSerialKeyDomain> Self,
                const Request::FUseByUserIdRequestPtr Request
            );

            FUseTask(
                const FUseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
            ) override;
        };
        friend FUseTask;

        TSharedPtr<FAsyncTask<FUseTask>> Use(
            Request::FUseByUserIdRequestPtr Request
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
            const TSharedPtr<FSerialKeyDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSerialKeyDomain> Self
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

    };

    typedef TSharedPtr<FSerialKeyDomain> FSerialKeyDomainPtr;
}
