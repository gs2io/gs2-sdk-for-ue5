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
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzVerifyActionResult.h"
#include "Enchant/Model/Gs2EnchantEzConsumeActionResult.h"
#include "Enchant/Model/Gs2EnchantEzAcquireActionResult.h"
#include "Enchant/Model/Gs2EnchantEzTransactionResult.h"
#include "Gs2EnchantEzBalanceParameterStatusGameSessionDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeBalanceParameterStatusesIterator.h"
#include "Gs2EnchantEzRarityParameterStatusGameSessionDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeRarityParameterStatusesIterator.h"
#include "Gs2EnchantEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Enchant::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Enchant::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterStatusesIteratorPtr BalanceParameterStatuses(
            const TOptional<FString> ParameterName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBalanceParameterStatuses(TFunction<void()> Callback);

        void UnsubscribeBalanceParameterStatuses(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomainPtr BalanceParameterStatus(
            const FString ParameterName,
            const FString PropertyId
        ) const;

        Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterStatusesIteratorPtr RarityParameterStatuses(
            const TOptional<FString> ParameterName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRarityParameterStatuses(TFunction<void()> Callback);

        void UnsubscribeRarityParameterStatuses(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomainPtr RarityParameterStatus(
            const FString ParameterName,
            const FString PropertyId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
