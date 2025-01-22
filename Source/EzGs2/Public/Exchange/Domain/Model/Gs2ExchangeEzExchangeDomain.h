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
#include "Exchange/Domain/Model/Exchange.h"
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
#include "Gs2ExchangeEzExchangeDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzExchangeDomain final :
        public TSharedFromThis<FEzExchangeDomain>
    {
        Gs2::Exchange::Domain::Model::FExchangeDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzExchangeDomain(
            Gs2::Exchange::Domain::Model::FExchangeDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

    };
    typedef TSharedPtr<FEzExchangeDomain> FEzExchangeDomainPtr;
}
