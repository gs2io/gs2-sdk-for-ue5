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

namespace Gs2::Formation::Request
{
    class FDeleteFormRequest;

    class GS2FORMATION_API FDeleteFormRequest final : public TSharedFromThis<FDeleteFormRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteFormRequest();
        FDeleteFormRequest(
            const FDeleteFormRequest& From
        );
        ~FDeleteFormRequest() = default;

        TSharedPtr<FDeleteFormRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteFormRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteFormRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteFormRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FDeleteFormRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FDeleteFormRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteFormRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteFormRequest> FDeleteFormRequestPtr;
}