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
    class FChangeSetRequest;

    class GS2DEPLOY_API FChangeSetRequest final : public TSharedFromThis<FChangeSetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        TOptional<FString> ModeValue;
        TOptional<FString> TemplateValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FChangeSetRequest();
        FChangeSetRequest(
            const FChangeSetRequest& From
        );
        ~FChangeSetRequest() = default;

        TSharedPtr<FChangeSetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FChangeSetRequest> WithStackName(const TOptional<FString> StackName);
        TSharedPtr<FChangeSetRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FChangeSetRequest> WithTemplate(const TOptional<FString> Template);
        TSharedPtr<FChangeSetRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetTemplate() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FChangeSetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FChangeSetRequest> FChangeSetRequestPtr;
}