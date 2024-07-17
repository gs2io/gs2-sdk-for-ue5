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

namespace Gs2::Identifier::Request
{
    class FChallengeMfaRequest;

    class GS2IDENTIFIER_API FChallengeMfaRequest final : public TSharedFromThis<FChallengeMfaRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> PasscodeValue;
        
    public:
        
        FChallengeMfaRequest();
        FChallengeMfaRequest(
            const FChallengeMfaRequest& From
        );
        ~FChallengeMfaRequest() = default;

        TSharedPtr<FChallengeMfaRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FChallengeMfaRequest> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FChallengeMfaRequest> WithPasscode(const TOptional<FString> Passcode);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetPasscode() const;

        static TSharedPtr<FChallengeMfaRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FChallengeMfaRequest, ESPMode::ThreadSafe> FChallengeMfaRequestPtr;
}