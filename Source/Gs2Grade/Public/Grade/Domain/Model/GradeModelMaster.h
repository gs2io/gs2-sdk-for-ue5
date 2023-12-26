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

    class GS2GRADE_API FGradeModelMasterDomain:
        public TSharedFromThis<FGradeModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Grade::Domain::FGs2GradeDomainPtr Service;
        const Gs2::Grade::FGs2GradeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GradeName;
    private:

        FString ParentKey;

    public:

        FGradeModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Grade::Domain::FGs2GradeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GradeName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGradeModelMasterDomain(
            const FGradeModelMasterDomain& From
        );

        class GS2GRADE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FGradeModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGradeModelMasterDomain> Self;
            const Request::FGetGradeModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGradeModelMasterDomain>& Self,
                const Request::FGetGradeModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGradeModelMasterRequestPtr Request
        );

        class GS2GRADE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FGradeModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGradeModelMasterDomain> Self;
            const Request::FUpdateGradeModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGradeModelMasterDomain>& Self,
                const Request::FUpdateGradeModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FGradeModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGradeModelMasterRequestPtr Request
        );

        class GS2GRADE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FGradeModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FGradeModelMasterDomain> Self;
            const Request::FDeleteGradeModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FGradeModelMasterDomain>& Self,
                const Request::FDeleteGradeModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FGradeModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteGradeModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GradeName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GradeName
        );

        class GS2GRADE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FGradeModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGradeModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGradeModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Grade::Model::FGradeModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGradeModelMasterDomain> FGradeModelMasterDomainPtr;
}
