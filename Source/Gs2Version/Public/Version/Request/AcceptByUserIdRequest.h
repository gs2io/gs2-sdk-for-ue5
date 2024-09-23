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
    class FAcceptByUserIdRequest;

    class GS2VERSION_API FAcceptByUserIdRequest final : public TSharedFromThis<FAcceptByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FVersion> VersionValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcceptByUserIdRequest();
        FAcceptByUserIdRequest(
            const FAcceptByUserIdRequest& From
        );
        ~FAcceptByUserIdRequest() = default;

        TSharedPtr<FAcceptByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcceptByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcceptByUserIdRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FAcceptByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcceptByUserIdRequest> WithVersion(const TSharedPtr<Model::FVersion> Version);
        TSharedPtr<FAcceptByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAcceptByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FVersion> GetVersion() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcceptByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcceptByUserIdRequest, ESPMode::ThreadSafe> FAcceptByUserIdRequestPtr;
}