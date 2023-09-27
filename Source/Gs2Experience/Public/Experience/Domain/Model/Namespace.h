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

    class GS2EXPERIENCE_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Experience::FGs2ExperienceRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2EXPERIENCE_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2EXPERIENCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2EXPERIENCE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2EXPERIENCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2EXPERIENCE_API FCreateThresholdMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FThresholdMasterDomain>,
            public TSharedFromThis<FCreateThresholdMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateThresholdMasterRequestPtr Request;
        public:
            explicit FCreateThresholdMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateThresholdMasterRequestPtr Request
            );

            FCreateThresholdMasterTask(
                const FCreateThresholdMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain>> Result
            ) override;
        };
        friend FCreateThresholdMasterTask;

        TSharedPtr<FAsyncTask<FCreateThresholdMasterTask>> CreateThresholdMaster(
            Request::FCreateThresholdMasterRequestPtr Request
        );

        class GS2EXPERIENCE_API FCreateExperienceModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Domain::Model::FExperienceModelMasterDomain>,
            public TSharedFromThis<FCreateExperienceModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateExperienceModelMasterRequestPtr Request;
        public:
            explicit FCreateExperienceModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateExperienceModelMasterRequestPtr Request
            );

            FCreateExperienceModelMasterTask(
                const FCreateExperienceModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FExperienceModelMasterDomain>> Result
            ) override;
        };
        friend FCreateExperienceModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateExperienceModelMasterTask>> CreateExperienceModelMaster(
            Request::FCreateExperienceModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Experience::Domain::Model::FCurrentExperienceMasterDomain> CurrentExperienceMaster(
        ) const;

        Gs2::Experience::Domain::Iterator::FDescribeExperienceModelsIteratorPtr ExperienceModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeExperienceModels(
            TFunction<void()> Callback
        );

        void UnsubscribeExperienceModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Experience::Domain::Model::FExperienceModelDomain> ExperienceModel(
            const FString ExperienceName
        ) const;

        TSharedPtr<Gs2::Experience::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Experience::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        Gs2::Experience::Domain::Iterator::FDescribeThresholdMastersIteratorPtr ThresholdMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeThresholdMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeThresholdMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain> ThresholdMaster(
            const FString ThresholdName
        ) const;

        Gs2::Experience::Domain::Iterator::FDescribeExperienceModelMastersIteratorPtr ExperienceModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeExperienceModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeExperienceModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Experience::Domain::Model::FExperienceModelMasterDomain> ExperienceModelMaster(
            const FString ExperienceName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2EXPERIENCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Experience::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Experience::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Experience::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
