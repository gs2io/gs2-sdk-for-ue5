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
#include "SeasonRating/Domain/Iterator/DescribeNamespacesIterator.h"
#include "SeasonRating/Domain/Iterator/DescribeMatchSessionsIterator.h"
#include "SeasonRating/Domain/Iterator/DescribeSeasonModelMastersIterator.h"
#include "SeasonRating/Domain/Iterator/DescribeSeasonModelsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::SeasonRating::Domain
{
    class FGs2SeasonRatingDomain;
    typedef TSharedPtr<FGs2SeasonRatingDomain> FGs2SeasonRatingDomainPtr;
}

namespace Gs2::SeasonRating::Domain::Model
{
    class FNamespaceDomain;
    class FMatchSessionDomain;
    class FSeasonModelMasterDomain;
    class FSeasonModelDomain;
    class FCurrentSeasonModelMasterDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2SEASONRATING_API FCurrentSeasonModelMasterDomain:
        public TSharedFromThis<FCurrentSeasonModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr Service;
        const Gs2::SeasonRating::FGs2SeasonRatingRestClientPtr Client;

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

        FCurrentSeasonModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentSeasonModelMasterDomain(
            const FCurrentSeasonModelMasterDomain& From
        );

        class GS2SEASONRATING_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2SEASONRATING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
            const Request::FGetCurrentSeasonModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
                const Request::FGetCurrentSeasonModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentSeasonModelMasterRequestPtr Request
        );

        class GS2SEASONRATING_API FPreUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>,
            public TSharedFromThis<FPreUpdateTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
            const Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request;
        public:
            explicit FPreUpdateTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
                const Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
            );

            FPreUpdateTask(
                const FPreUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
            ) override;
        };
        friend FPreUpdateTask;

        TSharedPtr<FAsyncTask<FPreUpdateTask>> PreUpdate(
            Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
        );

        class GS2SEASONRATING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
            const Request::FUpdateCurrentSeasonModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
                const Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
        );

        class GS2SEASONRATING_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
            const Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
                const Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SEASONRATING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentSeasonModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentSeasonModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SeasonRating::Model::FCurrentSeasonModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentSeasonModelMasterDomain> FCurrentSeasonModelMasterDomainPtr;
}
