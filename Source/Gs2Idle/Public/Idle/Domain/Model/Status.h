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

    class GS2IDLE_API FStatusDomain:
        public TSharedFromThis<FStatusDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Idle::FGs2IdleRestClientPtr Client;

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
        TOptional<FString> UserId;
        TOptional<FString> CategoryName;
    private:

        FString ParentKey;

    public:

        FStatusDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> CategoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusDomain(
            const FStatusDomain& From
        );

        class GS2IDLE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FGetStatusByUserIdRequestPtr Request
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
            Request::FGetStatusByUserIdRequestPtr Request
        );

        class GS2IDLE_API FPredictionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Idle::Model::FAcquireAction>>>,
            public TSharedFromThis<FPredictionTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FPredictionByUserIdRequestPtr Request;
        public:
            explicit FPredictionTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FPredictionByUserIdRequestPtr Request
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
            Request::FPredictionByUserIdRequestPtr Request
        );

        class GS2IDLE_API FReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FReceiveByUserIdRequestPtr Request;
        public:
            explicit FReceiveTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FReceiveByUserIdRequestPtr Request
            );

            FReceiveTask(
                const FReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
            Request::FReceiveByUserIdRequestPtr Request
        );

        class GS2IDLE_API FIncreaseMaximumIdleMinutesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FIncreaseMaximumIdleMinutesTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request;
        public:
            explicit FIncreaseMaximumIdleMinutesTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
            );

            FIncreaseMaximumIdleMinutesTask(
                const FIncreaseMaximumIdleMinutesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FIncreaseMaximumIdleMinutesTask;

        TSharedPtr<FAsyncTask<FIncreaseMaximumIdleMinutesTask>> IncreaseMaximumIdleMinutes(
            Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
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
            const TSharedPtr<FStatusDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusDomain> Self
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

    };

    typedef TSharedPtr<FStatusDomain> FStatusDomainPtr;
}
