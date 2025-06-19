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

    class GS2SKILLTREE_API FStatusAccessTokenDomain:
        public TSharedFromThis<FStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SkillTree::Domain::FGs2SkillTreeDomainPtr Service;
        const Gs2::SkillTree::FGs2SkillTreeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusAccessTokenDomain(
            const FStatusAccessTokenDomain& From
        );

        class GS2SKILLTREE_API FReleaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FReleaseTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FReleaseRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FReleaseTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FReleaseRequestPtr Request,
                bool SpeculativeExecute
            );

            FReleaseTask(
                const FReleaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FReleaseTask;

        TSharedPtr<FAsyncTask<FReleaseTask>> Release(
            Request::FReleaseRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2SKILLTREE_API FMarkRestrainTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FMarkRestrainTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FMarkRestrainRequestPtr Request;
        public:
            explicit FMarkRestrainTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FMarkRestrainRequestPtr Request
            );

            FMarkRestrainTask(
                const FMarkRestrainTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FMarkRestrainTask;

        TSharedPtr<FAsyncTask<FMarkRestrainTask>> MarkRestrain(
            Request::FMarkRestrainRequestPtr Request
        );

        class GS2SKILLTREE_API FRestrainTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FRestrainTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FRestrainRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FRestrainTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FRestrainRequestPtr Request,
                bool SpeculativeExecute
            );

            FRestrainTask(
                const FRestrainTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FRestrainTask;

        TSharedPtr<FAsyncTask<FRestrainTask>> Restrain(
            Request::FRestrainRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FGetStatusRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FGetStatusRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusRequestPtr Request
        );

        class GS2SKILLTREE_API FResetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FResetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FResetRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FResetTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FResetRequestPtr Request,
                bool SpeculativeExecute
            );

            FResetTask(
                const FResetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
            Request::FResetRequestPtr Request,
            bool SpeculativeExecute = true
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PropertyId
        );

        class GS2SKILLTREE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FStatus>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SkillTree::Model::FStatusPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStatusAccessTokenDomain> FStatusAccessTokenDomainPtr;
}
