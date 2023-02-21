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
#include "Gs2Credential.h"

namespace Gs2::Core::Model
{
    class GS2CORE_API FBasicGs2Credential final : public IGs2Credential, public TSharedFromThis<FBasicGs2Credential>
    {
        FGs2ClientId ClientIdValue;
        FGs2ClientSecret ClientSecretValue;
        FGs2ProjectToken ProjectTokenValue;

    public:
 
        FBasicGs2Credential(
            FString ClientId,
            FString ClientSecret
        );
 
        virtual const FGs2ClientId& ClientId() const override;
        virtual const FGs2ClientSecret& ClientSecret() const override;
        virtual const FGs2ProjectToken& ProjectToken() const override;
        virtual void UpdateProjectToken(const FGs2ProjectToken& Token) override;
    };
    typedef TSharedPtr<FBasicGs2Credential, ESPMode::ThreadSafe> FBasicGs2CredentialPtr;
}
