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
#include "Auth/Gs2Auth.h"
#include "SkillTree/Domain/Iterator/DescribeNamespacesIterator.h"
#include "SkillTree/Domain/Iterator/DescribeNodeModelsIterator.h"
#include "SkillTree/Domain/Iterator/DescribeNodeModelMastersIterator.h"
#include "SkillTree/Domain/Iterator/DescribeStatusesIterator.h"
#include "SkillTree/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::SkillTree::Domain
{
    class FGs2SkillTreeDomain;
    typedef TSharedPtr<FGs2SkillTreeDomain> FGs2SkillTreeDomainPtr;
}

namespace Gs2::SkillTree::Domain::Model
{
    class FNamespaceDomain;
    class FNodeModelDomain;
    class FNodeModelMasterDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FCurrentTreeMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2SKILLTREE_API FNodeModelDomain:
        public TSharedFromThis<FNodeModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SkillTree::Domain::FGs2SkillTreeDomainPtr Service;
        const Gs2::SkillTree::FGs2SkillTreeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> NodeModelName;
    private:

        FString ParentKey;

    public:

        FNodeModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> NodeModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNodeModelDomain(
            const FNodeModelDomain& From
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FNodeModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNodeModelDomain> Self;
            const Request::FGetNodeModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNodeModelDomain>& Self,
                const Request::FGetNodeModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNodeModelRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> NodeModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NodeModelName
        );

        class GS2SKILLTREE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FNodeModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNodeModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNodeModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SkillTree::Model::FNodeModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNodeModelDomain> FNodeModelDomainPtr;
}
