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

    class GS2EXPERIENCE_API FStatusDomain:
        public TSharedFromThis<FStatusDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Experience::FGs2ExperienceRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ExperienceName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FStatusDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ExperienceName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStatusDomain(
            const FStatusDomain& From
        );

        class GS2EXPERIENCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FStatus>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FGetStatusByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStatusByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FGetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FGetWithSignatureTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FGetStatusWithSignatureByUserIdRequestPtr Request;
        public:
            explicit FGetWithSignatureTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FGetStatusWithSignatureByUserIdRequestPtr Request
            );

            FGetWithSignatureTask(
                const FGetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FGetWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetWithSignatureTask>> GetWithSignature(
            Request::FGetStatusWithSignatureByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FAddExperienceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FAddExperienceTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FAddExperienceByUserIdRequestPtr Request;
        public:
            explicit FAddExperienceTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FAddExperienceByUserIdRequestPtr Request
            );

            FAddExperienceTask(
                const FAddExperienceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FAddExperienceTask;

        TSharedPtr<FAsyncTask<FAddExperienceTask>> AddExperience(
            Request::FAddExperienceByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FSetExperienceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FSetExperienceTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FSetExperienceByUserIdRequestPtr Request;
        public:
            explicit FSetExperienceTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FSetExperienceByUserIdRequestPtr Request
            );

            FSetExperienceTask(
                const FSetExperienceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FSetExperienceTask;

        TSharedPtr<FAsyncTask<FSetExperienceTask>> SetExperience(
            Request::FSetExperienceByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FAddRankCapTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FAddRankCapTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FAddRankCapByUserIdRequestPtr Request;
        public:
            explicit FAddRankCapTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FAddRankCapByUserIdRequestPtr Request
            );

            FAddRankCapTask(
                const FAddRankCapTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FAddRankCapTask;

        TSharedPtr<FAsyncTask<FAddRankCapTask>> AddRankCap(
            Request::FAddRankCapByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FSetRankCapTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FSetRankCapTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FSetRankCapByUserIdRequestPtr Request;
        public:
            explicit FSetRankCapTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FSetRankCapByUserIdRequestPtr Request
            );

            FSetRankCapTask(
                const FSetRankCapTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FSetRankCapTask;

        TSharedPtr<FAsyncTask<FSetRankCapTask>> SetRankCap(
            Request::FSetRankCapByUserIdRequestPtr Request
        );

        class GS2EXPERIENCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FStatusDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStatusDomain> Self;
            const Request::FDeleteStatusByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStatusDomain> Self,
                const Request::FDeleteStatusByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStatusByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> ExperienceName,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ExperienceName,
            TOptional<FString> PropertyId
        );

        class GS2EXPERIENCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FStatus>,
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
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FStatusDomain> FStatusDomainPtr;
}
