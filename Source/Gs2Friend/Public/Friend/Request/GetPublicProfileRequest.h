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

namespace Gs2::Friend::Request
{
    class FGetPublicProfileRequest;

    class GS2FRIEND_API FGetPublicProfileRequest final : public TSharedFromThis<FGetPublicProfileRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetPublicProfileRequest();
        FGetPublicProfileRequest(
            const FGetPublicProfileRequest& From
        );
        ~FGetPublicProfileRequest() = default;

        TSharedPtr<FGetPublicProfileRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPublicProfileRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPublicProfileRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetPublicProfileRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetPublicProfileRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPublicProfileRequest, ESPMode::ThreadSafe> FGetPublicProfileRequestPtr;
}