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

    class GS2GRADE_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Grade::Domain::FGs2GradeDomainPtr Service;
        const Gs2::Grade::FGs2GradeRestClientPtr Client;

        public:
        TOptional<FString> ExperienceNamespaceName;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetExperienceNamespaceName() const
        {
            return ExperienceNamespaceName;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Grade::Domain::FGs2GradeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        Gs2::Grade::Domain::Iterator::FDescribeStatusesIteratorPtr Statuses(
            const TOptional<FString> GradeName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(
            TFunction<void()> Callback
            , const TOptional<FString> GradeName = TOptional<FString>()
        );

        class FCollectStatusesTask;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(
            TFunction<void(TArray<Gs2::Grade::Model::FStatusPtr>)> Callback,const TOptional<FString> GradeName = TOptional<FString>()
        );

        void InvalidateStatuses(const TOptional<FString> GradeName = TOptional<FString>());

        class GS2GRADE_API FSubscribeStatusesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStatusesWithInitialCallTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const TFunction<void(TArray<Gs2::Grade::Model::FStatusPtr>)> Callback;
        const TOptional<FString> QueryGradeName;
        public:
            FSubscribeStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Grade::Model::FStatusPtr>)> Callback,const TOptional<FString> GradeName);
            FSubscribeStatusesWithInitialCallTask(const FSubscribeStatusesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStatusesWithInitialCallTask>> SubscribeStatusesWithInitialCall(
            TFunction<void(TArray<Gs2::Grade::Model::FStatusPtr>)> Callback,const TOptional<FString> GradeName = TOptional<FString>()
        );
        void UnsubscribeStatuses(

            Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> GradeName = TOptional<FString>()
        );

        TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain> Status(
            const FString GradeName,
            const FString PropertyId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
