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
#include "Dom/JsonObject.h"

namespace Gs2::Identifier::Request
{
    class FLoginByUserRequest;

    class GS2IDENTIFIER_API FLoginByUserRequest final : public TSharedFromThis<FLoginByUserRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> OtpValue;
        
    public:
        
        FLoginByUserRequest();
        FLoginByUserRequest(
            const FLoginByUserRequest& From
        );
        ~FLoginByUserRequest() = default;

        TSharedPtr<FLoginByUserRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLoginByUserRequest> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FLoginByUserRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FLoginByUserRequest> WithOtp(const TOptional<FString> Otp);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetOtp() const;

        static TSharedPtr<FLoginByUserRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLoginByUserRequest> FLoginByUserRequestPtr;
}