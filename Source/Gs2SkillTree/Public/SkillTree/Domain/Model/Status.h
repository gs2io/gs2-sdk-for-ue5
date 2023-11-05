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

    class GS2SKILLTREE_API FStatusDomain:
        public TSharedFromThis<FStatusDomain>
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
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FStatusDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusDomain(
            const FStatusDomain& From
        );

        class GS2SKILLTREE_API FMarkReleaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FMarkReleaseTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FMarkReleaseByUserIdRequestPtr Request;
        public:
            explicit FMarkReleaseTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FMarkReleaseByUserIdRequestPtr Request
            );

            FMarkReleaseTask(
                const FMarkReleaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FMarkReleaseTask;

        TSharedPtr<FAsyncTask<FMarkReleaseTask>> MarkRelease(
            Request::FMarkReleaseByUserIdRequestPtr Request
        );

        class GS2SKILLTREE_API FReleaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FReleaseTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FReleaseByUserIdRequestPtr Request;
        public:
            explicit FReleaseTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FReleaseByUserIdRequestPtr Request
            );

            FReleaseTask(
                const FReleaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FReleaseTask;

        TSharedPtr<FAsyncTask<FReleaseTask>> Release(
            Request::FReleaseByUserIdRequestPtr Request
        );

        class GS2SKILLTREE_API FMarkRestrainTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FMarkRestrainTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FMarkRestrainByUserIdRequestPtr Request;
        public:
            explicit FMarkRestrainTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FMarkRestrainByUserIdRequestPtr Request
            );

            FMarkRestrainTask(
                const FMarkRestrainTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FMarkRestrainTask;

        TSharedPtr<FAsyncTask<FMarkRestrainTask>> MarkRestrain(
            Request::FMarkRestrainByUserIdRequestPtr Request
        );

        class GS2SKILLTREE_API FRestrainTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FRestrainTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FRestrainByUserIdRequestPtr Request;
        public:
            explicit FRestrainTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FRestrainByUserIdRequestPtr Request
            );

            FRestrainTask(
                const FRestrainTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FRestrainTask;

        TSharedPtr<FAsyncTask<FRestrainTask>> Restrain(
            Request::FRestrainByUserIdRequestPtr Request
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FGetStatusByUserIdRequestPtr Request
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
            Request::FGetStatusByUserIdRequestPtr Request
        );

        class GS2SKILLTREE_API FResetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FResetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FResetByUserIdRequestPtr Request;
        public:
            explicit FResetTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FResetByUserIdRequestPtr Request
            );

            FResetTask(
                const FResetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
            Request::FResetByUserIdRequestPtr Request
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
            const TSharedPtr<FStatusDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusDomain> Self
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

    typedef TSharedPtr<FStatusDomain> FStatusDomainPtr;
}
