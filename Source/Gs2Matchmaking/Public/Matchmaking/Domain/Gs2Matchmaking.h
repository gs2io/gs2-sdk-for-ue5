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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Matchmaking/Gs2Matchmaking.h"

// Model
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentRatingModelMaster.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"

// Iterator
#include "Matchmaking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

// Notification
#include "Matchmaking/Model/JoinNotification.h"
#include "Matchmaking/Model/LeaveNotification.h"
#include "Matchmaking/Model/CompleteNotification.h"

namespace Gs2::Matchmaking::Domain
{
    DECLARE_EVENT_OneParam(FGs2MatchmakingDomain, FJoinNotificationEvent, Gs2::Matchmaking::Model::FJoinNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2MatchmakingDomain, FLeaveNotificationEvent, Gs2::Matchmaking::Model::FLeaveNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2MatchmakingDomain, FCompleteNotificationEvent, Gs2::Matchmaking::Model::FCompleteNotificationPtr);

    class GS2MATCHMAKING_API FGs2MatchmakingDomain:
        public TSharedFromThis<FGs2MatchmakingDomain>
    {
        FJoinNotificationEvent JoinNotificationEvent;
        FLeaveNotificationEvent LeaveNotificationEvent;
        FCompleteNotificationEvent CompleteNotificationEvent;
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2MatchmakingDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2MatchmakingDomain(
            const FGs2MatchmakingDomain& From
        );

        class GS2MATCHMAKING_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2MatchmakingDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2MatchmakingDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );
        FJoinNotificationEvent& OnJoinNotification();
        FLeaveNotificationEvent& OnLeaveNotification();
        FCompleteNotificationEvent& OnCompleteNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2MatchmakingDomain> FGs2MatchmakingDomainPtr;
}
