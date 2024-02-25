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

    class GS2SEASONRATING_API FMatchSessionDomain:
        public TSharedFromThis<FMatchSessionDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr Service;
        const Gs2::SeasonRating::FGs2SeasonRatingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> SessionName;
    private:

        FString ParentKey;

    public:

        FMatchSessionDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> SessionName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMatchSessionDomain(
            const FMatchSessionDomain& From
        );

        class GS2SEASONRATING_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FMatchSessionDomain> Self;
            const Request::FCreateMatchSessionRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FMatchSessionDomain>& Self,
                const Request::FCreateMatchSessionRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreateMatchSessionRequestPtr Request
        );

        class GS2SEASONRATING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FMatchSession>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMatchSessionDomain> Self;
            const Request::FGetMatchSessionRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMatchSessionDomain>& Self,
                const Request::FGetMatchSessionRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FMatchSession>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMatchSessionRequestPtr Request
        );

        class GS2SEASONRATING_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMatchSessionDomain> Self;
            const Request::FDeleteMatchSessionRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMatchSessionDomain>& Self,
                const Request::FDeleteMatchSessionRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMatchSessionRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> SessionName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SessionName
        );

        class GS2SEASONRATING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::SeasonRating::Model::FMatchSession>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMatchSessionDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMatchSessionDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FMatchSession>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::SeasonRating::Model::FMatchSessionPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMatchSessionDomain> FMatchSessionDomainPtr;
}
