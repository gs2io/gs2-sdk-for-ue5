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

namespace Gs2::Formation::Request
{
    class FGetMoldRequest;

    class GS2FORMATION_API FGetMoldRequest final : public TSharedFromThis<FGetMoldRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldModelNameValue;
        
    public:
        
        FGetMoldRequest();
        FGetMoldRequest(
            const FGetMoldRequest& From
        );
        ~FGetMoldRequest() = default;

        TSharedPtr<FGetMoldRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMoldRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMoldRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetMoldRequest> WithMoldModelName(const TOptional<FString> MoldModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldModelName() const;

        static TSharedPtr<FGetMoldRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMoldRequest, ESPMode::ThreadSafe> FGetMoldRequestPtr;
}