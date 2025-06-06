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
#include "Showcase/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemGroupMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesByUserIdIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Showcase::Domain
{
    class FGs2ShowcaseDomain;
    typedef TSharedPtr<FGs2ShowcaseDomain> FGs2ShowcaseDomainPtr;
}

namespace Gs2::Showcase::Domain::Model
{
    class FNamespaceDomain;
    class FSalesItemMasterDomain;
    class FSalesItemGroupMasterDomain;
    class FShowcaseMasterDomain;
    class FCurrentShowcaseMasterDomain;
    class FShowcaseDomain;
    class FShowcaseAccessTokenDomain;
    class FDisplayItemDomain;
    class FDisplayItemAccessTokenDomain;
    class FRandomShowcaseMasterDomain;
    class FRandomShowcaseDomain;
    class FRandomShowcaseAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FRandomShowcaseStatusDomain;
    class FRandomShowcaseStatusAccessTokenDomain;
    class FRandomDisplayItemDomain;
    class FRandomDisplayItemAccessTokenDomain;

    class GS2SHOWCASE_API FCurrentShowcaseMasterDomain:
        public TSharedFromThis<FCurrentShowcaseMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Showcase::Domain::FGs2ShowcaseDomainPtr Service;
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

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

        FCurrentShowcaseMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentShowcaseMasterDomain(
            const FCurrentShowcaseMasterDomain& From
        );

        class GS2SHOWCASE_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FCurrentShowcaseMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
            const Request::FGetCurrentShowcaseMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain>& Self,
                const Request::FGetCurrentShowcaseMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentShowcaseMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FPreUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>,
            public TSharedFromThis<FPreUpdateTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
            const Request::FPreUpdateCurrentShowcaseMasterRequestPtr Request;
        public:
            explicit FPreUpdateTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain>& Self,
                const Request::FPreUpdateCurrentShowcaseMasterRequestPtr Request
            );

            FPreUpdateTask(
                const FPreUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
            ) override;
        };
        friend FPreUpdateTask;

        TSharedPtr<FAsyncTask<FPreUpdateTask>> PreUpdate(
            Request::FPreUpdateCurrentShowcaseMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
            const Request::FUpdateCurrentShowcaseMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain>& Self,
                const Request::FUpdateCurrentShowcaseMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentShowcaseMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
            const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain>& Self,
                const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FCurrentShowcaseMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentShowcaseMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentShowcaseMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FCurrentShowcaseMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Showcase::Model::FCurrentShowcaseMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentShowcaseMasterDomain> FCurrentShowcaseMasterDomainPtr;
}
