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
#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Model/Gs2SkillTreeEzNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeEzStatus.h"
#include "SkillTree/Model/Gs2SkillTreeEzConfig.h"
#include "SkillTree/Model/Gs2SkillTreeEzAcquireAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzConsumeAction.h"
#include "Gs2SkillTreeEzStatusGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    class EZGS2_API FEzStatusGameSessionDomain final :
        public TSharedFromThis<FEzStatusGameSessionDomain>
    {
        Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzStatusGameSessionDomain(
            Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FReleaseTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FReleaseTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;
            TArray<FString> NodeModelNames;

        public:
            explicit FReleaseTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self,
                TArray<FString> NodeModelNames
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FReleaseTask;

        TSharedPtr<FAsyncTask<FReleaseTask>> Release(
            TArray<FString> NodeModelNames
        );

        class FRestrainTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FRestrainTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;
            TArray<FString> NodeModelNames;

        public:
            explicit FRestrainTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self,
                TArray<FString> NodeModelNames
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FRestrainTask;

        TSharedPtr<FAsyncTask<FRestrainTask>> Restrain(
            TArray<FString> NodeModelNames
        );

        class FGetStatusTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Model::FEzStatus>,
            public TSharedFromThis<FGetStatusTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FGetStatusTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzStatus>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
        );

        class FResetTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FResetTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FResetTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SkillTree::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzStatusGameSessionDomain> FEzStatusGameSessionDomainPtr;
}
