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
    class FGetFormRequest;

    class GS2FORMATION_API FGetFormRequest final : public TSharedFromThis<FGetFormRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldNameValue;
        TOptional<int32> IndexValue;
        
    public:
        
        FGetFormRequest();
        FGetFormRequest(
            const FGetFormRequest& From
        );
        ~FGetFormRequest() = default;

        TSharedPtr<FGetFormRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFormRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFormRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetFormRequest> WithMoldName(const TOptional<FString> MoldName);
        TSharedPtr<FGetFormRequest> WithIndex(const TOptional<int32> Index);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;

        static TSharedPtr<FGetFormRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormRequest, ESPMode::ThreadSafe> FGetFormRequestPtr;
}