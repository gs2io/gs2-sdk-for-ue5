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
#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Exchange/Model/Gs2ExchangeEzVerifyAction.h"
#include "Exchange/Model/Gs2ExchangeEzVerifyActionResult.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeActionResult.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireActionResult.h"
#include "Exchange/Model/Gs2ExchangeEzTransactionResult.h"
#include "Gs2ExchangeEzExchangeGameSessionDomain.h"
#include "Gs2ExchangeEzAwaitGameSessionDomain.h"
#include "Exchange/Domain/Iterator/Gs2ExchangeEzDescribeAwaitsIterator.h"
#include "Gs2ExchangeEzUserGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Exchange::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Exchange::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomainPtr Exchange(
        ) const;

        Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeAwaitsIteratorPtr Awaits(
            const TOptional<FString> RateName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAwaits(TFunction<void()> Callback);

        void UnsubscribeAwaits(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomainPtr Await(
            const FString AwaitName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
