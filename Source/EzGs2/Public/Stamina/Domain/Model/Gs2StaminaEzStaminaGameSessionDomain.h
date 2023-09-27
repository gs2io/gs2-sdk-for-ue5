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
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"
#include "Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverIntervalTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverValueTable.h"
#include "Stamina/Model/Gs2StaminaEzStamina.h"
#include "Gs2StaminaEzStaminaGameSessionDomain.h"
#include "Stamina/Domain/Iterator/Gs2StaminaEzDescribeStaminasIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    class EZGS2_API FEzStaminaGameSessionDomain final :
        public TSharedFromThis<FEzStaminaGameSessionDomain>
    {
        Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<int32> OverflowValue() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> StaminaName() const;

        FEzStaminaGameSessionDomain(
            Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetStaminaTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Model::FEzStamina>,
            public TSharedFromThis<FGetStaminaTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;

        public:
            explicit FGetStaminaTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Model::FEzStamina>> Result
            ) override;
        };
        friend FGetStaminaTask;

        TSharedPtr<FAsyncTask<FGetStaminaTask>> GetStamina(
        );

        class FConsumeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;
            int32 ConsumeValue;

        public:
            explicit FConsumeTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self,
                int32 ConsumeValue
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            int32 ConsumeValue
        );

        class FSetMaxValueTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>,
            public TSharedFromThis<FSetMaxValueTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;
            FString KeyId;
            FString SignedStatusBody;
            FString SignedStatusSignature;

        public:
            explicit FSetMaxValueTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self,
                FString KeyId,
                FString SignedStatusBody,
                FString SignedStatusSignature
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
            ) override;
        };
        friend FSetMaxValueTask;

        TSharedPtr<FAsyncTask<FSetMaxValueTask>> SetMaxValue(
            FString KeyId,
            FString SignedStatusBody,
            FString SignedStatusSignature
        );

        class FSetRecoverIntervalTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>,
            public TSharedFromThis<FSetRecoverIntervalTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;
            FString KeyId;
            FString SignedStatusBody;
            FString SignedStatusSignature;

        public:
            explicit FSetRecoverIntervalTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self,
                FString KeyId,
                FString SignedStatusBody,
                FString SignedStatusSignature
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
            ) override;
        };
        friend FSetRecoverIntervalTask;

        TSharedPtr<FAsyncTask<FSetRecoverIntervalTask>> SetRecoverInterval(
            FString KeyId,
            FString SignedStatusBody,
            FString SignedStatusSignature
        );

        class FSetRecoverValueTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>,
            public TSharedFromThis<FSetRecoverValueTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;
            FString KeyId;
            FString SignedStatusBody;
            FString SignedStatusSignature;

        public:
            explicit FSetRecoverValueTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self,
                FString KeyId,
                FString SignedStatusBody,
                FString SignedStatusSignature
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>> Result
            ) override;
        };
        friend FSetRecoverValueTask;

        TSharedPtr<FAsyncTask<FSetRecoverValueTask>> SetRecoverValue(
            FString KeyId,
            FString SignedStatusBody,
            FString SignedStatusSignature
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Model::FEzStamina>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStaminaGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStaminaGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Stamina::Model::FEzStaminaPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzStaminaGameSessionDomain> FEzStaminaGameSessionDomainPtr;
}
