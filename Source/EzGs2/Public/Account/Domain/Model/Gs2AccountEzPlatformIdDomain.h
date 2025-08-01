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
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Model/Gs2AccountEzAccount.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"
#include "Account/Model/Gs2AccountEzPlatformId.h"
#include "Account/Model/Gs2AccountEzPlatformUser.h"
#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountEzPlatformIdDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Account::Domain::Model
{

    class EZGS2_API FEzPlatformIdDomain final :
        public TSharedFromThis<FEzPlatformIdDomain>
    {
        Gs2::Account::Domain::Model::FPlatformIdDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<int32> Type() const;
        TOptional<FString> UserIdentifier() const;

        FEzPlatformIdDomain(
            Gs2::Account::Domain::Model::FPlatformIdDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Model::FEzPlatformId>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPlatformIdDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPlatformIdDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Account::Model::FEzPlatformIdPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzPlatformIdPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzPlatformIdDomain> FEzPlatformIdDomainPtr;
}
