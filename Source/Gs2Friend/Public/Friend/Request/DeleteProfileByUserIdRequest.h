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
    class FDeleteProfileByUserIdRequest;

    class GS2FRIEND_API FDeleteProfileByUserIdRequest final : public TSharedFromThis<FDeleteProfileByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteProfileByUserIdRequest();
        FDeleteProfileByUserIdRequest(
            const FDeleteProfileByUserIdRequest& From
        );
        ~FDeleteProfileByUserIdRequest() = default;

        TSharedPtr<FDeleteProfileByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteProfileByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteProfileByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteProfileByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteProfileByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteProfileByUserIdRequest, ESPMode::ThreadSafe> FDeleteProfileByUserIdRequestPtr;
}