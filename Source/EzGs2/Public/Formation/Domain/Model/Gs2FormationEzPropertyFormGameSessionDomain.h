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
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
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
#include "Gs2FormationEzPropertyFormGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribePropertyFormsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzPropertyFormGameSessionDomain final :
        public TSharedFromThis<FEzPropertyFormGameSessionDomain>
    {
        Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> PropertyFormModelName() const;
        TOptional<FString> PropertyId() const;

        FEzPropertyFormGameSessionDomain(
            Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetPropertyFormWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>,
            public TSharedFromThis<FGetPropertyFormWithSignatureTask>
        {
            TSharedPtr<FEzPropertyFormGameSessionDomain> Self;
            TOptional<FString> KeyId;

        public:
            explicit FGetPropertyFormWithSignatureTask(
                TSharedPtr<FEzPropertyFormGameSessionDomain> Self,
                TOptional<FString> KeyId = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>> Result
            ) override;
        };
        friend FGetPropertyFormWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetPropertyFormWithSignatureTask>> GetPropertyFormWithSignature(
            TOptional<FString> KeyId = TOptional<FString>()
        );

        class FSetPropertyFormTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>,
            public TSharedFromThis<FSetPropertyFormTask>
        {
            TSharedPtr<FEzPropertyFormGameSessionDomain> Self;
            TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots;
            TOptional<FString> KeyId;

        public:
            explicit FSetPropertyFormTask(
                TSharedPtr<FEzPropertyFormGameSessionDomain> Self,
                TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
                TOptional<FString> KeyId = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>> Result
            ) override;
        };
        friend FSetPropertyFormTask;

        TSharedPtr<FAsyncTask<FSetPropertyFormTask>> SetPropertyForm(
            TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotWithSignature>> Slots,
            TOptional<FString> KeyId = TOptional<FString>()
        );

        class FDeletePropertyFormTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>,
            public TSharedFromThis<FDeletePropertyFormTask>
        {
            TSharedPtr<FEzPropertyFormGameSessionDomain> Self;

        public:
            explicit FDeletePropertyFormTask(
                TSharedPtr<FEzPropertyFormGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>> Result
            ) override;
        };
        friend FDeletePropertyFormTask;

        TSharedPtr<FAsyncTask<FDeletePropertyFormTask>> DeletePropertyForm(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzPropertyForm>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPropertyFormGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPropertyFormGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzPropertyFormPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzPropertyFormGameSessionDomain> FEzPropertyFormGameSessionDomainPtr;
}
