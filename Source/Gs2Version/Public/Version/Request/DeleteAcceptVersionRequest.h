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

namespace Gs2::Version::Request
{
    class FDeleteAcceptVersionRequest;

    class GS2VERSION_API FDeleteAcceptVersionRequest final : public TSharedFromThis<FDeleteAcceptVersionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteAcceptVersionRequest();
        FDeleteAcceptVersionRequest(
            const FDeleteAcceptVersionRequest& From
        );
        ~FDeleteAcceptVersionRequest() = default;

        TSharedPtr<FDeleteAcceptVersionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteAcceptVersionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteAcceptVersionRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteAcceptVersionRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FDeleteAcceptVersionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteAcceptVersionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteAcceptVersionRequest, ESPMode::ThreadSafe> FDeleteAcceptVersionRequestPtr;
}