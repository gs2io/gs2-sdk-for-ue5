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
    class FDeletePasswordRequest;

    class GS2IDENTIFIER_API FDeletePasswordRequest final : public TSharedFromThis<FDeletePasswordRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        
    public:
        
        FDeletePasswordRequest();
        FDeletePasswordRequest(
            const FDeletePasswordRequest& From
        );
        ~FDeletePasswordRequest() = default;

        TSharedPtr<FDeletePasswordRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeletePasswordRequest> WithUserName(const TOptional<FString> UserName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;

        static TSharedPtr<FDeletePasswordRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeletePasswordRequest, ESPMode::ThreadSafe> FDeletePasswordRequestPtr;
}