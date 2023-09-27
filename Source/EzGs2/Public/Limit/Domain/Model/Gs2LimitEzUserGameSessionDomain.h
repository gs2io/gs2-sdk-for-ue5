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
#include "Limit/Domain/Model/UserAccessToken.h"
#include "Limit/Model/Gs2LimitEzCounter.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"
#include "Gs2LimitEzCounterGameSessionDomain.h"
#include "Limit/Domain/Iterator/Gs2LimitEzDescribeCountersIterator.h"
#include "Gs2LimitEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Limit::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Limit::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Limit::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Limit::Domain::Iterator::FEzDescribeCountersIteratorPtr Counters(
            const TOptional<FString> LimitName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCounters(TFunction<void()> Callback);

        void UnsubscribeCounters(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomainPtr Counter(
            const FString LimitName,
            const FString CounterName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
