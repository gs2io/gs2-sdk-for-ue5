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
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Model/Gs2EnhanceEzRateModel.h"
#include "Enhance/Model/Gs2EnhanceEzProgress.h"
#include "Enhance/Model/Gs2EnhanceEzConfig.h"
#include "Enhance/Model/Gs2EnhanceEzMaterial.h"
#include "Gs2EnhanceEzProgressGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    class EZGS2_API FEzProgressGameSessionDomain final :
        public TSharedFromThis<FEzProgressGameSessionDomain>
    {
        Gs2::Enhance::Domain::Model::FProgressAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<int64> AcquireExperience() const;
        TOptional<float> BonusRate() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzProgressGameSessionDomain(
            Gs2::Enhance::Domain::Model::FProgressAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FStartTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FStartTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;
            FString RateName;
            FString TargetItemSetId;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>> Materials;
            TOptional<bool> Force;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config;

        public:
            explicit FStartTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self,
                FString RateName,
                FString TargetItemSetId,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>> Materials = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>>(),
                TOptional<bool> Force = TOptional<bool>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FStartTask;

        TSharedPtr<FAsyncTask<FStartTask>> Start(
            FString RateName,
            FString TargetItemSetId,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>> Materials = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>>(),
            TOptional<bool> Force = TOptional<bool>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
        );

        class FEndTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FEndTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config;

        public:
            explicit FEndTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>>()
        );

        class FDeleteProgressTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FDeleteProgressTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;

        public:
            explicit FDeleteProgressTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteProgressTask;

        TSharedPtr<FAsyncTask<FDeleteProgressTask>> DeleteProgress(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Model::FEzProgress>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enhance::Model::FEzProgressPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Enhance::Model::FEzProgressPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzProgressGameSessionDomain> FEzProgressGameSessionDomainPtr;
}
