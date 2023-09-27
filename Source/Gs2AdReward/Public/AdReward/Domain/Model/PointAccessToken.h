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
#include "AdReward/Gs2AdReward.h"
#include "AdReward/Domain/Iterator/DescribeNamespacesIterator.h"

namespace Gs2::AdReward::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FPointDomain;
    class FPointAccessTokenDomain;

    class GS2ADREWARD_API FPointAccessTokenDomain:
        public TSharedFromThis<FPointAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::AdReward::FGs2AdRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FPointAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPointAccessTokenDomain(
            const FPointAccessTokenDomain& From
        );

        class GS2ADREWARD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::AdReward::Model::FPoint>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPointAccessTokenDomain> Self;
            const Request::FGetPointRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPointAccessTokenDomain> Self,
                const Request::FGetPointRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPointRequestPtr Request
        );

        class GS2ADREWARD_API FConsumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::AdReward::Domain::Model::FPointAccessTokenDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            const TSharedPtr<FPointAccessTokenDomain> Self;
            const Request::FConsumePointRequestPtr Request;
        public:
            explicit FConsumeTask(
                const TSharedPtr<FPointAccessTokenDomain> Self,
                const Request::FConsumePointRequestPtr Request
            );

            FConsumeTask(
                const FConsumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointAccessTokenDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            Request::FConsumePointRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2ADREWARD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::AdReward::Model::FPoint>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPointAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPointAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::AdReward::Model::FPointPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FPointAccessTokenDomain> FPointAccessTokenDomainPtr;
}
