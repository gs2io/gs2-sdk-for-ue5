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
#include "Grade/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Grade/Domain/Iterator/DescribeGradeModelMastersIterator.h"
#include "Grade/Domain/Iterator/DescribeGradeModelsIterator.h"
#include "Grade/Domain/Iterator/DescribeStatusesIterator.h"
#include "Grade/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Grade::Domain
{
    class FGs2GradeDomain;
    typedef TSharedPtr<FGs2GradeDomain> FGs2GradeDomainPtr;
}

namespace Gs2::Grade::Domain::Model
{
    class FNamespaceDomain;
    class FGradeModelMasterDomain;
    class FGradeModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;
    class FCurrentGradeMasterDomain;

    class GS2GRADE_API FCurrentGradeMasterDomain:
        public TSharedFromThis<FCurrentGradeMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Grade::Domain::FGs2GradeDomainPtr Service;
        const Gs2::Grade::FGs2GradeRestClientPtr Client;

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

        FCurrentGradeMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Grade::Domain::FGs2GradeDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentGradeMasterDomain(
            const FCurrentGradeMasterDomain& From
        );

        class GS2GRADE_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentGradeMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2GRADE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FCurrentGradeMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
            const Request::FGetCurrentGradeMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentGradeMasterDomain>& Self,
                const Request::FGetCurrentGradeMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FCurrentGradeMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentGradeMasterRequestPtr Request
        );

        class GS2GRADE_API FPreUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>,
            public TSharedFromThis<FPreUpdateTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
            const Request::FPreUpdateCurrentGradeMasterRequestPtr Request;
        public:
            explicit FPreUpdateTask(
                const TSharedPtr<FCurrentGradeMasterDomain>& Self,
                const Request::FPreUpdateCurrentGradeMasterRequestPtr Request
            );

            FPreUpdateTask(
                const FPreUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>> Result
            ) override;
        };
        friend FPreUpdateTask;

        TSharedPtr<FAsyncTask<FPreUpdateTask>> PreUpdate(
            Request::FPreUpdateCurrentGradeMasterRequestPtr Request
        );

        class GS2GRADE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
            const Request::FUpdateCurrentGradeMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentGradeMasterDomain>& Self,
                const Request::FUpdateCurrentGradeMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentGradeMasterRequestPtr Request
        );

        class GS2GRADE_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
            const Request::FUpdateCurrentGradeMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentGradeMasterDomain>& Self,
                const Request::FUpdateCurrentGradeMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FCurrentGradeMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentGradeMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2GRADE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FCurrentGradeMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentGradeMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentGradeMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FCurrentGradeMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Grade::Model::FCurrentGradeMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentGradeMasterDomain> FCurrentGradeMasterDomainPtr;
}
