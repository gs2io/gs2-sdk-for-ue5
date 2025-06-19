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
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enhance::Domain
{
    class FGs2EnhanceDomain;
    typedef TSharedPtr<FGs2EnhanceDomain> FGs2EnhanceDomainPtr;
}

namespace Gs2::Enhance::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FUnleashRateModelDomain;
    class FUnleashRateModelMasterDomain;
    class FEnhanceDomain;
    class FEnhanceAccessTokenDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2ENHANCE_API FEnhanceAccessTokenDomain:
        public TSharedFromThis<FEnhanceAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enhance::Domain::FGs2EnhanceDomainPtr Service;
        const Gs2::Enhance::FGs2EnhanceRestClientPtr Client;

        public:
        TOptional<int64> AcquireExperience;
        TOptional<float> BonusRate;
        TOptional<int64> GetAcquireExperience() const
        {
            return AcquireExperience;
        }
        TOptional<float> GetBonusRate() const
        {
            return BonusRate;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FEnhanceAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEnhanceAccessTokenDomain(
            const FEnhanceAccessTokenDomain& From
        );

        class GS2ENHANCE_API FDirectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FDirectTask>
        {
            const TSharedPtr<FEnhanceAccessTokenDomain> Self;
            const Request::FDirectEnhanceRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FDirectTask(
                const TSharedPtr<FEnhanceAccessTokenDomain>& Self,
                const Request::FDirectEnhanceRequestPtr Request,
                bool SpeculativeExecute
            );

            FDirectTask(
                const FDirectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FDirectTask;

        TSharedPtr<FAsyncTask<FDirectTask>> Direct(
            Request::FDirectEnhanceRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2ENHANCE_API FUnleashTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FUnleashTask>
        {
            const TSharedPtr<FEnhanceAccessTokenDomain> Self;
            const Request::FUnleashRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FUnleashTask(
                const TSharedPtr<FEnhanceAccessTokenDomain>& Self,
                const Request::FUnleashRequestPtr Request,
                bool SpeculativeExecute
            );

            FUnleashTask(
                const FUnleashTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FUnleashTask;

        TSharedPtr<FAsyncTask<FUnleashTask>> Unleash(
            Request::FUnleashRequestPtr Request,
            bool SpeculativeExecute = true
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FEnhanceAccessTokenDomain> FEnhanceAccessTokenDomainPtr;
}
