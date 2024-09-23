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
#include "../Model/TargetVersion.h"

namespace Gs2::Version::Request
{
    class FCheckVersionByUserIdRequest;

    class GS2VERSION_API FCheckVersionByUserIdRequest final : public TSharedFromThis<FCheckVersionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersionsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCheckVersionByUserIdRequest();
        FCheckVersionByUserIdRequest(
            const FCheckVersionByUserIdRequest& From
        );
        ~FCheckVersionByUserIdRequest() = default;

        TSharedPtr<FCheckVersionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCheckVersionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCheckVersionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCheckVersionByUserIdRequest> WithTargetVersions(const TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersions);
        TSharedPtr<FCheckVersionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCheckVersionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> GetTargetVersions() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCheckVersionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckVersionByUserIdRequest, ESPMode::ThreadSafe> FCheckVersionByUserIdRequestPtr;
}