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
#include "Formation/Domain/Model/Namespace.h"
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
#include "Formation/Model/Gs2FormationEzVerifyActionResult.h"
#include "Formation/Model/Gs2FormationEzConsumeActionResult.h"
#include "Formation/Model/Gs2FormationEzAcquireActionResult.h"
#include "Formation/Model/Gs2FormationEzTransactionResult.h"
#include "Gs2FormationEzMoldModelDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribeMoldModelsIterator.h"
#include "Gs2FormationEzPropertyFormModelDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribePropertyFormModelsIterator.h"
#include "Gs2FormationEzUserDomain.h"
#include "Gs2FormationEzUserDomain.h"
#include "Gs2FormationEzUserGameSessionDomain.h"
#include "Gs2FormationEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Formation::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Formation::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldModelsIteratorPtr MoldModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMoldModels(TFunction<void()> Callback);

        void UnsubscribeMoldModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomainPtr MoldModel(
            const FString MoldModelName
        ) const;

        Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormModelsIteratorPtr PropertyFormModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePropertyFormModels(TFunction<void()> Callback);

        void UnsubscribePropertyFormModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Formation::Domain::Model::FEzPropertyFormModelDomainPtr PropertyFormModel(
            const FString PropertyFormModelName
        ) const;

        Gs2::UE5::Formation::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Formation::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
