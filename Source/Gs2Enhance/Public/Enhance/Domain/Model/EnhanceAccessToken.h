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

    class GS2ENHANCE_API FEnhanceAccessTokenDomain:
        public TSharedFromThis<FEnhanceAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FEnhanceAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEnhanceAccessTokenDomain(
            const FEnhanceAccessTokenDomain& From
        );

        class GS2ENHANCE_API FDirectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FEnhanceAccessTokenDomain>,
            public TSharedFromThis<FDirectTask>
        {
            const TSharedPtr<FEnhanceAccessTokenDomain> Self;
            const Request::FDirectEnhanceRequestPtr Request;
        public:
            explicit FDirectTask(
                const TSharedPtr<FEnhanceAccessTokenDomain> Self,
                const Request::FDirectEnhanceRequestPtr Request
            );

            FDirectTask(
                const FDirectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FEnhanceAccessTokenDomain>> Result
            ) override;
        };
        friend FDirectTask;

        TSharedPtr<FAsyncTask<FDirectTask>> Direct(
            Request::FDirectEnhanceRequestPtr Request
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
