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
#include "Money/Domain/Model/WalletAccessToken.h"
#include "Money/Model/Gs2MoneyEzWallet.h"
#include "Gs2MoneyEzWalletGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Money::Domain::Model
{

    class EZGS2_API FEzWalletGameSessionDomain final :
        public TSharedFromThis<FEzWalletGameSessionDomain>
    {
        Gs2::Money::Domain::Model::FWalletAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<float> Price() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<int32> Slot() const;

        FEzWalletGameSessionDomain(
            Gs2::Money::Domain::Model::FWalletAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FWithdrawTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Money::Domain::Model::FEzWalletGameSessionDomain>,
            public TSharedFromThis<FWithdrawTask>
        {
            TSharedPtr<FEzWalletGameSessionDomain> Self;
            int32 Count;
            TOptional<bool> PaidOnly;

        public:
            explicit FWithdrawTask(
                TSharedPtr<FEzWalletGameSessionDomain> Self,
                int32 Count,
                TOptional<bool> PaidOnly = TOptional<bool>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Money::Domain::Model::FEzWalletGameSessionDomain>> Result
            ) override;
        };
        friend FWithdrawTask;

        TSharedPtr<FAsyncTask<FWithdrawTask>> Withdraw(
            int32 Count,
            TOptional<bool> PaidOnly = TOptional<bool>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Money::Model::FEzWallet>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzWalletGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzWalletGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Money::Model::FEzWalletPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Money::Model::FEzWalletPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzWalletGameSessionDomain> FEzWalletGameSessionDomainPtr;
}
