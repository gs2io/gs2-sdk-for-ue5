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
    class FUpdateDataObjectRequest;

    class GS2DATASTORE_API FUpdateDataObjectRequest final : public TSharedFromThis<FUpdateDataObjectRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateDataObjectRequest();
        FUpdateDataObjectRequest(
            const FUpdateDataObjectRequest& From
        );
        ~FUpdateDataObjectRequest() = default;

        TSharedPtr<FUpdateDataObjectRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateDataObjectRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateDataObjectRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FUpdateDataObjectRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateDataObjectRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FUpdateDataObjectRequest> WithAllowUserIds(
            const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FUpdateDataObjectRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateDataObjectRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequestPtr;
}