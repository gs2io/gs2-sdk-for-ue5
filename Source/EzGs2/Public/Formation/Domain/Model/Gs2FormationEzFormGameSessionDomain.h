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
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Model/Gs2FormationEzFormModel.h"
#include "Formation/Model/Gs2FormationEzMoldModel.h"
#include "Formation/Model/Gs2FormationEzPropertyFormModel.h"
#include "Formation/Model/Gs2FormationEzMold.h"
#include "Formation/Model/Gs2FormationEzForm.h"
#include "Formation/Model/Gs2FormationEzPropertyForm.h"
#include "Formation/Model/Gs2FormationEzSlot.h"
#include "Formation/Model/Gs2FormationEzSlotModel.h"
#include "Formation/Model/Gs2FormationEzSlotWithSignature.h"
#include "Formation/Model/Gs2FormationEzAcquireActionConfig.h"
#include "Formation/Model/Gs2FormationEzConfig.h"
#include "Formation/Model/Gs2FormationEzAcquireAction.h"
#include "Gs2FormationEzFormGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribeFormsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzFormGameSessionDomain final :
        public TSharedFromThis<FEzFormGameSessionDomain>
    {
        Gs2::Formation::Domain::Model::FFormAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> MoldModelName() const;
        TOptional<int32> Index() const;

        FEzFormGameSessionDomain(
            Gs2::Formation::Domain::Model::FFormAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetFormTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzForm>,
            public TSharedFromThis<FGetFormTask>
        {
            TSharedPtr<FEzFormGameSessionDomain> Self;

        public:
            explicit FGetFormTask(
                TSharedPtr<FEzFormGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzForm>> Result
            ) override;
        };
        friend FGetFormTask;

        TSharedPtr<FAsyncTask<FGetFormTask>> GetForm(
        );

        class FGetFormWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>,
            public TSharedFromThis<FGetFormWithSignatureTask>
        {
            TSharedPtr<FEzFormGameSessionDomain> Self;
            FString KeyId;

        public:
            explicit FGetFormWithSignatureTask(
                TSharedPtr<FEzFormGameSessionDomain> Self,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>> Result
            ) override;
        };
        friend FGetFormWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetFormWithSignatureTask>> GetFormWithSignature(
            FString KeyId
        );

        class FSetFormTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>,
            public TSharedFromThis<FSetFormTask>
        {
            TSharedPtr<FEzFormGameSessionDomain> Self;
            TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots;
            FString KeyId;

        public:
            explicit FSetFormTask(
                TSharedPtr<FEzFormGameSessionDomain> Self,
                TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>> Result
            ) override;
        };
        friend FSetFormTask;

        TSharedPtr<FAsyncTask<FSetFormTask>> SetForm(
            TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
            FString KeyId
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzForm>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzFormGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzFormGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Formation::Model::FEzFormPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzFormPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzFormGameSessionDomain> FEzFormGameSessionDomainPtr;
}
