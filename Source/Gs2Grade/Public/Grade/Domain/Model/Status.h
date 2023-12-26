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

    class GS2GRADE_API FStatusDomain:
        public TSharedFromThis<FStatusDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Grade::Domain::FGs2GradeDomainPtr Service;
        const Gs2::Grade::FGs2GradeRestClientPtr Client;

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
        TOptional<FString> GradeName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FStatusDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Grade::Domain::FGs2GradeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> GradeName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusDomain(
            const FStatusDomain& From
        );

        class GS2GRADE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FGetStatusByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusByUserIdRequestPtr Request
        );

        class GS2GRADE_API FAddGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FAddGradeTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FAddGradeByUserIdRequestPtr Request;
        public:
            explicit FAddGradeTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FAddGradeByUserIdRequestPtr Request
            );

            FAddGradeTask(
                const FAddGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FAddGradeTask;

        TSharedPtr<FAsyncTask<FAddGradeTask>> AddGrade(
            Request::FAddGradeByUserIdRequestPtr Request
        );

        class GS2GRADE_API FSubGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FSubGradeTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FSubGradeByUserIdRequestPtr Request;
        public:
            explicit FSubGradeTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FSubGradeByUserIdRequestPtr Request
            );

            FSubGradeTask(
                const FSubGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FSubGradeTask;

        TSharedPtr<FAsyncTask<FSubGradeTask>> SubGrade(
            Request::FSubGradeByUserIdRequestPtr Request
        );

        class GS2GRADE_API FSetGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FSetGradeTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FSetGradeByUserIdRequestPtr Request;
        public:
            explicit FSetGradeTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FSetGradeByUserIdRequestPtr Request
            );

            FSetGradeTask(
                const FSetGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FSetGradeTask;

        TSharedPtr<FAsyncTask<FSetGradeTask>> SetGrade(
            Request::FSetGradeByUserIdRequestPtr Request
        );

        class GS2GRADE_API FApplyRankCapTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FApplyRankCapTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FApplyRankCapByUserIdRequestPtr Request;
        public:
            explicit FApplyRankCapTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FApplyRankCapByUserIdRequestPtr Request
            );

            FApplyRankCapTask(
                const FApplyRankCapTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FApplyRankCapTask;

        TSharedPtr<FAsyncTask<FApplyRankCapTask>> ApplyRankCap(
            Request::FApplyRankCapByUserIdRequestPtr Request
        );

        class GS2GRADE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FDeleteStatusByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FDeleteStatusByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStatusByUserIdRequestPtr Request
        );

        class GS2GRADE_API FVerifyGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FVerifyGradeTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FVerifyGradeByUserIdRequestPtr Request;
        public:
            explicit FVerifyGradeTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FVerifyGradeByUserIdRequestPtr Request
            );

            FVerifyGradeTask(
                const FVerifyGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FVerifyGradeTask;

        TSharedPtr<FAsyncTask<FVerifyGradeTask>> VerifyGrade(
            Request::FVerifyGradeByUserIdRequestPtr Request
        );

        class GS2GRADE_API FVerifyGradeUpMaterialTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FVerifyGradeUpMaterialTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request;
        public:
            explicit FVerifyGradeUpMaterialTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
            );

            FVerifyGradeUpMaterialTask(
                const FVerifyGradeUpMaterialTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FVerifyGradeUpMaterialTask;

        TSharedPtr<FAsyncTask<FVerifyGradeUpMaterialTask>> VerifyGradeUpMaterial(
            Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
        );

        class GS2GRADE_API FMultiplyAcquireActionsTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FMultiplyAcquireActionsTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request;
        public:
            explicit FMultiplyAcquireActionsTask(
                const TSharedPtr<FStatusDomain>& Self,
                const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
            );

            FMultiplyAcquireActionsTask(
                const FMultiplyAcquireActionsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FMultiplyAcquireActionsTask;

        TSharedPtr<FAsyncTask<FMultiplyAcquireActionsTask>> MultiplyAcquireActions(
            Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> GradeName,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GradeName,
            TOptional<FString> PropertyId
        );

        class GS2GRADE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FStatus>,
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
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Grade::Model::FStatusPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStatusDomain> FStatusDomainPtr;
}
