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

namespace Gs2::Datastore::Request
{
    class FPrepareUploadRequest;

    class GS2DATASTORE_API FPrepareUploadRequest final : public TSharedFromThis<FPrepareUploadRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> NameValue;
        TOptional<FString> ContentTypeValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<bool> UpdateIfExistsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareUploadRequest();
        FPrepareUploadRequest(
            const FPrepareUploadRequest& From
        );
        ~FPrepareUploadRequest() = default;

        TSharedPtr<FPrepareUploadRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareUploadRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareUploadRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPrepareUploadRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FPrepareUploadRequest> WithContentType(const TOptional<FString> ContentType);
        TSharedPtr<FPrepareUploadRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FPrepareUploadRequest> WithAllowUserIds(
            const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FPrepareUploadRequest> WithUpdateIfExists(const TOptional<bool> UpdateIfExists);
        TSharedPtr<FPrepareUploadRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetContentType() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<bool> GetUpdateIfExists() const;
        FString GetUpdateIfExistsString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareUploadRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequestPtr;
}