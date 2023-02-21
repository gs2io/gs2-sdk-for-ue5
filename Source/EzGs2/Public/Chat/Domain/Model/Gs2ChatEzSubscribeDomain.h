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
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Model/Gs2ChatEzRoom.h"
#include "Chat/Model/Gs2ChatEzMessage.h"
#include "Chat/Model/Gs2ChatEzSubscribe.h"
#include "Chat/Model/Gs2ChatEzNotificationType.h"
#include "Gs2ChatEzSubscribeDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    class EZGS2_API FEzSubscribeDomain final :
        public TSharedFromThis<FEzSubscribeDomain>
    {
        Gs2::Chat::Domain::Model::FSubscribeDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RoomName() const;

        FEzSubscribeDomain(
            Gs2::Chat::Domain::Model::FSubscribeDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Model::FEzSubscribe>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSubscribeDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSubscribeDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Chat::Model::FEzSubscribePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzSubscribeDomain> FEzSubscribeDomainPtr;
}
