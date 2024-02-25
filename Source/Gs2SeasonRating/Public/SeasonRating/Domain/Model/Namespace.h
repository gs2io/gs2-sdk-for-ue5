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

    class GS2SEASONRATING_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr Service;
        const Gs2::SeasonRating::FGs2SeasonRatingRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
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
            const Core::Domain::FGs2Ptr& Gs2,
            const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2SEASONRATING_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2SEASONRATING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2SEASONRATING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2SEASONRATING_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2SEASONRATING_API FCreateSeasonModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FSeasonModelMasterDomain>,
            public TSharedFromThis<FCreateSeasonModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSeasonModelMasterRequestPtr Request;
        public:
            explicit FCreateSeasonModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateSeasonModelMasterRequestPtr Request
            );

            FCreateSeasonModelMasterTask(
                const FCreateSeasonModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FSeasonModelMasterDomain>> Result
            ) override;
        };
        friend FCreateSeasonModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateSeasonModelMasterTask>> CreateSeasonModelMaster(
            Request::FCreateSeasonModelMasterRequestPtr Request
        );

        class GS2SEASONRATING_API FVoteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FBallotDomain>,
            public TSharedFromThis<FVoteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FVoteRequestPtr Request;
        public:
            explicit FVoteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FVoteRequestPtr Request
            );

            FVoteTask(
                const FVoteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FBallotDomain>> Result
            ) override;
        };
        friend FVoteTask;

        TSharedPtr<FAsyncTask<FVoteTask>> Vote(
            Request::FVoteRequestPtr Request
        );

        class GS2SEASONRATING_API FVoteMultipleTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FBallotDomain>,
            public TSharedFromThis<FVoteMultipleTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FVoteMultipleRequestPtr Request;
        public:
            explicit FVoteMultipleTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FVoteMultipleRequestPtr Request
            );

            FVoteMultipleTask(
                const FVoteMultipleTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FBallotDomain>> Result
            ) override;
        };
        friend FVoteMultipleTask;

        TSharedPtr<FAsyncTask<FVoteMultipleTask>> VoteMultiple(
            Request::FVoteMultipleRequestPtr Request
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain> CurrentSeasonModelMaster(
        );

        Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelsIteratorPtr SeasonModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSeasonModels(
            TFunction<void()> Callback
        );

        void UnsubscribeSeasonModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FSeasonModelDomain> SeasonModel(
            const FString SeasonName
        );

        Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelMastersIteratorPtr SeasonModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSeasonModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeSeasonModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FSeasonModelMasterDomain> SeasonModelMaster(
            const FString SeasonName
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::SeasonRating::Domain::Iterator::FDescribeMatchSessionsIteratorPtr MatchSessions(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMatchSessions(
            TFunction<void()> Callback
        );

        void UnsubscribeMatchSessions(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain> MatchSession(
            const FString SessionName
        );

        TSharedPtr<Gs2::SeasonRating::Domain::Model::FVoteDomain> Vote(
            const FString SeasonName,
            const FString SessionName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2SEASONRATING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SeasonRating::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
