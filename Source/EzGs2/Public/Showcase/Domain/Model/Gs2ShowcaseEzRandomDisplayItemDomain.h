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
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"
#include "Showcase/Model/Gs2ShowcaseEzShowcase.h"
#include "Showcase/Model/Gs2ShowcaseEzDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzRandomDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzConfig.h"
#include "Showcase/Model/Gs2ShowcaseEzConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseEzVerifyAction.h"
#include "Showcase/Model/Gs2ShowcaseEzAcquireAction.h"
#include "Showcase/Model/Gs2ShowcaseEzVerifyActionResult.h"
#include "Showcase/Model/Gs2ShowcaseEzConsumeActionResult.h"
#include "Showcase/Model/Gs2ShowcaseEzAcquireActionResult.h"
#include "Showcase/Model/Gs2ShowcaseEzTransactionResult.h"
#include "Gs2ShowcaseEzRandomDisplayItemDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    class EZGS2_API FEzRandomDisplayItemDomain final :
        public TSharedFromThis<FEzRandomDisplayItemDomain>
    {
        Gs2::Showcase::Domain::Model::FRandomDisplayItemDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ShowcaseName() const;
        TOptional<FString> DisplayItemName() const;

        FEzRandomDisplayItemDomain(
            Gs2::Showcase::Domain::Model::FRandomDisplayItemDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Model::FEzRandomDisplayItem>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRandomDisplayItemDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRandomDisplayItemDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzRandomDisplayItemDomain> FEzRandomDisplayItemDomainPtr;
}
