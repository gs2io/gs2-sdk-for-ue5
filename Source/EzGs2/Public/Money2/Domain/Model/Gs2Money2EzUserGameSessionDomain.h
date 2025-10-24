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
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Model/Gs2Money2EzWallet.h"
#include "Money2/Model/Gs2Money2EzWalletSummary.h"
#include "Money2/Model/Gs2Money2EzDepositTransaction.h"
#include "Money2/Model/Gs2Money2EzSubscribeTransaction.h"
#include "Money2/Model/Gs2Money2EzSubscriptionStatus.h"
#include "Money2/Model/Gs2Money2EzStoreContentModel.h"
#include "Money2/Model/Gs2Money2EzAppleAppStoreContent.h"
#include "Money2/Model/Gs2Money2EzGooglePlayContent.h"
#include "Money2/Model/Gs2Money2EzAppleAppStoreSubscriptionContent.h"
#include "Money2/Model/Gs2Money2EzGooglePlaySubscriptionContent.h"
#include "Gs2Money2EzWalletGameSessionDomain.h"
#include "Money2/Domain/Iterator/Gs2Money2EzDescribeWalletsIterator.h"
#include "Gs2Money2EzSubscriptionStatusGameSessionDomain.h"
#include "Money2/Domain/Iterator/Gs2Money2EzDescribeSubscriptionStatusesIterator.h"
#include "Gs2Money2EzUserGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Money2::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> WithdrawTransactions() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Money2::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FAllocateSubscriptionStatusTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>,
            public TSharedFromThis<FAllocateSubscriptionStatusTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString Receipt;

        public:
            explicit FAllocateSubscriptionStatusTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString Receipt
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>> Result
            ) override;
        };
        friend FAllocateSubscriptionStatusTask;

        TSharedPtr<FAsyncTask<FAllocateSubscriptionStatusTask>> AllocateSubscriptionStatus(
            FString Receipt
        );

        class EZGS2_API FTakeOverSubscriptionStatusTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>,
            public TSharedFromThis<FTakeOverSubscriptionStatusTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString Receipt;

        public:
            explicit FTakeOverSubscriptionStatusTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString Receipt
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>> Result
            ) override;
        };
        friend FTakeOverSubscriptionStatusTask;

        TSharedPtr<FAsyncTask<FTakeOverSubscriptionStatusTask>> TakeOverSubscriptionStatus(
            FString Receipt
        );

        Gs2::UE5::Money2::Domain::Iterator::FEzDescribeWalletsIteratorPtr Wallets(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeWallets(TFunction<void()> Callback);

        void UnsubscribeWallets(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Money2::Domain::Iterator::FEzDescribeSubscriptionStatusesIteratorPtr SubscriptionStatuses(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscriptionStatuses(TFunction<void()> Callback);

        void UnsubscribeSubscriptionStatuses(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomainPtr Wallet(
            const int32 Slot
        ) const;

        Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomainPtr SubscriptionStatus(
            const FString ContentName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
