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
#include "Idle/Gs2Idle.h"
#include "Idle/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelMastersIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Idle::Domain
{
    class FGs2IdleDomain;
    typedef TSharedPtr<FGs2IdleDomain> FGs2IdleDomainPtr;
}

namespace Gs2::Idle::Domain::Model
{
    class FNamespaceDomain;
    class FCategoryModelMasterDomain;
    class FCategoryModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FCurrentCategoryMasterDomain;

    class GS2IDLE_API FStatusAccessTokenDomain:
        public TSharedFromThis<FStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Idle::Domain::FGs2IdleDomainPtr Service;
        const Gs2::Idle::FGs2IdleRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> CategoryName;
    private:

        FString ParentKey;

    public:

        FStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Idle::Domain::FGs2IdleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> CategoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusAccessTokenDomain(
            const FStatusAccessTokenDomain& From
        );

        class GS2IDLE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FGetStatusRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FGetStatusRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusRequestPtr Request
        );

        class GS2IDLE_API FPredictionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Idle::Model::FAcquireAction>>>,
            public TSharedFromThis<FPredictionTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FPredictionRequestPtr Request;
        public:
            explicit FPredictionTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FPredictionRequestPtr Request
            );

            FPredictionTask(
                const FPredictionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Idle::Model::FAcquireAction>>>> Result
            ) override;
        };
        friend FPredictionTask;

        TSharedPtr<FAsyncTask<FPredictionTask>> Prediction(
            Request::FPredictionRequestPtr Request
        );

        class GS2IDLE_API FReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FReceiveRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FReceiveTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FReceiveRequestPtr Request,
                bool SpeculativeExecute
            );

            FReceiveTask(
                const FReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
            Request::FReceiveRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2IDLE_API FDecreaseMaximumIdleMinutesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FDecreaseMaximumIdleMinutesTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FDecreaseMaximumIdleMinutesRequestPtr Request;
        public:
            explicit FDecreaseMaximumIdleMinutesTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FDecreaseMaximumIdleMinutesRequestPtr Request
            );

            FDecreaseMaximumIdleMinutesTask(
                const FDecreaseMaximumIdleMinutesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FDecreaseMaximumIdleMinutesTask;

        TSharedPtr<FAsyncTask<FDecreaseMaximumIdleMinutesTask>> DecreaseMaximumIdleMinutes(
            Request::FDecreaseMaximumIdleMinutesRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> CategoryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CategoryName
        );

        class GS2IDLE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FStatus>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Idle::Model::FStatusPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStatusAccessTokenDomain> FStatusAccessTokenDomainPtr;
}
