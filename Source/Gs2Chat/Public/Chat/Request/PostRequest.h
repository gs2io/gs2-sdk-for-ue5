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

namespace Gs2::Chat::Request
{
    class FPostRequest;

    class GS2CHAT_API FPostRequest final : public TSharedFromThis<FPostRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPostRequest();
        FPostRequest(
            const FPostRequest& From
        );
        ~FPostRequest() = default;

        TSharedPtr<FPostRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPostRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPostRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FPostRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPostRequest> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FPostRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPostRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FPostRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPostRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPostRequest> FPostRequestPtr;
}