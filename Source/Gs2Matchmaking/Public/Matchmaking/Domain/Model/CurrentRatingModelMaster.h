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
#include "Matchmaking/Gs2Matchmaking.h"
#include "Matchmaking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

namespace Gs2::Matchmaking::Domain::Model
{
    class FNamespaceDomain;
    class FGatheringDomain;
    class FGatheringAccessTokenDomain;
    class FRatingModelMasterDomain;
    class FRatingModelDomain;
    class FCurrentRatingModelMasterDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2MATCHMAKING_API FCurrentRatingModelMasterDomain:
        public TSharedFromThis<FCurrentRatingModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentRatingModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentRatingModelMasterDomain(
            const FCurrentRatingModelMasterDomain& From
        );

        class GS2MATCHMAKING_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentRatingModelMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentRatingModelMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FCurrentRatingModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentRatingModelMasterDomain> Self;
            const Request::FGetCurrentRatingModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentRatingModelMasterDomain> Self,
                const Request::FGetCurrentRatingModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FCurrentRatingModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentRatingModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentRatingModelMasterDomain> Self;
            const Request::FUpdateCurrentRatingModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentRatingModelMasterDomain> Self,
                const Request::FUpdateCurrentRatingModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentRatingModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentRatingModelMasterDomain> Self;
            const Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentRatingModelMasterDomain> Self,
                const Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentRatingModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FCurrentRatingModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentRatingModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentRatingModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FCurrentRatingModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentRatingModelMasterDomain> FCurrentRatingModelMasterDomainPtr;
}
