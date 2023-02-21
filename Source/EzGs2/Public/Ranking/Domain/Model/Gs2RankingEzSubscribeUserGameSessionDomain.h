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

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzSubscribeUserGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeSubscribesByCategoryNameIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzSubscribeUserGameSessionDomain final :
        public TSharedFromThis<FEzSubscribeUserGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;
        TOptional<FString> TargetUserId() const;

        FEzSubscribeUserGameSessionDomain(
            Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FUnsubscribeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>,
            public TSharedFromThis<FUnsubscribeTask>
        {
            TSharedPtr<FEzSubscribeUserGameSessionDomain> Self;

        public:
            explicit FUnsubscribeTask(
                TSharedPtr<FEzSubscribeUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
            ) override;
        };
        friend FUnsubscribeTask;

        TSharedPtr<FAsyncTask<FUnsubscribeTask>> Unsubscribe(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzSubscribeUser>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSubscribeUserGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSubscribeUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzSubscribeUserGameSessionDomain> FEzSubscribeUserGameSessionDomainPtr;
}
