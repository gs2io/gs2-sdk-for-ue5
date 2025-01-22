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
#include "../Model/Version.h"

namespace Gs2::Version::Request
{
    class FRejectRequest;

    class GS2VERSION_API FRejectRequest final : public TSharedFromThis<FRejectRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<Model::FVersion> VersionValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRejectRequest();
        FRejectRequest(
            const FRejectRequest& From
        );
        ~FRejectRequest() = default;

        TSharedPtr<FRejectRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRejectRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRejectRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FRejectRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FRejectRequest> WithVersion(const TSharedPtr<Model::FVersion> Version);
        TSharedPtr<FRejectRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<Model::FVersion> GetVersion() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRejectRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRejectRequest> FRejectRequestPtr;
}