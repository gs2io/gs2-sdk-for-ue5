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
    class FGetDataObjectHistoryRequest;

    class GS2DATASTORE_API FGetDataObjectHistoryRequest final : public TSharedFromThis<FGetDataObjectHistoryRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> GenerationValue;
        
    public:
        
        FGetDataObjectHistoryRequest();
        FGetDataObjectHistoryRequest(
            const FGetDataObjectHistoryRequest& From
        );
        ~FGetDataObjectHistoryRequest() = default;

        TSharedPtr<FGetDataObjectHistoryRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetDataObjectHistoryRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetDataObjectHistoryRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetDataObjectHistoryRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FGetDataObjectHistoryRequest> WithGeneration(const TOptional<FString> Generation);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetGeneration() const;

        static TSharedPtr<FGetDataObjectHistoryRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetDataObjectHistoryRequest> FGetDataObjectHistoryRequestPtr;
}