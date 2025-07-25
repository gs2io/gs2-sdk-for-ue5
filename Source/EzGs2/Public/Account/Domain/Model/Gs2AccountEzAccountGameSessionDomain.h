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
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Model/Gs2AccountEzAccount.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"
#include "Account/Model/Gs2AccountEzPlatformId.h"
#include "Account/Model/Gs2AccountEzPlatformUser.h"
#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountEzTakeOverGameSessionDomain.h"
#include "Account/Domain/Iterator/Gs2AccountEzDescribeTakeOversIterator.h"
#include "Gs2AccountEzPlatformIdGameSessionDomain.h"
#include "Account/Domain/Iterator/Gs2AccountEzDescribePlatformIdsIterator.h"
#include "Gs2AccountEzAccountGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Account::Domain::Model
{

    class EZGS2_API FEzAccountGameSessionDomain final :
        public TSharedFromThis<FEzAccountGameSessionDomain>
    {
        Gs2::Account::Domain::Model::FAccountAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Account::Model::FEzBanStatus>>> BanStatuses() const;
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> AuthorizationUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzAccountGameSessionDomain(
            Gs2::Account::Domain::Model::FAccountAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FDeleteTakeOverSettingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>,
            public TSharedFromThis<FDeleteTakeOverSettingTask>
        {
            TSharedPtr<FEzAccountGameSessionDomain> Self;
            int32 Type;

        public:
            explicit FDeleteTakeOverSettingTask(
                TSharedPtr<FEzAccountGameSessionDomain> Self,
                int32 Type
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTakeOverSettingTask;

        TSharedPtr<FAsyncTask<FDeleteTakeOverSettingTask>> DeleteTakeOverSetting(
            int32 Type
        );

        class EZGS2_API FGetAuthorizationUrlTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomain>,
            public TSharedFromThis<FGetAuthorizationUrlTask>
        {
            TSharedPtr<FEzAccountGameSessionDomain> Self;
            int32 Type;

        public:
            explicit FGetAuthorizationUrlTask(
                TSharedPtr<FEzAccountGameSessionDomain> Self,
                int32 Type
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomain>> Result
            ) override;
        };
        friend FGetAuthorizationUrlTask;

        TSharedPtr<FAsyncTask<FGetAuthorizationUrlTask>> GetAuthorizationUrl(
            int32 Type
        );

        Gs2::UE5::Account::Domain::Iterator::FEzDescribeTakeOversIteratorPtr TakeOvers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTakeOvers(TFunction<void()> Callback);

        void UnsubscribeTakeOvers(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomainPtr TakeOver(
            const int32 Type
        ) const;

        Gs2::UE5::Account::Domain::Iterator::FEzDescribePlatformIdsIteratorPtr PlatformIds(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePlatformIds(TFunction<void()> Callback);

        void UnsubscribePlatformIds(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Account::Domain::Model::FEzPlatformIdGameSessionDomainPtr PlatformId(
            const int32 Type,
            const FString UserIdentifier
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Model::FEzAccount>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAccountGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAccountGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Account::Model::FEzAccountPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzAccountPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAccountGameSessionDomain> FEzAccountGameSessionDomainPtr;
}
