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

namespace Gs2::Datastore::Request
{
    class FPrepareUploadByUserIdRequest;

    class GS2DATASTORE_API FPrepareUploadByUserIdRequest final : public TSharedFromThis<FPrepareUploadByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> ContentTypeValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<bool> UpdateIfExistsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareUploadByUserIdRequest();
        FPrepareUploadByUserIdRequest(
            const FPrepareUploadByUserIdRequest& From
        );
        ~FPrepareUploadByUserIdRequest() = default;

        TSharedPtr<FPrepareUploadByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithContentType(const TOptional<FString> ContentType);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithAllowUserIds(
            const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithUpdateIfExists(const TOptional<bool> UpdateIfExists);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPrepareUploadByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetContentType() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<bool> GetUpdateIfExists() const;
        FString GetUpdateIfExistsString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareUploadByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareUploadByUserIdRequest, ESPMode::ThreadSafe> FPrepareUploadByUserIdRequestPtr;
}