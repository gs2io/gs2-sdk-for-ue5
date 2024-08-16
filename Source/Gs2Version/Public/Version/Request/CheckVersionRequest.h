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
#include "../Model/TargetVersion.h"

namespace Gs2::Version::Request
{
    class FCheckVersionRequest;

    class GS2VERSION_API FCheckVersionRequest final : public TSharedFromThis<FCheckVersionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersionsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCheckVersionRequest();
        FCheckVersionRequest(
            const FCheckVersionRequest& From
        );
        ~FCheckVersionRequest() = default;

        TSharedPtr<FCheckVersionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCheckVersionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCheckVersionRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FCheckVersionRequest> WithTargetVersions(const TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersions);
        TSharedPtr<FCheckVersionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> GetTargetVersions() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCheckVersionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckVersionRequest> FCheckVersionRequestPtr;
}