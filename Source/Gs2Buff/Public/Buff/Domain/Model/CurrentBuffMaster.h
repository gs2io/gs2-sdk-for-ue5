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
#include "Buff/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelsIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Buff::Domain
{
    class FGs2BuffDomain;
    typedef TSharedPtr<FGs2BuffDomain> FGs2BuffDomainPtr;
}

namespace Gs2::Buff::Domain::Model
{
    class FNamespaceDomain;
    class FBuffEntryModelDomain;
    class FBuffEntryModelMasterDomain;
    class FBuffDomain;
    class FBuffAccessTokenDomain;
    class FCurrentBuffMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2BUFF_API FCurrentBuffMasterDomain:
        public TSharedFromThis<FCurrentBuffMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Buff::Domain::FGs2BuffDomainPtr Service;
        const Gs2::Buff::FGs2BuffRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentBuffMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Buff::Domain::FGs2BuffDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentBuffMasterDomain(
            const FCurrentBuffMasterDomain& From
        );

        class GS2BUFF_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentBuffMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentBuffMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2BUFF_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Model::FCurrentBuffMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentBuffMasterDomain> Self;
            const Request::FGetCurrentBuffMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentBuffMasterDomain>& Self,
                const Request::FGetCurrentBuffMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Model::FCurrentBuffMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentBuffMasterRequestPtr Request
        );

        class GS2BUFF_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentBuffMasterDomain> Self;
            const Request::FUpdateCurrentBuffMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentBuffMasterDomain>& Self,
                const Request::FUpdateCurrentBuffMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentBuffMasterRequestPtr Request
        );

        class GS2BUFF_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentBuffMasterDomain> Self;
            const Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentBuffMasterDomain>& Self,
                const Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2BUFF_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Model::FCurrentBuffMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentBuffMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentBuffMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Model::FCurrentBuffMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Buff::Model::FCurrentBuffMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentBuffMasterDomain> FCurrentBuffMasterDomainPtr;
}
