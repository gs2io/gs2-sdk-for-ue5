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
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Model/Gs2ExperienceEzExperienceModel.h"
#include "Experience/Model/Gs2ExperienceEzThreshold.h"
#include "Experience/Model/Gs2ExperienceEzStatus.h"
#include "Experience/Model/Gs2ExperienceEzAcquireAction.h"
#include "Experience/Model/Gs2ExperienceEzAcquireActionRate.h"
#include "Gs2ExperienceEzStatusGameSessionDomain.h"
#include "Experience/Domain/Iterator/Gs2ExperienceEzDescribeStatusesIterator.h"
#include "Gs2ExperienceEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Experience::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Experience::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Experience::Domain::Iterator::FEzDescribeStatusesIteratorPtr Statuses(
            const TOptional<FString> ExperienceName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStatuses(TFunction<void()> Callback);

        void UnsubscribeStatuses(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomainPtr Status(
            const FString ExperienceName,
            const FString PropertyId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
