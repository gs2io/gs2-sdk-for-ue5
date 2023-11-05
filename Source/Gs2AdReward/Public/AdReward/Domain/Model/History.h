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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::AdReward::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FPointDomain;
    class FPointAccessTokenDomain;

    class GS2ADREWARD_API FHistoryDomain:
        public TSharedFromThis<FHistoryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::AdReward::FGs2AdRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> TransactionId;
    private:

        FString ParentKey;

    public:

        FHistoryDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> TransactionId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FHistoryDomain(
            const FHistoryDomain& From
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> TransactionId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TransactionId
        );

        class GS2ADREWARD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::AdReward::Model::FHistory>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FHistoryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FHistoryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FHistory>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::AdReward::Model::FHistoryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FHistoryDomain> FHistoryDomainPtr;
}
