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
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Model/Gs2SerialKeyEzCampaignModel.h"
#include "SerialKey/Model/Gs2SerialKeyEzSerialKey.h"
#include "Gs2SerialKeyEzSerialKeyDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    class EZGS2_API FEzSerialKeyDomain final :
        public TSharedFromThis<FEzSerialKeyDomain>
    {
        Gs2::SerialKey::Domain::Model::FSerialKeyDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Url() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> Code() const;

        FEzSerialKeyDomain(
            Gs2::SerialKey::Domain::Model::FSerialKeyDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SerialKey::Model::FEzSerialKey>,
            public TSharedFromThis<FGetTask>
        {
            TSharedPtr<FEzSerialKeyDomain> Self;

        public:
            explicit FGetTask(
                TSharedPtr<FEzSerialKeyDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKey>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SerialKey::Model::FEzSerialKey>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSerialKeyDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSerialKeyDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKeyPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzSerialKeyDomain> FEzSerialKeyDomainPtr;
}
