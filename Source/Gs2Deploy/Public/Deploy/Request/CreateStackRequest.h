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

namespace Gs2::Deploy::Request
{
    class FCreateStackRequest;

    class GS2DEPLOY_API FCreateStackRequest final : public TSharedFromThis<FCreateStackRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ModeValue;
        TOptional<FString> TemplateValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FCreateStackRequest();
        FCreateStackRequest(
            const FCreateStackRequest& From
        );
        ~FCreateStackRequest() = default;

        TSharedPtr<FCreateStackRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStackRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStackRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStackRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FCreateStackRequest> WithTemplate(const TOptional<FString> Template);
        TSharedPtr<FCreateStackRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetTemplate() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FCreateStackRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStackRequest> FCreateStackRequestPtr;
}