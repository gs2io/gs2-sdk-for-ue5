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

#pragma once

#include "CoreMinimal.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Model/Gs2EnhanceEzRateModel.h"
#include "Enhance/Model/Gs2EnhanceEzProgress.h"
#include "Enhance/Model/Gs2EnhanceEzConfig.h"
#include "Enhance/Model/Gs2EnhanceEzMaterial.h"
#include "Gs2EnhanceEzEnhanceGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    class EZGS2_API FEzEnhanceGameSessionDomain final :
        public TSharedFromThis<FEzEnhanceGameSessionDomain>
    {
        Gs2::Enhance::Domain::Model::FEnhanceAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<int64> AcquireExperience() const;
        TOptional<float> BonusRate() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzEnhanceGameSessionDomain(
            Gs2::Enhance::Domain::Model::FEnhanceAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FEnhanceTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomain>,
            public TSharedFromThis<FEnhanceTask>
        {
            TSharedPtr<FEzEnhanceGameSessionDomain> Self;
            FString RateName;
            FString TargetItemSetId;
            TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>> Materials;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config;

        public:
            explicit FEnhanceTask(
                TSharedPtr<FEzEnhanceGameSessionDomain> Self,
                FString RateName,
                FString TargetItemSetId,
                TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>> Materials,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomain>> Result
            ) override;
        };
        friend FEnhanceTask;

        TSharedPtr<FAsyncTask<FEnhanceTask>> Enhance(
            FString RateName,
            FString TargetItemSetId,
            TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>> Materials,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
        );

    };
    typedef TSharedPtr<FEzEnhanceGameSessionDomain> FEzEnhanceGameSessionDomainPtr;
}
