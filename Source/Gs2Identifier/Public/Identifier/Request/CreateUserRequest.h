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
    class FCreateUserRequest;

    class GS2IDENTIFIER_API FCreateUserRequest final : public TSharedFromThis<FCreateUserRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        
    public:
        
        FCreateUserRequest();
        FCreateUserRequest(
            const FCreateUserRequest& From
        );
        ~FCreateUserRequest() = default;

        TSharedPtr<FCreateUserRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateUserRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateUserRequest> WithDescription(const TOptional<FString> Description);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;

        static TSharedPtr<FCreateUserRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateUserRequest> FCreateUserRequestPtr;
}