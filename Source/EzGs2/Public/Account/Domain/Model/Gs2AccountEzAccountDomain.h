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
#include "Account/Domain/Model/Account.h"
#include "Account/Model/Gs2AccountEzAccount.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"
#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountEzTakeOverDomain.h"
#include "Gs2AccountEzAccountDomain.h"
#include "Gs2AccountEzAccountDomain.h"
#include "Gs2AccountEzAccountGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Account::Domain::Model
{

    class EZGS2_API FEzAccountDomain final :
        public TSharedFromThis<FEzAccountDomain>
    {
        Gs2::Account::Domain::Model::FAccountDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Account::Model::FEzBanStatus>>> BanStatuses() const;
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzAccountDomain(
            Gs2::Account::Domain::Model::FAccountDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FAuthenticationTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>,
            public TSharedFromThis<FAuthenticationTask>
        {
            TSharedPtr<FEzAccountDomain> Self;
            FString Password;
            TOptional<FString> KeyId;

        public:
            explicit FAuthenticationTask(
                TSharedPtr<FEzAccountDomain> Self,
                FString Password,
                TOptional<FString> KeyId = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
            ) override;
        };
        friend FAuthenticationTask;

        TSharedPtr<FAsyncTask<FAuthenticationTask>> Authentication(
            FString Password,
            TOptional<FString> KeyId = TOptional<FString>()
        );

        Gs2::UE5::Account::Domain::Model::FEzTakeOverDomainPtr TakeOver(
            const int32 Type
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Model::FEzAccount>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAccountDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAccountDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Account::Model::FEzAccountPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzAccountPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAccountDomain> FEzAccountDomainPtr;
}
