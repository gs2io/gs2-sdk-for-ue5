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
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"
#include "Showcase/Model/Gs2ShowcaseEzShowcase.h"
#include "Showcase/Model/Gs2ShowcaseEzDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzConfig.h"
#include "Showcase/Model/Gs2ShowcaseEzConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseEzAcquireAction.h"
#include "Gs2ShowcaseEzShowcaseGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    class EZGS2_API FEzShowcaseGameSessionDomain final :
        public TSharedFromThis<FEzShowcaseGameSessionDomain>
    {
        Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ShowcaseName() const;

        FEzShowcaseGameSessionDomain(
            Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetShowcaseTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Model::FEzShowcase>,
            public TSharedFromThis<FGetShowcaseTask>
        {
            TSharedPtr<FEzShowcaseGameSessionDomain> Self;

        public:
            explicit FGetShowcaseTask(
                TSharedPtr<FEzShowcaseGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcase>> Result
            ) override;
        };
        friend FGetShowcaseTask;

        TSharedPtr<FAsyncTask<FGetShowcaseTask>> GetShowcase(
        );

        class FBuyTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomain>,
            public TSharedFromThis<FBuyTask>
        {
            TSharedPtr<FEzShowcaseGameSessionDomain> Self;
            TOptional<FString> DisplayItemId;
            TOptional<int32> Quantity;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config;

        public:
            explicit FBuyTask(
                TSharedPtr<FEzShowcaseGameSessionDomain> Self,
                TOptional<FString> DisplayItemId = TOptional<FString>(),
                TOptional<int32> Quantity = TOptional<int32>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomain>> Result
            ) override;
        };
        friend FBuyTask;

        TSharedPtr<FAsyncTask<FBuyTask>> Buy(
            TOptional<FString> DisplayItemId = TOptional<FString>(),
            TOptional<int32> Quantity = TOptional<int32>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConfig>>>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Model::FEzShowcase>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzShowcaseGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzShowcaseGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcasePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzShowcaseGameSessionDomain> FEzShowcaseGameSessionDomainPtr;
}
