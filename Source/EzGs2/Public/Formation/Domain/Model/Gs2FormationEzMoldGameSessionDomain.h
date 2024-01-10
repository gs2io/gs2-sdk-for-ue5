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
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Model/Gs2FormationEzFormModel.h"
#include "Formation/Model/Gs2FormationEzMoldModel.h"
#include "Formation/Model/Gs2FormationEzPropertyFormModel.h"
#include "Formation/Model/Gs2FormationEzMold.h"
#include "Formation/Model/Gs2FormationEzForm.h"
#include "Formation/Model/Gs2FormationEzPropertyForm.h"
#include "Formation/Model/Gs2FormationEzSlot.h"
#include "Formation/Model/Gs2FormationEzSlotModel.h"
#include "Formation/Model/Gs2FormationEzSlotWithSignature.h"
#include "Formation/Model/Gs2FormationEzConfig.h"
#include "Formation/Model/Gs2FormationEzAcquireAction.h"
#include "Gs2FormationEzFormGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribeFormsIterator.h"
#include "Gs2FormationEzMoldGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribeMoldsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzMoldGameSessionDomain final :
        public TSharedFromThis<FEzMoldGameSessionDomain>
    {
        Gs2::Formation::Domain::Model::FMoldAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> MoldModelName() const;

        FEzMoldGameSessionDomain(
            Gs2::Formation::Domain::Model::FMoldAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormsIteratorPtr Forms(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeForms(TFunction<void()> Callback);

        void UnsubscribeForms(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomainPtr Form(
            const int32 Index
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzMold>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzMoldGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzMoldGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzMoldPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzMoldGameSessionDomain> FEzMoldGameSessionDomainPtr;
}
