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
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
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
#include "Gs2Money2EzSubscriptionStatusGameSessionDomain.h"
#include "Money2/Domain/Iterator/Gs2Money2EzDescribeSubscriptionStatusesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    class EZGS2_API FEzSubscriptionStatusGameSessionDomain final :
        public TSharedFromThis<FEzSubscriptionStatusGameSessionDomain>
    {
        Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ContentName() const;

        FEzSubscriptionStatusGameSessionDomain(
            Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Money2::Model::FEzSubscriptionStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSubscriptionStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSubscriptionStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzSubscriptionStatusGameSessionDomain> FEzSubscriptionStatusGameSessionDomainPtr;
}
