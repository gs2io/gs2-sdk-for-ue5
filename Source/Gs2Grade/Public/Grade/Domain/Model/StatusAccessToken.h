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
#include "Grade/Gs2Grade.h"
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

    class GS2GRADE_API FStatusAccessTokenDomain:
        public TSharedFromThis<FStatusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Grade::Domain::FGs2GradeDomainPtr Service;
        const Gs2::Grade::FGs2GradeRestClientPtr Client;

        public:
        TOptional<FString> ExperienceNamespaceName;
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetExperienceNamespaceName() const
        {
            return ExperienceNamespaceName;
        }
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
        TOptional<FString> GradeName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FStatusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Grade::Domain::FGs2GradeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> GradeName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusAccessTokenDomain(
            const FStatusAccessTokenDomain& From
        );

        class GS2GRADE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Model::FStatus>,
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
                TSharedPtr<TSharedPtr<Gs2::Grade::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusRequestPtr Request
        );

        class GS2GRADE_API FApplyRankCapTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FApplyRankCapTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FApplyRankCapRequestPtr Request;
        public:
            explicit FApplyRankCapTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FApplyRankCapRequestPtr Request
            );

            FApplyRankCapTask(
                const FApplyRankCapTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FApplyRankCapTask;

        TSharedPtr<FAsyncTask<FApplyRankCapTask>> ApplyRankCap(
            Request::FApplyRankCapRequestPtr Request
        );

        class GS2GRADE_API FVerifyGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FVerifyGradeTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FVerifyGradeRequestPtr Request;
        public:
            explicit FVerifyGradeTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FVerifyGradeRequestPtr Request
            );

            FVerifyGradeTask(
                const FVerifyGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FVerifyGradeTask;

        TSharedPtr<FAsyncTask<FVerifyGradeTask>> VerifyGrade(
            Request::FVerifyGradeRequestPtr Request
        );

        class GS2GRADE_API FVerifyGradeUpMaterialTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>,
            public TSharedFromThis<FVerifyGradeUpMaterialTask>
        {
            const TSharedPtr<FStatusAccessTokenDomain> Self;
            const Request::FVerifyGradeUpMaterialRequestPtr Request;
        public:
            explicit FVerifyGradeUpMaterialTask(
                const TSharedPtr<FStatusAccessTokenDomain>& Self,
                const Request::FVerifyGradeUpMaterialRequestPtr Request
            );

            FVerifyGradeUpMaterialTask(
                const FVerifyGradeUpMaterialTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>> Result
            ) override;
        };
        friend FVerifyGradeUpMaterialTask;

        TSharedPtr<FAsyncTask<FVerifyGradeUpMaterialTask>> VerifyGradeUpMaterial(
            Request::FVerifyGradeUpMaterialRequestPtr Request
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
            const TSharedPtr<FStatusAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStatusAccessTokenDomain> Self
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

    typedef TSharedPtr<FStatusAccessTokenDomain> FStatusAccessTokenDomainPtr;
}
