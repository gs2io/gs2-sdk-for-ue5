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
#include "SkillTree/Gs2SkillTree.h"
#include "SkillTree/Domain/Iterator/DescribeNamespacesIterator.h"
#include "SkillTree/Domain/Iterator/DescribeNodeModelsIterator.h"
#include "SkillTree/Domain/Iterator/DescribeNodeModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2SKILLTREE_API FNodeModelMasterDomain:
        public TSharedFromThis<FNodeModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::SkillTree::FGs2SkillTreeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> NodeModelName;
    private:

        FString ParentKey;

    public:

        FNodeModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> NodeModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNodeModelMasterDomain(
            const FNodeModelMasterDomain& From
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FNodeModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNodeModelMasterDomain> Self;
            const Request::FGetNodeModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNodeModelMasterDomain> Self,
                const Request::FGetNodeModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNodeModelMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FNodeModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNodeModelMasterDomain> Self;
            const Request::FUpdateNodeModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNodeModelMasterDomain> Self,
                const Request::FUpdateNodeModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FNodeModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNodeModelMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FNodeModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNodeModelMasterDomain> Self;
            const Request::FDeleteNodeModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNodeModelMasterDomain> Self,
                const Request::FDeleteNodeModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FNodeModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNodeModelMasterRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FNodeModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNodeModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNodeModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SkillTree::Model::FNodeModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNodeModelMasterDomain> FNodeModelMasterDomainPtr;
}
