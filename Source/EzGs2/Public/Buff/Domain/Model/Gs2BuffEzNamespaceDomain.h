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
#include "Buff/Domain/Model/Namespace.h"
#include "Buff/Model/Gs2BuffEzBuffEntryModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetAction.h"
#include "Buff/Model/Gs2BuffEzBuffTargetGrn.h"
#include "Gs2BuffEzBuffEntryModelDomain.h"
#include "Buff/Domain/Iterator/Gs2BuffEzDescribeBuffEntryModelsIterator.h"
#include "Gs2BuffEzUserDomain.h"
#include "Gs2BuffEzUserDomain.h"
#include "Gs2BuffEzUserGameSessionDomain.h"
#include "Gs2BuffEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Buff::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Buff::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Buff::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Buff::Domain::Iterator::FEzDescribeBuffEntryModelsIteratorPtr BuffEntryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBuffEntryModels(TFunction<void()> Callback);

        void UnsubscribeBuffEntryModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Buff::Domain::Model::FEzBuffEntryModelDomainPtr BuffEntryModel(
            const FString BuffEntryName
        ) const;

        Gs2::UE5::Buff::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Buff::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::FGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
