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
#include "Auth/Domain/Model/AccessToken.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Gs2AuthEzAccessTokenDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Auth::Domain::Model
{

    class EZGS2_API FEzAccessTokenDomain final :
        public TSharedFromThis<FEzAccessTokenDomain>
    {
        Gs2::Auth::Domain::Model::FAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Token() const;
        TOptional<FString> UserId() const;
        TOptional<int64> Expire() const;
        TOptional<FString> Status() const;

        FEzAccessTokenDomain(
            Gs2::Auth::Domain::Model::FAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FLoginTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomain>,
            public TSharedFromThis<FLoginTask>
        {
            TSharedPtr<FEzAccessTokenDomain> Self;
            FString Body;
            FString Signature;
            TOptional<FString> KeyId;

        public:
            explicit FLoginTask(
                TSharedPtr<FEzAccessTokenDomain> Self,
                FString Body,
                FString Signature,
                TOptional<FString> KeyId = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomain>> Result
            ) override;
        };
        friend FLoginTask;

        TSharedPtr<FAsyncTask<FLoginTask>> Login(
            FString Body,
            FString Signature,
            TOptional<FString> KeyId = TOptional<FString>()
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Auth::Model::FEzAccessToken>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAccessTokenDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAccessTokenDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Auth::Model::FEzAccessTokenPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAccessTokenDomain> FEzAccessTokenDomainPtr;
}
