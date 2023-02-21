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
#include "Enhance/Gs2Enhance.h"
#include "Enhance/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelMastersIterator.h"

namespace Gs2::Enhance::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FEnhanceDomain;
    class FEnhanceAccessTokenDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2ENHANCE_API FProgressDomain:
        public TSharedFromThis<FProgressDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Enhance::FGs2EnhanceRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<int64> AcquireExperience;
        TOptional<float> BonusRate;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<int64> GetAcquireExperience() const
        {
            return AcquireExperience;
        }
        TOptional<float> GetBonusRate() const
        {
            return BonusRate;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FProgressDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FProgressDomain(
            const FProgressDomain& From
        );

        class GS2ENHANCE_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FCreateProgressByUserIdRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FCreateProgressByUserIdRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreateProgressByUserIdRequestPtr Request
        );

        class GS2ENHANCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FProgress>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FGetProgressByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FGetProgressByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FProgress>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetProgressByUserIdRequestPtr Request
        );

        class GS2ENHANCE_API FStartTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FStartTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FStartByUserIdRequestPtr Request;
        public:
            explicit FStartTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FStartByUserIdRequestPtr Request
            );

            FStartTask(
                const FStartTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FStartTask;

        TSharedPtr<FAsyncTask<FStartTask>> Start(
            Request::FStartByUserIdRequestPtr Request
        );

        class GS2ENHANCE_API FEndTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FEndTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FEndByUserIdRequestPtr Request;
        public:
            explicit FEndTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FEndByUserIdRequestPtr Request
            );

            FEndTask(
                const FEndTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            Request::FEndByUserIdRequestPtr Request
        );

        class GS2ENHANCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FDeleteProgressByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FDeleteProgressByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteProgressByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2ENHANCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FProgress>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FProgressDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FProgressDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FProgress>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FProgressDomain> FProgressDomainPtr;
}
