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
    class FCreatePasswordRequest;

    class GS2IDENTIFIER_API FCreatePasswordRequest final : public TSharedFromThis<FCreatePasswordRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> PasswordValue;
        
    public:
        
        FCreatePasswordRequest();
        FCreatePasswordRequest(
            const FCreatePasswordRequest& From
        );
        ~FCreatePasswordRequest() = default;

        TSharedPtr<FCreatePasswordRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreatePasswordRequest> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FCreatePasswordRequest> WithPassword(const TOptional<FString> Password);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetPassword() const;

        static TSharedPtr<FCreatePasswordRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreatePasswordRequest, ESPMode::ThreadSafe> FCreatePasswordRequestPtr;
}