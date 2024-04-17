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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Buff/Domain/Model/BuffAccessToken.h"
#include "Buff/Model/Gs2BuffEzBuffEntryModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetAction.h"
#include "Buff/Model/Gs2BuffEzBuffTargetGrn.h"
#include "Gs2BuffEzBuffGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Core::Domain
{
    class FGs2Domain;
}

namespace Gs2::UE5::Buff::Domain::Model
{

    class EZGS2_API FEzBuffGameSessionDomain final :
        public TSharedFromThis<FEzBuffGameSessionDomain>
    {
        Gs2::Buff::Domain::Model::FBuffAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzBuffGameSessionDomain(
            Gs2::Buff::Domain::Model::FBuffAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FApplyBuffTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Core::Domain::FGs2Domain>,
            public TSharedFromThis<FApplyBuffTask>
        {
            TSharedPtr<FEzBuffGameSessionDomain> Self;

        public:
            explicit FApplyBuffTask(
                TSharedPtr<FEzBuffGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FGs2Domain>> Result
            ) override;
        };
        friend FApplyBuffTask;

        TSharedPtr<FAsyncTask<FApplyBuffTask>> ApplyBuff(
        );

    };
    typedef TSharedPtr<FEzBuffGameSessionDomain> FEzBuffGameSessionDomainPtr;
}
