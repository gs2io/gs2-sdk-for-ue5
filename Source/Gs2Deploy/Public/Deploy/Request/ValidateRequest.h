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
    class FValidateRequest;

    class GS2DEPLOY_API FValidateRequest final : public TSharedFromThis<FValidateRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ModeValue;
        TOptional<FString> TemplateValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FValidateRequest();
        FValidateRequest(
            const FValidateRequest& From
        );
        ~FValidateRequest() = default;

        TSharedPtr<FValidateRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FValidateRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FValidateRequest> WithTemplate(const TOptional<FString> Template);
        TSharedPtr<FValidateRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetTemplate() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FValidateRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FValidateRequest> FValidateRequestPtr;
}