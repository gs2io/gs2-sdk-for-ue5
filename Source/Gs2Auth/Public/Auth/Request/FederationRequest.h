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

namespace Gs2::Auth::Request
{
    class FFederationRequest;

    class GS2AUTH_API FFederationRequest final : public TSharedFromThis<FFederationRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> OriginalUserIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PolicyDocumentValue;
        TOptional<int32> TimeOffsetValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FFederationRequest();
        FFederationRequest(
            const FFederationRequest& From
        );
        ~FFederationRequest() = default;

        TSharedPtr<FFederationRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FFederationRequest> WithOriginalUserId(const TOptional<FString> OriginalUserId);
        TSharedPtr<FFederationRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FFederationRequest> WithPolicyDocument(const TOptional<FString> PolicyDocument);
        TSharedPtr<FFederationRequest> WithTimeOffset(const TOptional<int32> TimeOffset);
        TSharedPtr<FFederationRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetOriginalUserId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPolicyDocument() const;
        TOptional<int32> GetTimeOffset() const;
        FString GetTimeOffsetString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FFederationRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFederationRequest> FFederationRequestPtr;
}