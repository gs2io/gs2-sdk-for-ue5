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

    class GS2SKILLTREE_API FStatusAccessTokenDomain:
        public TSharedFromThis<FStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::SkillTree::FGs2SkillTreeRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusAccessTokenDomain(
            const FStatusAccessTokenDomain& From
        );

        class GS2SKILLTREE_API FReleaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FReleaseTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FReleaseRequestPtr Request;
        public:
            explicit FReleaseTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self,
                const Request::FReleaseRequestPtr Request
            );

            FReleaseTask(
                const FReleaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FReleaseTask;

        TSharedPtr<FAsyncTask<FReleaseTask>> Release(
            Request::FReleaseRequestPtr Request
        );

        class GS2SKILLTREE_API FRestrainTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FRestrainTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FRestrainRequestPtr Request;
        public:
            explicit FRestrainTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self,
                const Request::FRestrainRequestPtr Request
            );

            FRestrainTask(
                const FRestrainTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FRestrainTask;

        TSharedPtr<FAsyncTask<FRestrainTask>> Restrain(
            Request::FRestrainRequestPtr Request
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FGetStatusRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self,
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
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FResetTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FResetRequestPtr Request;
        public:
            explicit FResetTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self,
                const Request::FResetRequestPtr Request
            );

            FResetTask(
                const FResetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
            Request::FResetRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
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
