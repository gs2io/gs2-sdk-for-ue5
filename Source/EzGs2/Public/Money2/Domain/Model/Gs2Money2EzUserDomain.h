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
#include "Money2/Domain/Model/User.h"
#include "Money2/Model/Gs2Money2EzWallet.h"
#include "Money2/Model/Gs2Money2EzWalletSummary.h"
#include "Money2/Model/Gs2Money2EzDepositTransaction.h"
#include "Money2/Model/Gs2Money2EzSubscribeTransaction.h"
#include "Money2/Model/Gs2Money2EzSubscriptionStatus.h"
#include "Gs2Money2EzWalletDomain.h"
#include "Gs2Money2EzSubscriptionStatusDomain.h"
#include "Gs2Money2EzUserDomain.h"
#include "Gs2Money2EzUserDomain.h"
#include "Gs2Money2EzUserGameSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Money2::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> WithdrawTransactions() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Money2::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Money2::Domain::Model::FEzWalletDomainPtr Wallet(
            const int32 Slot
        ) const;

        Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusDomainPtr SubscriptionStatus(
            const FString ContentName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
