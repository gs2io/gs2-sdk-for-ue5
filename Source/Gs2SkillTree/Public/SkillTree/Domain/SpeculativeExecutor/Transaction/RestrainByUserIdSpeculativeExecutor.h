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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Model/AcquireAction.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Model/VerifyAction.h"
#include "SkillTree/Domain/Gs2SkillTree.h"
#include "SkillTree/Request/RestrainByUserIdRequest.h"
#include "Math/BigInt.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    class FPreparedSpeculativeCommit;
}

namespace Gs2::SkillTree::Domain
{
    class FGs2SkillTreeDomain;
    typedef TSharedPtr<FGs2SkillTreeDomain> FGs2SkillTreeDomainPtr;
}

namespace Gs2::SkillTree::Domain::Transaction::SpeculativeExecutor
{
    class GS2SKILLTREE_API FRestrainByUserIdSpeculativeExecutor
    {
    public:
        static FString Action();

        class FCommitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr Request;

        public:
            GS2SKILLTREE_API explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr& Request
            );

            GS2SKILLTREE_API FCommitTask(
                const FCommitTask& From
            );

            GS2SKILLTREE_API virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
            ) override;
        };
        friend FCommitTask;

        static TSharedPtr<FAsyncTask<FRestrainByUserIdSpeculativeExecutor::FCommitTask>> Execute(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr& Request
        );
    };
}
