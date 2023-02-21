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
#include "IAuthenticator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API FGs2AccountAuthenticator final : public IAuthenticator
    {
        const FString AccountNamespaceName;
        const FString KeyId;

    public:
        FGs2AccountAuthenticator(
            const FString AccountNamespaceName,
            const FString KeyId
        );
        virtual ~FGs2AccountAuthenticator() override = default;
        
        virtual Gs2::Core::Model::FGs2ErrorPtr Authentication(
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
            const FString UserId,
            const FString Password,
            const TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
        ) override;
    };
    typedef TSharedPtr<FGs2AccountAuthenticator> FGs2AccountAuthenticatorPtr;
}
