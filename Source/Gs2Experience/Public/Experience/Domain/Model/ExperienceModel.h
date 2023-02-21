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
#include "Experience/Gs2Experience.h"
#include "Experience/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeExperienceModelsIterator.h"
#include "Experience/Domain/Iterator/DescribeThresholdMastersIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesIterator.h"
#include "Experience/Domain/Iterator/DescribeStatusesByUserIdIterator.h"

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
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Experience::FGs2ExperienceRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> ExperienceName;
    private:

        FString ParentKey;

    public:

        FExperienceModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
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
                const TSharedPtr<FExperienceModelDomain> Self,
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

    };

    typedef TSharedPtr<FExperienceModelDomain> FExperienceModelDomainPtr;
}
