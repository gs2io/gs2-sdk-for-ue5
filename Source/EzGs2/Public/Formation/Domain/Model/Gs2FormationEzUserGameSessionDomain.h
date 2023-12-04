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
#include "Formation/Domain/Model/UserAccessToken.h"
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
#include "Gs2FormationEzMoldGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribeMoldsIterator.h"
#include "Gs2FormationEzPropertyFormGameSessionDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribePropertyFormsIterator.h"
#include "Gs2FormationEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Formation::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Formation::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldsIteratorPtr Molds(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMolds(TFunction<void()> Callback);

        void UnsubscribeMolds(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Formation::Domain::Model::FEzMoldGameSessionDomainPtr Mold(
            const FString MoldModelName
        ) const;

        Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormsIteratorPtr PropertyForms(
            const FString PropertyFormModelName
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePropertyForms(TFunction<void()> Callback);

        void UnsubscribePropertyForms(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomainPtr PropertyForm(
            const FString PropertyFormModelName,
            const FString PropertyId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
