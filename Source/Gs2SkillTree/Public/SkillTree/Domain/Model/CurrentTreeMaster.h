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

    class GS2SKILLTREE_API FCurrentTreeMasterDomain:
        public TSharedFromThis<FCurrentTreeMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SkillTree::Domain::FGs2SkillTreeDomainPtr Service;
        const Gs2::SkillTree::FGs2SkillTreeRestClientPtr Client;

        public:
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentTreeMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentTreeMasterDomain(
            const FCurrentTreeMasterDomain& From
        );

        class GS2SKILLTREE_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentTreeMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FCurrentTreeMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
            const Request::FGetCurrentTreeMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentTreeMasterDomain>& Self,
                const Request::FGetCurrentTreeMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentTreeMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FPreUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>,
            public TSharedFromThis<FPreUpdateTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
            const Request::FPreUpdateCurrentTreeMasterRequestPtr Request;
        public:
            explicit FPreUpdateTask(
                const TSharedPtr<FCurrentTreeMasterDomain>& Self,
                const Request::FPreUpdateCurrentTreeMasterRequestPtr Request
            );

            FPreUpdateTask(
                const FPreUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
            ) override;
        };
        friend FPreUpdateTask;

        TSharedPtr<FAsyncTask<FPreUpdateTask>> PreUpdate(
            Request::FPreUpdateCurrentTreeMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
            const Request::FUpdateCurrentTreeMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentTreeMasterDomain>& Self,
                const Request::FUpdateCurrentTreeMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentTreeMasterRequestPtr Request
        );

        class GS2SKILLTREE_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
            const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentTreeMasterDomain>& Self,
                const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Domain::Model::FCurrentTreeMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SKILLTREE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SkillTree::Model::FCurrentTreeMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentTreeMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentTreeMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FCurrentTreeMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SkillTree::Model::FCurrentTreeMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentTreeMasterDomain> FCurrentTreeMasterDomainPtr;
}
