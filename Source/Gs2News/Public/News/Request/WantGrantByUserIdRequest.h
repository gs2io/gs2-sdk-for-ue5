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

namespace Gs2::News::Request
{
    class FWantGrantByUserIdRequest;

    class GS2NEWS_API FWantGrantByUserIdRequest final : public TSharedFromThis<FWantGrantByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FWantGrantByUserIdRequest();
        FWantGrantByUserIdRequest(
            const FWantGrantByUserIdRequest& From
        );
        ~FWantGrantByUserIdRequest() = default;

        TSharedPtr<FWantGrantByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FWantGrantByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FWantGrantByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FWantGrantByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FWantGrantByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWantGrantByUserIdRequest> FWantGrantByUserIdRequestPtr;
}