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
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"
#include "Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverIntervalTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverValueTable.h"
#include "Stamina/Model/Gs2StaminaEzStamina.h"
#include "Gs2StaminaEzStaminaDomain.h"
#include "Gs2StaminaEzUserDomain.h"
#include "Gs2StaminaEzUserDomain.h"
#include "Gs2StaminaEzUserGameSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Stamina::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<int32> OverflowValue() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Stamina::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Stamina::Domain::Model::FEzStaminaDomainPtr Stamina(
            const FString StaminaName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
