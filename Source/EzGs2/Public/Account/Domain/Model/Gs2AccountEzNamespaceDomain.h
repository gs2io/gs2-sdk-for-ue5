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
#include "Account/Domain/Model/Namespace.h"
#include "Account/Model/Gs2AccountEzAccount.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"
#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountEzAccountDomain.h"
#include "Gs2AccountEzAccountDomain.h"
#include "Gs2AccountEzAccountGameSessionDomain.h"
#include "Gs2AccountEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Account::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Account::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Account::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FCreateTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>,
            public TSharedFromThis<FCreateTask>
        {
            TSharedPtr<FEzNamespaceDomain> Self;

        public:
            explicit FCreateTask(
                TSharedPtr<FEzNamespaceDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
        );

        class FDoTakeOverTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>,
            public TSharedFromThis<FDoTakeOverTask>
        {
            TSharedPtr<FEzNamespaceDomain> Self;
            int32 Type;
            FString UserIdentifier;
            FString Password;

        public:
            explicit FDoTakeOverTask(
                TSharedPtr<FEzNamespaceDomain> Self,
                int32 Type,
                FString UserIdentifier,
                FString Password
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
            ) override;
        };
        friend FDoTakeOverTask;

        TSharedPtr<FAsyncTask<FDoTakeOverTask>> DoTakeOver(
            int32 Type,
            FString UserIdentifier,
            FString Password
        );

        Gs2::UE5::Account::Domain::Model::FEzAccountDomainPtr Account(
            const FString UserId
        ) const;

        Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
