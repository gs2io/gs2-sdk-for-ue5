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
#include "../Model/Version.h"

namespace Gs2::Version::Request
{
    class FAcceptRequest;

    class GS2VERSION_API FAcceptRequest final : public TSharedFromThis<FAcceptRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<Model::FVersion> VersionValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcceptRequest();
        FAcceptRequest(
            const FAcceptRequest& From
        );
        ~FAcceptRequest() = default;

        TSharedPtr<FAcceptRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcceptRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcceptRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FAcceptRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAcceptRequest> WithVersion(const TSharedPtr<Model::FVersion> Version);
        TSharedPtr<FAcceptRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<Model::FVersion> GetVersion() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcceptRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcceptRequest, ESPMode::ThreadSafe> FAcceptRequestPtr;
}