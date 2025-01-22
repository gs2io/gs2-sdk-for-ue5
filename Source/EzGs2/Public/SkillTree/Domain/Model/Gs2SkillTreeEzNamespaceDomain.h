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
#include "SkillTree/Domain/Model/Namespace.h"
#include "SkillTree/Model/Gs2SkillTreeEzNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeEzStatus.h"
#include "SkillTree/Model/Gs2SkillTreeEzConfig.h"
#include "SkillTree/Model/Gs2SkillTreeEzAcquireAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzConsumeAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzVerifyAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzVerifyActionResult.h"
#include "SkillTree/Model/Gs2SkillTreeEzConsumeActionResult.h"
#include "SkillTree/Model/Gs2SkillTreeEzAcquireActionResult.h"
#include "SkillTree/Model/Gs2SkillTreeEzTransactionResult.h"
#include "Gs2SkillTreeEzNodeModelDomain.h"
#include "SkillTree/Domain/Iterator/Gs2SkillTreeEzDescribeNodeModelsIterator.h"
#include "Gs2SkillTreeEzUserDomain.h"
#include "Gs2SkillTreeEzUserDomain.h"
#include "Gs2SkillTreeEzUserGameSessionDomain.h"
#include "Gs2SkillTreeEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::SkillTree::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::SkillTree::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::SkillTree::Domain::Iterator::FEzDescribeNodeModelsIteratorPtr NodeModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNodeModels(TFunction<void()> Callback);

        void UnsubscribeNodeModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::SkillTree::Domain::Model::FEzNodeModelDomainPtr NodeModel(
            const FString NodeModelName
        ) const;

        Gs2::UE5::SkillTree::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::SkillTree::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
