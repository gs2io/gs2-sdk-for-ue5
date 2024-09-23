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
    class FGetAcceptVersionByUserIdRequest;

    class GS2VERSION_API FGetAcceptVersionByUserIdRequest final : public TSharedFromThis<FGetAcceptVersionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetAcceptVersionByUserIdRequest();
        FGetAcceptVersionByUserIdRequest(
            const FGetAcceptVersionByUserIdRequest& From
        );
        ~FGetAcceptVersionByUserIdRequest() = default;

        TSharedPtr<FGetAcceptVersionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetAcceptVersionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetAcceptVersionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetAcceptVersionByUserIdRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FGetAcceptVersionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetAcceptVersionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetAcceptVersionByUserIdRequest, ESPMode::ThreadSafe> FGetAcceptVersionByUserIdRequestPtr;
}