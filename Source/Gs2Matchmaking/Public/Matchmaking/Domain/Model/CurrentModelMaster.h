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
#include "Matchmaking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeMatchmakingSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Matchmaking::Domain
{
    class FGs2MatchmakingDomain;
    typedef TSharedPtr<FGs2MatchmakingDomain> FGs2MatchmakingDomainPtr;
}

namespace Gs2::Matchmaking::Domain::Model
{
    class FNamespaceDomain;
    class FGatheringDomain;
    class FGatheringAccessTokenDomain;
    class FRatingModelMasterDomain;
    class FRatingModelDomain;
    class FCurrentModelMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSeasonDomain;
    class FSeasonAccessTokenDomain;
    class FSeasonModelDomain;
    class FSeasonModelMasterDomain;
    class FSeasonGatheringDomain;
    class FSeasonGatheringAccessTokenDomain;
    class FJoinedSeasonGatheringDomain;
    class FJoinedSeasonGatheringAccessTokenDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;

    class GS2MATCHMAKING_API FCurrentModelMasterDomain:
        public TSharedFromThis<FCurrentModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr Service;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentModelMasterDomain(
            const FCurrentModelMasterDomain& From
        );

        class GS2MATCHMAKING_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FCurrentModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FGetCurrentModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FGetCurrentModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FCurrentModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FUpdateCurrentModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FUpdateCurrentModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentModelMasterDomain>& Self,
                const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FCurrentModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FCurrentModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Matchmaking::Model::FCurrentModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentModelMasterDomain> FCurrentModelMasterDomainPtr;
}
