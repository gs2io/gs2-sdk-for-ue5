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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Model/Gs2AccountEzAccount.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"
#include "Account/Model/Gs2AccountEzPlatformId.h"
#include "Account/Model/Gs2AccountEzPlatformUser.h"
#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountEzTakeOverGameSessionDomain.h"
#include "Account/Domain/Iterator/Gs2AccountEzDescribeTakeOversIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Account::Domain::Model
{

    class EZGS2_API FEzTakeOverGameSessionDomain final :
        public TSharedFromThis<FEzTakeOverGameSessionDomain>
    {
        Gs2::Account::Domain::Model::FTakeOverAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> AuthorizationUrl() const;
        TOptional<FString> Payload() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<int32> Type() const;

        FEzTakeOverGameSessionDomain(
            Gs2::Account::Domain::Model::FTakeOverAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FAddTakeOverSettingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>,
            public TSharedFromThis<FAddTakeOverSettingTask>
        {
            TSharedPtr<FEzTakeOverGameSessionDomain> Self;
            FString UserIdentifier;
            FString Password;

        public:
            explicit FAddTakeOverSettingTask(
                TSharedPtr<FEzTakeOverGameSessionDomain> Self,
                FString UserIdentifier,
                FString Password
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
            ) override;
        };
        friend FAddTakeOverSettingTask;

        TSharedPtr<FAsyncTask<FAddTakeOverSettingTask>> AddTakeOverSetting(
            FString UserIdentifier,
            FString Password
        );

        class EZGS2_API FAddTakeOverSettingOpenIdConnectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>,
            public TSharedFromThis<FAddTakeOverSettingOpenIdConnectTask>
        {
            TSharedPtr<FEzTakeOverGameSessionDomain> Self;
            FString IdToken;

        public:
            explicit FAddTakeOverSettingOpenIdConnectTask(
                TSharedPtr<FEzTakeOverGameSessionDomain> Self,
                FString IdToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
            ) override;
        };
        friend FAddTakeOverSettingOpenIdConnectTask;

        TSharedPtr<FAsyncTask<FAddTakeOverSettingOpenIdConnectTask>> AddTakeOverSettingOpenIdConnect(
            FString IdToken
        );

        class EZGS2_API FUpdateTakeOverSettingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>,
            public TSharedFromThis<FUpdateTakeOverSettingTask>
        {
            TSharedPtr<FEzTakeOverGameSessionDomain> Self;
            FString OldPassword;
            FString Password;

        public:
            explicit FUpdateTakeOverSettingTask(
                TSharedPtr<FEzTakeOverGameSessionDomain> Self,
                FString OldPassword,
                FString Password
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateTakeOverSettingTask;

        TSharedPtr<FAsyncTask<FUpdateTakeOverSettingTask>> UpdateTakeOverSetting(
            FString OldPassword,
            FString Password
        );

        class EZGS2_API FDeleteTakeOverSettingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>,
            public TSharedFromThis<FDeleteTakeOverSettingTask>
        {
            TSharedPtr<FEzTakeOverGameSessionDomain> Self;

        public:
            explicit FDeleteTakeOverSettingTask(
                TSharedPtr<FEzTakeOverGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTakeOverSettingTask;

        TSharedPtr<FAsyncTask<FDeleteTakeOverSettingTask>> DeleteTakeOverSetting(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Model::FEzTakeOver>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzTakeOverGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzTakeOverGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOverPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzTakeOverPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzTakeOverGameSessionDomain> FEzTakeOverGameSessionDomainPtr;
}
