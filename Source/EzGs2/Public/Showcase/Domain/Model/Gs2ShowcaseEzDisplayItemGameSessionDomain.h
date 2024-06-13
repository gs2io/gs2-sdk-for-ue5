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
#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"
#include "Showcase/Model/Gs2ShowcaseEzShowcase.h"
#include "Showcase/Model/Gs2ShowcaseEzDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzRandomDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzConfig.h"
#include "Showcase/Model/Gs2ShowcaseEzConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseEzAcquireAction.h"
#include "Gs2ShowcaseEzDisplayItemGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    class EZGS2_API FEzDisplayItemGameSessionDomain final :
        public TSharedFromThis<FEzDisplayItemGameSessionDomain>
    {
        Gs2::Showcase::Domain::Model::FDisplayItemAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ShowcaseName() const;
        TOptional<FString> DisplayItemId() const;

        FEzDisplayItemGameSessionDomain(
            Gs2::Showcase::Domain::Model::FDisplayItemAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FBuyTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemGameSessionDomain>,
            public TSharedFromThis<FBuyTask>
        {
            TSharedPtr<FEzDisplayItemGameSessionDomain> Self;
            TOptional<int32> Quantity;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config;

        public:
            explicit FBuyTask(
                TSharedPtr<FEzDisplayItemGameSessionDomain> Self,
                TOptional<int32> Quantity = TOptional<int32>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemGameSessionDomain>> Result
            ) override;
        };
        friend FBuyTask;

        TSharedPtr<FAsyncTask<FBuyTask>> Buy(
            TOptional<int32> Quantity = TOptional<int32>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>>()
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Model::FEzDisplayItem>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzDisplayItemGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzDisplayItemGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItemPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzDisplayItemPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzDisplayItemGameSessionDomain> FEzDisplayItemGameSessionDomainPtr;
}
