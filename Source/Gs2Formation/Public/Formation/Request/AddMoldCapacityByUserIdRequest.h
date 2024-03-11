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
    class FAddMoldCapacityByUserIdRequest;

    class GS2FORMATION_API FAddMoldCapacityByUserIdRequest final : public TSharedFromThis<FAddMoldCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> CapacityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddMoldCapacityByUserIdRequest();
        FAddMoldCapacityByUserIdRequest(
            const FAddMoldCapacityByUserIdRequest& From
        );
        ~FAddMoldCapacityByUserIdRequest() = default;

        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddMoldCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddMoldCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddMoldCapacityByUserIdRequest, ESPMode::ThreadSafe> FAddMoldCapacityByUserIdRequestPtr;
}