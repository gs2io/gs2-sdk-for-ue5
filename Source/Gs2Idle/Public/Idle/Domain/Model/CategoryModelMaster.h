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
#include "Idle/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelMastersIterator.h"
#include "Idle/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesIterator.h"
#include "Idle/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Idle::Domain
{
    class FGs2IdleDomain;
    typedef TSharedPtr<FGs2IdleDomain> FGs2IdleDomainPtr;
}

namespace Gs2::Idle::Domain::Model
{
    class FNamespaceDomain;
    class FCategoryModelMasterDomain;
    class FCategoryModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FCurrentCategoryMasterDomain;

    class GS2IDLE_API FCategoryModelMasterDomain:
        public TSharedFromThis<FCategoryModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Idle::Domain::FGs2IdleDomainPtr Service;
        const Gs2::Idle::FGs2IdleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> CategoryName;
    private:

        FString ParentKey;

    public:

        FCategoryModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Idle::Domain::FGs2IdleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CategoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCategoryModelMasterDomain(
            const FCategoryModelMasterDomain& From
        );

        class GS2IDLE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FCategoryModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCategoryModelMasterDomain> Self;
            const Request::FGetCategoryModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCategoryModelMasterDomain>& Self,
                const Request::FGetCategoryModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCategoryModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCategoryModelMasterRequestPtr Request
        );

        class GS2IDLE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCategoryModelMasterDomain> Self;
            const Request::FUpdateCategoryModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCategoryModelMasterDomain>& Self,
                const Request::FUpdateCategoryModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCategoryModelMasterRequestPtr Request
        );

        class GS2IDLE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FCategoryModelMasterDomain> Self;
            const Request::FDeleteCategoryModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FCategoryModelMasterDomain>& Self,
                const Request::FDeleteCategoryModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteCategoryModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> CategoryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CategoryName
        );

        class GS2IDLE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Idle::Model::FCategoryModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCategoryModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCategoryModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCategoryModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Idle::Model::FCategoryModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCategoryModelMasterDomain> FCategoryModelMasterDomainPtr;
}
