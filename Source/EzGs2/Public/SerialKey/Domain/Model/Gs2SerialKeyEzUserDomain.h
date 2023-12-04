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
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Model/Gs2SerialKeyEzCampaignModel.h"
#include "SerialKey/Model/Gs2SerialKeyEzSerialKey.h"
#include "Gs2SerialKeyEzSerialKeyDomain.h"
#include "Gs2SerialKeyEzUserDomain.h"
#include "Gs2SerialKeyEzUserDomain.h"
#include "Gs2SerialKeyEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::SerialKey::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Url() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::SerialKey::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SerialKey::Model::FEzSerialKey>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzUserDomain> Self;
            FString Code;

        public:
            explicit FModelTask(
                TSharedPtr<FEzUserDomain> Self,
                FString Code
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKey>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model(
            FString Code
        );

        Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyDomainPtr SerialKey(
            const FString SerialKeyCode
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
