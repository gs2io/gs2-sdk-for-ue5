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
#include "Experience/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelsIterator.h"
#include "Experience/Domain/Iterator/DescribeThresholdMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Experience::Domain
{
    class FGs2ExperienceDomain;
    typedef TSharedPtr<FGs2ExperienceDomain> FGs2ExperienceDomainPtr;
}

namespace Gs2::Experience::Domain::Model
{
    class FNamespaceDomain;
    class FExperienceModelMasterDomain;
    class FExperienceModelDomain;
    class FThresholdMasterDomain;
    class FCurrentExperienceMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStatusDomain;
    class FStatusAccessTokenDomain;

    class GS2EXPERIENCE_API FExperienceModelDomain:
        public TSharedFromThis<FExperienceModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Experience::Domain::FGs2ExperienceDomainPtr Service;
        const Gs2::Experience::FGs2ExperienceRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> ExperienceName;
    private:

        FString ParentKey;

    public:

        FExperienceModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Experience::Domain::FGs2ExperienceDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ExperienceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FExperienceModelDomain(
            const FExperienceModelDomain& From
        );

        class GS2EXPERIENCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FExperienceModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FExperienceModelDomain> Self;
            const Request::FGetExperienceModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FExperienceModelDomain>& Self,
                const Request::FGetExperienceModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetExperienceModelRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> ExperienceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ExperienceName
        );

        class GS2EXPERIENCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FExperienceModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FExperienceModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FExperienceModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Experience::Model::FExperienceModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FExperienceModelDomain> FExperienceModelDomainPtr;
}
